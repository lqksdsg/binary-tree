#include <iostream>
#include <bitree.h>
#include <string>
using namespace std;

int main()
{
    bitree<__int64> *root = new bitree<__int64>;
    root->initialize(99999999999999);
    root->insert(444444444444444);
    root->insert(7777777777777777777);
    root->insert(4444444444444);
    root->insert(88888888888888888);
    root->insert(99999999999999);
    for(int i = 10000;i>0;--i)
    {
        root->insert(i);
    }
    root->sort();//递归排序
    return 0;
}
