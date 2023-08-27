#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include <stdbool.h>
#include "re_account_info.h"
#include "re_utils.h"
bool save_account(AccountInfo *info,FILE *fp)
{
    if(!info||!fp)
        return false;
    
    size_t num = fwrite(info,sizeof(AccountInfo),1,fp);
     return (1 == num);
}


/**
 * @brief  从文件读取账户信息
 * @param info 账户结构体指针
 * @param fp 文件指针*/
bool read_account(AccountInfo *info,FILE *fp)
{
    if(!info||!fp)
        return false;
    
    size_t num = fread(info,sizeof(AccountInfo),1,fp);
     return (1 == num);
}


/**
 * @brief 账号信息输出
 * 调用可变参数进行输出
*/
void account_prinf(AccountInfo *info)
{
     LOG("Account id:%d , name:%s ,pwd:%s ,type:%s",info->id,info->name,info->pwd,info->type);
}

/**
 * @brief 账户名称、密码匹配
*/

bool account_campare(const AccountInfo *infoA,const AccountInfo *infoB)
{
    //AccountInfo

    if(strncmp(infoA->name,infoB->name,MAX_ACCOUNT_STRLEN))
        return false;
    if(strncmp(infoA->pwd,infoB->pwd,MAX_ACCOUNT_STRLEN))
        return false;

    return true;
}

/**
 * @brief 账户信息封装
*/
AccountInfo account_warp(const char *name,const char *pwd)
{
    AccountInfo account;//账号结构体
    strncpy(account.name,name,MAX_ACCOUNT_STRLEN);//复制,name复制到account.name
    strncpy(account.name,pwd,MAX_ACCOUNT_STRLEN);
    return account;
}

/**
 * @brief 创建账号列表
*/
bool creat_accountlist(AccountList_Node *list,FILE *fp)
{
    rewind(fp);//文件内部的位置指针重新指向一个流(数据流/文件)的开头
    fseek(fp,0,SEEK_END);//将文件指针定位到末尾
    
    size_t capacity =ftell(fp);
    size_t size=sizeof(AccountInfo);
    size_t num= capacity/size;//文件可放入的账户数量
     
    AccountInfo* info = (AccountInfo*)malloc(num*size);
    if(info == NULL)
     return false;
   
   AccountInfo* curr=info;

   rewind(fp);//文件内部的位置指针指向从文件的开头
   while(1)//遍历
   {
    AccountInfo account;//账号结构体
    if(!read_account(&account,fp))//调用read_account判断文件内的账号是否已经全部读出
        break;
    *curr = account; //将账号account赋值给curr指针间接访问的info指针，将account。
    *curr++;//指向info指针的指针偏移
   }
   list->info =info;
   list->num=num;    
}

/**
 * @brief 账号信息初始化
 * 
 * @param 
*/
void init_account_list(char *filename,AccountList_Node *list)
{
    FILE* fp=fopen(filename,"a+");//“a+”----有则打开 无则创建
    if(NULL==fp)
       return ;
    
    //文件指针fp的总大小
    fseek(fp,0,SEEK_END);
    size_t size=ftell(fp);

    //文件内没有初值则为账号赋初值
    if(size==0)
    {
        AccountInfo account;
        strncpy(account.name,"root",MAX_ACCOUNT_STRLEN);
        strncpy(account.pwd,"123456",MAX_ACCOUNT_STRLEN);
        account.id=0;
        account.type=Ksuper;
        save_account(&account,fp);
    }
     //将初始化的账号信息放入账号列表
     creat_accountlist(list,fp);
     fclose(fp);

}
/**
 * @brief 搜索账号列表
 * 
 * @param list 账户列表指针
 * @param  acc    账号指针
 * @return true 给定账号在账号列表中
 * @return  false 给定账号不在账号列表中
*/
bool find_account_list(const AccountList_Node *list,const AccountInfo *acc)
{
    for(size_t i=0;i<list->num;++i){
        AccountInfo *account = list->info + i;
        if(account_campare(account,acc))
            return true;
    }
      return false;
}

/**
 * @brief 创建节点
 * 返回值：指针，指向我们本函数新创建的一个节点的首地址
*/
pNode creatlist()
{
   pNode head = (pNode) malloc(sizeof(AccountList_Node));
   if(NULL==head)
    {           printf("malloc error\n");
                return NULL;   
    }

 
    FILE *fp=fopen("accountinfo.txt","r+");
     if(NULL==fp)
       return ;

    pNode curr=head;//  取链表的入口
    while(1)
    {       //临时节点
        pNode temp=(pNode)malloc(sizeof(AccountList_Node));
        if(NULL==temp)
            exit(-1);//节点分配空间失败退出      
        
/*fscanf（fp，“%s%s”，temp->info->name，temp->info->pass）的返回值是成功匹配并成功读取的参数个数。
    在这里 如果成功读取了两个字符串，返回值就是2.不等于2----录入完毕*/
        if(2!=fscanf(fp,"%s%s",temp->info->name,temp->info->pwd))
        {  free(temp);
            break;
        }
        curr->next=temp;
        curr=temp;
        curr->next=NULL;
    }
    return head;
}

//使用链表初始化
void ini_account(pNode head)
{
    pNode temp =head->next;
    if(!temp)
    {
        temp= (pNode)malloc(sizeof(AccountList_Node));
        head->next=temp;
          
        strcpy(temp->info->name,"root",);
        strcpy(temp->info->pwd,"123456"); 
    }
  strcpy(temp->info->name,"root",);
  strcpy(temp->info->pwd,"123456");
    temp->next=NULL;
}







