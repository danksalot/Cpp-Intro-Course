#include "Functions.h"

extern int    i;
extern int    j;
extern int    Cost;
extern int    NumNodes;
extern char   CurrentPath;
extern int    MinCost;
extern char   MinPath;
extern bool   Visited;
extern ifstream   SourceFile;

void FindCost (int CurrentNode, int CurrentCost, int CurrentDepth)
  {
  Visited [CurrentNode] = true;
  for (i = 0; i < NumNodes; i++)
      if (!Visited [i] && (Cost [CurrentNode] [i] >= 0))
              {
              int TempCost (CurrentCost + Cost [CurrentNode] [i]);
              if (TempCost < MinCost)
                      {
                      CurrentPath [CurrentDepth] = i + 'A';
                      FindCost (i, TempCost, CurrentDepth + 1);
                      }
                  else;
              }
          else;
  for (i = 0; Visited [i] && (i < NumNodes); i++);
  if (i == NumNodes)
          {
          MinCost = CurrentCost;
          memcpy (MinPath, CurrentPath, NumNodes);
          }
      else;
  Visited [CurrentNode] = false;
  }

void PopulateTable ()
  {
  while (SourceFile.get () != EOF)
      {
      SourceFile.unget ();
      char Origin;
      char Destin;
      int Dist;
      SourceFile >> Origin;
      SourceFile >> Destin;
      SourceFile >> Dist;
      Cost  [(Origin - '0') - 17] [(Destin - '0') - 17] = Dist;
      }
  }

void PrintTable ()
  {
  for (i = 0; i < NumNodes; i++)
      cout << "\t" << static_cast <char> (i + 65);
  cout << endl;
  for (i = 0; i < NumNodes; i++)
      {
      cout << static_cast <char> (i + 65)  << "\t";
      for (j = 0; j < NumNodes; j++)
          cout << Cost [i] [j] << '\t';
      cout << endl;
      }
  }
