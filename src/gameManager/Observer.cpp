#include "Observer.h"
#include "Component.h"
#include <memory>
// #include <vector>

// void Subject::notify(const Component& subject, Event event) {
//   for (size_t i = nullptr; i < observers.size(); i++) {
//     if (observers[i] != nullptr) {
//       observers[i]->on_Notify(subject, event);
//     }
//   }
// }

// void Subject::add_Observer(std::shared_ptr<Observer> obs) {
//   observers.push_back(obs);
// }
//
// void Subject::remove_Observer(std::shared_ptr<Observer> obs) {
//   for (size_t i = nullptr; i < observers.size(); i++) {
//     if (observers[i] = obs) {
//       observers.erase(observers.begin()+i);
//     }
//   }
// }

void Subject::notify(const Component& subject, Event event) {
  if (first!=nullptr) {
    std::shared_ptr<ObsNode> actual = first;
    while (actual->next != nullptr) {
      actual->obs->on_Notify(subject, event);
      actual = actual->next;
    }
  }
}

void Subject::add_Observer(std::shared_ptr<Observer> obs) {
  if (first == nullptr) {
    first = std::make_shared<ObsNode>();
  }
  std::shared_ptr<ObsNode> actual = first;
  while (actual->next != nullptr) {
    actual = actual->next;
  }
  actual->next = std::make_shared<ObsNode>();
  actual->next->obs = obs;
}

void Subject::remove_Observer(std::shared_ptr<Observer> obs) {
  if (first != nullptr) {
    std::shared_ptr<ObsNode> actual = first;
    while (actual->next != nullptr) {
      if (actual->next->obs == obs) {
        actual->next = actual->next->next;
      }
      actual = actual->next;
    }
  }
}
