#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>//exit存在
#include <string.h>

int selectflag = 1;/*全局变量，记录是否存盘,1为未存*/

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
Student * Sort(Student *head);//插入排序法
Student * Sort_xuehao(Student *head);
Student *Locate(Student *head, int num);
Student *Locate_name(Student *head, char *name);
Student * Qur(Student *head);




/*--------------------------------------一级菜单----------------------------------------------*/
void Menu()
{
	printf("\n\n\n");
	printf("\t\t\t\t\t|=================================================|\n");
	printf("\t\t\t\t\t|\t\t学生自主选课系统                  |\n");
	printf("\t\t\t\t\t|=================================================|\n\n\n");
	printf("\t\t\t\t\t|=================请确认你的操作==================|\n");
	printf("\t\t\t\t\t| 1.输入记录                           2.删除记录 |\n");
	printf("\t\t\t\t\t| 3.查询记录                           4.修改记录 |\n");
	printf("\t\t\t\t\t| 5.插入记录                           6.统计记录 |\n");
	printf("\t\t\t\t\t| 7.排序记录                           8.保存记录 |\n");
	printf("\t\t\t\t\t| 9.显示记录                           0.退出系统 |\n");
	printf("\t\t\t\t\t|=================================================| \n");
	

}


void Disp(Student *head){
	Student *p = head;
	if (head == NULL)
	{
		printf("\t\t\t\t---->没有数据！");
		getchar();
		getchar();
		system("cls");
		return;
	}
	else
	{
		while (head->next != NULL)
		{   
		    //printf("学号 姓名 C语言 数学 英语\n ");
			printf("\n%4d%8s%4d%4d%4d", head->xuehao, head->name, head->c_score, head->math_score, head->eng_score);
			head = head->next;
		}
		printf("\n%4d%8s%4d%4d%4d", head->xuehao, head->name, head->c_score, head->math_score, head->eng_score);
	}
	head = p;
}


/*------------------“打开文件”----------------*/

FILE *openfile(char *f_name,char *openmode)
{
	FILE *p = NULL;
	if ((p = fopen(f_name, openmode)) == NULL)
	{
		printf("无法打开%s文件!\n",f_name);
		exit(0);
	}
	return (p);
}

/*--------------------1.增添-------------------*/

