#include "Observer.h"
#include "Component.h"
#include <memory>
#include <iostream>

void Subject::notify(Component * subject, Event event)
{
    std::shared_ptr<ObsNode> actual = first;
    while (actual != nullptr)
    {
        actual->obs->on_Notify(subject, event);
        actual = actual->next;
    }
}

void Subject::add_Observer(std::shared_ptr<Observer> obs)
{
  if (first == nullptr)
  {
    first = std::make_shared<ObsNode>();
    first->obs = obs;
    first->next = nullptr;
  }

  std::shared_ptr<ObsNode> actual = first;
  while (actual != nullptr && actual->obs != obs)
  {
      actual = actual->next;
  }

  if(actual == nullptr)
  {
      actual = std::make_shared<ObsNode>();
      actual->next = nullptr;
  }

  actual->obs = obs;
}

void Subject::remove_Observer(std::shared_ptr<Observer> obs)
{
  if (first != nullptr && first->obs != obs)
  {
    std::shared_ptr<ObsNode> actual = first;
    while (actual->next != nullptr)
    {
      if (actual->next->obs == obs)
      {
        actual->next = actual->next->next;
      }
      actual = actual->next;
    }
  }
  else if(first->obs == obs)
  {
      first = first->next;
  }
}
