//
// Created by Hython on 2018/6/4.
//

#include <cstring>
#include "xallocator.h"
#include "Allocator.h"
#include "Fault.h"
#include <iostream>
using std::cout;
using std::endl;
namespace hython {

	// The default configuration is to use automatic init and destroy for convenience
	// You can #undef AUTOMATIC_XALLOCATOR_INIT_DESTROY to disable this feature
#ifndef CHAR_BIT
#define CHAR_BIT	8
#endif
#ifdef _WIN32
	static CRITICAL_SECTION _criticalSection;
#else
	/// sjn changed.
#include <pthread.h>
	static pthread_mutex_t mutex;
	static pthread_mutexattr_t attr;
#endif
	static BOOL _xallocInitialized = FALSE;
#ifdef AUTOMATIC_XALLOCATOR_INIT_DESTROY
	INT XallocInitDestroy::refCount = 0;

	XallocInitDestroy::XallocInitDestroy() {
		// Track how many static instances of XallocInitDestroy are created
		if (refCount++ == 0)
			xalloc_init();
	}

	XallocInitDestroy::~XallocInitDestroy() {
		// Last static instance to have destructor called?
		if (--refCount == 0)
			xalloc_destroy();
	}

#endif    // AUTOMATIC_XALLOCATOR_INIT_DESTROY

	// Default to enable STATIC_POOLS
#ifdef STATIC_POOLS
	// Update this section as necessary if you want to use static memory pools.
	// See also xalloc_init() and xalloc_destroy() for additional updates required.
#define MAX_ALLOCATORS    12
#define MAX_BLOCKS        32

	// Create static storage for each static allocator instance
	CHAR _allocator8[sizeof(AllocatorPool<CHAR[8], MAX_BLOCKS>)];
	CHAR _allocator16[sizeof(AllocatorPool<CHAR[16], MAX_BLOCKS>)];
	CHAR _allocator32[sizeof(AllocatorPool<CHAR[32], MAX_BLOCKS>)];
	CHAR _allocator64[sizeof(AllocatorPool<CHAR[64], MAX_BLOCKS>)];
	CHAR _allocator128[sizeof(AllocatorPool<CHAR[128], MAX_BLOCKS>)];
	CHAR _allocator256[sizeof(AllocatorPool<CHAR[256], MAX_BLOCKS>)];
	CHAR _allocator396[sizeof(AllocatorPool<CHAR[396], MAX_BLOCKS>)];
	CHAR _allocator512[sizeof(AllocatorPool<CHAR[512], MAX_BLOCKS>)];
	CHAR _allocator768[sizeof(AllocatorPool<CHAR[768], MAX_BLOCKS>)];
	CHAR _allocator1024[sizeof(AllocatorPool<CHAR[1024], MAX_BLOCKS>)];
	CHAR _allocator2048[sizeof(AllocatorPool<CHAR[2048], MAX_BLOCKS>)];
	CHAR _allocator4096[sizeof(AllocatorPool<CHAR[4096], MAX_BLOCKS>)];

	// Array of pointers to all allocator instances
	static Allocator *_allocators[MAX_ALLOCATORS];

#else
#define MAX_ALLOCATORS  15
	static Allocator* _allocators[MAX_ALLOCATORS];
#endif    // STATIC_POOLS

	/// Returns the next higher powers of two. For instance, pass in 27 and
	/// the value returned would be 32.
	/// @param[in] k - numeric value to compute the next higher power of two.
	/// @return	The next higher power of two based on the input k.
	template <class T>
	T nexthigher(T k)
	{
		k--;
		for (size_t i = 1; i < sizeof(T)*CHAR_BIT; i <<= 1)
			k |= (k >> i);
		return k + 1;
	}

	/// Create the xallocator lock. Call only one time at startup.
	static void lock_init()
	{
		/// sjn changed.
		BOOL success;
#ifdef _WIN32
		success = InitializeCriticalSectionAndSpinCount(&_criticalSection, 0x00000400);
#else
		BOOL result1 = pthread_mutexattr_init(&attr);
		BOOL result2 = pthread_mutex_init(&mutex, &attr);
		success = (result1 == 0) && (result2 == 0);
#endif
		ASSERT_TRUE(success != 0);
		_xallocInitialized = TRUE;
	}

	/// Destroy the xallocator lock.
	static void lock_destroy()
	{
		/// sjn changed.
#ifdef _WIN32
		DeleteCriticalSection(&_criticalSection);
#else
		BOOL result = pthread_mutex_destroy(&mutex);
		ASSERT_TRUE(result == 0);
#endif
		_xallocInitialized = FALSE;
	}

	/// Lock the shared resource.
	static inline void lock_get()
	{
		/// sjn changed.
		if (_xallocInitialized == FALSE)
			return;
#ifdef _WIN32
		EnterCriticalSection(&_criticalSection);
#else
		// note: there are 2 versions of lock in *nix. mutex_lock will wait for the lock,
		// while mutex_trylock will throw return an error code.
		// I think using mutex_lock is more appropriate.
		BOOL result = pthread_mutex_lock(&mutex);
		// BOOL result = pthread_mutex_trylock(&mutex);
		ASSERT_TRUE(result == 0);
#endif
	}

