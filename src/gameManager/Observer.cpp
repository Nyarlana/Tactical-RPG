#include "Observer.h"
#include "Component.h"
#include <memory>

void Subject::notify(const Component * subject, Event event)
{
  if (first!=nullptr)
  {
    std::shared_ptr<ObsNode> actual = first;
    while (actual->next != nullptr)
    {
      actual->obs->on_Notify(subject, event);
      actual = actual->next;
    }
  }
}

void Subject::add_Observer(std::shared_ptr<Observer> obs)
{
  if (first == nullptr)
  {
    first = std::make_shared<ObsNode>();
    first->next = nullptr;
  }
  std::shared_ptr<ObsNode> actual = first;
  while (actual->next != nullptr)
  {
    actual = actual->next;
  }
  actual->next = std::make_shared<ObsNode>();
  actual->next->obs = obs;
  actual->next->next = nullptr;
}

void Subject::remove_Observer(std::shared_ptr<Observer> obs)
{
  if (first != nullptr)
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
}
