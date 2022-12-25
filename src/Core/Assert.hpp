#ifndef CLEGINE_CORE_ASSERT_HPP
#define CLEGINE_CORE_ASSERT_HPP

#include <Core/Common.hpp>

#if defined(CLEGINE_DEBUG_ALWAYS) && CLEGINE_DISABLE_ASSERTING == 0
# include <assert.h>
# define ASSERT(cond) assert(cond);
#else // CLEGINE_DEBUG_ALWAYS
# define ASSERT(cond);
#endif
#endif // CLEGINE_CORE_ASSERT_HPP