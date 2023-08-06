#include <stdio.h>
#include <stdlib.h>

//登录界面
void loginMenu()
{
	//登录操作同步到文件 
    printf("----------【信息管理系统欢迎您】-----------\n");
    printf("\t\t0.管理员登录\n");
    printf("\t\t1.用户登录\n");
    printf("------------------请选择身份-----------------\n"); 
	printf("---------------------------------------------\n");	
 }
 
 //用户登录交互 
 //登录的操作
 void  login()
 {
 	int op=0;
 	scanf("%d",&op);
 	switch(op)
 	{
 		case 0:
 		       printf("姓名:");
 		       scan  
		case 1: 
		        printf("")
	 }
  } 
  
 //管理员操作 菜单界面
 void managerMenu()
 {
    printf("**************管理员你好******************");
    printf("\t\t0.退出登录\n");
    printf("\t\t1.录入用户信息\n");
    printf("\t\t2.删除用户信息\n");
    printf("\t\t3.修改用户信息\n");
    printf("\t\t4.浏览用户信息\n");
    printf("\t\t5.查找用户信息\n");
    printf("****************************************");
 }

 //管理员的交互 
 //根据所选的菜单项，实现相应的操作
void  managerDown()
{
    int op=0;
    scanf("%d",&op);
    switch (op)
    {
    case:0
        printf("正常退出登录");
        system("pause");
        exit(0);
        loginMenu();
        break;
    case:1
        printf("**************【录入用户信息】******************");
        break;
    case:2
        printf("**************【删除用户信息】******************");
        break;
    case:3
        printf("**************【修改用户信息】******************");
        break;
    case:4
        printf("**************【浏览用户信息】******************");
        break;
    case:5
        printf("**************【查找用户信息】******************");
        break;   
    default:
        printf("输入错误，请重新输入");
        system("pause");
        break;
    }
}
  
int main()
{
   // loginMenu();
    while (1)
    {
        managerMenu();
        managerDown();
   
    }
    

	system("pause");
	return 0;
}