//
// Created by mvonkeil on 22.11.22.
//

#ifndef FDE_ENGINEOBJECT_H
#define FDE_ENGINEOBJECT_H

namespace fde {

class Engine;

template<typename T>
class EngineObject {
public:
    explicit EngineObject(Engine &engine) : _engine(engine) {}

    [[nodiscard]] inline Engine &getEngine() {
        return _engine;
    }

private:
    Engine &_engine;
};

}// namespace fde

#endif//FDE_ENGINEOBJECT_H
