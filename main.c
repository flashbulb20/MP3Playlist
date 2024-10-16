#define _CRT_SECURE_NO_WARNINGS				//scanf���� ����
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <Windows.h>
#include <string.h>

struct tfield {
	struct tfield* left;			//���ʰ���
	char Singer[20];			//������
	char title[20];				//�뷡����
	char date[20];				//�߸���
	int select;					//�뷡�� �����Ͽ������� ��Ÿ��
	struct tfield* right;			//�����ʰ���
};

int check = 0;
char dat1[20], dat2[20], dat3[20], pt[20];
struct tfield* root, * Song, * forw, * bacw;			//����Ʈ���� ����Ű�� root�� �ϳ��� ��带 ����ų�� �ִ� ����ü ������
struct tfield* talloc();									//���� �޸� �Ҵ�
struct tfield* gentree(struct tfield*, char*, char*, char*);	//����Ʈ�� ����
struct tfield* addNode(struct tfield*, char*, char*, char*);	//����Ʈ�� Ž���� ����߰�
void Songsearch(struct tfield*);	//�뷡�˻�
void treewalk1(struct tfield*);		//��ȸ
void treewalk2(struct tfield*);
void treewalk3(struct tfield*);
void makelist();				//��ϻ����ϴ� �Լ�
void display();					//ȭ�鱸���ϴ� �Լ�
void play(char*);				//�뷡�� �����ϴ� �Լ�
void backward();				//������
void forward();					//������
void addSong();					//�뷡�߰�
void songinfo();				//�뷡�������

