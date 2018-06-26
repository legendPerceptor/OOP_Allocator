//
// Created by Hython on 2018/6/4.
//

#ifndef OOP_ALLOCATOR_HLIST_H
#define OOP_ALLOCATOR_HLIST_H

#include "h_allocator.h"
#include <list>
#include <vector>

namespace hython {
    template<class _Ty, class _Ax =h_allocator<_Ty> >
    class hlist : public std::list<_Ty,_Ax>{
    };
};
#endif //OOP_ALLOCATOR_HLIST_H
