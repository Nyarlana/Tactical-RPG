#include "Component.h"

Component::Component() {}

Component::~Component() {}

void Component::deactivate() {
  active = false;
}

void Component::activate() {
  active = true;
}

bool Component::is_Active() {
  return active;
}
