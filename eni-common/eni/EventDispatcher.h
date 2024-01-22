//
// Created by void on 10/3/23.
//

#ifndef ENI_EVENTDISPATCHER_H
#define ENI_EVENTDISPATCHER_H

#include <eni/build_config.h>

#include <atomic>
#include <functional>
#include <map>
#include <memory>
#include <optional>

namespace eni {

template<typename CallbackT, typename EventT>
concept event_callback = requires {
    std::is_convertible_v<CallbackT, std::function<void(const EventT &event)>>;
};

namespace detail {
template<typename Ret, typename Arg, typename... Rest>
Arg _event_type_from_callback(Ret (*f)(Arg, Rest...)) { return {}; }

template<typename Ret, typename F, typename Arg, typename... Rest>
Arg _event_type_from_callback(Ret (F::*f)(Arg, Rest...)) { return {}; }

template<typename Ret, typename F, typename Arg, typename... Rest>
Arg _event_type_from_callback(Ret (F::*f)(Arg, Rest...) const) { return {}; }

template<typename F>
decltype(_event_type_from_callback(&F::operator())) _event_type_from_callback(F f) { return {}; }

template<typename T>
using event_type_from_callback = std::decay_t<decltype(_event_type_from_callback(std::declval<T>()))>;

template<typename CallbackT, typename EventT>
using is_valid_event_callback = std::is_same<EventT, event_type_from_callback<CallbackT>>;

template<typename EventT>
class EventDispatcher;

class EventDispatcherBase {
public:
    virtual ~EventDispatcherBase() = default;

protected:
    using id_type = uint32;

public:
    class ListenerHandle {
        friend class EventDispatcherBase;

    public:
        ListenerHandle() = default;

        virtual ~ListenerHandle() {
            if (_dispatcher) {
                _dispatcher->get().removeEventListener(_id);
            }
        }

    private:
        ListenerHandle(EventDispatcherBase &dispatcher, const id_type id) : _id(id), _dispatcher(dispatcher) {
        }

        id_type _id{};
        std::optional<std::reference_wrapper<EventDispatcherBase>> _dispatcher;
    };

protected:
    std::unique_ptr<ListenerHandle> createListenerHandle(const id_type id) {
        return std::unique_ptr<ListenerHandle>(new ListenerHandle(*this, id));
    };

    virtual void removeEventListener(id_type id) = 0;
};

template<typename EventT>
class EventDispatcher : EventDispatcherBase {
    using id_type = uint32;
    using callback_type = std::function<void(const EventT &event)>;

protected:
    template<typename T, typename = EventT>
        requires std::is_same_v<std::decay_t<T>, EventT>
    void fireEvent(T event) {
        std::unique_ptr<std::lock_guard<std::mutex>> lk;

        if (!_firing) {
            lk = std::make_unique<std::lock_guard<std::mutex>>(_mutex);
            _firing = true;
        }

        for (const auto &[key, listener] : _listeners) {
            (*listener)(event);
        }
    }

public:
    template<typename CallbackT>
        requires is_valid_event_callback<CallbackT, EventT>::value
    std::unique_ptr<ListenerHandle>
    addEventListener(CallbackT listener) {
        std::unique_ptr<callback_type> callback = std::make_unique<callback_type>(std::move(listener));

        auto lk = std::lock_guard(_mutex);
        _listeners.emplace(std::make_pair(_nextId, std::move(callback)));

        return createListenerHandle(_nextId++);
    }

private:
    void removeEventListener(id_type id) override {
        auto lk = std::lock_guard(_mutex);
        _listeners.erase(id);
    }

private:
    std::mutex _mutex;
    std::atomic_bool _firing = false;
    std::map<id_type, std::unique_ptr<callback_type>> _listeners;
    id_type _nextId{};
};
}// namespace detail

template<typename... EventTypes>
class EventDispatcher : detail::EventDispatcher<EventTypes>... {
protected:
    using detail::EventDispatcher<EventTypes>::fireEvent...;

public:
    using detail::EventDispatcher<EventTypes>::addEventListener...;

private:
    class MultiListenerHandle final : public detail::EventDispatcherBase::ListenerHandle {
    public:
        explicit MultiListenerHandle(
                std::array<std::unique_ptr<detail::EventDispatcherBase::ListenerHandle>, sizeof...(EventTypes)>
                        wrappedHandles) : _handles(std::move(wrappedHandles)) {
        }

    private:
        std::array<std::unique_ptr<detail::EventDispatcherBase::ListenerHandle>, sizeof...(EventTypes)> _handles{};
    };

    template<typename CallbackT, typename EventT>
    void _wrapAndAddEventListener(
            CallbackT listener,
            std::array<std::unique_ptr<detail::EventDispatcherBase::ListenerHandle>, sizeof...(EventTypes)> &result,
            size_t index) {
        auto wrapper = [listener](const EventT &e) {
            listener(e);
        };

        result[index] = detail::EventDispatcher<EventT>::addEventListener(wrapper);
    }

public:
    // Generic implementation of addEventListener that allows the use of the auto keyword in a lambda expression.
    template<typename CallbackT>
    std::unique_ptr<detail::EventDispatcherBase::ListenerHandle> addEventListener(CallbackT listener) {
        size_t i = 0;
        std::array<std::unique_ptr<detail::EventDispatcherBase::ListenerHandle>, sizeof...(EventTypes)> wrapped;
        (_wrapAndAddEventListener<CallbackT, EventTypes>(listener, wrapped, i++), ...);

        return std::make_unique<MultiListenerHandle>(std::move(wrapped));
    }
};
}// namespace eni

#endif//ENI_EVENTDISPATCHER_H
