#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>//exit����
#include <string.h>

int selectflag = 1;/*ȫ�ֱ�������¼�Ƿ����,1Ϊδ��*/

struct student{
	int xuehao;
	char name[10];
	int c_score;
	int math_score;
	int eng_score;
	struct student *next;
};
typedef struct student Student;

void Menu();
void Disp(Student *head);
FILE *openfile(char *f_name, char *openmode);
Student * Add(Student *head);
void Save(Student *head, FILE *fp);
void Wrong();
int get_count(FILE *fp);
Student *creat_link(int s_count, FILE *fp);
Student * Del(Student *head);
void Modify(Student *head);
Student * Insert(Student *head);
Student * Sort(Student *head);//��������
Student * Sort_xuehao(Student *head);
Student *Locate(Student *head, int num);
Student *Locate_name(Student *head, char *name);
Student * Qur(Student *head);




/*--------------------------------------һ���˵�----------------------------------------------*/
void Menu()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t|=================================================|\n");
	printf("\t\t\t\t\t|\t\tѧ������ѡ��ϵͳ                  |\n");
	printf("\t\t\t\t\t|=================================================|\n\n\n");
	printf("\t\t\t\t\t|=================��ȷ����Ĳ���==================|\n");
	printf("\t\t\t\t\t| 1.�����¼                           2.ɾ����¼ |\n");
	printf("\t\t\t\t\t| 3.��ѯ��¼                           4.�޸ļ�¼ |\n");
	printf("\t\t\t\t\t| 5.�����¼                           6.ͳ�Ƽ�¼ |\n");
	printf("\t\t\t\t\t| 7.�����¼                           8.�����¼ |\n");
	printf("\t\t\t\t\t| 9.��ʾ��¼                           0.�˳�ϵͳ |\n");
	printf("\t\t\t\t\t|=================================================| \n");
	

}


void Disp(Student *head){
	Student *p = head;
	if (head == NULL)
	{
		printf("\t\t\t\t---->û�����ݣ�");
		getchar();
		getchar();
		system("cls");
		return;
	}
	else
	{
		while (head->next != NULL)
		{   
		    //printf("ѧ�� ���� C���� ��ѧ Ӣ��\n ");
			printf("\n%4d%8s%4d%4d%4d", head->xuehao, head->name, head->c_score, head->math_score, head->eng_score);
			head = head->next;
		}
		printf("\n%4d%8s%4d%4d%4d", head->xuehao, head->name, head->c_score, head->math_score, head->eng_score);
	}
	head = p;
}


/*------------------�����ļ���----------------*/

FILE *openfile(char *f_name,char *openmode)
{
	FILE *p = NULL;
	if ((p = fopen(f_name, openmode)) == NULL)
	{
		printf("�޷���%s�ļ�!\n",f_name);
		exit(0);
	}
	return (p);
}

/*--------------------1.����-------------------*/

Student * Add(Student *head)
{
	Student *pnew, *p = head;
	pnew = (Student *)malloc(sizeof(Student));
	pnew->xuehao=1;
	if(pnew->xuehao!=0){
	printf("������ѧ��<��'0'�������˵�>: \n");
	scanf("%d", &pnew->xuehao);
	if (pnew->xuehao == 0) return head;
	printf("���������� \n");
	scanf("%s", pnew->name);
	printf("������C���Գɼ�[0--100]�� \n");
	scanf("%d", &pnew->c_score);
	printf("��������ѧ�ɼ�[0--100]�� \n");
	scanf("%d", &pnew->math_score);
	printf("������Ӣ��ɼ�[0--100]�� \n");
	scanf("%d", &pnew->eng_score);
	pnew->next = NULL;
}
	if (head == NULL){
		head = pnew;
	}
	else
	{
		while (head->next != NULL)
		{
			head = head->next;
		}
		head->next = pnew;
		head = p;
	}
}
/*Student * Add(Student *head)
{
	int xuehao,c_score,math_score,eng_score;
	char name[20];
	Student *p;
	xuehao=1;
	while(xuehao!=0){
	printf("����ѧ�ţ�����0���������˵�����\n");
	scanf("%d",&xuehao);
	if(xuehao==0){Menu(); break;}
	else{
	printf("������\n");
	scanf("%s",name);
	printf("C ���Գɼ���\n");
	scanf("%d",&c_score);
	printf("��ѧ�ɼ���\n");
	scanf("%d",&math_score);
	printf("Ӣ��ɼ���\n");
	scanf("%d",&eng_score);
}
}
	p = (Student *)malloc(sizeof(Student));
	p->xuehao=xuehao;
	strcpy(p->name,name);
	p->c_score=c_score;
	p->math_score=math_score;
	p->eng_score=eng_score;
	p->next=head->next;
	head->next=p;
}*/


	
	

