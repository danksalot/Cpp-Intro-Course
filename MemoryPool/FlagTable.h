#ifndef FLAG_TABLE_H
#define FLAG_TABLE_H

#include <cLimits>

class FlagTable
	{
	public:
		enum				Constants		{AllBitsSet = ULONG_MAX};
		enum				Exceptions		{NoFreeBlocks, BadFlagNumber};
		typedef				unsigned long	BitTable;
							FlagTable		(int = CHAR_BIT * sizeof (BitTable));
							~FlagTable		();
		void				FreeFlag		(int);
		int					GetUnusedFlag	();
		int					HowMany			() const;
	private:
							FlagTable		(const FlagTable &);
		void				operator =		(const FlagTable &);
		BitTable *			Ptr;
		int					NumFlags;
		int					NumTables;
		static const int	FlagsPerTable;
	};

inline FlagTable::FlagTable (const FlagTable &)
	{
	}

inline FlagTable::~FlagTable ()
	{
	delete [] Ptr;
	}

inline int FlagTable::HowMany () const
	{
	return NumFlags;
	}

inline void FlagTable::operator = (const FlagTable &)
	{
	}

#endif
