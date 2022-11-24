//
// Created by mvonkeil on 01.11.22.
//

#ifndef FDE_ENGINE_H
#define FDE_ENGINE_H

#include <eni/ManagedObject.h>

#include <fde/Node.h>
#include <fde/schemapush.h>

#include <atomic>
#include <future>
#include <iostream>
#include <memory>
#include <set>

namespace fde {

template<typename T>
    requires std::is_base_of_v<EngineObject<T>, T>
class EngineReference;

template<typename T>
struct EngineHandle : std::shared_ptr<EngineReference<T>> {
    using std::shared_ptr<EngineReference<T>>::shared_ptr;

    inline T &operator*() {
        return *this->get().operator*();
    }

    inline T *operator->() {
        return this->get().operator->();
    }
};

class Engine : public eni::ManagedObject<Engine> {
public:
    virtual ~Engine() = default;

public:
    std::packaged_task<EngineHandle<Node>()> registerNode();

    std::packaged_task<SchemaPushResult()> pushSchema(const EngineHandle<Node> &node, SchemaPushRequest request);

protected:
    [[nodiscard]] std::unique_ptr<Node> createNode();

protected:
    void onInit() override;
    void onRelease() override;

private:
    friend class EngineReference<Node>;
    void _notifyUnused(Node &node);

private:
    std::binary_semaphore _semaphore{1};
    std::set<std::unique_ptr<Node>> _nodes{};
};

}// namespace fde

#endif//FDE_ENGINE_H
