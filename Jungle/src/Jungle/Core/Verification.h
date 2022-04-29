#pragma once

#include "Log.h"

#ifdef JNGL_ENABLE_ASSERTS
#define JNGL_ASSERT(x, ...) { if(!(x)) { JNGL_LOG_ERROR("Assertion Failed: {0}.", __VA_ARGS__); __debugbreak(); } }
#define JNGL_CORE_ASSERT(x, ...) { if(!(x)) { JNGL_CORE_LOG_ERROR("Assertion Failed: {0}.", __VA_ARGS__); __debugbreak(); } }
#else
#define JNGL_ASSERT(x, ...)
#define JNGL_CORE_ASSERT(x, ...)
#endif

#define JNGL_VERIFY(x, ...) { if(!(x)) { JNGL_LOG_ERROR("Verification Failed: {0}.", __VA_ARGS__); __debugbreak(); } }
#define JNGL_CORE_VERIFY(x, ...) { if(!(x)) { JNGL_CORE_LOG_ERROR("Verification Failed: {0}.", __VA_ARGS__); __debugbreak(); } }