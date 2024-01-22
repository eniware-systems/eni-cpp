//
// Created by void on 21/08/2021.
//

#include <catch2/catch_all.hpp>

#include <eni/Interceptor.h>

#include <utility>

using namespace eni;

class MyInterceptor0 {
public:
    void invoke() {
        called++;
    }

    std::future<void> invokeAsync() {
        return std::async([this] {
            called++;
        });
    }

    std::size_t called = 0;
};

class MyInterceptor1 {
public:
    explicit MyInterceptor1(std::string val) : _val(std::move(val)) {}

    void invoke(std::vector<std::string> &params) const {
        params.push_back(_val);
    }

private:
    std::string _val;
};

class MyCountingInterceptor {
public:
    virtual ~MyCountingInterceptor() = default;
    virtual void invoke(std::size_t &n) {
        n++;
    }
};

class MyErrorInterceptor : public MyCountingInterceptor {
public:
    void invoke(std::size_t &/*n*/) override {
        throw std::runtime_error("this should stop execution");
    }
};

class MyPriorityInterceptor {
public:
    virtual ~MyPriorityInterceptor() = default;
    explicit MyPriorityInterceptor(int32 priority = 0) : _priority(priority) {}

    void invoke(std::vector<int32> &priorities) const {
        priorities.push_back(_priority);
    }

private:
    int32 _priority;
};

TEST_CASE("Can (un-)register interceptors", "[Interceptor]") {
    InterceptorRegistry<MyInterceptor0> reg;
    auto interceptor = std::make_shared<MyInterceptor0>();
    reg.registerInterceptor(interceptor);
    auto result = reg.getInterceptors();

    REQUIRE(1 == std::distance(result.first, result.second));
    reg.unregisterInterceptor(interceptor);

    result = reg.getInterceptors();
    REQUIRE(0 == std::distance(result.first, result.second));
}

TEST_CASE("Can invoke interceptor without parameters", "[Interceptor]") {
    InterceptorRegistry<MyInterceptor0> reg;
    auto interceptor = std::make_shared<MyInterceptor0>();
    reg.registerInterceptor(interceptor);

    reg.invoke(&MyInterceptor0::invoke);

    REQUIRE(1 == interceptor->called);
}

TEST_CASE("Can invoke interceptor with parameters", "[Interceptor]") {
    InterceptorRegistry<MyInterceptor1> reg;
    std::string value = "hello";
    std::vector<std::string> values{};

    auto interceptor = std::make_shared<MyInterceptor1>(value);
    reg.registerInterceptor(interceptor);

    reg.invoke(&MyInterceptor1::invoke, values);

    REQUIRE(!values.empty());
    REQUIRE(values.front() == value);
}

TEST_CASE("Interceptors can interrupt execution", "[Interceptor]") {
    InterceptorRegistry<MyCountingInterceptor> reg;
    reg.registerInterceptor(std::make_shared<MyCountingInterceptor>());
    reg.registerInterceptor(std::make_shared<MyCountingInterceptor>());
    reg.registerInterceptor(std::make_shared<MyErrorInterceptor>());
    reg.registerInterceptor(std::make_shared<MyCountingInterceptor>());

    std::size_t n = 0;
    REQUIRE_THROWS(reg.invoke(&MyCountingInterceptor::invoke, n));

    REQUIRE(n == 2);
}

TEST_CASE("Priorities are working", "[Interceptor]") {
    InterceptorRegistry<MyPriorityInterceptor> reg;
    reg.registerInterceptor(std::make_shared<MyPriorityInterceptor>(10), 10);
    reg.registerInterceptor(std::make_shared<MyPriorityInterceptor>(-12), -12);
    reg.registerInterceptor(std::make_shared<MyPriorityInterceptor>(12234), 12234);
    reg.registerInterceptor(std::make_shared<MyPriorityInterceptor>(3345), 3345);
    reg.registerInterceptor(std::make_shared<MyPriorityInterceptor>(2), 2);
    reg.registerInterceptor(std::make_shared<MyPriorityInterceptor>(5), 5);
    reg.registerInterceptor(std::make_shared<MyPriorityInterceptor>(0), 0);

    std::vector<int32> priorities{};
    reg.invoke(&MyPriorityInterceptor::invoke, priorities);

    REQUIRE(priorities.size() == 7);

    auto sorted = std::ranges::is_sorted(std::ranges::rbegin(priorities), std::ranges::rend(priorities));
    REQUIRE(sorted);
}

TEST_CASE("Can invoke async interceptor", "[Interceptor]") {
    InterceptorRegistry<MyInterceptor0> reg;

    auto interceptor = std::make_shared<MyInterceptor0>();
    reg.registerInterceptor(interceptor);

    auto future = reg.invoke(&MyInterceptor0::invokeAsync);
    REQUIRE(0 == interceptor->called);
    future.get();
    REQUIRE(1 == interceptor->called);
}