#define _CRT_SECURE_NO_WARNINGS				//scanf오류 방지
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>

struct tfield {
	struct tfield* left;			//왼쪽가지
	char Singer[20];			//가수명
	char title[20];				//노래제목
	char date[20];				//발매일
	int select;					//노래를 선택하였는지를 나타냄
	struct tfield* right;			//오른쪽가지
};

int check = 0;
char dat1[20], dat2[20], dat3[20], pt[20];
struct tfield* root, * Song, * forw, * bacw;			//이진트리를 가리키는 root와 하나의 노드를 가리킬수 있는 구조체 포인터
struct tfield* talloc();									//동적 메모리 할당
struct tfield* gentree(struct tfield*, char*, char*, char*);	//이진트리 생성
struct tfield* addNode(struct tfield*, char*, char*, char*);	//이진트리 탐색후 노드추가
void Songsearch(struct tfield*);	//노래검색
void treewalk1(struct tfield*);		//순회
void treewalk2(struct tfield*);
void treewalk3(struct tfield*);
void makelist();				//목록생성하는 함수
void display();					//화면구성하는 함수
void play(char*);				//노래를 선택하는 함수
void backward();				//이전곡
void forward();					//다음곡
void addSong();					//노래추가
void songinfo();				//노래정보출력

void main() {					//메인함수
	int button = 0;				//어떤버튼을 눌렀는지 입력받는 변수
	root = NULL;
	Song = NULL;				//root와 Song은 NULL을 가리키게 함
	printf("\t\t현재 재생중인 노래\n\n\n");
	if (Song != NULL) {
		if (Song->select == 1)
			printf("\t\t%s - %s\n\n", Song->title, Song->Singer);
	}
	else {
		printf("\t\t선택된 곡이 없습니다\n\n\n");
	}
	printf("1.목록생성\t2.재생\t3.이전곡\t4.다음곡\t5.노래추가\t6.노래정보\t7.종료\n\n");		//화면 메뉴
	while (1) {									//무한반복
		scanf("%d", &button);
		if (button == 1) {						//1번 버튼을 누르면 목록 생성
			printf("\n목록생성\n\n");
			makelist();
			display();
			button = 0;				//다시 버튼을 초기화
		}
		else if (button == 2) {					//2번 버튼을 누르면 노래재생
			printf("\n재생할 노래제목을 입력하세요\n");
			scanf("%s", pt);
			play(pt);
			display();
			button = 0;
		}
		else if (button == 3) {					//3번 버튼을 누르면 이전곡 재생
			printf("\n이전곡\n");
			Sleep(1000);
			backward();
			display();
			button = 0;
		}
		else if (button == 4) {					//4번 버튼을 누르면 다음곡 재생
			printf("\n다음곡\n");
			Sleep(1000);
			forward();
			display();
			button = 0;
		}
		else if (button == 5) {					//5번 버튼을 누르면 노래 추가
			printf("\n노래추가\n");
			addSong();
			display();
			button = 0;
		}
		else if (button == 6) {					//6번버튼을 누르면 노래검색
			printf("\n\t\t노래정보검색\n\n");
			songinfo();
			display();
			button = 0;
		}
		else if (button == 7) {					//7번 버튼을 누르면 종료
			break;
		}
	}
}

struct tfield* talloc() {
	return (struct tfield*)malloc(sizeof(struct tfield));
}

struct tfield* gentree(struct tfield* p, char* s, char* n, char* a) {
	if (p == NULL) {
		p = talloc();
		strcpy(p->Singer, s);					//입력받은 가수명,제목,발매일을 p가 가리키는 노드에 저장
		strcpy(p->title, n);
		strcpy(p->date, a);
		p->left = p->right = NULL;
	}
	else if (strcmp(n, p->title) < 0)
		p->left = gentree(p->left, s, n, a);	//제목을 비교하여 작으면 왼쪽가지로 이동
	else
		p->right = gentree(p->right, s, n, a);	//아니면 오른쪽가지로 이동
	return p;
}

struct tfield* addNode(struct tfield* p, char* s, char* n, char* a) {
	if (p == NULL) {
		p = talloc();
		strcpy(p->Singer, s);				//gentree와 동일
		strcpy(p->title, n);
		strcpy(p->date, a);
		p->left = p->right = NULL;
	}
	else if (strcmp(n, p->title) < 0)
		p->left = addNode(p->left, s, n, a);
	else if (strcmp(s, p->Singer) == 0 && strcmp(n, p->title) == 0)		//가수명과 제목을 비교하여 같을시에 이미 있다고 알림
		printf("이미 있는 곡입니다.\n");
	else
		p->right = addNode(p->right, s, n, a);
	return p;
}

