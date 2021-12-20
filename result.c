#include "header.h"

void make_score(int scores[], double* average, double* var, double* dev);
void typing_speed();

//결과 창
extern double score;
extern int difficulty;
extern int countAnswer;
extern double playtime;
extern int cor_typing_length;

int result(int level)
{
	int aplus_number, a_number, b_number, c_number, d_number; //등급컷 인원
	double dev, var = 0, average = 0;
	int flag = 0;
	int scores[STUDENT_NUMBER + 1];	// 학생들 점수
	char* subjectName[3] = { "C프로그래밍", "컴퓨터공학개론", "웹프로그래밍" };

	srand(time(0));

	make_score(scores, &average, &var, &dev);	// 학생들 점수 생성 함수

	aplus_number = (int) STUDENT_NUMBER * 0.2;
	a_number = (int) STUDENT_NUMBER * 0.35;
	b_number = (int) STUDENT_NUMBER * 0.7;
	c_number = (int) STUDENT_NUMBER * 0.8;
	d_number = (int) STUDENT_NUMBER * 0.9;
	
	system("cls");

	printf("============ 시험 결과 ============\n\n");
	printf("  시험 과목: %s\n", subjectName[level - 1]);
	switch (difficulty / 10) {
	case 2:
		printf("  시험 난이도: 매우 쉬움 (1/6) \n"); break;
	case 3:
		printf("  시험 난이도: 쉬움 (2/6) \n"); break;
	case 4:
		printf("  시험 난이도: 보통 (3/6) \n"); break;
	case 5:
		printf("  시험 난이도: 조금 어려움 (4/6) \n"); break;
	case 6:
		printf("  시험 난이도: 어려움 (5/6) \n"); break;
	case 7: case 8:
		printf("  시험 난이도: 매우 어려움 (6/6) \n"); break;
	}
	printf("  평균 점수: %.2lf점\n", average);
	printf("  표준 편차: %.2lf\n", dev);
	printf("  응시 인원: %d명\n", STUDENT_NUMBER + 1);
	printf("  --------------------\n");
	printf("  A+ 성적 컷: %.2d점\n", scores[aplus_number]);
	printf("  A  성적 컷: %.2d점\n", scores[a_number]);
	printf("  B  성적 컷: %.2d점\n", scores[b_number]);
	printf("  C  성적 컷: %.2d점\n", scores[c_number]);
	printf("  D  성적 컷: %.2d점\n\n", scores[d_number]);
	printf("====================================\n\n");

	//다른 학생들과 나의 점수를 이용해 시험 결과와 등급 컷을 출력함.
	printf("============ 나의 성적 ============\n\n");
	printf("        나의 점수: %.2f\n", score);
	printf("        맞은 개수: %d/%d\n", countAnswer, PROBLEM_NUMBER);
	typing_speed();		//타수 출력

	if (score >= scores[aplus_number])
	{
		printf("        나의 등급: A+\n\n");
		printf("        해당 과목 PASS\n\n");
		printf("====================================\n\n");
		printf("아무 키나 눌러 다음 과목으로 넘어가세요: ");
		flag = 1;//return 값을 1로 만들기(1이 다음 과목으로)

	}
	else if (score < scores[aplus_number] && score >= scores[a_number])
	{
		printf("        나의 등급: A\n\n");
		printf("        해당 과목 PASS\n\n");
		printf("====================================\n\n");
		printf("아무 키나 눌러 다음 과목으로 넘어가세요: ");
		flag = 1;//return 값을 1로 만들기(1이 다음 과목으로)
	}
	else if (score < scores[a_number] && score >= scores[b_number])
	{
		printf("        나의 등급: B\n\n");
		printf("        해당 과목 PASS\n\n");
		printf("====================================\n\n");
		printf("아무 키나 눌러 다음 과목으로 넘어가세요: ");
		flag = 1;//return 값을 1로 만들기(1이 다음 과목으로)
	}
	else if (score < scores[b_number] && score >= scores[c_number])
	{
		printf("        나의 등급: C\n\n");
		printf("        해당 과목 FAIL\n\n");
		printf("====================================\n\n");
		printf("아무 키나 눌러 다음 과목으로 넘어가세요: ");
		flag = 0;//return 값을 0으로 만들기 (0은 초기 화면으로)
	}
	else if (score < scores[c_number] && score >= scores[d_number])
	{
		printf("        나의 등급: D\n\n");
		printf("        해당 과목 FAIL\n\n");
		printf("====================================\n\n");
		printf("아무 키나 눌러 메인 메뉴로 돌아가세요: ");
		flag = 0;//return 값을 0으로 만들기 (0은 초기 화면으로)
	}
	else
	{
		printf("        나의 등급: F\n\n");
		printf("        해당 과목 FAIL\n\n");
		printf("====================================\n\n");
		printf("아무 키나 눌러 메인 메뉴로 돌아가세요: ");
		flag = 0;//return 값을 0으로 만들기 (0은 초기 화면으로)
	}

	// 점수 정보 초기화
	score = 0;
	difficulty = 0;
	countAnswer = 0;
	cor_typing_length = 0;
	playtime = 0;
	system("pause");
	system("cls");
	return flag;
}


