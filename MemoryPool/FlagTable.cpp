#include <stdlib.h>

#include "FlagTable.h"

const int FlagTable::FlagsPerTable = CHAR_BIT * sizeof (BitTable);

FlagTable::FlagTable (int HowManyFlags)
	{
	Ptr = new BitTable [NumTables = (HowManyFlags + FlagsPerTable - 1) / FlagsPerTable];
	NumFlags = NumTables * FlagsPerTable;
	for (int i = 0; i < NumTables; i++)
		Ptr [i] = 0;
	}

void FlagTable::FreeFlag (int Which)
	{
	if (Which < NumFlags)
			{
			ldiv_t Result = ldiv (Which, FlagsPerTable);
			Ptr [Result.quot] &= ~(1UL << Result.rem);
			}
		else
			throw BadFlagNumber;
	}

int FlagTable::GetUnusedFlag ()
	{
	for (int i = 0; (i < NumTables) && (Ptr [i] == AllBitsSet); i++);
	if (i < NumTables)
			for (int j = 0; j < FlagsPerTable; j++)
				if (!(Ptr [i] & (1UL << j)))
						{
						Ptr [i] |= (1UL << j);
						return (i * FlagsPerTable) + j;
						}
					else;
		else;
	throw NoFreeBlocks;
	}
