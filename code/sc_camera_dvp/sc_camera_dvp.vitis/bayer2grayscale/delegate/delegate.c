#include "delegate.h"

void (*invoke) ();

void delegate_init(const void *p)
{
    invoke = p;
}

void delegate_invoke()
{
    invoke();
}