/*--------------------2.����-------------------*/

void Save(Student *head,FILE *fp){
	Student *p = head;
	if (head == NULL) {
		printf("û�����ݿɱ��棡");
		return;
	}

	while (head->next != NULL)
	{
		fwrite(head, sizeof(struct student), 1, fp);      //д���¼
		head = head->next;
	}
	fwrite(head, sizeof(struct student), 1, fp);      //д���¼
	head = p;
	printf("����ɹ����������������");
	selectflag = 0;
	_getch();
	system("cls");
}
/*--------------------3.����-------------------*/

void Wrong(){
	printf("\t\t\t\t\t�����������ȷ���룡��������������ѡ��");
	_getch();
	system("cls");
}


void Tongji(Student *head){
	Student *p = head, *pMax = NULL, *pC = NULL, *pM = NULL, *pE = NULL;
	int score = 0, c_score = 0, eng_score = 0, math_score = 0, Totalscore = 0;
	int res[3] = { 0, 0, 0 };//���������� 
	while (p != NULL){
		int Tscore;
		Tscore = p->c_score + p->eng_score + p->math_score;//ѧ���ܷ� 
		if (Tscore > Totalscore) {
			Totalscore = Tscore;
			pMax = p;
		}
		if (p->c_score > c_score){
			c_score = p->c_score;
			pC = p;
		}
		if (p->eng_score > eng_score){
			eng_score = p->eng_score;
			pE = p;
		}
		if (p->math_score > math_score){
			math_score = p->math_score;
			pM = p;
		}
		if (p->c_score < 60) res[0]++;
		if (p->eng_score < 60) res[1]++;
		if (p->math_score < 60) res[2]++;
		p = p->next;
	}
	printf("----------------ͳ�ƽ��--------------\n");
	printf("C���Գɼ�������������%d��\n", res[0]);
	printf("��ѧ�ɼ������������� %d��\n", res[1]);
	printf("Ӣ��ɼ������������� %d��\n", res[2]);
	printf("--------------------------------------\n");
	printf("�ܷ���ߵ�ѧ����      %s  �ܷ�:  %d\n", pMax->name, pMax->c_score + pMax->eng_score + pMax->math_score);
	printf("C���Գɼ���ߵ�ѧ���� %s  ����:  %d\n", pC->name, pC->c_score);
	printf("��ѧ�ɼ���ߵ�ѧ����  %s  ����:  %d\n", pE->name, pE->eng_score);
	printf("Ӣ��ɼ���ߵ�ѧ����  %s  ����:  %d\n", pM->name, pM->math_score);
	printf("--------------------------------------\n");
	printf("��������������˵���");
	getchar();
	getchar();
	system("cls");

}

/*-------------��ȡ�γ��˻���¼����-------------*/
int get_count(FILE *fp){
	int s_begain, s_end, s_count;
	fseek(fp, 0L, 0);                  //�ļ�ָ���Ƶ���ͷ
	s_begain = ftell(fp);             //��ȡ�ļ��׵�ƫ���ֽ���
	fseek(fp, 0L, 2);                 //�ļ�ָ���Ƶ�ĩβ
	s_end = ftell(fp);                //��ȡ�ļ�β��ƫ���ֽ���
	s_count = (s_end - s_begain) / sizeof(struct student);    //�����¼����
	return s_count;
}

/*-------------�γ̽ڵ�-------------*/

Student *creat_link(int s_count,FILE *fp){
	Student *head = NULL, *p1, *p2 = NULL;
	int i;
	fseek(fp, 0L, 0);
	if (s_count <= 0){
		return NULL;
	}
	
	for (i = 1; i <= s_count; i++)
	{
		if ((p1 = (Student  *)malloc(sizeof(Student))) == NULL){
			printf("���ܳɹ����䴢��飡\n");
			exit(0);
		}
		printf("%d",fread(p1, sizeof(struct student), 1, fp) );      //������¼
		if (i == 1)head = p1;
		else p2->next = p1;
		p2 = p1;
	} 
	p2->next = NULL;
	return head;
}


/*-------------ɾ��-------------*/