Student * Add(Student *head)
{
	Student *pnew, *p = head;
	pnew = (Student *)malloc(sizeof(Student));
	pnew->xuehao=1;
	if(pnew->xuehao!=0){
	printf("请输入学号<按'0'返回主菜单>: \n");
	scanf("%d", &pnew->xuehao);
	if (pnew->xuehao == 0) return head;
	printf("输入姓名： \n");
	scanf("%s", pnew->name);
	printf("请输入C语言成绩[0--100]： \n");
	scanf("%d", &pnew->c_score);
	printf("请输入数学成绩[0--100]： \n");
	scanf("%d", &pnew->math_score);
	printf("请输入英语成绩[0--100]： \n");
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
	printf("输入学号（按‘0’返回主菜单）：\n");
	scanf("%d",&xuehao);
	if(xuehao==0){Menu(); break;}
	else{
	printf("姓名：\n");
	scanf("%s",name);
	printf("C 语言成绩：\n");
	scanf("%d",&c_score);
	printf("数学成绩：\n");
	scanf("%d",&math_score);
	printf("英语成绩：\n");
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


	
	

/*--------------------2.保存-------------------*/

void Save(Student *head,FILE *fp){
	Student *p = head;
	if (head == NULL) {
		printf("没有数据可保存！");
		return;
	}

	while (head->next != NULL)
	{
		fwrite(head, sizeof(struct student), 1, fp);      //写入记录
		head = head->next;
	}
	fwrite(head, sizeof(struct student), 1, fp);      //写入记录
	head = p;
	printf("保存成功，按任意键继续。");
	selectflag = 0;
	_getch();
	system("cls");
}
/*--------------------3.错误-------------------*/

void Wrong(){
	printf("\t\t\t\t\t输入错误！请正确输入！按任意键继续你的选择！");
	_getch();
	system("cls");
}


void Tongji(Student *head){
	Student *p = head, *pMax = NULL, *pC = NULL, *pM = NULL, *pE = NULL;
	int score = 0, c_score = 0, eng_score = 0, math_score = 0, Totalscore = 0;
	int res[3] = { 0, 0, 0 };//不及格人数 
	while (p != NULL){
		int Tscore;
		Tscore = p->c_score + p->eng_score + p->math_score;//学生总分 
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
	printf("----------------统计结果--------------\n");
	printf("C语言成绩不及格人数：%d人\n", res[0]);
	printf("数学成绩不及格人数： %d人\n", res[1]);
	printf("英语成绩不及格人数： %d人\n", res[2]);
	printf("--------------------------------------\n");
	printf("总分最高的学生：      %s  总分:  %d\n", pMax->name, pMax->c_score + pMax->eng_score + pMax->math_score);
	printf("C语言成绩最高的学生： %s  分数:  %d\n", pC->name, pC->c_score);
	printf("数学成绩最高的学生：  %s  分数:  %d\n", pE->name, pE->eng_score);
	printf("英语成绩最高的学生：  %s  分数:  %d\n", pM->name, pM->math_score);
	printf("--------------------------------------\n");
	printf("按任意键返回主菜单！");
	getchar();
	getchar();
	system("cls");

}

/*-------------获取课程账户记录总数-------------*/
int get_count(FILE *fp){
	int s_begain, s_end, s_count;
	fseek(fp, 0L, 0);                  //文件指针移到开头
	s_begain = ftell(fp);             //获取文件首的偏移字节数
	fseek(fp, 0L, 2);                 //文件指针移到末尾
	s_end = ftell(fp);                //获取文件尾的偏移字节数
	s_count = (s_end - s_begain) / sizeof(struct student);    //计算记录总数
	return s_count;
}

/*-------------课程节点-------------*/

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
			printf("不能成功分配储存块！\n");
			exit(0);
		}
		printf("%d",fread(p1, sizeof(struct student), 1, fp) );      //读出记录
		if (i == 1)head = p1;
		else p2->next = p1;
		p2 = p1;
	} 
	p2->next = NULL;
	return head;
}


/*-------------删除-------------*/

Student * Del(Student *head){
	int xuehao;
	Student *p1 = head, *p2 = head;
	printf("请输入要删除信息对应的学号：");
	scanf("%d",&xuehao);
	if (head->next == NULL){
		printf("删除成功！\n");
		printf("请按任意键继续！");
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
		printf("删除成功！\n");
	}
	else printf("无指定数据信息！\n");
	printf("请按任意键继续！");
	getchar();
	getchar();
	system("cls");
	return head;
}

/*-------------修改-------------*/

void Modify(Student *head){
	int xuehao;
	Student *p = head;
	system("cls");
	printf("\n\t\t-->请输入现有学号：");
	scanf("%d", &xuehao);
	if(xuehao==0) Menu();
	p = Locate(head, xuehao);
	if (p == NULL) printf("无该学生记录！\n");
	else{
		printf("该生原始数据：");
		printf("\n%4d%8s%4d%4d%4d", p->xuehao, p->name, p->c_score, p->math_score, p->eng_score);
		printf("请输入该生修改后的数据：\n");
	    printf("请输入学号<按'0'返回主菜单>: \n");
	    scanf("%d", &p->xuehao);
	    if (p->xuehao == 0) Menu();
    	printf("输入姓名： \n");
    	scanf("%s", p->name);
    	printf("请输入C语言成绩[0--100]： \n");
    	scanf("%d", &p->c_score);
    	printf("请输入数学成绩[0--100]： \n");
    	scanf("%d", &p->math_score);
     	printf("请输入英语成绩[0--100]： \n");
	    scanf("%d", &p->eng_score);
		selectflag = 1;
		printf("请按任意键继续！");
		getchar();
		getchar();
		system("cls");
	}
}

/*-------------插入-------------*/

Student * Insert(Student *head){
	Disp(head);
	Student *p0 = NULL, *p1 = head;
	int xuehao;
	printf("\n请在学号之后输入插入位置：");
	scanf("%d", &xuehao);
	
	printf("\n请输入所需要添加的信息！\n");
	//添加一个新节点
	p0 = (Student *)malloc(sizeof(Student));
	printf("请输入学号<按'0'返回主菜单>: \n");
	scanf("%d", &p0->xuehao);
	if (p0->xuehao == 0)return head;
	printf("输入姓名： \n");
	scanf("%s", p0->name);
	printf("请输入C语言成绩[0--100]： \n");
	scanf("%d", &p0->c_score);
	printf("请输入数学成绩[0--100]： \n");
	scanf("%d", &p0->math_score);
	printf("请输入英语成绩[0--100]： \n");
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
	printf("请输入要插入的节点\n");
	scanf("%d",i);
	printf("请输入要插入的信息\n"); 
	printf("请输入学号<按'0'返回主菜单>: \n");
	scanf("%d", &xuehao);
	if (xuehao == 0) return head;
	printf("输入姓名： \n");
	scanf("%s", name);
	printf("请输入C语言成绩[0--100]： \n");
	scanf("%d", &c_score);
	printf("请输入数学成绩[0--100]： \n");
	scanf("%d", &math_score);
	printf("请输入英语成绩[0--100]： \n");
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
	
	
	


/*-------------排序-------------*/

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
	printf("排序成功！\n");
	printf("排序后：\n");
	Disp(head);
	printf("按任意键继续！");
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

/*-------------查找节点-------------*/
//利用学号
Student *Locate(Student *head, int num){
	Student *p = head;
	while ((p->xuehao != num) && (p->next != NULL))
		p = p->next;
	if (p->xuehao != num)
		p = NULL;
	return p;
}
//利用姓名
Student *Locate_name(Student *head, char name[10]){
	Student *p = head;
	while ((strcmp(p->name,name)!=0) && (p->next!= NULL))
		p = p->next;
	if (strcmp(p->name,name)!=0)
		p = NULL;
	return p;
}

/*-------------查询学生记录-------------*/
Student * Qur(Student *head){
	system("cls");
	Student *p = head;
	int select, flag=1;
	printf("\n\t\t1.按学号查询");
	printf("\n\t\t2.按姓名查询");
	printf("\n\t\t0.返回主菜单");
	printf("\n\t\t-->请输入你的选择：");
	scanf("%d", &select);
	while (flag){
		switch (select){
		case 0:
			Menu(); break;
		case 1:
			printf("\t\t请输入你要查询信息的对应学号：");
			int num;
			scanf("%d", &num);
			p = Locate(head, num);
			printf("查询结果：");
			if (p == NULL) printf("无该学生记录！\n");
			else printf("\n%4d%8s%4d%4d%4d\n", p->xuehao, p->name, p->c_score, p->math_score, p->eng_score);
			break;
		case 2:
			printf("\t\t请输入你要查询信息的对应姓名：");
			char name[10];
			scanf("%s", &name);
			p = Locate_name(head, name); 
			printf("查询结果：");
			if (p == NULL) {
			printf("无该学生记录！\n"); getchar();}	
			else printf("\n%4d%8s%4d%4d%4d\n", p->xuehao, p->name, p->c_score, p->math_score, p->eng_score);
			break;
		default: printf("输入错误！"); break;
		}
		printf("是否还要继续（Y/N）：");
		char a; 
		scanf("%c", &a);
		if (a != 'Y' && a != 'y') {
			flag = 0;
			printf("\n\t\t\t按任意键继续！");
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
		printf("\n\t\t\t\t\t\t\t请输入对应数字： ");
		scanf("%d", &select);
		Infor = openfile("D:\\student\\Outfile.txt", "wb");
		if (select == 0){
			if (selectflag == 1){
				printf("\n\t\t\t\t\t\t\t还未存盘，是否存盘（Y/N）： ");
				char a; getchar();
				scanf("%c",&a);
				if (a == 'Y'||a=='y'){
					Save(head, Infor);
					fclose(Infor);
					printf("\n\t\t\t\t\t\t保存成功！按任意键退出。");
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
			记录模块：输入：1；查询：3；更新:2.删除4.修改5.插入7.排序；统计:6；输出8.9；
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



