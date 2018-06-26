//
// Created by Hython on 2018/6/4.
//

#ifndef OOP_ALLOCATOR_ALLOCATOR_H
#define OOP_ALLOCATOR_ALLOCATOR_H

#include <cstdlib>
#include <cstddef>
#include "xallocator.h"
#include <iostream>


namespace hython {


    template<class T>
    class h_allocator;

    template<>
    class h_allocator<void> {
    public:
        typedef void *pointer;
        typedef const void *const_pointer;
        // reference to void members are impossible.
        typedef void value_type;

        template<class U>
        struct rebind {
            typedef h_allocator<U> other;
        };
    };

    /// @brief h_allocator is STL-compatible allocator used to provide fixed block allocation.
    ///
    template<class T>
    class h_allocator {//Rename to be compatible with namespace std
    public:
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef const T *const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef T value_type;

        template<class U>
        struct rebind {
            typedef h_allocator<U> other;
        };

        h_allocator() noexcept = default;

        h_allocator(const h_allocator &) noexcept = default;

      //  template<class U>
      //  h_allocator(const h_allocator<U> &) noexcept = default;

        ~h_allocator() = default;

        const_pointer address(const_reference x) const noexcept { return &x; }

        pointer allocate(size_type n, h_allocator<void>::const_pointer hint = 0) {
            return static_cast<pointer>(xmalloc(n * sizeof(T)));
        }

        void deallocate(pointer p, size_type n) noexcept {
            xfree(p);
        }

        /// Get the maximum size of memory.
        /// @return	Max memory size in bytes.
        size_type max_size() const throw() { return size_t(-1) / sizeof(value_type); }

        /// Constructs a new instance.
        /// @param[in] p - pointer to the memory where the instance is constructed
        ///		using placement new.
        /// @param[in] val - instance of object to copy construct.
        void construct(pointer p, const T &val) {
            //std::cout<<"CONSTRUCT:"<<val<<std::endl;
            new(static_cast<void *>(p)) T(val);
        }

        /// Create a new object instance using placement new.
        /// @param[in] p - pointer to the memory where the instance is constructed
        ///		using placement new.
        void construct(pointer p) {
            new(static_cast<void *>(p)) T();
        }

        /// Destroys an instance. Objects created with placement new must
        ///	explicitly call the destructor.
        /// @param[in] p - pointer to object instance.
        void destroy(pointer p) {
            p->~T();
        }
    };

    template<typename T, typename U>
    inline bool operator==(const h_allocator<T> &, const h_allocator<U>) { return true; }

    template<typename T, typename U>
    inline bool operator!=(const h_allocator<T> &, const h_allocator<U>) { return false; }
}

#ifdef _WIN32
#define STD_ALLOC_CDECL __cdecl
#else
#define STD_ALLOC_CDECL
#endif
namespace std {
    template<class _Tp1, class _Tp2>
    inline hython::h_allocator<_Tp2> &STD_ALLOC_CDECL
    __stl_alloc_rebind(hython::h_allocator<_Tp1> &__a, const _Tp2 *) {
        return (hython::h_allocator<_Tp2> &) (__a);
    }

    template<class _Tp1, class _Tp2>
    inline hython::h_allocator<_Tp2> STD_ALLOC_CDECL
    __stl_alloc_create(const hython::h_allocator<_Tp1> &, const _Tp2 *) {
        return hython::h_allocator<_Tp2>();
    }
}

#endif //OOP_ALLOCATOR_ALLOCATOR_H