Student * Del(Student *head){
	int xuehao;
	Student *p1 = head, *p2 = head;
	printf("������Ҫɾ����Ϣ��Ӧ��ѧ�ţ�");
	scanf("%d",&xuehao);
	if (head->next == NULL){
		printf("ɾ���ɹ���\n");
		printf("�밴�����������");
		getchar();
		system("cls");
		return NULL;
	}
	while ((p1->xuehao != xuehao) && (p1->next != NULL)){
		p2 = p1;
		p1 = p1->next;
	}
	if (p1->xuehao == xuehao){
		if (head == p1) head = p1->next;
		else p2->next = p1->next;
		free(p1);
		printf("ɾ���ɹ���\n");
	}
	else printf("��ָ��������Ϣ��\n");
	printf("�밴�����������");
	getchar();
	getchar();
	system("cls");
	return head;
}

/*-------------�޸�-------------*/

void Modify(Student *head){
	int xuehao;
	Student *p = head;
	system("cls");
	printf("\n\t\t-->����������ѧ�ţ�");
	scanf("%d", &xuehao);
	if(xuehao==0) Menu();
	p = Locate(head, xuehao);
	if (p == NULL) printf("�޸�ѧ����¼��\n");
	else{
		printf("����ԭʼ���ݣ�");
		printf("\n%4d%8s%4d%4d%4d", p->xuehao, p->name, p->c_score, p->math_score, p->eng_score);
		printf("����������޸ĺ�����ݣ�\n");
	    printf("������ѧ��<��'0'�������˵�>: \n");
	    scanf("%d", &p->xuehao);
	    if (p->xuehao == 0) Menu();
    	printf("���������� \n");
    	scanf("%s", p->name);
    	printf("������C���Գɼ�[0--100]�� \n");
    	scanf("%d", &p->c_score);
    	printf("��������ѧ�ɼ�[0--100]�� \n");
    	scanf("%d", &p->math_score);
     	printf("������Ӣ��ɼ�[0--100]�� \n");
	    scanf("%d", &p->eng_score);
		selectflag = 1;
		printf("�밴�����������");
		getchar();
		getchar();
		system("cls");
	}
}

/*-------------����-------------*/

Student * Insert(Student *head){
	Disp(head);
	Student *p0 = NULL, *p1 = head;
	int xuehao;
	printf("\n����ѧ��֮���������λ�ã�");
	scanf("%d", &xuehao);
	
	printf("\n����������Ҫ��ӵ���Ϣ��\n");
	//���һ���½ڵ�
	p0 = (Student *)malloc(sizeof(Student));
	printf("������ѧ��<��'0'�������˵�>: \n");
	scanf("%d", &p0->xuehao);
	if (p0->xuehao == 0)return head;
	printf("���������� \n");
	scanf("%s", p0->name);
	printf("������C���Գɼ�[0--100]�� \n");
	scanf("%d", &p0->c_score);
	printf("��������ѧ�ɼ�[0--100]�� \n");
	scanf("%d", &p0->math_score);
	printf("������Ӣ��ɼ�[0--100]�� \n");
	scanf("%d", &p0->eng_score);
	p0->next = NULL;

	while (head != NULL){
		if (head->xuehao == xuehao){
			p0->next = head->next;
			head->next = p0;
		}
		head = head->next;
	}
	head = p1;
	return head;
}

/*Student * Insert(Student *head){
	Student *temp;
	Student *target;
	Student *p;
	int i,j,xuehao,c_score,math_score,eng_score;
	char name[10];
	printf("������Ҫ����Ľڵ�\n");
	scanf("%d",i);
	printf("������Ҫ�������Ϣ\n"); 
	printf("������ѧ��<��'0'�������˵�>: \n");
	scanf("%d", &xuehao);
	if (xuehao == 0) return head;
	printf("���������� \n");
	scanf("%s", name);
	printf("������C���Գɼ�[0--100]�� \n");
	scanf("%d", &c_score);
	printf("��������ѧ�ɼ�[0--100]�� \n");
	scanf("%d", &math_score);
	printf("������Ӣ��ɼ�[0--100]�� \n");
	scanf("%d", &eng_score);
	target=head;
	j=1;
	for(;j<i-1;target=target->next,++j);
	temp=(Student*)malloc(sizeof(Student));
	temp->c_score=c_score;
	temp->eng_score=eng_score;
	temp->math_score=math_score;
	temp->xuehao=xuehao;
	strcpy(temp->name,name);
	p=target->next;
	target->next=temp;
	temp->next=p;
	return target;
}*/
	
	
	


/*-------------����-------------*/

Student * Sort(Student *head){
	Student *first, *t, *p = NULL, *q;
	first = head->next;
	head->next = NULL;
	while (first != NULL)
	{
		for (t = first, q = head; ((q != NULL) && ((q->c_score + q->eng_score + q->math_score) > (t->c_score + t->eng_score + t->math_score))); p = q, q = q->next);
		first = first->next;
		if (q == head)
			head = t;
		else
			p->next = t;
		t->next = q;
	}
	printf("����ɹ���\n");
	printf("�����\n");
	Disp(head);
	printf("�������������");
	getchar();
	getchar();
	system("cls");
	return head;
}

