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

void mazeBull(int row,int coll,int deep,int yön);

int KapalýYolmu(int row,int coll,int yön);

void kapalýyolTýka(int row,int coll);

void mazeisaretle(Smaze m,int row,int coll);

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

	mazeisaretle(maze,maze.finRow,maze.FinColl);

	mazeYaz(maze);

	scanf("%d");
    return 0;
}

void mazeBull(int row,int coll,int deep,int yön)
{
	if(maze.mazevizit[row][coll] == MAXColl*MAXROW)
		return;
	if(maze.maze[row+1][coll] == 'f' || maze.maze[row-1][coll] == 'f' || maze.maze[row][coll+1] == 'f' || maze.maze[row][coll-1] == 'f')
	{
		if(maze.minYol>deep)
		{maze.minYol = deep; maze.finRow = row;maze.FinColl = coll;maze.mazevizit[row][coll] = deep;}
		return;
	}
	if(KapalýYolmu(row,coll,yön))
	{
		maze.mazevizit[row][coll] = MAXColl*MAXROW;
		return;
	}
	if(maze.maze[row][coll] == '*' || maze.mazevizit[row][coll] < deep || maze.minYol < deep)
		return;

	Sleep(2);

	mazeHareket(maze,row,coll);

	if(maze.maze[row][coll] == ' ' && maze.minYol > deep && maze.mazevizit[row][coll] > deep && maze.mazevizit[row][coll] != MAXColl*MAXROW)
		maze.mazevizit[row][coll] = deep;
	if(yön != 2)
		mazeBull(row,coll-1,deep+1,1);
	if(yön != 1)
		mazeBull(row,coll+1,deep+1,2);
	if(yön != 4)
		mazeBull(row-1,coll,deep+1,3);
	if(yön != 3)
		mazeBull(row+1,coll,deep+1,4);
	return;
}

int KapalýYolmu(int row,int coll,int yön)
{
	if(yön == 1 && maze.maze[row][coll-1] == '*' && maze.maze[row+1][coll] == '*' && maze.maze[row-1][coll] == '*')//alt 
		return True;
	else if(yön == 2 && maze.maze[row][coll+1] == '*' && maze.maze[row+1][coll] == '*' && maze.maze[row-1][coll] == '*')//üst
		return True;
	else if(yön == 3 && maze.maze[row-1][coll] == '*' && maze.maze[row][coll-1] == '*' && maze.maze[row][coll+1] == '*')//sað
		return True;
	else if(yön == 4 && maze.maze[row+1][coll] == '*' && maze.maze[row][coll-1] == '*' && maze.maze[row][coll+1] == '*')//sol
		return True;
	else
		return False;
}

void mazeYaz(Smaze m)
{
	CONSOLE_CURSOR_INFO curInfo;
        HANDLE hStdout;
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos={10,10};

        GetConsoleCursorInfo(hStdout,&curInfo);

        curInfo.bVisible=false;

        SetConsoleCursorInfo(hStdout,&curInfo);
		pos.X=0;
		pos.Y=0;
        SetConsoleCursorPosition(hStdout,pos);
		SetConsoleTextAttribute(hStdout, 2);
	//system("CLS");
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
	 CONSOLE_CURSOR_INFO curInfo;

 

        HANDLE hStdout;

        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        int i=0;

        int j=0;

        COORD pos={10,10};

        GetConsoleCursorInfo(hStdout,&curInfo);

        curInfo.bVisible=false;

        SetConsoleCursorInfo(hStdout,&curInfo);
		pos.X=0;
		pos.Y=0;
        SetConsoleCursorPosition(hStdout,pos);
		SetConsoleTextAttribute(hStdout, 2);
	//system("CLS");
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

void mazeisaretle(Smaze m,int row,int coll)
{
	if(maze.mazevizit[row][coll] == 1){
		maze.maze[row][coll] = '-';
		return;
	}
	if(!KapalýYolmu(row,coll,1) && maze.mazevizit[row][coll]>maze.mazevizit[row][coll+1])
	{
		maze.maze[row][coll] = '-';
		mazeisaretle(m,row,coll+1);
		return;
	}
	if(!KapalýYolmu(row,coll,2))
	{
		if(maze.mazevizit[row][coll]>maze.mazevizit[row][coll-1]){
			maze.maze[row][coll] = '-';
			mazeisaretle(m,row,coll-1);
			return;
		}
	}
	if(!KapalýYolmu(row,coll,3))
	{
		if(maze.mazevizit[row][coll]>maze.mazevizit[row+1][coll]){
			maze.maze[row][coll] = '-';
			mazeisaretle(m,row+1,coll);
			return;
		}
	}
	if(!KapalýYolmu(row,coll,4))
	{
		if(maze.mazevizit[row][coll]>maze.mazevizit[row-1][coll]){
			maze.maze[row][coll] = '-';
			mazeisaretle(m,row-1,coll);
			return;
		}
	}
	return;
}