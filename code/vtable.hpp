// Copyright Louis Dionne 2017
// Distributed under the Boost Software License, Version 1.0.

#ifndef VTABLE_HPP
#define VTABLE_HPP

#include <cstddef>


// sample(vtable)
struct vtable {
  void (*accelerate)(void* this_);
  void (*delete_)(void* this_);
  void* (*clone)(void const* this_);        // skip-sample
  void (*copy)(void* p, void const* other); // skip-sample
  void (*dtor)(void* p);                    // skip-sample
};

template <typename T>
vtable const vtable_for = {
  [](void* this_) {
    static_cast<T*>(this_)->accelerate();
  },

  [](void* this_) {
    delete static_cast<T*>(this_);
  }
  ,                                               // skip-sample
  [](void const* this_) -> void* {                // skip-sample
    return new T(*static_cast<T const*>(this_));  // skip-sample
  },                                              // skip-sample
                                                  // skip-sample
  [](void* p, void const* other) {                // skip-sample
    new (p) T(*static_cast<T const*>(other));     // skip-sample
  },                                              // skip-sample
                                                  // skip-sample
  [](void* this_) {                               // skip-sample
    static_cast<T*>(this_)->~T();                 // skip-sample
  }                                               // skip-sample
};
// end-sample

#endif // header guard
