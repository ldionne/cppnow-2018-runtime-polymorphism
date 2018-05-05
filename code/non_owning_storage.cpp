// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include "vtable.hpp"

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>


// sample(VehicleRef)
class VehicleRef {
  vtable const* const vptr_;
  void* ref_;

public:
  template <typename Any>
  VehicleRef(Any& vehicle)
    : vptr_{&vtable_for<Any>}
    , ref_{&vehicle}
  { }

  void accelerate()
  { vptr_->accelerate(ref_); }
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

int main() {
  Car audi{"Audi", 2017};
  Truck chevrolet{"Chevrolet", 2015};
  Plane boeing{"Boeing", "747"};

  std::vector<VehicleRef> vehicles;
  vehicles.push_back(audi);
  vehicles.push_back(chevrolet);
  vehicles.push_back(boeing);

  for (VehicleRef vehicle : vehicles) {
    vehicle.accelerate();
  }
}
