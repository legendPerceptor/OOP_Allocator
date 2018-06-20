#include <iostream>
#include <Fault.h>
#include <time.h>
#include "hlist.h"

#define SHUFFLE 1
#define NORMAL 0

using namespace hython;
using namespace std;
void ListGlobalHeapTest();
void ListFixedBlockTest();
static int MAX_BENCHMARK = 10000;
static void out_of_memory()
{
    // new-handler function called by Allocator when pool is out of memory
    ASSERT();
}

void Benchmark_iter(hlist<int> &myList, list<int> &stdList, int repeatTimes)
{
	clock_t start, end;
	double time_duration;
	start = clock();

	// testing mylist
	for (int i = 0; i < repeatTimes; i++)
	{
		for (auto it = myList.begin(); it != myList.end(); it++);
	}
	end = clock();
	time_duration = ((double)end - start) / CLOCKS_PER_SEC;
	cout << "hlist:\t\t" << myList.size() << " elements, traversed for " << repeatTimes << " times in " << time_duration << " seconds" << endl;

	// testing std::list
	start = clock();
	for (int i = 0; i < repeatTimes; i++)
	{
		for (auto it = stdList.begin(); it != stdList.end(); it++);
	}
	end = clock();
	time_duration = ((double)end - start) / CLOCKS_PER_SEC;
	cout << "std::list:\t" << myList.size() << " elements, traversed for " << repeatTimes << " times in " << time_duration << " seconds" << endl;
	return;
}

void Benchmark_push(hlist<int> &myList, list<int> &stdList, int numsize, int mode)
{
	clock_t start, end;
	double time_duration;

	// clear the 2 lists first.
	myList.clear();
	stdList.clear();

	// generate random shuffle.
	int* random_shuffle = (int*)malloc(sizeof(int) * numsize);
	srand(time(NULL));
	for (int i = 0; i < numsize; i++)
		random_shuffle[i] = rand() % numsize;

	// testing mylist
	start = clock();
	for (int i = 0; i < numsize; i++)
	{
		// insert with random order and random front/back.
		if (mode && random_shuffle[i] % 2 == 0)
			myList.push_back(random_shuffle[i]);
		else
			myList.push_front(random_shuffle[i]);
	}
	end = clock();
	time_duration = ((double)end - start) / CLOCKS_PER_SEC;
	cout << "hist:\t\tinserted " << numsize << " elements in " << time_duration << " seconds. Mode: " << (mode ? "Shuffle" : "Normal") << endl;
	// testing std::list
	start = clock();
	for (int i = 0; i < numsize; i++)
	{
		// insert with random order and random front/back.
		if (mode && random_shuffle[i] % 2 == 0)
			stdList.push_back(random_shuffle[i]);
		else
			stdList.push_front(random_shuffle[i]);
	}
	end = clock();
	time_duration = ((double)end - start) / CLOCKS_PER_SEC;
	cout << "std::list:\tinserted " << numsize << " elements in " << time_duration <<" seconds. Mode: " << (mode ? "Shuffle" : "Normal") << endl;
	return;
}

void Benchmark_pop(hlist<int> &myList, list<int> &stdList, int mode)
{
	clock_t start, end;
	double time_duration;
	int myList_size = myList.size();
	int stdList_size = stdList.size();

	// generate random shuffle.
	int random_size = max(myList_size, stdList_size) + 1;
	int* random_shuffle = (int*)malloc(sizeof(int) * random_size);
	srand(time(NULL));
	for (int i = 0; i < random_size; i++)
		random_shuffle[i] = rand() % random_size;

	// testing mylist
	start = clock();
	for (int i = 0; i < myList_size; i++)
	{
		// pop with random order and random front/back.
		if (mode && random_shuffle[i] % 2 == 0)
			myList.pop_back();
		else
			myList.pop_front();
	}
	end = clock();
	ASSERT_TRUE(myList.empty() == true);
	time_duration = ((double)end - start) / CLOCKS_PER_SEC;
	cout << "hist:\t\tpopped " << myList_size << " elements in " << time_duration << " seconds. Mode: " << (mode ? "Shuffle" : "Normal") << endl;

	// testing std::list
	start = clock();
	for (int i = 0; i < stdList_size; i++)
	{
		// pop with random order and random front/back.
		if (mode && random_shuffle[i] % 2 == 0)
			stdList.pop_back();
		else
			stdList.pop_front();
	}
	end = clock();
	ASSERT_TRUE(stdList.empty() == true);
	time_duration = ((double)end - start) / CLOCKS_PER_SEC;
	cout << "std::list:\tpopped " << stdList_size << " elements in " << time_duration << " seconds. Mode: " << (mode ? "Shuffle" : "Normal") << endl;
	return;
}


int main() {
	std::set_new_handler(out_of_memory);
	hlist<int> myList;
	list<int> stdList;
	const int N = 10000000;
	Benchmark_push(myList, stdList, N, SHUFFLE);
	Benchmark_iter(myList, stdList, 200);
	Benchmark_pop(myList, stdList, SHUFFLE);
	Benchmark_push(myList, stdList, N, NORMAL);
	Benchmark_pop(myList, stdList, NORMAL);

	return 0;
}


void ListFixedBlockTest()
{
    hlist<int> myList;
    for (int i=0; i<MAX_BENCHMARK; i++)
        myList.push_back(123);
    myList.clear();
}

