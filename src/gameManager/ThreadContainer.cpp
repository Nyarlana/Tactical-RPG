#include "ThreadContainer.h"

#include <iostream>

ThreadContainer::ThreadContainer(Entity* _e)
{
    e = _e;
}

void ThreadContainer::operator()()
{
    while(!e->isDead())
    {
        e->pause();
        e->check();
        e->action();
    }
}
