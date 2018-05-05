// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#ifndef VTABLE_DYNO_HPP
#define VTABLE_DYNO_HPP

#include <dyno.hpp>
using namespace dyno::literals;


// sample(IVehicle)
struct IVehicle : decltype(dyno::requires(
  dyno::CopyConstructible{},
  dyno::Destructible{},
  "accelerate"_s = dyno::function<void(dyno::T&)>
)) { };

template <typename T>
auto dyno::default_concept_map<IVehicle, T> = dyno::make_concept_map(
  "accelerate"_s = [](T& vehicle) { vehicle.accelerate(); }
);
// end-sample

#endif // header guard
