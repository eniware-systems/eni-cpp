//
// Created by mvonkeil on 01.11.22.
//

#include <exception>

#include <eni/util.h>

#include <fde/Engine.h>
#include <fde/EngineReference.h>

namespace fde {

std::unique_ptr<Node> Engine::createNode() {
    return std::make_unique<Node>(*this);
}

void Engine::onInit() {
}

void Engine::onRelease() {
    if (!_nodes.empty()) {
        throw std::logic_error("Cannot destroy engine, has active nodes");
    }
}

std::packaged_task<EngineHandle<Node>()> Engine::registerNode() {
    auto task = std::packaged_task([this] {
        auto node = createNode();
        auto ref = EngineHandle<Node>(new EngineReference<Node>(*node));

        _semaphore.acquire();
        _nodes.emplace(std::move(node));
        _semaphore.release();

        return EngineHandle(ref);
    });

    task();
    return task;
}

std::packaged_task<SchemaPushResult()> Engine::pushSchema(const EngineHandle<Node> &node, SchemaPushRequest request) {
    auto task = std::packaged_task([this] {
        return SchemaPushResult{};
    });

    task();
    return task;
}

void Engine::_notifyUnused(Node &node) {
    _semaphore.acquire();
    auto x = eni::erase_pointer(_nodes, node);
    _semaphore.release();
}

}// namespace fde