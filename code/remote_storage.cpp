// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include "vtable.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


// sample(Vehicle)
class Vehicle {
  vtable const* const vptr_;
  void* ptr_;

public:
  template <typename Any>
    // enabled only when vehicle.accelerate() is valid
  Vehicle(Any vehicle)
    : vptr_{&vtable_for<Any>}
    , ptr_{new Any(vehicle)}
  { }

  Vehicle(Vehicle const& other); // implementation omitted

  void accelerate()
  { vptr_->accelerate(ptr_); }

  ~Vehicle()
  { vptr_->delete_(ptr_); }
};
// end-sample

Vehicle::Vehicle(Vehicle const& other)
  : vptr_{other.vptr_}
  , ptr_{other.vptr_->clone(other.ptr_)}
{ }

//////////////////////////////////////////////////////////////////////////////
struct Car {
  std::string make;
  int year;
  void accelerate() { std::cout << "Car::accelerate()" << std::endl; }
};

struct Truck {
  std::string make;
  int year;
  void accelerate() { std::cout << "Truck::accelerate()" << std::endl; }
};

struct Plane {
  std::string make;
  std::string model;
  void accelerate() { std::cout << "Plane::accelerate()" << std::endl; }
};

// sample(main)
int main() {
  std::vector<Vehicle> vehicles;

  vehicles.push_back(Car{"Audi", 2017});
  vehicles.push_back(Truck{"Chevrolet", 2015});
  vehicles.push_back(Plane{"Boeing", "747"});

  for (auto& vehicle : vehicles) {
    vehicle.accelerate();
  }
}
// end-sample