	/// Unlock the shared resource.
	static inline void lock_release()
	{
		/// sjn changed.
		if (_xallocInitialized == FALSE)
			return;
#ifdef _WIN32
		LeaveCriticalSection(&_criticalSection);
#else
		BOOL result = pthread_mutex_unlock(&mutex);
		ASSERT_TRUE(result == 0);
#endif
	}


	void xalloc_destroy() {
		lock_get();

#ifdef STATIC_POOLS
		for (INT i = 0; i < MAX_ALLOCATORS; i++) {
			_allocators[i]->~Allocator();
			_allocators[i] = nullptr;
		}
#else
		for (INT i = 0; i < MAX_ALLOCATORS; i++)
		{
			if (_allocators[i] == 0)
				break;
			delete _allocators[i];
			_allocators[i] = 0;
		}
#endif

		lock_release();

		lock_destroy();
	}

	/// This function must be called exactly one time *before* any other xallocator
	/// API is called. XallocInitDestroy constructor calls this function automatically.
	void xalloc_init()
	{
		lock_init();

#ifdef STATIC_POOLS
		// For STATIC_POOLS mode, the allocators must be initialized before any other
		// static user class constructor is run. Therefore, use placement new to initialize
		// each allocator into the previously reserved static memory locations.
		new (&_allocator8) AllocatorPool<CHAR[8], MAX_BLOCKS>();
		new (&_allocator16) AllocatorPool<CHAR[16], MAX_BLOCKS>();
		new (&_allocator32) AllocatorPool<CHAR[32], MAX_BLOCKS>();
		new (&_allocator64) AllocatorPool<CHAR[64], MAX_BLOCKS>();
		new (&_allocator128) AllocatorPool<CHAR[128], MAX_BLOCKS>();
		new (&_allocator256) AllocatorPool<CHAR[256], MAX_BLOCKS>();
		new (&_allocator396) AllocatorPool<CHAR[396], MAX_BLOCKS>();
		new (&_allocator512) AllocatorPool<CHAR[512], MAX_BLOCKS>();
		new (&_allocator768) AllocatorPool<CHAR[768], MAX_BLOCKS>();
		new (&_allocator1024) AllocatorPool<CHAR[1024], MAX_BLOCKS>();
		new (&_allocator2048) AllocatorPool<CHAR[2048], MAX_BLOCKS>();
		new (&_allocator4096) AllocatorPool<CHAR[4096], MAX_BLOCKS>();

		// Populate allocator array with all instances
		_allocators[0] = (Allocator*)&_allocator8;
		_allocators[1] = (Allocator*)&_allocator16;
		_allocators[2] = (Allocator*)&_allocator32;
		_allocators[3] = (Allocator*)&_allocator64;
		_allocators[4] = (Allocator*)&_allocator128;
		_allocators[5] = (Allocator*)&_allocator256;
		_allocators[6] = (Allocator*)&_allocator396;
		_allocators[7] = (Allocator*)&_allocator512;
		_allocators[8] = (Allocator*)&_allocator768;
		_allocators[9] = (Allocator*)&_allocator1024;
		_allocators[10] = (Allocator*)&_allocator2048;
		_allocators[11] = (Allocator*)&_allocator4096;
#endif
	}





	/// Stored a pointer to the allocator instance within the block region.
	///	a pointer to the client's area within the block.
	/// @param[in] block - a pointer to the raw memory block.
	///	@param[in] size - the client requested size of the memory block.
	/// @return	A pointer to the client's address within the raw memory block.
	static inline void *set_block_allocator(void* block, Allocator* allocator)
	{
		// Cast the raw block memory to a Allocator pointer
		Allocator** pAllocatorInBlock = static_cast<Allocator**>(block);

		// Write the size into the memory block
		*pAllocatorInBlock = allocator;

		// Advance the pointer past the Allocator* block size and return a pointer to
		// the client's memory region
		return ++pAllocatorInBlock;
	}

	/// Gets the size of the memory block stored within the block.
	/// @param[in] block - a pointer to the client's memory block.
	/// @return	The original allocator instance stored in the memory block.
	static inline Allocator* get_block_allocator(void* block)
	{
		// Cast the client memory to a Allocator pointer
		Allocator** pAllocatorInBlock = static_cast<Allocator**>(block);

		// Back up one Allocator* position to get the stored allocator instance
		pAllocatorInBlock--;

		// Return the allocator instance stored within the memory block
		return *pAllocatorInBlock;
	}

	/// Returns the raw memory block pointer given a client memory pointer.
	/// @param[in] block - a pointer to the client memory block.
	/// @return	A pointer to the original raw memory block address.
	static inline void *get_block_ptr(void* block)
	{
		// Cast the client memory to a Allocator* pointer
		Allocator** pAllocatorInBlock = static_cast<Allocator**>(block);

		// Back up one Allocator* position and return the original raw memory block pointer
		return --pAllocatorInBlock;
	}