void treewalk1(struct tfield* p) {
	if (p != NULL) {
		treewalk1(p->left);
		if (strcmp(pt, p->title) == 0) {	//중위순회를 하면서 입력받은 제목과 비교하여 같을때
			Song = p;						//선택
		}
		treewalk1(p->right);
	}
}

void treewalk2(struct tfield* p) {
	if (p != NULL) {
		treewalk2(p->left);
		if (strcmp(p->title, Song->title) < 0) {	//현재 Song이 가리키는 제목과 비교하여 작을때 선택
			bacw = p;
		}
		treewalk2(p->right);
	}
}

void treewalk3(struct tfield* p) {
	if (p != NULL) {
		treewalk3(p->left);
		if (strcmp(p->title, Song->title) > 0) {	//현재 Song이 가리키는 제목과 비교하여 클때
			if (check < 1) {						//선택되지 않았을때
				forw = p;							//선택후 선택되었음을 표시
				check = 1;
			}
		}
		treewalk3(p->right);
	}
}

void Songsearch(struct tfield* p) {
	if (p != NULL) {
		Songsearch(p->left);
		if (strcmp(pt, p->title) == 0) {
			printf("\n 제목: %s\t 가수: %s\t 발매일: %s\n\n\n", p->title, p->Singer, p->date);
			check = 1;						//노래정보가 표시되었으면 1
		}
		Songsearch(p->right);
	}
}

void makelist() {
	printf("가수명, 제목, 발매일 순으로 정보를 입력하고 마지막에 Ctrl+z를 누르시오.\n");
	while (scanf("%s %s %s", dat1, dat2, dat3) != EOF) {		//Ctrl+z를 누르기 전까지
		root = gentree(root, dat1, dat2, dat3);					//이진트리 생성
	}
	printf("목록이 제목순으로 정렬됩니다.");
	Sleep(1000);
}

void addSong() {
	printf("가수명, 제목, 발매일 순으로 정보를 입력하고 마지막에 Ctrl+z를 누르시오.\n");
	while (scanf("%s %s %s", dat1, dat2, dat3) != EOF) {
		root = addNode(root, dat1, dat2, dat3);
	}
	printf("완료\n");
	Sleep(1000);
}

void display() {
	system("cls");						//화면 지우기
	printf("\t\t현재 재생중인 노래\n\n\n");
	if (Song != NULL) {					//Song이 NULL값을 가리키지 않을때
		if (Song->select == 1)			//Song이 노래를 선택하고 있을때 제목-가수명 출력
			printf("\t\t%s - %s\n\n\n", Song->title, Song->Singer);
	}
	else {								//Song이 NULL값을 가리키고 있을때
		printf("\t\t선택된 곡이 없습니다\n\n\n");
	}
	printf("1.목록생성\t2.재생\t3.이전곡\t4.다음곡\t5.노래추가\t6.노래정보\t7.종료\n\n");		//메뉴
}

void play(char* pt) {
	Song = talloc();		//동적 메모리 할당
	treewalk1(root);			//순회
	if (Song != NULL)
		Song->select = 1;	//노래가 선택되었음을 표시
}

void backward() {
	bacw = talloc();
	Song->select = 0;
	treewalk2(root);
	if (bacw != NULL) {
		Song = bacw;
		Song->select = 1;
	}
}

void forward() {
	check = 0;
	forw = talloc();
	Song->select = 0;		//노래가 선택되지 않았다고 표시
	treewalk3(root);
	if (forw != NULL) {
		Song = forw;		//forw가 가리키는 노드를 Song이 가리키게 함. 즉, 다음곡을 선택함
		Song->select = 1;	//노래가 선택되었다고 표시
	}
}

void songinfo() {
	check = 0;
	printf("검색할 노래의 제목을 입력하세요.\n");
	scanf("%s", pt);
	Songsearch(root);
	if (check != 1)						//노래정보가 출력되지 않았을때 출력
		printf("목록에 노래가 없습니다\n");
	Sleep(5000);			//5초간 멈춤
}