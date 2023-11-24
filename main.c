#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"


#define MAX_CHARNAME	200
#define MAX_DIE		6 
#define N_PLAYER	3  //3인용 게임이라는 뜻
 
#define PLAYERSTATUS_LIVE	0
#define PLAYERSTATUS_DIE	1
#define PLAYERSTATUS_END	2


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];
char player_statusString[3][MAX_CHARNAME]={"LIVE","DIE","END"};


void opening(void){
	printf("================================================\n");
	printf("************************************************\n");
	printf("    		 GAME START				  	\n");
	printf("************************************************\n");
	printf("================================================\n\n\n");
	
}

int rolldie(){
	return rand()%MAX_DIE+1;
}

void printPlayerPosition(int player)
{
	int i;
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if(i==player_position[player])
			printf("%c",player_name[player][0]);
		else
		{
			if(board_getBoardStatus(i) == BOARDSTATUS_NOK)
				printf("X");
			else	//멀쩡한 경우 
				printf(" ");
		}
		
				
	}
	printf("|\n");
	
}

void printPlayerStatus(void){
	int i;
	printf("player status");
	for(i=0;i<N_PLAYER;i++)
	{
		printf("\n%s : pos %i, coin %i, status : %s\n",player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
		
	}
	printf("----------------------------------\n");
}

void checkDie(void)
{
	int i;
	for(i=0;i<N_PLAYER;i++)
		if(board_getBoardStatus(player_position[i])==BOARDSTATUS_NOK)
			player_status[i]=PLAYERSTATUS_DIE;
}

int main(int argc, char *argv[]) {
	
	int pos = 0;	
	srand((unsigned)time(NULL));
	int i;
	int turn=0;
	
	//0,opening
	opening();
	
	//1.초기화 & 플레이어를 결정
	int board_initBoard(); 
	//1-2.
	 
	for(i=0;i<N_PLAYER;i++)
	{
		player_position[i]=0;
		player_coin[i]=0;
		player_status[i]=PLAYERSTATUS_LIVE;
		//player_name
		printf("Player %i's name:",i);
		scanf("%s",player_name[i]);  	 //&필요 없음   
	}
	
	//2.반복문
	do{
		int step = rolldie();
		int coinResult;
		char c;
		
		if(player_status[turn] != PLAYERSTATUS_LIVE)
		{
			turn = (turn+1) % N_PLAYER;
			continue;
		}
		
		
		
		//2-1.  플레이어 상태 출력
		board_printBoardStatus();
		
		for(i=0;i<N_PLAYER;i++)
			printPlayerPosition(i);
		printPlayerStatus();
		 
		//2-2. 주사위 던지기
		printf("%s turn!",player_name[turn]);
		printf("press any key to roll a die");
		scanf("%i",&c);
		fflush(stdin);
		step = rolldie();
		
		
		//2-3. 이동
		player_position[turn] += step;
		
		printf("\n%s가 %i칸 이동했습니다.\n",player_name[turn],player_position[turn]);
	
		if(player_position[turn] >= N_BOARD)
		{
			player_position[turn] = N_BOARD-1;
			printf("\n\n<<<<%s가 마지막칸으로 이동했습니다.>>>>\n",player_name[turn]); //어디로 이동했는지 작성..
		}
		else if(player_position[turn]==N_BOARD-1)
		{
			player_status[turn]=PLAYERSTATUS_END;
			printf("\n\n<<<<%s가 마지막칸에 도착했습니다.>>>>\n\n",player_name[turn]);
		}
		 
		
		
		//2-4. 동전 줍기
		coinResult = board_getBoardCoin(pos);
		player_coin[turn] += coinResult;
		//printf("") 적절한 상황을 알려주기 동전 몇을 주웠다.. 이런식으로? 
		
		
		//2-5.  다음 턴
		//turn = turn+1; //계속 돌리면 turn이 플레이어 수보다 많아지면 뻗음 그래서 0,1,2 이렇게 반복시켜야함 
		turn = (turn+1) % N_PLAYER; //0,1,2 만 반복 
		
		//2-6. if (조건: 모든 플레이어가 한번씩 돌기)
		if(turn == 0)
		{
			int shark_pos = board_stepShark();
			//printf()
			//checkDie();
			
		 } 
			//상어 동작
		 
	} while(1);
	//3. 정리(승자 계산, 출력 등) 

	
	
	
	return 0;
}
