#define BOARDSTATUS_OK		1
#define BOARDSTATUS_NOK		0
#define N_BOARD		15

int board_initBoard();		//보드 초기화 

int board_getBoardStatus(int pos);		//특정 칸의 파손 여부 출력
int board_getSharkPosition(void);		 //상어의 위치 출력
int board_stepShark(void);			//상어 전진 명령
int board_getBoardCoin(int pos);		//동전 습득 명령 
int board_printBoardStatus(void);		//전체 보드의 상태 출력   
