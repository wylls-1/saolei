#include "saolei.h"
using namespace std;
DWORD WINAPI fun_time(LPVOID)
{
    while(1)
    {
        Sleep(1000);
        time_i++;
        if(time_i>=60)
        {
            time_j++;
            time_i=0;
        }
    }
}

int main()
{
    CreateThread(NULL, 0,fun_time,NULL, 0,NULL);
    show_for_user();
    initmap();
    while(1)
    {
        gotoxy(mapsize+2,0);
        if(time_j) cout<<time_j<<"·Ö"<<time_i<<"Ãë";
        else cout <<time_i<<"Ãë";
         HideCursor();
         input();
         reflesh();
    }

    return 0;
}













