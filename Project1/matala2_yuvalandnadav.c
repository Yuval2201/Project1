#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	long unsigned int id;
	char* name;
	long unsigned int salary;
	union year
	{
		char hebrewDate[7];
		unsigned long int regular;
	}year;
}Worker;

typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;

int TheMinsal(WorkerList* head);
Worker* CreateWorker(int a);
void printWorker(Worker* a, int c);
WorkerList* addWorker(WorkerList* head, Worker* w);
int index(WorkerList* head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float percent);
WorkerList* reverse(WorkerList* head);
void freeWorkers(WorkerList* head);

WorkerList* list = NULL;
WorkerList* e;
WorkerList* newHead;

void main() {

	int a;
	long unsigned searchid;
	Worker* v;
	unsigned int size;
	printf("How many workers do you have?");
	scanf("%d", &size); // ����� ���� ������� ����� ������� ���� ������

	for (int i = 0; i < size; i++)//����� �� ����� ������ ���� ������
	{
		printf("if hebraw enter 1, regular enter 0: ");
		scanf("%d", &a);
		v = CreateWorker(a);

		list = addWorker(list, v);
	}

	//���� �����
	printf("print list \n");

	for (e = list; e != NULL; e = e->next) {
		printWorker(e->data, 0);
	}
	//��� �� ����� �� ������ ����
	printf("Enter the ID number of the worker you want to search for:\n");
	scanf("%ld", &searchid);
	int indexWorker = index(list, searchid);
	printf("the index of the worker tou were looking for: %d\n\n", indexWorker);


	//��� �� ����� �� ���� ����� �����
	printf("delete The low Worker \n");
	list = deleteWorstWorker(list);
	for (e = list; e != NULL; e = e->next) {
		printWorker(e->data, 0);
	}


	printf("\n");
	printf("update worker \n");//���� ��� ������� ����
	update_worker(list, 10);
	for (e = list; e != NULL; e = e->next) {
		printWorker(e->data, 0);
	}

	printf("reverse \n");//����� �� ���� �� �� ������� ������
	list = reverse(list);
	for (e = list; e != NULL; e = e->next) {
		printWorker(e->data, 0);
	}


	freeWorkers(list);
}


Worker* CreateWorker(int a) //�������  ������ ����� ���� ���� ����� �����
{
	Worker* b;
	b = (Worker*)calloc(1, sizeof(Worker));
	printf("Enter a new Worker!\n");
	char arr[50]; //����� ������ ���� ������ ���
	printf("Enter a name:");
	fseek(stdin, 0, SEEK_END);
	gets(arr);//����� ����� ����� ���� �����
	b->name = (char*)malloc(1 * (strlen(arr) + 1));// ����� ����� ���
	strcpy(b->name, arr); // ����� ������� ������ ������� ��� �� �����
	if (!(b->name)) exit(1);  // ���� ������ ���� ��������
	printf("enter a  id:");
	scanf("%d", &b->id);
	printf("enter a  salary:");
	scanf("%d", &b->salary);
	printf("enter a year:");
	if (a == 1) {
		scanf("%s", b->year.hebrewDate);
		printf("\n");
	}
	else {
		scanf("%d", &b->year.regular);
		printf("\n");
	}

	return b;
}


void printWorker(Worker* a, int c)  //  �������� �����
{
	printf("the name worker: %s\nthe id is: %d\nthe salary is: %d\n", a->name, a->id, a->salary);
	if (c == 1)
		printf("the year of start work is: %s\n", a->year.hebrewDate);
	else if (c == 0)
		printf("the year of start work is: %d\n\n", a->year.regular);
}

WorkerList* addWorker(WorkerList* head, Worker* w) {
	WorkerList* ptr;
	WorkerList* p = head;


	ptr = (WorkerList*)calloc(1, sizeof(WorkerList));//����� ������� ������ ������
	ptr->data = w;
	if (!ptr) {//���� �� ������ ������
		exit(0);
	}
	if (head == NULL) {//����� ���� �� ������ ����
		ptr->next = NULL;
		head = ptr;
		return head;
	}
	else if (p->data->salary < w->salary) { //  ���� ��� ������� �� ����� ���� ��� ����� ����� ���� ����
		ptr->next = p;
		head = ptr;
		return head;
	}
	else
		for (p = head; p->next != NULL; p = p->next) {//�� ������� �� ����� ������ ������� �����
			if ((p->data->salary <= w->salary) && (p->next->data->salary >= w->salary)) {

				ptr->next = p->next;
				p->next = ptr;
				return head;
			}
		}
	p->next = ptr;
	ptr->next = NULL;
	return head;

}



int index(WorkerList* head, long unsigned id) {//������� ������� �� ������ �� ����� �� ������ ���� ������
	int d = 1;
	WorkerList* a = head;
	for (a = head; a != NULL; a = a->next) {
		if (a->data->id != id) {
			++d;
		}
		else
			return(d);
	}
	return -1;
}

WorkerList* deleteWorstWorker(WorkerList* head) {

	int minSalary = TheMinsal(head); //������� ������ �� ���� ����� �����

	if (head->data->salary == minSalary) {//�� ������ ������ ��� �������� * ���� ���� ���

		if (head->next != NULL) //�� ������ �� ���� 1 ���� ����
		{
			head = head->next;
			return head;
		}

		else
		{
			head = NULL;//�� ��� ����
			printf("List is empty now");
			return head;
		}
	}

	{
		//���� �����
		WorkerList* prev = head;
		WorkerList* current = head;
		while (current->next != NULL && current->data->salary !=
			minSalary) {
			prev = current;
			current = current->next;
		}
		if (current->data->salary == minSalary) {
			prev->next = prev->next->next;
			free(current);
		}
		return head;
	}
}

int TheMinsal(WorkerList* head) {
	int minSalary = head->data->salary;
	WorkerList* p;
	for (p = head->next; p->next != NULL; p = p->next) {
		if (p->next->data->salary < minSalary)
			minSalary = p->next->data->salary;
	}
	return minSalary;
}






void update_worker(WorkerList* head, float percent) {
	WorkerList* p;
	float q = percent;

	for (p = head; p != NULL; p = p->next) {
		p->data->salary = (p->data->salary + (p->data->salary) * q);
	}

}

WorkerList* reverse(WorkerList* head) {
	WorkerList* A, * B, * C;
	if (head == NULL || head->next == NULL)
		return head;
	A = head;
	B = A->next;
	C = B->next;
	while (C != NULL)
	{
		B->next = A;
		A = B;
		B = C;
		C = C->next;
	}
	B->next = A;
	head->next = NULL;
	head = B;
	return head;



}

void freeWorkers(WorkerList* head)//����� �������
{
	WorkerList* p;
	WorkerList* pmove = NULL;

	for (p = head; p != NULL; p = p->next)
	{
		free(p->data->name);
		pmove = head->next;
		free(p);
		p = pmove;

	}

}

