#ifndef	POOL_REF_COUNT_H
#define	POOL_REF_COUNT_H

#include <iostream>

using namespace std;

#include "MemoryPool.h"

class PoolRefCount
	{
	public:
						PoolRefCount	();
		virtual			~PoolRefCount	();
				void	UpCount		();
				void	DownCount	();
		static	void	SetPool			(const void *);
	private:
		static	void *	pPool;
				int		References;
	};

inline void PoolRefCount::UpCount ()
	{
	++References;
	}

inline void PoolRefCount::DownCount ()
	{
	if (--References == 0)
			{
			cout << "Deleting Item" << endl;
			(*reinterpret_cast <MemoryPool <T> *>(pPool)).AllocationFlags.FreeFlag (FlagNumber);
			}
		else;
	}

template <class T>
	inline void PoolRefCount::SetPool (const void * Ptr)
		{
		pPool = const_cast <void *> (Ptr);
		}

#endif
