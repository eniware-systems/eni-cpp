//
// Created by mvonkeil on 21.11.22.
//

#ifndef ENI_MANAGED_OBJECT_H
#define ENI_MANAGED_OBJECT_H

#include <memory>

namespace eni {

template<typename T>
class ManagedObject {
protected:
    ~ManagedObject() = default;

private:
    struct Deleter {
        void operator()(T *ptr) {
            auto managedObjectReleasedBeforeDestruction = ptr->_released;
            assert(managedObjectReleasedBeforeDestruction);
            std::default_delete<T>().operator()(ptr);
        }
    };

public:
    using unique_ptr = std::unique_ptr<T, Deleter>;

public:
    template<typename... Args>
    static unique_ptr create(Args &&...args) {
        auto ptr = new T(std::forward<Args>(args)...);// NOLINT(cppcoreguidelines-owning-memory)
        static_cast<ManagedObject<T> *>(ptr)->onInit();
        return unique_ptr(ptr);
    }

public:
    void release() {
        if (_released) {
            throw std::logic_error("Object has already been released");
        }
        _released = true;
        onRelease();
    }

protected:
    virtual void onInit() {}
    virtual void onRelease() {}

private:
    bool _released = false;
};

}// namespace eni

#endif//ENI_MANAGED_OBJECT_H
