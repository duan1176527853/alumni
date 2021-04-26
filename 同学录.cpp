#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 文件名
#define ALUMNI_FILE "alumni.txt" 
// 定义信息结构体 
typedef struct student{
  // 身份证 
  char    id[20];
  // 人名
  char  name[20];
  //性别
  char gender[3];
  //年龄
  int old; 
  //手机号 
  char tele[12]; 
  // qq号 
  char  qq[11];
  //电子邮箱
  char email[20]; 
  //地址 
  char  address[60];
  // 爱好 
  char hobby[60];
}Student;
// 定义链表结点结构类型
struct node
{
  Student student;
  struct node* next;
}; 
// 显示功能菜单
void showMenu(struct node *head);  
// 添加同学信息 传递链表头结点指针 
void addStudent(struct node *head);  
// 查看所有学生 
void queryStudent(struct node *head); 
// 根据姓名，qq，手机号等信息删除同学信息 
void deleteStudent(struct node *head);  
// 根据同学ID，手机号，姓名，qq号，地址查找并修改学生结点
void updateStudent(struct node *head);   
// 定义链表基础功能函数 
struct node* createStudentNode(Student *student);
struct node* insertStudentNode(struct node* head, Student *student);
struct node* createStudentList();
void freeStudentList(struct node* head);
struct node* queryStudentList(struct node* head, int id);
int deleteStudentLstById(struct node* head, int id);
int getStudentListLength(struct node* head);
void queryprint(struct node* head);
void printStudentLstInfo(struct node* head);
void saveStudentLstToFile(struct node* head);
void readStudentListFromFile(struct node* head);
void error(const char* err);

int main() {
  // 创建链表保存数据
  struct node* list = createStudentList(); 
  // 当文件alumni.txt已有学生信息时
  // 先全部读取所有学生信息
  readStudentListFromFile(list);
  
  // 显示功能主菜单 
  showMenu(list);    
  char a[10];  
  while (1) {
    printf("\n请输出0-5,回车结束！\n");
    if (fgets(a, 10, stdin) != NULL) {  // 按行读取，0-5字符表示功能
      switch (a[0]) {
      case '0':    // 退出程序 
        freeStudentList(list);
        printf("ByeBye,下次再见!\n");
        exit(0);
      case '1':    // 添加
        addStudent(list);
        break;
      case '2':    // 查看
        queryprint(list);
        break;
      case '3':    // 删除
        deleteStudent(list);
        break;
      case '4':    // 修改
        updateStudent(list);break;
      case '5':
      	queryStudent(list);//展示 
        break;
      default:
        printf("请重新输入正确的功能数字0-5!\n");
      }
    }
  }
  return 0;
}

// 创建学生结点
struct node* createStudentNode(Student *student)
{
  struct node* p = (struct node*)calloc(1,sizeof(struct node));
	Student *b;
  if(p != NULL)
  {
    if(student != NULL)
    {
      b = &(p->student);
      strcpy(b->id , student->id);
      strcpy(b->name, student->name);
      strcpy(b->gender, student->gender);
      b->old = student->old;
      strcpy(b->tele , student->tele);
      strcpy(b->qq , student->qq);
      strcpy(b->email , student->email);
      strcpy(b->address , student->address);
      strcpy(b->hobby , student->hobby);
    }
    p->next = NULL;
  }
  return p;
} 


// 表尾增加同学结点 
struct node* insertStudentNode(struct node* head, Student *student)
{
  if(head != NULL)
  {
    struct node* node = createStudentNode(student);
    Student *b = &(node->student);
    if(node != NULL)
    {
      struct node* p = head;

      // 循环找到链表最后的结点
      while(p->next != NULL)
        p = p->next;
      p->next = node;
      return node;
    }
  }
  return NULL;
}


// 创建带头结点的空链表
struct node* createStudentList()
{
  // 创建头结点
  return createStudentNode(NULL);
}


// 释放同学录链表内存空间
void freeStudentList(struct node* head)
{
  struct node* p = head;
  while(p != NULL)
  {
    head = p->next;
    free(p);
    p = head;
  }
}




// 根据同学ID，手机号，姓名，qq号，地址查找学生结点
struct node* queryStudentList(struct node* head, char temp[])
{
  
  struct node *p = NULL;
  if(head != NULL)
  {
    p = head->next;
    while(p != NULL)
    {
      if(strcmp(p->student.id , temp)==0) break;
      else if(strcmp(p->student.name,temp)==0) break;
      else if(strcmp(p->student.qq,temp)==0) break;
      else if(strcmp(p->student.tele,temp)==0) break;
      else if(strcmp(p->student.address,temp)==0) break;
      p = p->next;
    }
  }
  return p;
} 