void make_score(int scores[], double *average, double *var, double *dev) {	//학생들 점수 생성 프로그램
	int i, flag, tempRand;
	double sum = 0;

	switch (difficulty / 10) {
	case 2: 
		for (i = 0; i < STUDENT_NUMBER; i++) {
			tempRand = rand() % 100 + 1;
			if (tempRand <= 10)
				scores[i] = rand() % 30; // 10% 확률로 0~30점
			else if (tempRand <= 50)
				scores[i] = rand() % 40 + 31; // 40% 확률로 31~70점
			else {
				scores[i] = rand() % 30 + 71; // 50% 확률로 71~100점
			}
		}
		break;
	case 3:
		for (i = 0; i < STUDENT_NUMBER; i++) {
			tempRand = rand() % 100 + 1;
			if (tempRand <= 20)
				scores[i] = rand() % 30; // 20% 확률로 0~30점
			else if (tempRand <= 70)
				scores[i] = rand() % 40 + 31; // 50% 확률로 31~70점
			else {
				scores[i] = rand() % 30 + 71; // 30% 확률로 71~100점
			}
		}
		break;
	case 4: 
		for (i = 0; i < STUDENT_NUMBER; i++) {
			tempRand = rand() % 100 + 1;
			if (tempRand <= 30)
				scores[i] = rand() % 30; // 30% 확률로 0~30점
			else if (tempRand <= 80)
				scores[i] = rand() % 40 + 31; // 50% 확률로 31~70점
			else {
				scores[i] = rand() % 30 + 71; // 20% 확률로 71~100점
			}
		}
		break;
	case 5:
		for (i = 0; i < STUDENT_NUMBER; i++) {
			tempRand = rand() % 100 + 1;
			if (tempRand <= 35)
				scores[i] = rand() % 30; // 35% 확률로 0~30점
			else if (tempRand <= 80)
				scores[i] = rand() % 40 + 31; // 45% 확률로 31~70점
			else {
				scores[i] = rand() % 30 + 71; // 20% 확률로 71~100점
			}
		}
		break;
	case 6: 
		for (i = 0; i < STUDENT_NUMBER; i++) {
			tempRand = rand() % 100 + 1;
			if (tempRand <= 40)
				scores[i] = rand() % 30; // 40% 확률로 0~30점
			else if (tempRand <= 85)
				scores[i] = rand() % 40 + 31; // 45% 확률로 31~70점
			else {
				scores[i] = rand() % 30 + 71; // 15% 확률로 71~100점
			}
		}
		break;
	case 7: case 8:
		for (i = 0; i < STUDENT_NUMBER; i++) {
			tempRand = rand() % 100 + 1;
			if (tempRand <= 50)
				scores[i] = rand() % 30; // 50% 확률로 0~30점
			else if (tempRand <= 95)
				scores[i] = rand() % 40 + 31; // 45% 확률로 31~70점
			else {
				scores[i] = rand() % 30 + 71; // 5% 확률로 71~100점
			}
		}
		break;
	}


	for (i = STUDENT_NUMBER - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (scores[j] < scores[j + 1]) {
				flag = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = flag;
			}
		}
	}
	
	for (i = 0; i < STUDENT_NUMBER; i++) {
		sum += scores[i];
	}
	sum += score; // 내 점수 더하기

	*average = sum / (STUDENT_NUMBER+1);

	for (i = 0; i < STUDENT_NUMBER; i++) {
		*var += (scores[i] - *average) * (scores[i] - *average);
	}
	*var += (score - *average) * (score - *average); // 내 편차 제곱 더하기

	*var /= (STUDENT_NUMBER+1); // 학생 수로 나눠서 분산 구하기
	*dev = sqrt(*var); // 표준편차 구하기 
}

void typing_speed() {	//타수 계산 및 출력함수
	double typing_speed = 0;
	if (playtime != 0) {
		typing_speed = (cor_typing_length / playtime) * 60;
	}
	
	printf("	타수: %d\n", (int)(typing_speed + 0.5));
	printf("	타자입력시간: %.2lf초\n", playtime);
}