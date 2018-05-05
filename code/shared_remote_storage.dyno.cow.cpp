// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include "vtable.dyno.hpp"

#include <dyno.hpp>

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace dyno::literals;


// sample(Vehicle)
struct Vehicle {
  template <typename Any>
  Vehicle(Any vehicle) : poly_{vehicle} { }

  void accelerate() {
    poly_ = poly_.clone();
    poly_.virtual_("accelerate"_s)(poly_);
  }

  bool is_stopped() const
  { return poly_.virtual_("is_stopped"_s)(poly_); }

private:
  dyno::poly<IVehicle, dyno::shared_remote_storage> poly_;
};
// end-sample


//////////////////////////////////////////////////////////////////////////////
struct Car {
  std::string make;
  int year;
  void accelerate() { std::cout << "Car::accelerate()" << std::endl; }
  bool is_stopped() const { std::cout << "Car::is_stopped()" << std::endl; return false; }
};

struct Truck {
  std::string make;
  int year;
  void accelerate() { std::cout << "Truck::accelerate()" << std::endl; }
  bool is_stopped() const { std::cout << "Truck::is_stopped()" << std::endl; return false; }
};

struct Plane {
  std::string make;
  std::string model;
  void accelerate() { std::cout << "Plane::accelerate()" << std::endl; }
  bool is_stopped() const { std::cout << "Plane::is_stopped()" << std::endl; return false; }
};

// sample(main)
int main() {
  std::vector<Vehicle> vehicles;

  vehicles.push_back(Car{"Audi", 2017});
  vehicles.push_back(Truck{"Chevrolet", 2015});
  vehicles.push_back(Plane{"Boeing", "747"});

  for (auto& vehicle : vehicles) {
    vehicle.accelerate();
    vehicle.is_stopped();
  }
}
// end-sample
