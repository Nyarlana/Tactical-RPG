/**@file Observer class header*/
#ifndef OBSRV_SUBJ_H
#define OBSRV_SUBJ_H

// #include <vector>
#include <memory>
#include "Component.h"

/**@brief event enum*/
enum Event {
  EVENT_TEST,
  GM_ADD_COMPONENT,
  GM_ADD_THREAD,
  E_OUT_REQ,
  E_GET_RANDOM_PATH,
  E_GET_PATH_TARGET,
  E_PAUSE
};

/**@class Observer
@brief observer class
observes a subject and react to events*/
class Observer : public std::enable_shared_from_this<Observer> {
public:
  /**@brief class destructor*/
  //virtual ~Observer();
  /**@brief called by subject notify, launches different method based on the event
     overriten by every child, forks to a function
     @param subject the subject that sent the signal
     @param event chosen event*/
  virtual void on_Notify(Component* subject, Event event) = 0;
};

/**@brief Node for observer list*/
struct ObsNode {
  std::shared_ptr<Observer> obs;
  std::shared_ptr<ObsNode> next;
};

/**@class Subject
@brief subject class
observed by observers, can notify them*/
class Subject {
public:
  /**@brief notifies all observers
     @param event chosen event*/
  virtual void notify(Component* subject, Event event);
  /**@brief add an observer
  add an observer using "subject->add_Observer(std::dynamic_pointer_cast<Observer>(shared_from_this()));"*/
  void add_Observer(std::shared_ptr<Observer> obs);
  /**@brief removes an observer*/
  void remove_Observer(std::shared_ptr<Observer> obs);

protected:
  // std::vector<std::shared_ptr<Observer>> observers;
  std::shared_ptr<ObsNode> first = nullptr;
};

#endif
