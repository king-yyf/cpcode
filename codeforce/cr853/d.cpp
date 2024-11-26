#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

string ans;
int n;

bool dfs()
{
    char str[5];
    if (scanf("%s", str) == -1) return false;

    if (!strcmp(str, "pair"))
    {
        ans += str;
        ans += '<';
        if (!dfs()) return false;
        ans += ',';
        if (!dfs()) return false;
        ans += '>';
    }
    else ans += str;

    return true;
}

int main()
{
    scanf("%d",&n);

    if (dfs() && scanf("%*s") == -1){
       for(int i=0;i+3<=ans.size();++i){
        if(ans.substr(i,3)=="int")n--;
       }
       assert(n==0);
       puts(ans.c_str());
    }
    else puts("Error occurred");

    return 0;
}

