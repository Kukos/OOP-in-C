#ifndef OOP_H
#define OOP_H

/*
    Object Oriented Programming for C

    This header contains some useful macros to deal with OOP in C
    Singleton - provide macro to make static memory private for fuction only
    Object Alloca - provide macro to alloc every object on stack (even if compiler cannot do that)
    Iterators - provide macros to enable iterator framework for your structures
    Checker - provide macro to check in compile time compatibility of your structure with this framework

    Author: Michal Kukowski
    email: michalkukowski10@gmail.com

    LICENCE: GPL 3.0
*/

#include "oop_checker.h"
#include "oop_iterators.h"
#include "oop_object_alloca.h"
#include "oop_singleton.h"

#endif