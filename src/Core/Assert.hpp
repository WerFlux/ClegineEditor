#ifndef CLEGINE_CORE_ASSERT_HPP
#define CLEGINE_CORE_ASSERT_HPP

#include <Core/Common.hpp>

#if defined(CLEGINE_DEBUG_ALWAYS) && CLEGINE_DISABLE_ASSERTING == 0
# include <assert.h>
# define ASSERT(cond, msg) do { if(!!(cond)) { LOG_CRITICAL("{0}, {1} file={2} line={3}", #cond, msg, __FILE__, __LINE__); } } while(0)
#else // CLEGINE_DEBUG_ALWAYS
# define ASSERT(cond, msg);
#endif
#endif // CLEGINE_CORE_ASSERT_HPP