// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include "vtable.hpp"

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


// sample(Vehicle)
struct Vehicle {
  vtable const* const vptr_;
  union { void* ptr_;
          std::aligned_storage_t<16> buffer_; };
  bool on_heap_;

  template <typename Any>
  Vehicle(Any vehicle) : vptr_{&vtable_for<Any>} {
    if (sizeof(Any) > 16) {
      on_heap_ = true;
      ptr_ = new Any(vehicle);
    } else {
      on_heap_ = false;
      new (&buffer_) Any{vehicle};
    }
  }

  void accelerate()
  { vptr_->accelerate(on_heap_ ? ptr_ : &buffer_); }
// end-sample

  Vehicle(Vehicle const& other) : vptr_{other.vptr_} {
    if (other.on_heap_) {
      ptr_ = other.vptr_->clone(other.ptr_);
    } else {
      other.vptr_->copy(&buffer_, &other.buffer_);
    }
  }

  ~Vehicle() {
    if (on_heap_) {
      vptr_->delete_(ptr_);
    } else {
      vptr_->dtor(&buffer_);
    }
  }
// sample(Vehicle)
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
