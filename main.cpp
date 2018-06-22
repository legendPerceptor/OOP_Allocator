#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <limits>
#include <fstream>
#include <Fault.h>
#include "hlist.h"
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

void generate_testfile(int vectorCount = 15000, int max_size = 200)
{
	ofstream out_file("testcase.txt");
	out_file << vectorCount << endl;

	std::vector<hlist<int>> hlists(vectorCount);
	for (int i = 0; i < vectorCount; i++)
	{
		hlists[i].resize(rand() % max_size + 1);
	}
	for (int i = 0; i < vectorCount; i++)
	{
		hlists[i].clear();
	}
}

void Benchmark_standard(int count = 15000, int max_size = 200)
{
	chrono::duration<double> time_duration;
	vector<hlist<int>> hlists(count);
	vector<list<int>> stdlists(count);

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < count; i++)
	{
		hlists[i].resize(rand() % max_size + 1);
	}
	for (int i = 0; i < count; i++)
	{
		hlists[i].clear();
	}
	auto end = chrono::high_resolution_clock::now();

	time_duration = end - start;
	cout << "MyLists:\t" << count << " lists, max size: " << max_size << ". Time: " << time_duration.count() << " seconds" << endl;
	
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < count; i++)
	{
		stdlists[i].resize(rand() % max_size + 1);
	}
	for (int i = 0; i < count; i++)
	{
		stdlists[i].clear();
	}
	end = chrono::high_resolution_clock::now();
	time_duration = end - start;
	cout << "stdLists:\t" << count << " lists, max size: " << max_size << ". Time: " << time_duration.count() << " seconds" << endl;
}

void Benchmark_iter(hlist<int> &myList, list<int> &stdList, int repeatTimes)
{
	chrono::duration<double> time_duration;

	auto start = chrono::high_resolution_clock::now();
	// testing mylist
	for (int i = 0; i < repeatTimes; i++)
	{
		for (auto it = myList.begin(); it != myList.end(); it++);
	}
	auto end = chrono::high_resolution_clock::now();
	time_duration = end - start;
	cout << "MyList :\t" << myList.size() << " elements, repeated for " << repeatTimes << " times in " << time_duration.count() << " seconds" << endl;

	// testing std::list
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < repeatTimes; i++)
	{
		for (auto it = stdList.begin(); it != stdList.end(); it++);
	}
	end = chrono::high_resolution_clock::now();
	time_duration = end - start;
	cout << "stdlist:\t" << myList.size() << " elements, repeated for " << repeatTimes << " times in " << time_duration.count() << " seconds" << endl;
	return;
}

void Benchmark_push(hlist<int> &myList, list<int> &stdList, int numsize)
{
	chrono::duration<double> time_duration;

	// clear the 2 lists first.
	myList.clear();
	stdList.clear();

	// generate random shuffle.
	int* random_shuffle = (int*)malloc(sizeof(int) * numsize);
	srand(time(NULL));
	for (int i = 0; i < numsize; i++)
		random_shuffle[i] = rand() % numsize;

	// testing mylist
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < numsize; i++)
	{
		// insert with random order and random front/back.
		if (random_shuffle[i] % 2 == 0)
			myList.push_back(random_shuffle[i]);
		else
			myList.push_front(random_shuffle[i]);
	}
	auto end = chrono::high_resolution_clock::now();
	time_duration = end - start;
	cout << "MyList :\tinserted " << numsize << " elements in " << time_duration.count() << " seconds" << endl;

	// testing std::list
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < numsize; i++)
	{
		// insert with random order and random front/back.
		if (random_shuffle[i] % 2 == 0)
			stdList.push_back(random_shuffle[i]);
		else
			stdList.push_front(random_shuffle[i]);
	}
	end = chrono::high_resolution_clock::now();
	time_duration = end - start;
	cout << "stdlist:\tinserted " << numsize << " elements in " << time_duration.count() << " seconds" << endl;
	return;
}

void Benchmark_pop(hlist<int> &myList, list<int> &stdList)
{
	chrono::duration<double> time_duration;
	int myList_size = myList.size();
	int stdList_size = stdList.size();

	// generate random shuffle.
	int random_size = max(myList_size, stdList_size) + 1;
	int* random_shuffle = (int*)malloc(sizeof(int) * random_size);
	srand(time(NULL));
	for (int i = 0; i < random_size; i++)
		random_shuffle[i] = rand() % random_size;

	// testing mylist
	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < myList_size; i++)
	{
		// pop with random order and random front/back.
		if (random_shuffle[i] % 2 == 0)
			myList.pop_back();
		else
			myList.pop_front();
	}
	auto end = chrono::high_resolution_clock::now();
	ASSERT_TRUE(myList.empty() == true);
	time_duration = end - start;
	cout << "MyList :\tpopped " << myList_size << " elements in " << time_duration.count() << " seconds" << endl;

	// testing std::list
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < stdList_size; i++)
	{
		// pop with random order and random front/back.
		if (random_shuffle[i] % 2 == 0)
			stdList.pop_back();
		else
			stdList.pop_front();
	}
	end = chrono::high_resolution_clock::now();
	ASSERT_TRUE(stdList.empty() == true);
	time_duration = end - start;
	cout << "stdlist:\tpopped " << stdList_size << " elements in " << time_duration.count() << " seconds" << endl;
	return;
}


int main() {
	std::set_new_handler(out_of_memory);
	hlist<int> myList;
	list<int> stdList;
	const int N = 10000000;
	for (int i = 1; i <= 5; i++)
	{
		Benchmark_standard(10000 * i, 200 * i);
	}
	Benchmark_push(myList, stdList, N);
	Benchmark_iter(myList, stdList, 20);
	Benchmark_pop(myList, stdList);

	return 0;
}


void ListFixedBlockTest()
{
	hlist<int> myList;
	for (int i = 0; i < MAX_BENCHMARK; i++)
		myList.push_back(123);
	myList.clear();
}

