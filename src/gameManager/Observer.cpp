#include "Observer.h"
#include <memory>
#include <vector>

void Subject::notify(Event event) {
  for (size_t i = 0; i < observers.size(); i++) {
    if (observers[i] != nullptr) {
      observers[i]->on_Notify(event);
    }
  }
}

void Subject::add_Observer(std::shared_ptr<Observer> obs) {
  observers.push_back(obs);
}

void Subject::remove_Observer(std::shared_ptr<Observer> obs) {
  for (size_t i = 0; i < observers.size(); i++) {
    if (observers[i] = obs) {
      observers.erase(observers.begin()+i);
    }
  }
}
