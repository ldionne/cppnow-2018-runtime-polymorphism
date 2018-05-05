// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include <dyno.hpp>

#include <cassert>
#include <functional>
#include <string>
#include <utility>
using namespace dyno::literals;


template <typename Signature>
struct Callable;

template <typename R, typename ...Args>
struct Callable<R(Args...)> : decltype(dyno::requires(
  dyno::CopyConstructible{},
  dyno::MoveConstructible{},
  dyno::Destructible{},
  "call"_s = dyno::function<R (dyno::T const&, Args...)>
)) { };

template <typename R, typename ...Args, typename F>
auto const dyno::default_concept_map<Callable<R(Args...)>, F> = dyno::make_concept_map(
  "call"_s = [](F const& f, Args ...args) -> R {
    return f(std::forward<Args>(args)...);
  }
);

// sample(basic_function)
template <typename Signature, typename StoragePolicy>
struct basic_function;

template <typename R, typename ...Args, typename StoragePolicy>
struct basic_function<R(Args...), StoragePolicy> {
  template <typename F>
  basic_function(F&& f) : poly_{std::forward<F>(f)} { }

  R operator()(Args ...args) const
  { return poly_.virtual_("call"_s)(poly_, args...); }

private:
  dyno::poly<Callable<R(Args...)>, StoragePolicy> poly_;
};
// end-sample

// sample(function)
template <typename Signature>
using function = basic_function<Signature,
                                dyno::sbo_storage<16>>;
// end-sample

// sample(function_view)
template <typename Signature>
using function_view = basic_function<Signature,
                                     dyno::non_owning_storage>;
// end-sample

// sample(inplace_function)
template <typename Signature, std::size_t Size = 32>
using inplace_function = basic_function<Signature,
                                        dyno::local_storage<Size>>;
// end-sample

// sample(shared_function)
template <typename Signature>
using shared_function = basic_function<Signature,
                                       dyno::shared_remote_storage>;
// end-sample


//
// Tests
//

struct ToStringAdd {
  ToStringAdd(int num) : num_(num) { }
  std::string to_string_add(int i) const { return std::to_string(num_ + i); }
  int num_;
};

struct ToString {
  std::string operator()(int i) const { return std::to_string(i); }
};

template <template <typename> class Function>
void test() {
  // store a lambda
  {
    auto lambda = [](std::string const& s) {
      return s.size();
    };
    Function<int(std::string const&)> size = lambda;

    assert(size("") == 0);
    assert(size("a") == 1);
    assert(size("ab") == 2);
    assert(size("abc") == 3);
    assert(size("abcdef") == 6);
  }

  // store the result of a call to std::bind
  {
    auto bind = std::bind(static_cast<std::string(*)(int)>(std::to_string), 31337);
    Function<std::string()> tostring = bind;
    assert(tostring() == "31337");
  }

  // store a call to a member function and object
  {
    ToStringAdd const adder{314159};
    auto bind = std::bind(&ToStringAdd::to_string_add, adder, std::placeholders::_1);
    Function<std::string(int)> f = bind;
    assert(f(1) == "314160");
    assert(f(2) == "314161");
    assert(f(3) == "314162");
    assert(f(-10) == "314149");
  }

  // store a call to a member function and object ptr
  {
    ToStringAdd const adder{314159};
    auto bind = std::bind(&ToStringAdd::to_string_add, &adder, std::placeholders::_1);
    Function<std::string(int)> f = bind;
    assert(f(1) == "314160");
    assert(f(2) == "314161");
    assert(f(3) == "314162");
    assert(f(-10) == "314149");
  }

  // store a call to a function object
  {
    ToString f{};
    Function<std::string(int)> tostring = f;
    assert(tostring(1) == "1");
    assert(tostring(2) == "2");
    assert(tostring(3) == "3");
    assert(tostring(18) == "18");
  }
}

template <typename Signature>
using my_inplace_function = inplace_function<Signature>;

int main() {
  test<function>();
  test<function_view>();
  test<my_inplace_function>();
  test<shared_function>();
}
