#include "account_info.h"

int main()
{
    // test_info();

    AccountList al;
    account_init("./account_info", &al);
    print_account_list(&al);
    destroy_account_list(&al);

    return 0;
}