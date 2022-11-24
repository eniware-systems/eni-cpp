//
// Created by mvonkeil on 01.11.22.
//

#include <catch2/catch_all.hpp>

#include <fde/Engine.h>

using namespace fde;

TEST_CASE("Can register node", "[Engine]") {
    auto engine = Engine::create();
    auto node = engine->registerNode().get_future().get();
    node.reset();

    REQUIRE_NOTHROW(engine->release());
}

TEST_CASE("Throws when destroying engine with active nodes", "[Engine]") {
    auto engine = Engine::create();
    auto node = engine->registerNode().get_future().get();

    REQUIRE_THROWS(engine->release());
}

TEST_CASE("Won't throw when destroying engine after nodes have been released", "[Engine]") {
    auto engine = Engine::create();
    auto node = engine->registerNode().get_future().get();

    node.reset();
    REQUIRE_NOTHROW(engine->release());
}

TEST_CASE("Can request schema push", "[Engine][Node]") {
    auto engine = Engine::create();
    auto node = engine->registerNode().get_future().get();

    SchemaPushRequest request{};
    auto result = engine->pushSchema(node, request).get_future().get();

    node.reset();
    engine->release();
}