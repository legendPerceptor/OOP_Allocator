//
// Created by Hython on 2018/6/4.
//
#include "Fault.h"
#include <cassert>
namespace hython {

    void FaultHandler(const char *file, unsigned short line) {
#if WIN32
        // If you hit this line, it means one of the ASSERT macros failed.
        DebugBreak();
#endif

        assert(0);
    }
}