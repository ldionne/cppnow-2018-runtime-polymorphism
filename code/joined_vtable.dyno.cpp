// Copyright Louis Dionne 2018
// Distributed under the Boost Software License, Version 1.0.

#include "vtable.dyno.hpp"

#include <dyno.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace dyno::literals;


// sample(Vehicle)
struct Vehicle {
  template <typename Any>
  Vehicle(Any vehicle) : poly_{vehicle} { }

  void accelerate()
  { poly_.virtual_("accelerate"_s)(poly_); }

private:
  using VTable = dyno::vtable<
                  dyno::local<dyno::only<decltype("accelerate"_s)>>,
                  dyno::remote<dyno::everything_else>>;
  //              ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
  dyno::poly<IVehicle, dyno::remote_storage, VTable> poly_;
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
