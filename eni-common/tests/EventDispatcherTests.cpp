//
// Created by void on 1/12/24.
//

#include "catch2/catch_all.hpp"

#include <eni/EventDispatcher.h>

template<typename... EventTypes>
class TestEventDispatcher final : public eni::EventDispatcher<EventTypes...> {
public:
    using eni::EventDispatcher<EventTypes...>::fireEvent;
};

TEST_CASE("can dispatch any given type", "[EventDispatcher]") {
    class MyEvent {
    };

    TestEventDispatcher<MyEvent> dispatcher;

    int received = 0;

    auto handle = dispatcher.addEventListener([&](const MyEvent &evt) {
        received++;
    });

    dispatcher.fireEvent(MyEvent());

    REQUIRE(received == 1);
}

TEST_CASE("can dispatch multiple types and listen only for specific type", "[EventDispatcher]") {
    class MyEventA {
    };

    class MyEventB {
    };

    TestEventDispatcher<MyEventA, MyEventB> dispatcher;

    int received = 0;

    auto handle = dispatcher.addEventListener([&](const MyEventB &evt) {
        received++;
    });

    dispatcher.fireEvent(MyEventA());
    dispatcher.fireEvent(MyEventB());
    dispatcher.fireEvent(MyEventA());

    REQUIRE(received == 1);
}

TEST_CASE("can listen to any given event", "[EventDispatcher]") {
    class MyEventA {
    };

    class MyEventB {
    };

    TestEventDispatcher<MyEventA, MyEventB> dispatcher;

    int received = 0;

    auto handle = dispatcher.addEventListener([&](const auto &evt) {
        if constexpr (std::is_same_v<std::decay_t<decltype(evt)>, MyEventB>) {
            received++;
        }
    });

    dispatcher.fireEvent(MyEventA());
    dispatcher.fireEvent(MyEventB());
    dispatcher.fireEvent(MyEventA());

    REQUIRE(received == 1);

    handle.reset();

    received = 0;

    auto handle2 = dispatcher.addEventListener([&](const MyEventA &evt) {
        received++;
    });

    dispatcher.fireEvent(MyEventA());
    dispatcher.fireEvent(MyEventB());

    REQUIRE(received == 1);
}
