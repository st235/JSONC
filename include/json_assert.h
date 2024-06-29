#ifndef __JSONC_JSON_ASSERT_H__
#define __JSONC_JSON_ASSERT_H__

#ifdef ASSERT

#include <cassert>

#endif // ASSERT


#ifdef ASSERT

#define JASSERT(expression) assert(expression)
#define JTHROW() assert(false)
#define JUNREACHABLE() assert(false)

#else // !ASSERT

#define JASSERT(expression)
#define JTHROW()
#define JUNREACHABLE()

#endif // ASSERT

#endif // __JSONC_JSON_ASSERT_H__
