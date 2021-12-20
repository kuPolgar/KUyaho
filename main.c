#include "header.h"

// score 전역 변수
double score = 0;
int difficulty = 0;
int countAnswer = 0;
int character = 1;
double playtime = 0;
int cor_typing_length = 0;

int main(void) {
	int selectStartEnd;
	int flag = 0;
	int game_level = 0;

	while (1) {
		system("cls");
		printf("=========== 컴공생들의 코딩 용어 시험 ============\n\n");
		printf("  1. 게임 시작하기\n");
		printf("  2. 게임 종료하기\n\n");
		printf("==================================================\n");
		selectStartEnd = chooseNumber(1, 2);
		switch (selectStartEnd) {
		case 1:
			system("cls"); //창 정리
			character = character_select();

			system("cls"); //창 정리
			game_level = level_select(); 

			system("cls"); //창 정리
			game(game_level); // 게임 시작!

			system("cls"); //창 정리
			if(!result(game_level)) break;

			if (game_level == 1) {
				game_level++;
				game(game_level);
				if (!result(game_level)) break;
			}
			
			if (game_level == 2) {
				game_level++;
				game(game_level);
				if (!result(game_level)) break;
			}

			// Ending
			system("cls");
			ending();
			break;
		case 2:
			flag = 1; // 게임 종료 시 flag 1로 변환
			break;
		default:
			break;
		}

		if (flag) 
			break; // 게임 종료 선택 시 빠져나옴
	}
	
	return 0;
}

