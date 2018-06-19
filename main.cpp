#include <iostream>
#include <Fault.h>
#include "hlist.h"
using namespace hython;
void ListGlobalHeapTest();
void ListFixedBlockTest();
static int MAX_BENCHMARK = 10000;
static void out_of_memory()
{
    // new-handler function called by Allocator when pool is out of memory
    ASSERT();
}
int main() {
    std::set_new_handler(out_of_memory);

    hlist<int> myList;
    myList.push_back(123);
    myList.push_back(355);
    auto it =myList.begin();
    while(it!=myList.end()){
        std::cout<<*it++<<std::endl;
    }




    return 0;
}

void ListFixedBlockTest()
{
    hlist<int> myList;
    for (int i=0; i<MAX_BENCHMARK; i++)
        myList.push_back(123);
    myList.clear();
}