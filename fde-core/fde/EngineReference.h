//
// Created by mvonkeil on 22.11.22.
//

#ifndef FDE_ENGINEREFERENCE_H
#define FDE_ENGINEREFERENCE_H

#include <fde/Engine.h>
#include <fde/EngineObject.h>

#include <memory>

namespace fde {

template<typename T>
    requires std::is_base_of_v<EngineObject<T>, T>
class EngineReference {
public:
    explicit EngineReference(T &object) : _object(object) {}

    ~EngineReference() {
        _object.getEngine()._notifyUnused(_object);
    }

    inline T &operator*() {
        return _object.operator&();
    }

    inline T *operator->() const {
        return _object.operator*();
    }

private:
    T &_object;
};

}// namespace fde

#endif//FDE_ENGINEREFERENCE_H
