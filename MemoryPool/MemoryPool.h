#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include "FlagTable.h"
#include "MemoryNode.h"
#include "PoolPointer.h"

#define POOL_POINTER(a) PoolPointer <MemoryNode <a> >

template <class T>
	class MemoryPool
		{
			friend	MemoryNode <T>;
		public:
										MemoryPool			();
										MemoryPool			(int);
										~MemoryPool			();
			POOL_POINTER (T)			GetMemoryBlock		();
			POOL_POINTER (T)			GetMemoryBlock		(const T &);
			void						FreeMemoryBlock		(POOL_POINTER (T) &);
		private:
			void						ReleaseMemoryBlock	(const MemoryNode <T> *);
										MemoryPool			(const MemoryPool <T> &);
			void						operator =			(const MemoryPool <T> &);
			void						SetPtr				();
			MemoryNode <T> *			Ptr;
			FlagTable					AllocationFlags;
		};

template <class T>
	inline MemoryPool<T>::MemoryPool (): AllocationFlags ()
		{
		SetPtr ();
		}

template <class T>
	inline MemoryPool<T>::MemoryPool (int HowManyUnits): AllocationFlags (HowManyUnits)
		{
		SetPtr ();
		}

template <class T>
	inline MemoryPool<T>::MemoryPool (const MemoryPool <T> &)
		{
		}

template <class T>
	inline MemoryPool<T>::~MemoryPool ()
		{
		delete [] Ptr;
		}

template <class T>
	inline void MemoryPool<T>::operator = (const MemoryPool <T> &)
		{
		}

template <class T>
	inline POOL_POINTER (T) MemoryPool<T>::GetMemoryBlock ()
		{
		POOL_POINTER (T) P (&Ptr [AllocationFlags.GetUnusedFlag ()]);
		(*P).Init ();
		return P;
		}

template <class T>
	inline POOL_POINTER (T) MemoryPool<T>::GetMemoryBlock (const T & Base)
		{
		POOL_POINTER (T) P (&Ptr [AllocationFlags.GetUnusedFlag ()]);
		(*P).Init (Base);
		return P;
		}

template <class T>
	inline void MemoryPool<T>::FreeMemoryBlock (POOL_POINTER (T) & P)
		{
		P.SetToNull ();
		}

template <class T>
	inline void MemoryPool<T>::ReleaseMemoryBlock (const MemoryNode <T> * P)
		{
		AllocationFlags.FreeFlag ((*P).GetFlagNumber ());
		}

template <class T>
	inline void MemoryPool<T>::SetPtr ()
		{
		Ptr = new MemoryNode <T> [AllocationFlags.HowMany ()];
		for (int i = 0; i < AllocationFlags.HowMany (); i++)
			{
			Ptr [i].SetPool (this);
			Ptr [i].SetFlagNumber (i);
			}
		}

#endif
