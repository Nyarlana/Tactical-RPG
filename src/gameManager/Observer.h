/**@file Observer class header*/
#ifndef OBSRV_SUBJ_H
#define OBSRV_SUBJ_H

#include <vector>
#include <memory>
#include "Component.h"

enum Event {
  EVENT_TEST
};

/**@class observer class*/
class Observer {
public:
  /**@brief class destructor*/
  //virtual ~Observer();
  /**@brief called by subject notify, launches different method based on the event
     overriten by every child, forks to a function
     @param subject the subject that sent the signal
     @param event chosen event*/
  virtual void on_Notify(const Component& subject, Event event) = 0;
};

/**@class subject class*/
class Subject {
public:
  /**@brief notifies all observers
     @param event chosen event*/
  virtual void notify(const Component& subject, Event event);
  /**@brief add an observer*/
  void add_Observer(std::shared_ptr<Observer> obs);
  /**@brief removes an observer*/
  void remove_Observer(std::shared_ptr<Observer> obs);

protected:
  std::vector<std::shared_ptr<Observer>> observers;
};

#endif
