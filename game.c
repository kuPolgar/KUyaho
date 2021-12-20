
/*game.c : 게임 동작 관련 파일*/
// 1. 단어 분류
// 2. 단어 랜덤으로 골라지는 함수
// 한 문자당 (1/1.5/2), 문제 갯수(우선 30개)

#include "header.h"

extern double score;
extern int difficulty;
extern int countAnswer;
extern int character;
extern double playtime;
extern int cor_typing_length;

// lv1: 3~4자리 / 2: 5자리 / 3: 6자리 / 4: 7자리 이상
char* C_lv1[] = { "int", "rows", "cols", "auto" , "else", "long", "case", "enum", "char", "void", "goto", "link", "main", "loop", "sqrt", "rand","line","gets","puts", "user", "edit", "time", "size","flag","exit","call" };
char* C_lv2[] = { "srand", "break", "debug", "ascii", "union", "const", "short", "while", "scanf", "debug", "float", "scope","undef","ifdef","endif","width","fopen","fseek","stack", "stdio" };
char* C_lv3[] = { "double", "struct", "switch", "extern", "return", "signed", "sizeof", "static", "printf", "string", "static","ifndef","pragma","stream","fflush","rewind","remove","fscanf","fwrite","buffer","header" };
char* C_lv4[] = { "integer", "pointer", "library", "compile", "comment", "typedef", "default", "declare", "linkage","putchar","getchar","fsetpos","fprintf", "include",
				  "function", "variable", "constant", "volatile", "unsigned", "register", "continue", "overflow", "operator", "lifetime", "underflow", "parameter","precision","statement","datatype" };

// lv1: 3~4자리 / 2: 5~6자리 / 3: 7~8자리 / 4: 9~10자리 이상
char* Intro_lv1[] = { "log", "ray" , "bus", "bit", "leak" , "roll", "loop", "gate", "byte", "flag", "time", "load", "user", "file", "path", "page", "boot", "set", "kill", "open", "hub", "peer", "grid", "end", "post", "tag", "spam", "html", "link", "hop" };
char* Intro_lv2[] = { "graph" , "chart" , "depth" , "agile", "logic", "pixel", "clock", "queue", "shell",
					  "mining" , "kernel" , "paging" ,"router" ,"raster" , "object" , "public", "coding", "sector", "serial", "window", "folder", "kernel", "device", "driver", "paging", "loader", "update", "random", "socket", "analog","malloc","calloc","realloc" };
char* Intro_lv3[] = { "integer", "library", "compile", "comment", "typedef", "default", "declare", "linkage", "putchar", "getchar", "fsetpos", "fprintf", "digital", "program", "keyword", "spyware", "firewall" ,"function", "pretest",
					  "dataflow" , "checksum" , "firmware" ,"robotics" , "deadlock" , "sniffing" , "protocol" , "diskette" , "malware" , "cohesion", "bitwise" };
char* Intro_lv4[] = { "bandwidth" , "decorator", "debugging" , "directory" ,"rendering" , "scheduler", "auditiong"  ,"strapping" , "semaphore" , "privilege" ,"papameter" , "radiosity" , "checkbyte", "insertion", "statement", "aggregate", "overloading",
					  "dispatcher" , "refraction", "multiprogramming", "administrator" , "interprocess" , "microprocessor" , "rasterization" , "implementation", "incremental", "dataflow", "prototype", "coupling", "assembler" };

// lv1: 3~4자리 / lv2: 5~6자리 / lv3: 7~8자리 / lv4: 9~10자리 이상
char* Web_lv1[] = { "var", "app",  "xml", "tag", "load", "css", "sub", "src", "img", "div", "top", "web","req","res", "next", "html", "head", "body", "font", "port", "http", "href", "code", "type", "list", "form", "text", "name", "span", "left", "ajax", "json" };
char* Web_lv2[] = { "style", "table", "write", "title", "class", "width","audio", "radio", "input", "value", "label", "aside", "hover", "block", "fixed", "right", "float", "route",
					"onload", "router", "strong", "script", "margin", "border", "target", "height", "volume", "source", "poster", "hidden", "submit", "action", "button", "inline", "header", "footer", "active", "radius", "length", "scroll", "jQuery" };
