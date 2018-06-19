//
// Created by Hython on 2018/6/4.
//

#ifndef OOP_ALLOCATOR_FAULT_H
#define OOP_ALLOCATOR_FAULT_H
namespace hython {

#define ASSERT() \
    FaultHandler(__FILE__, (unsigned short) __LINE__)

#define ASSERT_TRUE(condition) \
    do {if (!(condition)) FaultHandler(__FILE__, (unsigned short) __LINE__);} while (0)

/// Handles all software assertions in the system.
/// @param[in] file - the file name that the software assertion occurred on
/// @param[in] line - the line number that the software assertion occurred on
    void FaultHandler(const char *file, unsigned short line);
}

#endif //OOP_ALLOCATOR_FAULT_H
