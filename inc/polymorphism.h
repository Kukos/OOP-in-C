#ifndef POLYMORPHISM_H
#define POLYMORPHISM_H

#include <interface.h>
#include <public.h>
#include <private.h>

/*
    in C++ we have new overwriting. Here we are during the same but in C way.
    Each class that want to use interface needs create "constructors" to hide
    all of callbacks etc.

    This should but put in public and private files, but for demo consistency I put it here
*/
Interface_object* interface_object_create_object_public(void *object, size_t size);
Interface_object* interface_object_create_object_private(void *object, size_t size);

#endif