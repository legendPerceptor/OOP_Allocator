#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <algorithm>
#include <Fault.h>
<<<<<<< HEAD
#include "hlist.h"

=======

#include "h_allocator.h"
#include <list>
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3
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

void read_testfile(string filename)
{
<<<<<<< HEAD
	freopen(filename.c_str(), "r", stdin);
	int vec_num, list_num;
	const int resize_num = 1000;
	cin >> vec_num;
	hvector<int> *vectors = (hvector<int>*) malloc(sizeof(hvector<int>) * vec_num);
	for (int i = 0; i < vec_num; i++)
	{
		size_t size;
		string type;
		cin >> size;
		cin >> type;
		transform(type.begin(), type.end(), type.begin(), ::tolower);
		/// TODO
		//if (type == "int")
		//	vectors[i] = hvector<int>(size);
		//else if (type == "float")
		//	vectors[i] = hvector<float>(size);
		//else if (type == "string")
		//	vectors[i] = hvector<string>(size);
	}

	cin >> list_num;
	for (int i = 0; i < list_num; i++)
	{
		/// TODO:
	}

	for (int i = 0; i < resize_num; i++)
	{

	}
=======
    freopen(filename.c_str(), "r", stdin);
    int vec_num, list_num;
    const int resize_num = 1000;
    cin >> vec_num;
    std::vector<int,hython::h_allocator<int>> *vectors = (std::vector<int,hython::h_allocator<int>>*) malloc(sizeof(std::vector<int,hython::h_allocator<int>>) * vec_num);
    for (int i = 0; i < vec_num; i++)
    {
        size_t size;
        string type;
        cin >> size;
        cin >> type;
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        /// TODO
        //if (type == "int")
        //	vectors[i] = std::vector<int,hython::h_allocator<int>>(size);
        //else if (type == "float")
        //	vectors[i] = hvector<float>(size);
        //else if (type == "string")
        //	vectors[i] = hvector<string>(size);
    }

    cin >> list_num;
    for (int i = 0; i < list_num; i++)
    {
        /// TODO:
    }

    for (int i = 0; i < resize_num; i++)
    {

    }
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3
}

void generate_testfile(int vectorCount = 15000, int max_size = 200)
{
<<<<<<< HEAD
	ofstream out_file("testcase.txt");
	out_file << vectorCount << endl;

	std::vector<list<int, h_allocator<int>>> hlists(vectorCount);
	for (int i = 0; i < vectorCount; i++)
	{
		hlists[i].resize(rand() % max_size + 1);
	}
	for (int i = 0; i < vectorCount; i++)
	{
		hlists[i].clear();
	}
=======
    ofstream out_file("testcase.txt");
    out_file << vectorCount << endl;

    std::vector<std::vector<int,hython::h_allocator<int>>> hlists(vectorCount);
    for (int i = 0; i < vectorCount; i++)
    {
        hlists[i].resize(rand() % max_size + 1);
    }
    for (int i = 0; i < vectorCount; i++)
    {
        hlists[i].clear();
    }
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3
}

void Benchmark_standard(int vec_num = 15000, int list_num = 100, int max_size = 200)
{
<<<<<<< HEAD
	chrono::duration<double> time_duration;

	vector<vector<int, h_allocator<int>>> hvectors(vec_num);
	vector<vector<int>> stdvectors(vec_num);

	vector<list<int, h_allocator<int>>> hlists(list_num);
	vector<list<int>> stdlists(list_num);

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < vec_num; i++)
	{
		hvectors[i].resize(rand() % max_size + 1);
		hvectors[i].resize(rand() % max_size + 1);
	}
	for (int i = 0; i < list_num; i++)
	{
		hlists[i].resize(rand() % max_size + 1);
	}
	for (int i = 0; i < vec_num; i++)
	{
		hvectors[i].clear();
	}
	auto end = chrono::high_resolution_clock::now();

	time_duration = end - start;
	cout << "MyLists:  " << vec_num << " lists, max size: " << max_size << ". Time: " << time_duration.count() << " seconds" << endl;

	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < vec_num; i++)
	{
		stdvectors[i].resize(rand() % max_size + 1);
		stdvectors[i].resize(rand() % max_size + 1);
	}
	for (int i = 0; i < list_num; i++)
	{
		stdlists[i].resize(rand() % max_size + 1);
	}
	for (int i = 0; i < vec_num; i++)
	{
		stdvectors[i].clear();
	}
	end = chrono::high_resolution_clock::now();
	time_duration = end - start;
	cout << "stdLists: " << vec_num << " lists, max size: " << max_size << ". Time: " << time_duration.count() << " seconds" << endl;
}

void Benchmark_iter(list<int, h_allocator<int>> &myList, list<int> &stdList, int repeatTimes)
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
	cout << "MyList:  " << myList.size() << " elements, repeated for " << repeatTimes << " times in " << time_duration.count() << " seconds" << endl;
