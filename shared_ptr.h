#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <exception>

namespace tsk {

template <typename T>
class shared_ptr {
 public:
  shared_ptr();
  shared_ptr(T* ptr);
  shared_ptr(shared_ptr<T>& shptr);
  ~shared_ptr();
  T* get();
  unsigned int use_count() const;
  void reset(T* ptr);
  void reset();
  shared_ptr<T> operator=(const shared_ptr<T>& shptr);
  T& operator*();
  T* operator->();

 private:
  T* raw_ptr_;
  unsigned int* ref_counter_;
};

template <typename T>
shared_ptr<T>::shared_ptr() : raw_ptr_(nullptr), ref_counter_(nullptr) {}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr)
    : raw_ptr_(ptr), ref_counter_(new unsigned int) {
  if (ref_counter_ != nullptr) {
    (*ref_counter_) = 1;
  } else {
    throw std::bad_alloc();
  }
}

template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>& shptr)
    : raw_ptr_(shptr.get()), ref_counter_(shptr.ref_counter_) {
  (*ref_counter_)++;
}

template <typename T>
shared_ptr<T>::~shared_ptr() {
  if (ref_counter_ != nullptr) {
    if (*ref_counter_ == 1) {
      delete ref_counter_;
      delete raw_ptr_;
    } else {
      (*ref_counter_)--;
    }
  }
}

template <typename T>
T* shared_ptr<T>::get() {
  return raw_ptr_;
}

template <typename T>
unsigned int shared_ptr<T>::use_count() const {
  if (ref_counter_ != nullptr) {
    return (*ref_counter_);
  }
  return 0;
}

template <typename T>
void shared_ptr<T>::reset(T* ptr) {
  if (ref_counter_ != nullptr) {
    if (*ref_counter_ == 1) {
      delete ref_counter_;
      delete raw_ptr_;
    } else {
      (*ref_counter_)--;
    }
  }

  raw_ptr_ = ptr;
  ref_counter_ = new unsigned int;
  if (ref_counter_ != nullptr) {
    (*ref_counter_) = 1;
  } else {
    throw std::bad_alloc();
  }
}

template <typename T>
void shared_ptr<T>::reset() {
  if (ref_counter_ != nullptr) {
    if (*ref_counter_ == 1) {
      delete ref_counter_;
      delete raw_ptr_;
    } else {
      (*ref_counter_)--;
      raw_ptr_ = nullptr;
    }
  }
}

template <typename T>
shared_ptr<T> shared_ptr<T>::operator=(const shared_ptr<T>& shptr) {
  if (this != &shptr) {
    if (ref_counter_ != nullptr) {
      if (*ref_counter_ == 1) {
        delete ref_counter_;
        delete raw_ptr_;
      } else {
        (*ref_counter_)--;
      }

      raw_ptr_ = shptr.get();
      ref_counter_ = shptr.ref_counter_;
      (*ref_counter_)++;
    }
  }
  return *this;
}

template <typename T>
T& shared_ptr<T>::operator*() {
  return (*raw_ptr_);
}

template <typename T>
T* shared_ptr<T>::operator->() {
  return raw_ptr_;
}

}  // namespace tsk

#endif
