<<<<<<< HEAD
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

	template<class _Ty, class _Ax = h_allocator<_Ty> >
	class hvector : public std::vector<_Ty, _Ax> {

	};
};
#endif //OOP_ALLOCATOR_HLIST_H
=======
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
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3