=======
    chrono::duration<double> time_duration;

    vector<std::vector<int,hython::h_allocator<int>> > hvectors(vec_num);
    vector<vector<int>> stdvectors(vec_num);

    vector<std::vector<int,hython::h_allocator<int>>> hlists(list_num);
    vector<std::list<int>> stdlists(list_num);

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < vec_num; i++)
    {
        hvectors[i].resize(rand() % max_size + 1);
        hvectors[i].resize(rand() % max_size + 1);
    }
    for (int i = 0; i < list_num; i++)
    {
        hlists[i].resize(rand() % max_size + 1);
    }
    for (int i = 0; i < vec_num; i++)
    {
        hvectors[i].clear();
    }
    auto end = chrono::high_resolution_clock::now();

    time_duration = end - start;
    cout << "MyLists:  " << vec_num << " vectors, max size: " << max_size << ". Time: " << time_duration.count() << " seconds" << endl;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < vec_num; i++)
    {
        stdvectors[i].resize(rand() % max_size + 1);
        stdvectors[i].resize(rand() % max_size + 1);
    }
    for (int i = 0; i < list_num; i++)
    {
        stdlists[i].resize(rand() % max_size + 1);
    }
    for (int i = 0; i < vec_num; i++)
    {
        stdvectors[i].clear();
    }
    end = chrono::high_resolution_clock::now();
    time_duration = end - start;
    cout << "stdLists: " << vec_num << " vectors, max size: " << max_size << ". Time: " << time_duration.count() << " seconds" << endl;
}

void Benchmark_iter(std::list<int,hython::h_allocator<int>> &myList, list<int> &stdList, int repeatTimes)
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
    cout << "MyList:  " << myList.size() << " elements, repeated for " << repeatTimes << " times in " << time_duration.count() << " seconds" << endl;

    // testing std::list
    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < repeatTimes; i++)
    {
        for (auto it = stdList.begin(); it != stdList.end(); it++);
    }
    end = chrono::high_resolution_clock::now();
    time_duration = end - start;
    cout << "stdlist: " << myList.size() << " elements, repeated for " << repeatTimes << " times in " << time_duration.count() << " seconds" << endl;
    return;
}

void Benchmark_push(std::list<int,hython::h_allocator<int>> &myList, list<int> &stdList, int numsize)
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
    cout << "MyList:  inserted " << numsize << " elements in " << time_duration.count() << " seconds" << endl;

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
    cout << "stdList: inserted " << numsize << " elements in " << time_duration.count() << " seconds" << endl;
    return;
}

void Benchmark_pop(std::list<int,hython::h_allocator<int>> &myList, list<int> &stdList)
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
    cout << "MyList:  popped " << myList_size << " elements in " << time_duration.count() << " seconds" << endl;

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
    cout << "stdList: popped " << stdList_size << " elements in " << time_duration.count() << " seconds" << endl;
    return;
}


int main() {
    std::set_new_handler(out_of_memory);
    std::cout<<"INT:"<<sizeof(int)<<std::endl;
    std::cout<<"CHAR:"<<sizeof(char)<<std::endl;
    std::list<int,hython::h_allocator<int>> myList;
//    myList.push_back(1);
//    myList.push_back(2);
//    myList.push_back(3);
    for(int i=0;i<10;i++){
        myList.push_back(i);
    }
    list<int> stdList;
    const int N = 100000;
    for (int i = 1; i < 10; i++)
    {
        Benchmark_standard(10000 * i, 100 * i, 200 * i);
    }
    Benchmark_push(myList, stdList, N);
    Benchmark_iter(myList, stdList, 100);
    Benchmark_pop(myList, stdList);
    xalloc_stats();
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3

	// testing std::list
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < repeatTimes; i++)
	{
		for (auto it = stdList.begin(); it != stdList.end(); it++);
	}
	end = chrono::high_resolution_clock::now();
	time_duration = end - start;
	cout << "stdlist: " << myList.size() << " elements, repeated for " << repeatTimes << " times in " << time_duration.count() << " seconds" << endl;
	return;
}

<<<<<<< HEAD
void Benchmark_push(list<int, h_allocator<int>> &myList, list<int> &stdList, int numsize)
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
	cout << "MyList:  inserted " << numsize << " elements in " << time_duration.count() << " seconds" << endl;

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
	cout << "stdList: inserted " << numsize << " elements in " << time_duration.count() << " seconds" << endl;
	return;
}

void Benchmark_pop(list<int, h_allocator<int>> &myList, list<int> &stdList)
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
	cout << "MyList:  popped " << myList_size << " elements in " << time_duration.count() << " seconds" << endl;

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
	cout << "stdList: popped " << stdList_size << " elements in " << time_duration.count() << " seconds" << endl;
	return;
}


int main() {
	std::set_new_handler(out_of_memory);
	list<int, h_allocator<int>> myList;
	list<int> stdList;
	const int N = 1000000;
	for (int i = 1; i < 10; i++)
	{
		Benchmark_standard(10000 * i, 100 * i, 200 * i);
	}
	Benchmark_push(myList, stdList, N);
	Benchmark_iter(myList, stdList, 100);
	Benchmark_pop(myList, stdList);

	return 0;
}


void ListFixedBlockTest()
{
	hlist<int> myList;
	for (int i = 0; i < MAX_BENCHMARK; i++)
		myList.push_back(123);
	myList.clear();
=======

void ListFixedBlockTest()
{
    vector<int, hython::h_allocator<int>> myList;
    for (int i = 0; i < MAX_BENCHMARK; i++)
        myList.push_back(123);
    myList.clear();
>>>>>>> 34264074337c7fa91f6c2fb2387ce7bb200d11e3
}