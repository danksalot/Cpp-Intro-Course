#ifndef MEMORY_NODE_H
#define MEMORY_NODE_H

template <class T>
	class MemoryNode: public T
		{
		public:
							MemoryNode		();
							~MemoryNode		();
					int		GetFlagNumber	() const;
					void	SetFlagNumber	(int);
					void	SetPool			(const void *);
					void	UpCount			();
					void	DownCount		();
		private:
							MemoryNode		(const MemoryNode <T> &);
					void	operator =		(const MemoryNode <T> &);
					int		FlagNumber;
					void *	pPool;
					int		References;
		};

template <class T>
	inline MemoryNode <T>::MemoryNode ()
		{
		FlagNumber = -1;
		}

template <class T>
	inline MemoryNode <T>::MemoryNode (const MemoryNode <T> &)
		{
		}

template <class T>
	inline MemoryNode <T>::~MemoryNode ()
		{
		}

template <class T>
	inline void MemoryNode <T>::operator = (const MemoryNode <T> &)
		{
		}

template <class T>
	inline int MemoryNode <T>::GetFlagNumber () const
		{
		return FlagNumber;
		}

template <class T>
	inline void MemoryNode <T>::SetFlagNumber (int Which)
		{
		FlagNumber = Which;
		}

template <class T>
	inline void MemoryNode <T>::SetPool (const void * Ptr)
		{
		pPool = const_cast <void *> (Ptr);
		}

template <class T>
	inline void MemoryNode <T>::UpCount ()
		{
		++References;
		}

template <class T>
	inline void MemoryNode <T>::DownCount ()
		{
		if (--References == 0)
				(*reinterpret_cast <MemoryPool <T> *>(pPool)).AllocationFlags.FreeFlag (FlagNumber);
			else;
		}

#endif
