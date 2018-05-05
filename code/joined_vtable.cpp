// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


// sample(vtable)
struct vtable {
  void (*delete_)(void* this_);
  // ...
  void* (*clone)(void const* other); // skip-sample
};

template <typename T>
vtable const vtable_for = {
  [](void* this_) {
    delete static_cast<T*>(this_);
  }
  // ...
  ,                                               // skip-sample
  [](void const* this_) -> void* {                // skip-sample
    return new T(*static_cast<T const*>(this_));  // skip-sample
  }                                               // skip-sample
};
// end-sample

// sample(joined_vtable)
struct joined_vtable {
  vtable const* const remote;
  void (*accelerate)(void* this_);
};

template <typename T>
joined_vtable const joined_vtable_for = {
  &vtable_for<T>,
  [](void* this_) {
    static_cast<T*>(this_)->accelerate();
  }
};
// end-sample

// sample(Vehicle)
class Vehicle {
  joined_vtable const vtbl_;
  void* ptr_;

public:
  template <typename Any>
  Vehicle(Any vehicle)
    : vtbl_{joined_vtable_for<Any>}
    , ptr_{new Any(vehicle)}
  { }
                                                      // skip-sample
  Vehicle(Vehicle const& other)                       // skip-sample
    : vtbl_{other.vtbl_}                              // skip-sample
    , ptr_{other.vtbl_.remote->clone(other.ptr_)}     // skip-sample
  { }                                                 // skip-sample

  void accelerate()
  { vtbl_.accelerate(ptr_); }

  ~Vehicle()
  { vtbl_.remote->delete_(ptr_); }
};
// end-sample


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
