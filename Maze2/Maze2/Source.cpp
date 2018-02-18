#include <iostream>
#include <time.h>
#include <string>
#include <ctime>
#include <conio.h>
#include <windows.h>

#define mazefileloc "maze.txt"
#define MAXROW 50
#define MAXColl 50

#define True 1
#define False 0

struct Smaze{
    char maze[MAXROW][MAXColl];
	int mazevizit[MAXROW][MAXColl];
	int minYol;
	int finRow;
	int FinColl;
    int row;
    int coll;
    int StartRow;
    int StartColl;
};
struct Sstack{
    int row;
    int coll;
};
struct Stack {
    Sstack member[(MAXROW*MAXColl)/3];
    int number;
};

using std::string ;

void mazeHareket(Smaze m,int row,int coll);

void mazeYaz(Smaze m);

void mazeBull(int row,int coll,int deep,int y�n);

int Kapal�Yolmu(int row,int coll,int y�n);

void kapal�yolT�ka(int row,int coll);

void mazeisaretle(int row,int coll);

Smaze maze;

int main()
{
	for (int i = 0; i < MAXROW; i++)
	{
		for (int j = 0; j < MAXColl; j++)
		{
			maze.mazevizit[i][j] = ((MAXROW*MAXColl)/2);
		}
	}
	maze.minYol = ((MAXROW*MAXColl)/2);
	maze.finRow = 0;
	maze.FinColl = 0;

	  FILE *MazeFile;
    MazeFile = fopen(mazefileloc,"r");
    int RowIndex = -1;
    int CollIndex = 0;
	fscanf(MazeFile,"%d %d",&maze.StartRow,&maze.StartColl);
    char a = 'a';
    int fc = 0;
    while(!feof(MazeFile))
    {
        fscanf(MazeFile, "%c", &a);
        CollIndex = 0;
        while('\n' != a)
        {
            
            maze.maze[RowIndex][CollIndex] = a;
            CollIndex++;
            if(feof(MazeFile))
               break;
            else
                fscanf(MazeFile, "%c", &a);
            if(fc < CollIndex)
                fc = CollIndex;
        }
        RowIndex++;
    }
    fclose(MazeFile);
    maze.row = RowIndex-1;
    maze.coll = fc;
    
	mazeYaz(maze);

	mazeBull(maze.StartRow,maze.StartColl,0,0);

	mazeisaretle(maze.finRow,maze.FinColl);

	mazeYaz(maze);

	scanf("%d");
    return 0;
}

void mazeBull(int row,int coll,int deep,int y�n)
{
	if(maze.mazevizit[row][coll] == -1)
		return;
	if(maze.maze[row+1][coll] == 'f' || maze.maze[row-1][coll] == 'f' || maze.maze[row][coll+1] == 'f' || maze.maze[row][coll-1] == 'f')
	{
		if(maze.minYol>deep)
		{maze.minYol = deep; maze.finRow = row;maze.FinColl = coll;}
		return;
	}
	if(True == Kapal�Yolmu(row,coll,y�n))
	{
		maze.mazevizit[row][coll] = -1;
		return;
	}
	if(maze.maze[row][coll] == '*' || maze.mazevizit[row][coll] < deep || maze.minYol < deep)
		return;

	Sleep(5);

	mazeHareket(maze,row,coll);

	if(maze.maze[row][coll] == ' ' && maze.minYol > deep && maze.mazevizit[row][coll] > deep && maze.mazevizit[row][coll] != -1)
		maze.mazevizit[row][coll] = deep;
	if(y�n != 2)
	mazeBull(row,coll-1,deep+1,1);
	if(y�n != 1)
	mazeBull(row,coll+1,deep+1,2);
	if(y�n != 4)
	mazeBull(row-1,coll,deep+1,3);
	if(y�n != 3)
	mazeBull(row+1,coll,deep+1,4);
	
	return;
}

int Kapal�Yolmu(int row,int coll,int y�n)
{
	if(y�n == 1 && maze.maze[row][coll-1] == '*' && maze.maze[row+1][coll] == '*' && maze.maze[row-1][coll] == '*')
		return True;
	else if(y�n == 2 && maze.maze[row][coll+1] == '*' && maze.maze[row+1][coll] == '*' && maze.maze[row-1][coll] == '*')
		return True;
	else if(y�n == 3 && maze.maze[row-1][coll] == '*' && maze.maze[row][coll-1] == '*' && maze.maze[row][coll+1] == '*')
		return True;
	else if(y�n == 4 && maze.maze[row+1][coll] == '*' && maze.maze[row][coll-1] == '*' && maze.maze[row][coll+1] == '*')
		return True;
	else
		return False;
}

void mazeYaz(Smaze m)
{
	system("CLS");
	printf("\n");
	for(int i = 0 ;i < m.row;i++)
    {
        for (int j = 0; j< m.coll; j++) {
            printf("%c",m.maze[i][j]);
        }
        printf("\n");
    }
	printf("\n");
}

void mazeHareket(Smaze m,int row,int coll)
{
	system("CLS");
	printf("\n");
	for(int i = 0 ;i < m.row;i++)
    {
        for (int j = 0; j< m.coll; j++) {
			if(i == row && j == coll)
				printf("o");
			else
				printf("%c",m.maze[i][j]);

        }
        printf("\n");
    }
	printf("\n");
}

void mazeisaretle(int row,int coll)
{
	if(maze.mazevizit[row][coll] == 0)
		return;
	
}