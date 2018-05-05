// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#include <iostream>
#include <string>
#include <vector>


// sample(Vehicle)
struct Vehicle {
  virtual void accelerate() = 0;
  virtual ~Vehicle() { }
};

struct Car : Vehicle {
  void accelerate() override;
};

struct Truck : Vehicle {
  void accelerate() override;
};

struct Plane : Vehicle {
  void accelerate() override;
};
// end-sample

void Car::accelerate() { std::cout << "Car::accelerate()" << std::endl; }
void Truck::accelerate() { std::cout << "Truck::accelerate()" << std::endl; }
void Plane::accelerate() { std::cout << "Plane::accelerate()" << std::endl; }

// sample(main)
int main() {
  std::vector<std::unique_ptr<Vehicle>> vehicles;

  vehicles.push_back(std::make_unique<Car>(/*...*/));
  vehicles.push_back(std::make_unique<Truck>(/*...*/));
  vehicles.push_back(std::make_unique<Plane>(/*...*/));

  for (auto& vehicle : vehicles) {
    vehicle->accelerate();
  }
}
// end-sample
