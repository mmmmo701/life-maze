#pragma once

#ifdef NDEBUG
    // Release mode: contracts do nothing
    #define REQUIRES(cond)    ((void)0)
    #define ENSURES(cond)     ((void)0)
    #define ASSERT(cond)      ((void)0)
#else
    // Debug mode: contracts are assertions
    #include <cassert>
    #define REQUIRES(cond)    assert(cond)
    #define ENSURES(cond)     assert(cond)
    #define ASSERT(cond)      assert(cond)
#endif