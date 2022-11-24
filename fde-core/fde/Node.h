//
// Created by mvonkeil on 04.11.22.
//

#ifndef FDE_ENGINE_NODE_H
#define FDE_ENGINE_NODE_H

#include <fde/schemapush.h>
#include <fde/EngineObject.h>

#include <future>

namespace fde {

class Engine;

class Node : public EngineObject<Node> {
public:
    using EngineObject::EngineObject;
};

}// namespace fde

#endif//FDE_ENGINE_NODE_H
