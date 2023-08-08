#include "account_info.h"

size_t save_account(AccountInfo *info, FILE *fp)
{
    return fwrite(info, sizeof(AccountInfo), 1, fp);
}

size_t read_account(AccountInfo *info, FILE *fp)
{
    return fread(info, sizeof(AccountInfo), 1, fp);
}

void open_account_info()
{
    FILE *fp = fopen("./lhy/account_info", "w");
    if (NULL == fp)
        return;

    AccountInfo info = {1, "admin", "123456", kAdmin};
    save_account(&info, fp);

    AccountInfo info1 = {1, "lhy", "123456", kAdmin};
    save_account(&info1, fp);

    fclose(fp);
}

void read_account_info()
{
    FILE *fp = fopen("./lhy/account_info", "r");
    if (NULL == fp)
        return;
    
    while (1)
    {
        AccountInfo info;
        if (1 != read_account(&info, fp))
            break;

        printf("Read id : %d\n", info.id);
        printf("Read Account : %s\n", info.account);
        printf("Read pwd : %s\n", info.pwd);
        printf("Read type : %d\n", info.type);
        printf("====================\n");
    }

    fclose(fp);
}

void test_info()
{
    open_account_info();
    read_account_info();
}

