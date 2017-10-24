#ifndef	POOL_POINTER_H
#define	POOL_POINTER_H

#include "MemoryNode.h"

#ifndef NULL
#define NULL	0
#endif

#ifdef	NULL_POINTER
#undef	NULL_POINTER
#endif
#define	NULL_POINTER	(static_cast <T *> (NULL))

#define Obj(P) (*P)

// NOTE:
//		1) The class used to replace T in the template below must be derived from RefCount
//		2) The object that PoolPointer "points to" must be dynamically allocated

template <class T>
	class PoolPointer
		{
		public:
			enum	Exceptions		{NullPointerException};

									PoolPointer			();
			explicit				PoolPointer			(T *);
									PoolPointer			(const PoolPointer<T> &);
			virtual					~PoolPointer		();
					bool			DoesNotExist	() const;
					bool			Exists			() const;
					PoolPointer <T> &	New				();
					PoolPointer <T> &	New				(const T &);
					T &				ObjectOf		()						throw (...);
			const	T &				ObjectOf		() const				throw (...);
					PoolPointer<T> &	PointsTo		(const PoolPointer<T> &);
					PoolPointer<T> &	SetTo			(const PoolPointer<T> &);
					void			SetToNull		();
					T &				operator *		()						throw (...);
			const	T &				operator *		() const				throw (...);
					T*				operator ->		()						throw (...);
			const	T*				operator ->		() const				throw (...);
					PoolPointer<T> &	operator =		(const PoolPointer<T> &);
					bool			operator ==		(const PoolPointer<T> &) const;
					bool			operator !		() const;
					bool			operator !=		(const PoolPointer<T> &) const;
									operator bool	() const;
		private:
					PoolPointer<T> &	Copy			(const PoolPointer<T> &);
					void			Decrement		();
					void			SetAndIncrement	(const T *);
					PoolPointer<T> &	SetTo			(const T *);
					PoolPointer<T> &	operator =		(const T *);

					T *				Ptr;
		};

template <class T>
	PoolPointer <T>::PoolPointer ():Ptr (NULL_POINTER)
		{
		}

template <class T>
	PoolPointer <T>::PoolPointer (T * p)
		{
		SetAndIncrement (p);
		}

template <class T>
	PoolPointer <T>::PoolPointer (const PoolPointer<T> & P)
		{
		SetAndIncrement (P.Ptr);
		}

template <class T>
	PoolPointer <T>::~PoolPointer ()
		{
		Decrement ();
		}

template <class T>
	inline bool PoolPointer<T>::DoesNotExist () const
		{
		return Ptr == NULL_POINTER;
		}

template <class T>
	inline bool PoolPointer<T>::Exists () const
		{
		return Ptr != NULL_POINTER;
		}

template <class T>
	inline PoolPointer <T> & PoolPointer<T>::New ()
		{
		Decrement ();
		SetAndIncrement (new T);
		return *this;
		}

template <class T>
	inline PoolPointer <T> & PoolPointer<T>::New (const T & t)
		{
		Decrement ();
		SetAndIncrement (new T (t));
		return *this;
		}

template <class T>
	inline T & PoolPointer<T>::ObjectOf ()
		{
		if (Ptr)
				return *Ptr;
			else
				throw NullPointerException;
		}

template <class T>
	inline const T & PoolPointer<T>::ObjectOf () const
		{
		if (Ptr)
				return *Ptr;
			else
				throw NullPointerException;
		}

template <class T>
	inline PoolPointer<T> & PoolPointer<T>::PointsTo (const PoolPointer<T> & P)
		{
		return Copy (P);
		}

template <class T>
	inline PoolPointer<T> & PoolPointer<T>::SetTo (const PoolPointer<T> & P)
		{
		return SetTo (P.Ptr);
		}

template <class T>
	inline void PoolPointer<T>::SetToNull ()
		{
		SetTo (NULL_POINTER);
		}

template <class T>
	inline T & PoolPointer<T>::operator * ()
		{
		return ObjectOf ();
		}

template <class T>
	inline const T & PoolPointer<T>::operator * () const
		{
		return ObjectOf ();
		}

template <class T>
	inline T * PoolPointer<T>::operator -> ()
		{
		if (Ptr)
				return Ptr;
			else
				throw NullPointerException;
		}

template <class T>
	inline const T * PoolPointer<T>::operator -> () const
		{
		if (Ptr)
				return Ptr;
			else
				throw NullPointerException;
		}

template <class T>
	inline PoolPointer<T> & PoolPointer<T>::operator = (const PoolPointer<T> & P)
		{
		if (this != &P)
				SetTo (P.Ptr);
			else;
		return *this;
		}

template <class T>
	inline bool PoolPointer<T>::operator == (const PoolPointer<T> & P) const
		{
		return Ptr == P.Ptr;
		}

template <class T>
	inline bool PoolPointer<T>::operator ! () const
		{
		return DoesNotExist ();
		}

template <class T>
	inline bool PoolPointer<T>::operator != (const PoolPointer<T> & P) const
		{
		return Ptr != P.Ptr;
		}

template <class T>
	inline PoolPointer<T>::operator bool () const
		{
		return Exists ();
		}

template <class T>
	inline PoolPointer<T> & PoolPointer<T>::Copy (const PoolPointer<T> & P)
		{
		return *this = P;
		}

template <class T>
	inline void PoolPointer<T>::Decrement ()
		{
		if (Ptr)
				(*Ptr).DownCount ();
			else;
		}

template <class T>
	inline void PoolPointer<T>::SetAndIncrement (const T * p)
		{
		if ((Ptr = (T *) (p)) != NULL_POINTER)
				(*Ptr).UpCount ();
			else;
		}

template <class T>
	inline PoolPointer<T> & PoolPointer<T>::SetTo (const T * p)
		{
		Decrement ();
		SetAndIncrement (p);
		return *this;
		}

template <class T>
	inline PoolPointer<T> & PoolPointer<T>::operator = (const T * p)
		{
		return SetTo (p);
		}

#endif
