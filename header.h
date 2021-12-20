#pragma once
// 사용할 헤더파일
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// 기호상수 정의
#define PROBLEM_NUMBER 20 // 문항 개수
#define TIME_LIMIT 5 // 기본 시간 제한
#define STUDENT_NUMBER 99 // 가상의 학생수로 설정
#define MAX_STRING_SIZE 20 // 단어 최대 길이

int chooseNumber(int min, int max);
void game(int level);
void show_string(char* wordList[], int nowNum, int level);
int checkWordList(char* wordList[], int i, int size, char* targetList[]);
void getRandomWords(int level, char* wordList[]);
int level_select();
void make_score(int scores[], double *average, double *var, double *dev);
void typing_speed();
int character_select();
void gotoxy(int x, int y);
void sleepNoGetch(int sleepTime);
int result(int level);
void ending();
void show_level(int level);