char* Web_lv3[] = { "express", "DOCTYPE", "heading", "element", "padding", "colspan", "rowspan", "caption", "preload", "checked", "section", "article", "visited", "enabled", "display", "opacity", "inherit", "trigger",
					"callback", "protocol","document", "function", "semantic", "autoplay", "controls", "password", "selected", "optgroup", "textarea", "selector", "checked", "disabled", "nthChild",
					"fontSize", "overline", "collapse", "position", "relative", "absolute", "overflow", "ellipsis", "mouseout" };
char* Web_lv4[] = { "paragraph", "lastChild", "textAlign", "listStyle", "fontStyle", "underline", "boxShadow" , "localhost", "fillStyle","beginPath", "closePath", "mousemove", "mouseover",
					"fontFamily", "availWidth", "availHeight", "background", "navigation", "firstChild", "fontWeight", "lineHeight", "visibility", "textShadow", "attachment", "whitespace", "javascript", "middleware",
					"strokeStyle", "setInterval", "setTimeout", "clearInterval", "clearTimeout", "innerHTML", "getElementById", "backgroundColor", "setAttribute" };

void game(int level)
{
	int nowNum = 0, j = 0, i = 0, temp, nowTime;
	char ch;
	double startTime, endTime, timeInterval;
	int timeLimit = TIME_LIMIT + (level - 1); // 레벨별로 제한 시간 1초씩 감소.
	char* wordList[MAX_STRING_SIZE + 1], input[MAX_STRING_SIZE]; // 단어 리스트 (최대 단어개수 20개, 길이 10자까지 (마지막은 NULL 문자))
	int skill2 = 0;
	int skill3 = 3;
	int skill4 = 2;
	double add_score;
	double scores[PROBLEM_NUMBER];
	for (i = 0; i < PROBLEM_NUMBER; i++) {
		scores[i] = 0;
	}

	for (i = 3; i > 0; i--) {
		switch (character)
		{
		case 1: {
			printf("============================================================\n\n");
			show_level(level);
			printf("  캐릭터명: 빅데이터 전문가\n");
			printf("  스킬 정보: 다음 단어가 보이는 지속적인 고유 기능\n");
			printf("  현재 점수: %.2lf\n\n", score);
			printf("============================================================\n");
			printf("  %d초 후 게임이 시작됩니다.\n", i);
			printf("============================================================\n\n");
			break;
		}
		case 2: {
			printf("============================================================\n\n");
			show_level(level);
			printf("  캐릭터명: 인공지능 전문가\n");
			printf("  스킬 정보: space 키를 누르면 3문제 연속 자동 입력\n");
			printf("  현재 점수: %.2lf\n\n", score);
			printf("============================================================\n");
			printf("  %d초 후 게임이 시작됩니다.\n", i);
			printf("============================================================\n\n");
			break;
		}
		case 3: {
			printf("============================================================\n\n");
			show_level(level);
			printf("  캐릭터명: 소프트웨어개발 전문가\n");
			printf("  스킬 정보: space 키를 누르면 쉬운 단어가 오게 함\n");
			printf("  현재 점수: %.2lf\n\n", score);
			printf("============================================================\n");
			printf("  %d초 후 게임이 시작됩니다.\n", i);
			printf("============================================================\n\n");
			break;
		}
		case 4: {
			printf("============================================================\n\n");
			show_level(level);
			printf("  캐릭터명: 컴퓨터보안 전문가\n");
			printf("  스킬 정보: 문제를 틀릴 시 자동으로 맞게 고침\n");
			printf("  현재 점수: %.2lf\n\n", score);
			printf("============================================================\n");
			printf("  %d초 후 게임이 시작됩니다.\n", i);
			printf("============================================================\n\n");
			break;
		}
		}
		
		sleepNoGetch(1);
		system("cls");
	}

	getRandomWords(level, &wordList); // wordList에 단어 목록이 들어감
	// 게임 시작

	srand(time(0));
	startTime = clock(); // 문제 풀이 시작 시간
	show_string(wordList, 0, level); // 1번 문제 시작

	while (1) {
		if ((clock() - startTime) / CLOCKS_PER_SEC > timeLimit) { // 한 문제당 제한시간
			printf("\n시간이 초과되었습니다. 1초 후 다음 문제가 공개됩니다.\n");
			sleepNoGetch(1);
			system("cls");
			startTime = clock();
			nowNum++; // 문제 번호 UP
			if (nowNum == PROBLEM_NUMBER) break; // 문제 다 풀면 반복문 탈출
			show_string(wordList, nowNum, level);
			j = 0;
		}

		if (_kbhit()) { // 키보드 입력 처리
			ch = _getch();

			if (ch == 27) { // ESC (빨리 종료해버림)
				score = 100;
				break;
			}

			if (ch == 8) { // backspace
				if (j > 0) {
					printf("\b \b");
					j--;
				}
			}

			if (skill2 == 0 && character == 2 && ch == 32) // z 2번 캐릭터 스킬(1번만 사용 가능)
			{
				skill2++;
				system("cls");
				show_string(wordList, nowNum, level);
				for (int t = 0; t < 3; t++) {
					startTime = clock();
					printf("%s [자동 입력 중]", wordList[nowNum]);
					sleepNoGetch(3);
					
					timeInterval = round((clock() - startTime) * 10 / CLOCKS_PER_SEC) / 10;
					add_score = (100 / PROBLEM_NUMBER) * (1 - (timeInterval / timeLimit));
					score += add_score;
					scores[nowNum] = add_score;
					printf("\n\n정답입니다. 1초 후 다음 문제가 공개됩니다.\n\n=============================\n\n");
					printf("걸린 시간: %.1f초\n", timeInterval);
					printf("%.2lf점이 추가되었습니다.\n", add_score);
					sleepNoGetch(1);
					
					countAnswer++;
					nowNum++;
					if (nowNum == PROBLEM_NUMBER) break; // 문제 다 풀면 반복문 탈출
					system("cls");
					show_string(wordList, nowNum, level);
					startTime = clock();
					j = 0;
				}
			}

			if (nowNum < PROBLEM_NUMBER - 1 && skill3 > 0 && character == 3 && ch == 32) // z키 3번 캐릭터 스킬 (3번만 사용 가능)
			{
				switch (level) {
				case 1:
					temp = checkWordList(wordList, PROBLEM_NUMBER, sizeof(C_lv1) / sizeof(C_lv1[0]), C_lv1);
					wordList[nowNum + 1] = C_lv1[temp];
					break;
				case 2:
					temp = checkWordList(wordList, PROBLEM_NUMBER, sizeof(Intro_lv1) / sizeof(Intro_lv1[0]), C_lv1);
					wordList[nowNum + 1] = Intro_lv1[temp];
					break;
				case 3:
					temp = checkWordList(wordList, PROBLEM_NUMBER, sizeof(Web_lv1) / sizeof(Web_lv1[0]), C_lv1);
					wordList[nowNum + 1] = Web_lv1[temp];
					break;
				}
				CONSOLE_SCREEN_BUFFER_INFO presentCur;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &presentCur);
				printf("\n\n\n\n\n\n\n\n\n==========================================\n");
				puts("  [ 다음 문제의 단어가 쉬워졌습니다. ]");
				printf("  스킬 남은 횟수: %d회", --skill3);
				printf("\n==========================================");
				gotoxy(presentCur.dwCursorPosition.X, presentCur.dwCursorPosition.Y); // 커서 위치 기존 위치로 바꾸기
			}

			if (ch == '\r') { // enter
				for (int k = MAX_STRING_SIZE - 1; k >= j; k--) {
					input[k] = '\0';
				}
				
				if (!strcmp(wordList[nowNum], input)) { // 정답일경우
					countAnswer++; // 맞은 개수 증가
					timeInterval = round((clock() - startTime) * 10 / CLOCKS_PER_SEC ) / 10;
					add_score = (100 / PROBLEM_NUMBER) * (1 - (timeInterval / timeLimit));
					score += add_score;
					scores[nowNum] = add_score;
					printf("\n\n정답입니다. 1초 후 다음 문제가 공개됩니다.\n\n=============================\n\n");
					printf("걸린 시간: %.1f초\n", timeInterval);
					printf("%.2lf점이 추가되었습니다.\n", add_score);
					playtime += timeInterval;	//타수 계산용 타자 입력시간에 추가
					cor_typing_length += j;		//타수 계산용 정타수에 추가
					sleepNoGetch(1);
				}
				else {
					if (character == 4 && skill4 > 0) // 4번 캐릭터 스킬(최대 2번 사용 가능)
					{
						countAnswer++; // 맞은 개수 증가
						score += (100 / PROBLEM_NUMBER); // 만점 처리 (타수 저장 X)
						scores[nowNum] = (100 / PROBLEM_NUMBER);
						printf("\n\n[남은 스킬 횟수: %d회]\n스킬이 자동 적용되어 정답 처리되었습니다. 1초 후 다음 문제가 공개됩니다.\n", --skill4);
						printf("%.2lf점이 추가되었습니다.\n", (100.0 / PROBLEM_NUMBER));
						sleepNoGetch(1);
					}
					else {
						printf("\n\n틀렸습니다!! 1초 후 다음 문제가 공개됩니다.\n");
						scores[nowNum] = 0;
						playtime += (clock() - startTime) / CLOCKS_PER_SEC;	//타수 계산용 타자 입력시간에 추가
						sleepNoGetch(1);
					}
				}

				system("cls");
				nowNum++; // 문제 번호 UP
				if (nowNum == PROBLEM_NUMBER) break; // 문제 다 풀면 반복문 탈출
				show_string(wordList, nowNum, level);
				startTime = clock();
				j = 0;

			}
			if (((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) && j < MAX_STRING_SIZE) { // j가 input 바깥 index 못 나가게 함
				printf("%c", ch);
				input[j++] = ch;
			}
		}
	}

	system("cls");
	printf("      [채점 결과]\n\n");
	for (i = 0; i < PROBLEM_NUMBER; i++) 
		printf("  (%.2f점) [%02d] %s  \n", scores[i], i + 1, wordList[i]);
	printf("\n  총점: %.2f점\n", score);
	system("pause");
	system("cls");
}

