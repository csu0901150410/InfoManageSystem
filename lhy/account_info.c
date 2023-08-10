#include <stdlib.h>
#include <string.h>

#include "account_info.h"
#include "utils.h"

/**
 * @brief 保存账户信息到文件
 * 
 * @param info 账户结构体指针
 * @param fp 文件指针
 * @return true 保存成功
 * @return false 保存失败
 */
bool save_account(AccountInfo *info, FILE *fp)
{
    if (!info || !fp)
        return false;

    size_t nums = fwrite(info, sizeof(AccountInfo), 1, fp);
    return (1 == nums);
}

/**
 * @brief 从文件读取账户信息
 * 
 * @param info 账户结构体指针
 * @param fp 文件指针
 * @return true 读取成功
 * @return false 读取失败
 */
bool read_account(AccountInfo *info, FILE *fp)
{
    if (!info || !fp)
        return false;

    size_t nums = fread(info, sizeof(AccountInfo), 1, fp);
    return (1 == nums);
}

// 打印账户信息
void account_print(AccountInfo *info)
{
    LOG("Account : id-%d name-%s pwd-%s type-%d", info->id, info->name, info->pwd, info->type);
}

// 测试多账号写入
void test_save_account_info()
{
    FILE *fp = fopen("./account_info", "w");
    if (NULL == fp)
        return;

    AccountInfo info = {1, "admin", "123456", kAdmin};
    save_account(&info, fp);

    AccountInfo info1 = {1, "lhy", "123456", kAdmin};
    save_account(&info1, fp);

    account_print(&info);
    account_print(&info1);
    LOG("***********************");

    fclose(fp);
}

// 测试多账号读取
void test_read_account_info()
{
    FILE *fp = fopen("./account_info", "r");
    if (NULL == fp)
        return;
    
    while (1)
    {
        AccountInfo info;
        if (!read_account(&info, fp))
            break;

        account_print(&info);
        LOG("====================");
    }

    fclose(fp);
}

void test_info()
{
    LOG("hello");

    test_save_account_info();
    test_read_account_info();
}

/**
 * @brief 系统开始运行时，需要从文件中将所有登记的账户信息读取出来存储形成账户列表，
 * 当控制台请求登录时，将输入的账密和账户列表中的信息比对，符合即登入，否则登入失败。
 * 但是当系统初次运行时，这个文件还是空文件，所以我们需要写入初始账密。
 */

/**
 * @brief 创建账户列表
 * 
 * @param al 账户列表指针
 * @param fp 文件指针
 * @return true 创建成功
 * @return false 创建失败
 */
bool create_account_list(AccountList *al, FILE *fp)
{
	rewind(fp);
	fseek(fp, 0, SEEK_END);
	size_t capacity = ftell(fp);
	size_t size = sizeof(AccountInfo);
	size_t num = capacity / size;

	AccountInfo* ptr = (AccountInfo*)malloc(num * size);
	if (NULL == ptr)
		return false;
	AccountInfo* curr = ptr;

	rewind(fp);
	while (1)
	{
		AccountInfo account;
		if (!read_account(&account, fp))
			break;
		*curr = account;
		curr++;
	}

	al->ptr = ptr;
	al->num = num;
	return true;
}

/**
 * @brief 销毁账户列表
 * 
 * @param al 账户列表指针
 */
void destroy_account_list(AccountList *al)
{
    if (NULL == al || NULL == al->ptr)
        return;

    for (size_t i = 0; i < al->num; ++i)
    {
        AccountInfo *curr = al->ptr + i;
        free(curr);
        curr = NULL;
    }
}

/**
 * @brief 打印账户列表
 * 
 * @param al 账户列表指针
 */
void print_account_list(AccountList *al)
{
    if (NULL == al || NULL == al->ptr)
        return;

    for (size_t i = 0; i < al->num; ++i)
    {
        AccountInfo *curr = al->ptr + i;
        account_print(curr);
    }
}

/**
 * @brief 账户信息初始化
 * 
 * @param filename 保存账户信息的文件路径
 */
void account_init(char *filename, AccountList *al)
{
    // 创建或者打开账户信息文件，有则打开，无则创建
	FILE* fp = fopen(filename, "a+");
	if (NULL == fp)
		return;

	fseek(fp, 0, SEEK_END);
	size_t size = ftell(fp);
	if (0 == size)
	{
		AccountInfo super;
		strncpy(super.name, "root", MAX_ACCOUNT_STRLEN);
		strncpy(super.pwd, "123456", MAX_ACCOUNT_STRLEN);
		super.id = 0;
		super.type = kSuper;
		save_account(&super, fp);
	}

    create_account_list(al, fp);

	fclose(fp);
}

