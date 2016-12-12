/* Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved */

#pragma once

#include <cassert>

#ifdef assert
#undef assert
#endif

#ifdef NDEBUG
#define assert(EX) ((void)0)
#else
#define assert(EX) (void)((EX) or (__assert (#EX, __FILE__, __LINE__),0))
#endif
