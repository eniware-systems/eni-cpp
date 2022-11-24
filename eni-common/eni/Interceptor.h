//
// Created by void on 21/08/2021.
//

#ifndef ENI_INTERCEPTOR_H
#define ENI_INTERCEPTOR_H

#include <eni/debug.h>
#include <eni/types.h>

#include <algorithm>
#include <future>
#include <list>
#include <memory>

namespace eni {

/**
 * A registry for intercepting a single point-in-code. All registered Interceptors will be invoked in order of priority when the registries invoke() method has been called.
 *
 * @tparam Args The invocation arguments.
 */
template<typename InterceptorT>
class InterceptorRegistry {
public:
    using interceptor_type = InterceptorT;

    InterceptorRegistry &operator=(const InterceptorRegistry &other) = delete;

public:
    /**
     * Registers a new interceptor to this registry.
     *
     * @param interceptor The interceptor to register.
     */
    void registerInterceptor(std::shared_ptr<interceptor_type> interceptor, s32 priority = 0) {
        auto it = _interceptors.begin();
        for (; it != _interceptors.end(); ++it) {
            if (it->first < priority) {
                break;
            }
        }

        _interceptors.insert(it, std::make_pair(priority, std::move(interceptor)));
    }

    /**
     * Registers an anonymous callback method to this registry.
     *
     * @tparam FunT The callback method type, must match the signature of the Interceptors invoke() method.
     * @param fun The callback to invoke.
     */
    template<typename FunT>
    void registerCallback(FunT fun) {
        registerCallback(0, std::move(fun));
    }

    /**
     * Unregisters an interceptor.
     * @param interceptor The interceptor to remove.
     */
    void unregisterInterceptor(const std::shared_ptr<interceptor_type> &interceptor) {
        auto it = std::find_if(_interceptors.begin(), _interceptors.end(), [&interceptor](const auto &i) { return i.second == interceptor; });
        _interceptors.erase(it);
    }

public:
    /**
     * Invokes the registered Interceptors in order of priority.
     * @param args The invocation arguments passed to the interceptors.
     */
    template<typename... ArgsT, typename... FunArgsT>
    void invoke(void (interceptor_type::*FunT)(FunArgsT...), ArgsT &&...args) const {
        for (const auto &i : _interceptors) {
            if constexpr (sizeof...(ArgsT) > 0) {
                ((*i.second).*FunT)(std::forward<ArgsT>(args)...);
            } else {
                ((*i.second).*FunT)();
            }
        }
    }

    /**
     * Invokes the registered Interceptors in order of priority.
     * @param args The invocation arguments passed to the interceptors.
     */
    template<typename... ArgsT, typename... FunArgsT>
    void invoke(void (interceptor_type::*FunT)(FunArgsT...) const, ArgsT &&...args) {
        for (const auto &i : _interceptors) {
            if constexpr (sizeof...(ArgsT) > 0) {
                ((*i.second).*FunT)(std::forward<ArgsT>(args)...);
            } else {
                ((*i.second).*FunT)();
            }
        }
    }

    /**
     * Asynchronously invokes the registered Interceptors in order of priority.
     * @param FunT The method to invoke
     * @param args The invocation arguments passed to the interceptors.
     */
    template<typename... ArgsT, typename... FunArgsT>
    std::future<void> invoke(std::future<void> (interceptor_type::*FunT)(FunArgsT...), ArgsT &&...args) {
        return invoke(std::launch::async, FunT, std::forward<ArgsT>(args)...);
    }

    /**
     * Asynchronously invokes the registered Interceptors in order of priority.
     * @param FunT The method to invoke
     * @param args The invocation arguments passed to the interceptors.
     */
    template<typename... ArgsT, typename... FunArgsT>
    std::future<void> invoke(std::future<void> (interceptor_type::*FunT)(FunArgsT...) const, ArgsT &&...args) {
        return invoke(std::launch::async, FunT, std::forward<ArgsT>(args)...);
    }

    /**
     * Asynchronously invokes the registered Interceptors in order of priority.
     * @param launch_type The async launch type
     * @param FunT The method to invoke
     * @param args The invocation arguments passed to the interceptors.
     */
    template<typename... ArgsT, typename... FunArgsT>
    std::future<void> invoke(std::launch launch_type, std::future<void> (interceptor_type::*FunT)(FunArgsT...), ArgsT &&...args) {
        return std::async(launch_type, [this, FunT, args...] () mutable {
            for (const auto &i : _interceptors) {
                if constexpr (sizeof...(ArgsT) > 0) {
                    // We can't perfect forward the arguments here because they might illegally transfer their ownership.
                    // The function invoked needs to use either referenced or copy-by-value parameters.
                    ((*i.second).*FunT)(args...);
                } else {
                    ((*i.second).*FunT)();
                }
            }
        });
    }

    /**
     * Asynchronously invokes the registered Interceptors in order of priority.
     * @param launch_type The async launch type
     * @param FunT The method to invoke
     * @param args The invocation arguments passed to the interceptors.
     */
    template<typename... ArgsT, typename... FunArgsT>
    std::future<void> invoke(std::launch launch_type, std::future<void> (interceptor_type::*FunT)(FunArgsT...) const, ArgsT &&...args) {
        return std::async(launch_type, [this, FunT, args...] () mutable {
            for (const auto &i : _interceptors) {
                std::future<void> result;

                if constexpr (sizeof...(ArgsT) > 0) {
                    result = ((*i.second).*FunT)(std::forward<ArgsT>(args)...);
                } else {
                    result = ((*i.second).*FunT)();
                }

                result.get();
            }
        });
    }

    public:
    /**
     * @return An iterator view of registered interceptors.
     */
    [[nodiscard]] inline auto getInterceptors() const {
        return std::make_pair(_interceptors.begin(), _interceptors.end());
    }

private:
    std::list<std::pair<s32, std::shared_ptr<interceptor_type>>> _interceptors;
};

}// namespace eni

#endif//ENI_INTERCEPTOR_H