// 根据学生姓名，qq，手机号，删除同学结点
int deleteStudentList(struct node* head, char temp[])
{
  // p保存当前结点，pre保存前一个结点 
  struct node *p = NULL, *pre = NULL;
  // 返回结果0或1 
  if(head != NULL)
  {
    pre = head;
    p = head->next;
    while(p != NULL)
    {
      if(strcmp(p->student.tele, temp)==0)
      {
	  	pre->next = p->next;
        free(p);        
        break;
		}
	  else if(strcmp(p->student.name, temp)==0)
      {
        pre->next = p->next;
        free(p);       
        break;
      }
      else if(strcmp(p->student.qq,temp)==0)
	  {
        pre->next = p->next;
        free(p);       
        break;
      }
      pre = p;
      p = p->next;
    }
  }
  return 1;
} 


// 获取同学录链表的长度 
int getStudentListLength(struct node* head)
{
  int n = 0;
  struct node *p = NULL;
  if(head != NULL)
  {
    p = head->next;
    while(p != NULL)
    {
      n++;
      p = p->next;
    }
  }
  return n;
}
void queryprint(struct node* head){
	char temp[60];struct node* p;
	printf("请输入该同学的信息（身份证号，姓名，手机号，qq，地址任输其一）\n");
	scanf("%s",temp);
	p=queryStudentList(head, temp);
	if(p!=NULL) {
	printf("\n找到了这位老友了！\n");
	printf("%s %s %s %s %d %s %s %s %s\n", (p->student).id, (p->student).name,\
		  (p->student).gender,(p->student).tele ,(p->student).old , (p->student).qq , (p->student).email,\
		   (p->student).address ,(p->student).hobby);}
	else printf("抱歉并未找到这位同学");
printf("\n**************************************\n");
}
int showInfo()
{	int a;
	printf("请选择需要全部输出的项："); 
	printf("1.姓名\n");
	printf("2.身份证\n");
	printf("3.性别\n");
	printf("4.手机号\n");
	printf("5.年龄\n");
	printf("6.QQ号\n");
	printf("7.email\n");
	printf("8.地址\n");
	printf("9.爱好\n");
	printf("0.全部信息展示\n");
	printf("请输入选择的展示的方式：");
	scanf("%d",&a);
	switch(a)
	{
		case 1:printf("*****姓名列表如下：\n");break;
		case 2:printf("姓名------身份证\n");break;
		case 3:printf("姓名------性别\n");break;
		case 4:printf("姓名------手机号\n");break;
		case 5:printf("姓名------年龄\n");break;
		case 6:printf("姓名------QQ号\n");break;
		case 7:printf("姓名------email\n");break;
		case 8:printf("姓名------地址\n");break;
		case 9:printf("姓名------爱好\n");break;
		case 0:printf("名字 身份证号	性别 手机号 年龄   QQ号  email    地址   爱好\n");break;
	}
	return a;
}
// 打印出链表所有结点保存的同学信息
void printStudentListInfo(struct node* head)
{
  struct node* p = head->next;int a;
  a= showInfo();
  Student *b;
  while(p != NULL)
  {	
    b = &(p->student);
    switch(a){
    	case 1: printf("*****%s\n",b->name);break;
    	case 2:printf("%s------%s\n",b->name,b->id);break;
    	case 3:printf("%s------%s\n",b->name,b->gender);break;
    	case 4:printf("%s------%s\n",b->name,b->tele);break;
    	case 5:printf("%s------%d\n",b->name,b->old);break;
    	case 6:printf("%s------%s\n",b->name,b->qq);break;
    	case 7:printf("%s------%s\n",b->name,b->email);break;
    	case 8:printf("%s------%s\n",b->name,b->address);break;
    	case 9:printf("%s------%s\n",b->name,b->hobby);break;
    	case 0:printf("%s %s %s %s %d %s %s %s %s\n", b->name,b->id,  b->gender, b->tele ,b->old ,  \
						b->qq , b->email, b->address ,b->hobby);break;
	}
    p = p->next;
  }
 printf("\n**************************************\n");
}


// 文件保存同学链表所有信息
void saveStudentListToFile(struct node* head)
{
  if(head != NULL)
  {
    struct node *p = head->next;
    FILE* fp = fopen(ALUMNI_FILE, "w+");
    if(fp != NULL)
    {
      while(p != NULL)
      {
         fprintf(fp,"%s %s %s %s %d %s %s %s %s\n", (p->student).name, (p->student).id,\
		  (p->student).gender,(p->student).tele ,(p->student).old , (p->student).qq , (p->student).email,\
		   (p->student).address ,(p->student).hobby);
        p = p->next;
      }
      fclose(fp);
      
    }else {      
      error("打开alumni.txt文件失败，请检查！/n"); 
}}}
 // 从文件读取图书信息保存到链表
void readStudentListFromFile(struct node* head)
{
  FILE* fp = fopen(ALUMNI_FILE, "a+");
  Student student;
  if (fp != NULL) {
    while (fscanf(fp, "%s %s %s %s %d %s %s %s %s",student.name, student.id, student.gender, \
	 student.tele ,&student.old ,student.qq , student.email, student.address ,student.hobby) != EOF) {
        
      insertStudentNode(head, &student);
    }
    fclose(fp);
  }else {
    error("打开alumni.txt文件失败，请检查!\n");
  }
} 


