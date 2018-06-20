//
// Created by Hython on 2018/6/4.
//

#ifndef OOP_ALLOCATOR_XALLOCATOR_H
#define OOP_ALLOCATOR_XALLOCATOR_H

#include "DataTypes.h"
#include <cstddef>
namespace hython {

    class XallocInitDestroy {
    public:
        XallocInitDestroy();

        ~XallocInitDestroy();

    private:
        static INT refCount;
    };

    static XallocInitDestroy xallocInitDestroy;

    /// This function must be called exactly one time before the operating system threading starts
    /// Users never call it manually! The constructor should do the job.
    void xalloc_init();
    /// This function must be called once before the application exits.
    /// Users never call it manually! The destructor should do the job.
    void xalloc_destroy();
    /// Allocate a block of memory
    /// @param[in] size - the size of the block to allocate
    void *xmalloc(size_t size);
    /// Frees a previously xalloc allocated block
    /// @param[in] ptr - a pointer to a previously allocated memory using xalloc
    void xfree(void*ptr);
    /// Reallocates an existing xalloc block to a new size
    /// @param[in] size - the size of the new block
    void *xrealloc(void*ptr, size_t size);

    #define AUTOMATIC_XALLOCATOR_INIT_DESTROY
    //#define STATIC_POOLS // test


    // Macro to overload new/delete with xalloc/xfree
    #define XALLOCATOR \
        public: \
            void* operator new(size_t size) { \
                return xmalloc(size); \
            } \
            void operator delete(void* pObject) { \
                xfree(pObject); \
            }
}


#endif //OOP_ALLOCATOR_XALLOCATOR_H