Student * Sort_xuehao(Student *head){
	Student *first, *t, *p = NULL, *q;
	first = head->next;
	head->next = NULL;
	while (first != NULL)
	{
		for (t = first, q = head; ((q != NULL) && (q->xuehao < t->xuehao)); p = q, q = q->next);
		first = first->next;
		if (q == head)
			head = t;
		else
			p->next = t;
		t->next = q;
	}
	return head;
}

/*-------------���ҽڵ�-------------*/
//����ѧ��
Student *Locate(Student *head, int num){
	Student *p = head;
	while ((p->xuehao != num) && (p->next != NULL))
		p = p->next;
	if (p->xuehao != num)
		p = NULL;
	return p;
}
//��������
Student *Locate_name(Student *head, char name[10]){
	Student *p = head;
	while ((strcmp(p->name,name)!=0) && (p->next!= NULL))
		p = p->next;
	if (strcmp(p->name,name)!=0)
		p = NULL;
	return p;
}

/*-------------��ѯѧ����¼-------------*/
Student * Qur(Student *head){
	system("cls");
	Student *p = head;
	int select, flag=1;
	printf("\n\t\t1.��ѧ�Ų�ѯ");
	printf("\n\t\t2.��������ѯ");
	printf("\n\t\t0.�������˵�");
	printf("\n\t\t-->���������ѡ��");
	scanf("%d", &select);
	while (flag){
		switch (select){
		case 0:
			Menu(); break;
		case 1:
			printf("\t\t��������Ҫ��ѯ��Ϣ�Ķ�Ӧѧ�ţ�");
			int num;
			scanf("%d", &num);
			p = Locate(head, num);
			printf("��ѯ�����");
			if (p == NULL) printf("�޸�ѧ����¼��\n");
			else printf("\n%4d%8s%4d%4d%4d\n", p->xuehao, p->name, p->c_score, p->math_score, p->eng_score);
			break;
		case 2:
			printf("\t\t��������Ҫ��ѯ��Ϣ�Ķ�Ӧ������");
			char name[10];
			scanf("%s", &name);
			p = Locate_name(head, name); 
			printf("��ѯ�����");
			if (p == NULL) {
			printf("�޸�ѧ����¼��\n"); getchar();}	
			else printf("\n%4d%8s%4d%4d%4d\n", p->xuehao, p->name, p->c_score, p->math_score, p->eng_score);
			break;
		default: printf("�������"); break;
		}
		printf("�Ƿ�Ҫ������Y/N����");
		char a; 
		scanf("%c", &a);
		if (a != 'Y' && a != 'y') {
			flag = 0;
			printf("\n\t\t\t�������������");
			getchar();
			system("cls");
		}
	}
	return p;
}




void main(){
	int select;
	Student *head = NULL, *p = NULL;
	FILE *Infor = NULL;
	Infor = openfile("D:\\student\\Outfile.txt", "ab+");
	head = creat_link(get_count(Infor), Infor);
	fclose(Infor);
	system("cls");
	while (1){
		Menu();
		printf("\n\t\t\t\t\t\t\t�������Ӧ���֣� ");
		scanf("%d", &select);
		Infor = openfile("D:\\student\\Outfile.txt", "wb");
		if (select == 0){
			if (selectflag == 1){
				printf("\n\t\t\t\t\t\t\t��δ���̣��Ƿ���̣�Y/N���� ");
				char a; getchar();
				scanf("%c",&a);
				if (a == 'Y'||a=='y'){
					Save(head, Infor);
					fclose(Infor);
					printf("\n\t\t\t\t\t\t����ɹ�����������˳���");
					_getch();
					exit(0);
				}
				else{
					fclose(Infor);
					exit(0);
				}
			}
			fclose(Infor);
			exit(0);
		}
		else{
			/*
			��¼ģ�飺���룺1����ѯ��3������:2.ɾ��4.�޸�5.����7.����ͳ��:6�����8.9��
			*/

			switch(select){
			case 1:head = Add(head);  break;
			case 2:head = Del(head); break;
			case 3:Qur(head); break; 
			case 4:Modify(head); break;     
			case 5:head = Insert(head); break; 
			case 6:Tongji(head); break;
			case 7:head = Sort(head); break;
			case 8:Save(head,Infor); break;
			case 9:Disp(head); break;
			default:Wrong(); break;
			fclose(Infor);
			}
		}
		
	}


}



