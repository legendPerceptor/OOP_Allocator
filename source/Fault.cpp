//
// Created by Hython on 2018/6/4.
//
#include "Fault.h"
/// sjn changed here. Withoug <debugapi.h>, DebugBreak() cannot operate.
//#include <debugapi.h>
#include <cassert>
namespace hython {

    void FaultHandler(const char *file, unsigned short line) {
<<<<<<< HEAD
#if _WIN32
        // If you hit this line, it means one of the ASSERT macros failed.
        DebugBreak();
#endif
=======
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3

        assert(0);
    }
}