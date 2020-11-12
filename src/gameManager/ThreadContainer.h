#ifndef THREAD_CONTAINER_H
#define THREAD_CONTAINER_H

#include "../entities/Entity.h"

class ThreadContainer
{
public:
    ThreadContainer(Entity* _e);
    void operator()();
private:
    Entity* e;
};

#endif
