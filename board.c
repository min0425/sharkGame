#include <stdio.h>
#include <stdlib.h>
#include "board.h"


#define N_COINPOS	12
#define MAX_COIN	4

#define SHARK_INITPOS	-4
#define MAX_SHARKSTEP	6

static int board_status[N_BOARD];
static int board_coin[N_BOARD];

static int shark_position;

int board_initBoard()		//보드 초기화 
{
	int i;
	for(i=0;i<N_BOARD;i++)
	{
		board_status[i] == BOARDSTATUS_OK;
		board_coin[i] = 0;
	}
	
	for(i=0;i<N_COINPOS;i++)
	{
		int flag=0;
		while(flag==0)
		{
			int allocpos = rand()%N_BOARD;
			if(board_coin[allocpos]==0)
			{
				board_coin[allocpos]=rand()%MAX_COIN+1;
				flag = 1;
			}
		}
		
	}
}

int board_printBoardStatus() 	//전체 보드의 상태 출력 
{
	int i;
	
	printf("--------------------------------------------- Board Status ---------------------------------------------------\n");
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if (board_status[i]==BOARDSTATUS_NOK)
			printf("X");
		else
			printf("O");
	}
	printf("|\n");
	printf("--------------------------------------------------------------------------------------------------------------\n");
	
}

int board_getBoardCoin(int pos)		//동전 습득 명령 
{
	int coin = board_coin[pos];
	board_coin[pos] = 0;
	return board_coin[pos];
	
}

int board_getBoardStatus(int pos)		//특정칸의 파손 여부 출력 
{
	return board_status[pos];
}

//상어의 위치 출력
int  board_getSharkPosition(void)
{
	
}

//상어의 전진 명령 
int board_stepShark(void){
	int step = rand()%MAX_SHARKSTEP+1;
	int i;
	
	for(i=shark_position+1;i<=shark_position+step;i++)
	{
		if(i >= 0 && i<N_BOARD)
			board_status[i]=BOARDSTATUS_NOK;
	}
	
	shark_position += step;
	
}