void show_level(int level) {
	printf("  현재 과목: ");
	switch (level) {
	case 1:
		printf("C프로그래밍 (초급)\n");
		break;
	case 2:
		printf("컴퓨터공학개론 (중급)\n");
		break; 
	case 3:
		printf("웹프로그래밍 (상급)\n");
		break;
	}
}


void show_string(char* wordList[], int nowNum, int level) {
	switch (character)
	{
	case 1: {
		printf("============================================================\n\n");
		show_level(level);
		printf("  캐릭터명: 빅데이터 전문가\n");
		printf("  스킬 정보: 다음 단어가 보이는 지속적인 고유 기능\n");
		printf("  현재 점수: %.2lf\n\n", score);
		printf("============================================================\n");
		printf("  [%02d] ", nowNum + 1);
		puts(wordList[nowNum]);
		if (nowNum != PROBLEM_NUMBER - 1)
			printf("\n  다음 단어: %s\n", wordList[nowNum + 1]);
		printf("============================================================\n\n");
		printf("단어를 따라 입력하세요: ");
		break;
	}
	case 2: {
		printf("============================================================\n\n");
		show_level(level);
		printf("  캐릭터명: 인공지능 전문가\n");
		printf("  스킬 정보: space 키를 누르면 3문제 연속 자동 입력\n");
		printf("  현재 점수: %.2lf\n\n", score);
		printf("============================================================\n");
		printf("  [%02d] ", nowNum + 1);
		puts(wordList[nowNum]);
		printf("============================================================\n\n");
		printf("단어를 따라 입력하세요: ");
		break;
	}
	case 3: {
		printf("============================================================\n\n");
		show_level(level);
		printf("  캐릭터명: 소프트웨어개발 전문가\n");
		printf("  스킬 정보: space 키를 누르면 쉬운 단어가 오게 함\n");
		printf("  현재 점수: %.2lf\n\n", score);
		printf("============================================================\n");
		printf("  [%02d] ", nowNum + 1);
		puts(wordList[nowNum]);
		printf("============================================================\n\n");
		printf("단어를 따라 입력하세요: ");
		break;
	}
	case 4: {
		printf("============================================================\n\n");
		show_level(level);
		printf("  캐릭터명: 컴퓨터보안 전문가\n");
		printf("  스킬 정보: 문제를 틀릴 시 자동으로 맞게 고침\n");
		printf("  현재 점수: %.2lf\n\n", score);
		printf("============================================================\n");
		printf("  [%02d] ", nowNum + 1);
		puts(wordList[nowNum]);
		printf("============================================================\n\n");
		printf("단어를 따라 입력하세요: ");
		break;
	}
	}
}