	/// Returns an allocator instance matching the size provided
	/// @param[in] size - allocator block size
	/// @return Allocator instance handling requested block size or NULL
	/// if no allocator exists.
	static inline Allocator* find_allocator(size_t size)
	{
		for (INT i = 0; i < MAX_ALLOCATORS; i++)
		{
			if (_allocators[i] == nullptr)
				break;

			if (_allocators[i]->GetBlockSize() == size)
				return _allocators[i];
		}

		return nullptr;
	}

	/// Insert an allocator instance into the array
	/// @param[in] allocator - An allocator instance
	static inline void insert_allocator(Allocator* allocator)
	{
		for (INT i = 0; i < MAX_ALLOCATORS; i++)
		{
			if (_allocators[i] == 0)
			{
				_allocators[i] = allocator;
				return;
			}
		}

		ASSERT();
	}


	Allocator* xallocator_get_allocator(size_t size)
	{
		// Based on the size, find the next higher powers of two value.
		// Add sizeof(Allocator*) to the requested block size to hold the size
		// within the block memory region. Most blocks are powers of two,
		// however some common allocator block sizes can be explicitly defined
		// to minimize wasted storage. This offers application specific tuning.
		size_t blockSize = size + sizeof(Allocator*);
		if (blockSize > 256 && blockSize <= 396)
			blockSize = 396;
		else if (blockSize > 512 && blockSize <= 768)
			blockSize = 768;
		else
			blockSize = nexthigher<size_t>(blockSize);

		Allocator* allocator = find_allocator(blockSize);

#ifdef STATIC_POOLS
		ASSERT_TRUE(allocator != NULL);
#else
		// If there is not an allocator already created to handle this block size
		if (allocator == NULL)
		{
			// Create a new allocator to handle blocks of the size required
			allocator = new Allocator(blockSize, 0, 0, "xallocator");

			// Insert allocator into array
			insert_allocator(allocator);
		}
#endif

		return allocator;
	}

	/// Allocates a memory block of the requested size. The blocks are created from
	///	the fixed block allocators.
	///	@param[in] size - the client requested size of the block.
	/// @return	A pointer to the client's memory block.
	void *xmalloc(size_t size)
	{
		lock_get();

		// Allocate a raw memory block
		Allocator* allocator = xallocator_get_allocator(size);
		void* blockMemoryPtr = allocator->Allocate(sizeof(Allocator*) + size);

		lock_release();

		// Set the block Allocator* within the raw memory block region
		void* clientsMemoryPtr = set_block_allocator(blockMemoryPtr, allocator);
		return clientsMemoryPtr;
	}

	/// Frees a memory block previously allocated with xalloc. The blocks are returned
	///	to the fixed block allocator that originally created it.
	///	@param[in] ptr - a pointer to a block created with xalloc.
	void xfree(void* ptr)
	{
		if (ptr == 0)
			return;

		// Extract the original allocator instance from the caller's block pointer
		Allocator* allocator = get_block_allocator(ptr);

		// Convert the client pointer into the original raw block pointer
		void* blockPtr = get_block_ptr(ptr);

		lock_get();

		// Deallocate the block
		allocator->Deallocate(blockPtr);

		lock_release();
	}

	/// Reallocates a memory block previously allocated with xalloc.
	///	@param[in] ptr - a pointer to a block created with xalloc.
	///	@param[in] size - the client requested block size to create.
	void *xrealloc(void *oldMem, size_t size)
	{
		if (oldMem == 0)
			return xmalloc(size);

		if (size == 0)
		{
			xfree(oldMem);
			return 0;
		}
		else
		{
			// Create a new memory block
			void* newMem = xmalloc(size);
			if (newMem != 0)
			{
				// Get the original allocator instance from the old memory block
				Allocator* oldAllocator = get_block_allocator(oldMem);
				size_t oldSize = oldAllocator->GetBlockSize() - sizeof(Allocator*);

				// Copy the bytes from the old memory block into the new (as much as will fit)
				memcpy(newMem, oldMem, (oldSize < size) ? oldSize : size);

				// Free the old memory block
				xfree(oldMem);

				// Return the client pointer to the new memory block
				return newMem;
			}
			return 0;
		}
	}

	void xalloc_stats()
	{
		lock_get();

		for (INT i = 0; i < MAX_ALLOCATORS; i++)
		{
			if (_allocators[i] == 0)
				break;

			if (_allocators[i]->GetName() != NULL)
				cout << _allocators[i]->GetName();
			cout << " Block Size: " << _allocators[i]->GetBlockSize();
			cout << " Block Count: " << _allocators[i]->GetBlockCount();
			cout << " Blocks In Use: " << _allocators[i]->GetBlocksInUse();
			cout << endl;
		}

		lock_release();
	}
}