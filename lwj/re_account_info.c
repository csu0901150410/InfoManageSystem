#include <stdlib.h>
#include <stdio.h>

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
    strncpy(account.name,name,MAX_ACCOUNT_STRLEN);//复制
    strncpy(account.name,pwd,MAX_ACCOUNT_STRLEN);
    return account;
}

/**
 * @brief 创建账号列表
*/
bool creat_accountlist(AccountList *list,FILE *fp)
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
void init_account_info(char *filename,AccountList *list)
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
bool find_account_list(const AccountList *list,const AccountInfo *acc)
{
    for(size_t i=0;i<list->num;++i){
        AccountInfo *account = list->info + i;
        if(account_campare(account,acc))
            return true;
    }
      return false;
}