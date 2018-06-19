//
// Created by Hython on 2018/6/4.
//

#ifndef OOP_ALLOCATOR_HSTRING_H
#define OOP_ALLOCATOR_HSTRING_H
#include "h_allocator.h"
#include <string>
namespace hython {
    typedef std::basic_string<char, std::char_traits<char>, h_allocator<char> > xstring;
    typedef std::basic_string<wchar_t, std::char_traits<wchar_t>,h_allocator<wchar_t> > xwstring;

};
#endif //OOP_ALLOCATOR_HSTRING_H