// 在屏幕显示各类出错信息，并退出程序
void error(const char* err)
{
  printf(err);
  exit(-1);
 } 
void showMenu(struct node *head) {
  printf("----------欢迎使用同学录管理系统----------\n\n");
  printf("当前系统共有%d位同学！\n\n", getStudentListLength(head));
  printf("系统提供以下功能：\n");
  printf("1:添加同学信息\n");
  printf("2:查看同学信息\n");
  printf("3:删除同学信息\n");
  printf("4:修改同学信息\n");
  printf("5.展示同学录\n");
  printf("0:退出系统\n\n");
}
void addStudent(struct node *head) {
  
  printf("请您按提示添加同学信息：\n");
  printf("依次输入名字 身份证号	性别 手机号 年龄   QQ号  email    地址   爱好		，以空格分隔:\n");
  
  char a[1024];
  Student student;
  if (fgets(a, 1024, stdin) != NULL && \
        sscanf(a,"%s %s %s %s %d %s %s %s %s",student.name, student.id, student.gender, \
	student.tele, &student.old ,student.qq , student.email, student.address ,student.hobby )!= EOF) {


        // 已存在，则无法增加 
    if (queryStudentList(head, student.id) != NULL||queryStudentList(head, student.name) != NULL||\
	queryStudentList(head, student.tele) != NULL||queryStudentList(head, student.qq) != NULL)
	printf("该信息对应的同学已经存在，无法增加!\n");
    else {
      insertStudentNode(head, &student);
      saveStudentListToFile(head);
      printf("添加成功，当前共有%d位同学!\n\n", getStudentListLength(head));
    }


  }
  else {
    error("输入有误，请重新添加!\n");
  }
	printf("\n**************************************\n");
}
void queryStudent(struct node *head) {
  printStudentListInfo(head);
}


void deleteStudent(struct node *head) {
  printf("请输入要删除的同学信息（姓名，手机号，qq(填其中之一即可)：");
  char a[1024];char temp[60];
  if (fgets(a, 1024, stdin) != NULL && \
       sscanf(a, "%s", temp) != EOF) {


    if (deleteStudentList(head, temp))
    { saveStudentListToFile(head);
      printf("该同学信息删除成功!\n");
      
    }else
    {
      printf("找不到该同学!\n");
    }
  }
  else {
    error("输入有误，请重新输入!\n");
  }
}
int modify(Student *student){
	int a,t;char temp[60];int flag=0;
	printf("请输入要修改的信息：");
	printf("1.身份证号 ");
	printf("2.姓名 ");
	printf("3.性别 ");
	printf("4.年龄 ");
	printf("5.手机号 ");
	printf("6.QQ号 ");
	printf("7.Email "); 
	printf("8.地址 ");
	printf("9.爱好 ");
	scanf("%d",&a);
	switch(a){
		case 1:{scanf("%s",temp);strcpy(student->id,temp);flag=1;break;}
		case 2:{scanf("%s",temp);strcpy(student->name,temp);flag=1;break;}
		case 3:{scanf("%s",temp);strcpy(student->gender,temp);flag=1;break;}
		case 4:{scanf("%d",&t);student->old=t;flag=1;break;}
		case 5:{scanf("%s",temp);strcpy(student->tele,temp);flag=1;break;}
		case 6:{scanf("%s",temp);strcpy(student->qq,temp);flag=1;break;}
		case 7:{scanf("%s",temp);strcpy(student->email,temp);flag=1;break;}
		case 8:{scanf("%s",temp);strcpy(student->address,temp);flag=1;break;}
		case 9:{scanf("%s",temp);strcpy(student->hobby,temp);flag=1;break;}
	}  return flag;    
}
void updateStudent(struct node *head) {

  printf("请输入要修改的同学信息：(姓名，身份证，qq,手机号，地址均可)\n");
	char temp[60]; char a[1024];
  if (fgets(a, 1024, stdin) != NULL &&  \
      sscanf(a, "%s", &temp) != EOF) {
        
    struct node *p = queryStudentList(head, temp);
 
    if (p == NULL)
      printf("该信息对应的同学不存在!\n");
    else {
      printf("该编号对应的信息如下，请按照提示修改：\n");
      printf("名字	   身份证号     性别  手机号   年龄  QQ号       	email       地址      爱好		\n");
      Student *student = &(p->student);
      printf("%s %s %s %s %d %s %s %s %s\n", student->name, student->id, student->gender,  student->tele ,student->old , \
	student->qq , student->email, student->address ,student->hobby);
      if (modify(student)) {
        saveStudentListToFile(head);
        printf("修改成功，修改后的学生信息如下：\n");
      printf("名字	身份证号  性别   	年龄 手机号   	QQ号     email      地址      	爱好		\n");
    printf("%s %s %s %s %d %s %s %s %s\n", student->name, student->id, student->gender, student->tele , student->old , \
	student->qq , student->email, student->address ,student->hobby);
      }
      else {
        error("输入有误，请重新修改!\n");
      }
    }
  }
  else {
    error("输入有误，请重新输入!\n");
  }
  printf("\n**************************************\n");
}