void main() {					//�����Լ�
	int button = 0;				//���ư�� �������� �Է¹޴� ����
	root = NULL;
	Song = NULL;				//root�� Song�� NULL�� ����Ű�� ��
	printf("\t\t���� ������� �뷡\n\n\n");
	if (Song != NULL) {
		if (Song->select == 1)
			printf("\t\t%s - %s\n\n", Song->title, Song->Singer);
	}
	else {
		printf("\t\t���õ� ���� �����ϴ�\n\n\n");
	}
	printf("1.��ϻ���\t2.���\t3.������\t4.������\t5.�뷡�߰�\t6.�뷡����\t7.����\n\n");		//ȭ�� �޴�
	while (1) {									//���ѹݺ�
		scanf("%d", &button);
		if (button == 1) {						//1�� ��ư�� ������ ��� ����
			printf("\n��ϻ���\n\n");
			makelist();
			display();
			button = 0;				//�ٽ� ��ư�� �ʱ�ȭ
		}
		else if (button == 2) {					//2�� ��ư�� ������ �뷡���
			printf("\n����� �뷡������ �Է��ϼ���\n");
			scanf("%s", pt);
			play(pt);
			display();
			button = 0;
		}
		else if (button == 3) {					//3�� ��ư�� ������ ������ ���
			printf("\n������\n");
			Sleep(1000);
			backward();
			display();
			button = 0;
		}
		else if (button == 4) {					//4�� ��ư�� ������ ������ ���
			printf("\n������\n");
			Sleep(1000);
			forward();
			display();
			button = 0;
		}
		else if (button == 5) {					//5�� ��ư�� ������ �뷡 �߰�
			printf("\n�뷡�߰�\n");
			addSong();
			display();
			button = 0;
		}
		else if (button == 6) {					//6����ư�� ������ �뷡�˻�
			printf("\n\t\t�뷡�����˻�\n\n");
			songinfo();
			display();
			button = 0;
		}
		else if (button == 7) {					//7�� ��ư�� ������ ����
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
		strcpy(p->Singer, s);					//�Է¹��� ������,����,�߸����� p�� ����Ű�� ��忡 ����
		strcpy(p->title, n);
		strcpy(p->date, a);
		p->left = p->right = NULL;
	}
	else if (strcmp(n, p->title) < 0)
		p->left = gentree(p->left, s, n, a);	//������ ���Ͽ� ������ ���ʰ����� �̵�
	else
		p->right = gentree(p->right, s, n, a);	//�ƴϸ� �����ʰ����� �̵�
	return p;
}

struct tfield* addNode(struct tfield* p, char* s, char* n, char* a) {
	if (p == NULL) {
		p = talloc();
		strcpy(p->Singer, s);				//gentree�� ����
		strcpy(p->title, n);
		strcpy(p->date, a);
		p->left = p->right = NULL;
	}
	else if (strcmp(n, p->title) < 0)
		p->left = addNode(p->left, s, n, a);
	else if (strcmp(s, p->Singer) == 0 && strcmp(n, p->title) == 0)		//������� ������ ���Ͽ� �����ÿ� �̹� �ִٰ� �˸�
		printf("�̹� �ִ� ���Դϴ�.\n");
	else
		p->right = addNode(p->right, s, n, a);
	return p;
}

void treewalk1(struct tfield* p) {
	if (p != NULL) {
		treewalk1(p->left);
		if (strcmp(pt, p->title) == 0) {	//������ȸ�� �ϸ鼭 �Է¹��� ����� ���Ͽ� ������
			Song = p;						//����
		}
		treewalk1(p->right);
	}
}

void treewalk2(struct tfield* p) {
	if (p != NULL) {
		treewalk2(p->left);
		if (strcmp(p->title, Song->title) < 0) {	//���� Song�� ����Ű�� ����� ���Ͽ� ������ ����
			bacw = p;
		}
		treewalk2(p->right);
	}
}

void treewalk3(struct tfield* p) {
	if (p != NULL) {
		treewalk3(p->left);
		if (strcmp(p->title, Song->title) > 0) {	//���� Song�� ����Ű�� ����� ���Ͽ� Ŭ��
			if (check < 1) {						//���õ��� �ʾ�����
				forw = p;							//������ ���õǾ����� ǥ��
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
			printf("\n ����: %s\t ����: %s\t �߸���: %s\n\n\n", p->title, p->Singer, p->date);
			check = 1;						//�뷡������ ǥ�õǾ����� 1
		}
		Songsearch(p->right);
	}
}

void makelist() {
	printf("������, ����, �߸��� ������ ������ �Է��ϰ� �������� Ctrl+z�� �����ÿ�.\n");
	while (scanf("%s %s %s", dat1, dat2, dat3) != EOF) {		//Ctrl+z�� ������ ������
		root = gentree(root, dat1, dat2, dat3);					//����Ʈ�� ����
	}
	printf("����� ��������� ���ĵ˴ϴ�.");
	Sleep(1000);
}

void addSong() {
	printf("������, ����, �߸��� ������ ������ �Է��ϰ� �������� Ctrl+z�� �����ÿ�.\n");
	while (scanf("%s %s %s", dat1, dat2, dat3) != EOF) {
		root = addNode(root, dat1, dat2, dat3);
	}
	printf("�Ϸ�\n");
	Sleep(1000);
}

void display() {
	system("cls");						//ȭ�� �����
	printf("\t\t���� ������� �뷡\n\n\n");
	if (Song != NULL) {					//Song�� NULL���� ����Ű�� ������
		if (Song->select == 1)			//Song�� �뷡�� �����ϰ� ������ ����-������ ���
			printf("\t\t%s - %s\n\n\n", Song->title, Song->Singer);
	}
	else {								//Song�� NULL���� ����Ű�� ������
		printf("\t\t���õ� ���� �����ϴ�\n\n\n");
	}
	printf("1.��ϻ���\t2.���\t3.������\t4.������\t5.�뷡�߰�\t6.�뷡����\t7.����\n\n");		//�޴�
}

void play(char* pt) {
	Song = talloc();		//���� �޸� �Ҵ�
	treewalk1(root);			//��ȸ
	if (Song != NULL)
		Song->select = 1;	//�뷡�� ���õǾ����� ǥ��
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
	Song->select = 0;		//�뷡�� ���õ��� �ʾҴٰ� ǥ��
	treewalk3(root);
	if (forw != NULL) {
		Song = forw;		//forw�� ����Ű�� ��带 Song�� ����Ű�� ��. ��, �������� ������
		Song->select = 1;	//�뷡�� ���õǾ��ٰ� ǥ��
	}
}

void songinfo() {
	check = 0;
	printf("�˻��� �뷡�� ������ �Է��ϼ���.\n");
	scanf("%s", pt);
	Songsearch(root);
	if (check != 1)						//�뷡������ ��µ��� �ʾ����� ���
		printf("��Ͽ� �뷡�� �����ϴ�\n");
	Sleep(5000);			//5�ʰ� ����
}