int checkWordList(char* wordList[], int i, int size, char* targetList[]) {
	int flag = 1, randNum;
	while (1) {
		randNum = rand() % size;
		flag = 1;
		for (int j = 0; j < i; j++) {
			if (!strcmp(wordList[j], targetList[randNum])) { // wordList에 중복으로 존재하면 반복문 다시 돌기
				flag = 0;
			}
		}
		if (flag)
			break;
	}
	return randNum;
}

// 문자열 배열에 대입
void getRandomWords(int level, char* wordList[]) {
	int flag = 1, size = 0;
	int randNum1, randNum2;
	srand((unsigned)time(NULL));

	switch (level) {
		// C프로그래밍 단어 리턴
	case 1:
		for (int i = 0; i < PROBLEM_NUMBER; i++) {
			randNum1 = rand() % 100 + 1;

			if (randNum1 <= 40) { // 40% 확률로 레벨1 단어
				difficulty += 1;
				size = sizeof(C_lv1) / sizeof(C_lv1[0]);
				randNum2 = checkWordList(wordList, i, size, C_lv1);
				wordList[i] = C_lv1[randNum2];
			}
			else if (randNum1 <= 70) { // 30% 확률로 레벨2 단어
				difficulty += 2;
				size = sizeof(C_lv2) / sizeof(C_lv2[0]);
				randNum2 = checkWordList(wordList, i, size, C_lv2);
				wordList[i] = C_lv2[randNum2];
			}
			else if (randNum1 <= 90) { // 20% 확률로 레벨3 단어
				difficulty += 3;
				size = sizeof(C_lv3) / sizeof(C_lv3[0]);
				randNum2 = checkWordList(wordList, i, size, C_lv3);
				wordList[i] = C_lv3[randNum2];
			}
			else { // 10% 확률로 레벨4 단어
				difficulty += 4;
				size = sizeof(C_lv4) / sizeof(C_lv4[0]);
				randNum2 = checkWordList(wordList, i, size, C_lv4);
				wordList[i] = C_lv4[randNum2];
			}
		}
		break;

		// 컴공개론 단어 리턴
	case 2:
		for (int i = 0; i < PROBLEM_NUMBER; i++) {
			randNum1 = rand() % 100 + 1;

			if (randNum1 <= 25) { // 25% 확률로 레벨1 단어
				difficulty += 1;
				size = sizeof(Intro_lv1) / sizeof(Intro_lv1[0]);
				randNum2 = checkWordList(wordList, i, size, Intro_lv1);
				wordList[i] = Intro_lv1[randNum2];
			}
			else if (randNum1 <= 50) { // 25% 확률로 레벨2 단어
				difficulty += 2;
				size = sizeof(Intro_lv2) / sizeof(Intro_lv2[0]);
				randNum2 = checkWordList(wordList, i, size, Intro_lv2);
				wordList[i] = Intro_lv2[randNum2];
			}
			else if (randNum1 <= 75) { // 25% 확률로 레벨3 단어
				difficulty += 3;
				size = sizeof(Intro_lv3) / sizeof(Intro_lv3[0]);
				randNum2 = checkWordList(wordList, i, size, Intro_lv3);
				wordList[i] = Intro_lv3[randNum2];
			}
			else { // 25% 확률로 레벨4 단어
				difficulty += 4;
				size = sizeof(Intro_lv4) / sizeof(Intro_lv4[0]);
				randNum2 = checkWordList(wordList, i, size, Intro_lv4);
				wordList[i] = Intro_lv4[randNum2];
			}
		}
		break;


	case 3:
		for (int i = 0; i < PROBLEM_NUMBER; i++) {
			randNum1 = rand() % 100 + 1;

			if (randNum1 <= 10) { // 10% 확률로 레벨1 단어
				difficulty += 1;
				size = sizeof(Web_lv1) / sizeof(Web_lv1[0]);
				randNum2 = checkWordList(wordList, i, size, Web_lv1);
				wordList[i] = Web_lv1[randNum2];
			}
			else if (randNum1 <= 30) { // 20% 확률로 레벨2 단어
				difficulty += 2;
				size = sizeof(Web_lv2) / sizeof(Web_lv2[0]);
				randNum2 = checkWordList(wordList, i, size, Web_lv2);
				wordList[i] = Web_lv2[randNum2];
			}
			else if (randNum1 <= 60) { // 30% 확률로 레벨3 단어
				difficulty += 3;
				size = sizeof(Web_lv3) / sizeof(Web_lv3[0]);
				randNum2 = checkWordList(wordList, i, size, Web_lv3);
				wordList[i] = Web_lv3[randNum2];
			}
			else { // 40% 확률로 레벨4 단어
				difficulty += 4;
				size = sizeof(Web_lv4) / sizeof(Web_lv4[0]);
				randNum2 = checkWordList(wordList, i, size, Web_lv4);
				wordList[i] = Web_lv4[randNum2];
			}
		}
		break;

	}
}