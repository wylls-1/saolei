#ifndef SAOLEI_H_INCLUDED
#define SAOLEI_H_INCLUDED
#include<iostream>
#include<time.h>
#include<windows.h>
#include<conio.h>
using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
const int maxs =1000;
const int  mapsize=15;
const int leishu=20;
int x=0,y=0,n=0,bushu=0,nx=0,ny=0,time_i=0,time_j=0;
int maptrue[mapsize][mapsize]={0};//记录雷 -1为雷
int mapfalse[mapsize][mapsize]={0};
//后台数据
int initlei(int nx,int ny)//初始雷
{
    int i=0;
    srand(time(0));
    while(i<leishu)
    {
        int a,b;
        a=rand()%mapsize;
        b=rand()%mapsize;
        if(a!=x&&b!=y&&maptrue[a][b]!=-1) {
            i++;
            maptrue[a][b]=-1;
        }
    }
    return 0;
}

int initdata()
{
    int i,j;
    for(i=0;i<mapsize;i++)
        for(j=0;j<mapsize;j++)
    {
        if(maptrue[i][j]==-1)
        {
            for(int a=-1;a<2;a++)
            for(int b=-1;b<2;b++)
            {
                if(i+a>=0&&i+a<mapsize&&j+b>0&&j+b<mapsize&&maptrue[i+a][j+b]!=-1)
                    maptrue[i+a][j+b]++;
            }
            maptrue[i][j]=-1;
        }

    }
    return 0;
}

void dfs_show(int nx,int ny)
{
    if(nx<0||nx>=mapsize||ny<0||ny>=mapsize||maptrue[nx][ny]==-1)
        return ;
    if(maptrue[nx][ny]!=0){
        mapfalse[nx][ny]=1;
        return;
    }
    for(int i=-1;i<2;i++)
        for(int j=-1;j<2;j++)
    {
        if(i==0&&j==0) {mapfalse[nx][ny]=1;continue;}
        int xx=i+nx,yy=ny+j;
        if(xx>=0&&xx<mapsize&&yy>=0&&yy<mapsize&&mapfalse[xx][yy]==0&&maptrue[xx][yy]!=-1)
        {
            mapfalse[xx][yy]=1;
            n++;
            dfs_show(xx,yy);
        }
    }
}

int click(int nx,int ny)//点击事件
{
    if(maptrue[nx][ny]==-1&&mapfalse[nx][ny]==0)
    {
        MessageBoxA(NULL,"游戏失败","",0);
    }
    else if(maptrue[nx][ny]==0)
    {
        mapfalse[nx][ny]=1;
        n++;
        dfs_show(nx,ny);
    }
    else
    {
       mapfalse[nx][ny]=1;
       n++;
    }
    if(n>=mapsize*mapsize-leishu)
    {
        void reflesh();
        reflesh();
        MessageBoxA(NULL,"恭喜你！游戏胜利！","",0);
        return 0;
    }
    return 1;
}
void reflesh()
{
    void gotoxy(int n_y,int n_x);
    gotoxy(0,0);
    for(int i=0;i<mapsize;i++)
        for(int j=0;j<mapsize;j++)
    {
        if(i==x&&j==y/2){
             SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_RED);//红色
            cout<<"■";
        }
        else if(mapfalse[i][j]==0){
             SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_GREEN);//绿色
        cout<<"■";
        }
        else if(maptrue[i][j]==0){
            SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);//白色
            cout<<"■";
        }
        else {
            cout<<maptrue[i][j]<<' ';
        }
        if(j==mapsize-1) cout<<endl;
    }
}

/******************************************************
                   可视化界面
*******************************************************/

void gotoxy(int n_y, int n_x) // 获取标准输出设备句柄 SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
{
    COORD pos = {(SHORT)n_x,(SHORT)n_y};
   SetConsoleCursorPosition(hOut,pos);
}

void HideCursor()//隐藏光标
{
    CONSOLE_CURSOR_INFO cursor_info = {1,0};
    SetConsoleCursorInfo(hOut, &cursor_info);//控制控制台光标大小及可视性
}

void initmap()
{
    gotoxy(0,0);
    for(int i=0;i<mapsize;i++)
        for(int j=0;j<mapsize;j++)
    {
        if(i==x&&j==ny) {
             SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_RED);//红色
            cout<<"■";
        }
        else{
            SetConsoleTextAttribute(hOut,FOREGROUND_INTENSITY|FOREGROUND_GREEN);//绿色
        cout<<"■";
        }

        if(j==mapsize-1) cout<<endl;
    }
        gotoxy(0,0);
}

void show_for_user()
{
    gotoxy(mapsize+4,2);
    cout<<"W";
    gotoxy(mapsize+5,0);
    cout<<"A S D";
    gotoxy(mapsize+6,0);
    cout<<"空格确定";
}

int input()//监控输入
{
	int ch;
	if(_kbhit())
    {
        ch=_getch();
        if(ch==65||ch==97)//左移
        {
            if(y-2>=0)
                y-=2;
        }
        else if(ch==68||ch==100)//右移
        {
            if(y+2<mapsize*2)
                y+=2;
        }
        else if(ch==87||ch==119)//上移
        {
            if(x-1>=0)
                x--;
        }
        else if(ch==83||ch==115)//下移
        {
            if(x+1<mapsize)
                x++;
        }
        else if(ch==32)//确认
        {

             if(bushu==0){
                 initlei(x,y);
                initdata();
                bushu=1;
             }
             click(x,y/2);
            reflesh();
        }

    }
    return 0;
}

#endif // SAOLEI_H_INCLUDED
















