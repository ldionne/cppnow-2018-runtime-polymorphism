// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include "vtable.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


// sample(Vehicle)
class Vehicle {
  vtable const* const vptr_;
  std::aligned_storage_t<64> buffer_;

public:
  template <typename Any>
  Vehicle(Any vehicle) : vptr_{&vtable_for<Any>} {
    static_assert(sizeof(Any) <= sizeof(buffer_),
      "can't hold such a large object in a Vehicle");
    new (&buffer_) Any(vehicle);
  }
                                                        // skip-sample
  Vehicle(Vehicle const& other) : vptr_{other.vptr_} {  // skip-sample
    other.vptr_->copy(&buffer_, &other.buffer_);        // skip-sample
  }                                                     // skip-sample

  void accelerate()
  { vptr_->accelerate(&buffer_); }

  ~Vehicle()
  { vptr_->dtor(&buffer_); }
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
