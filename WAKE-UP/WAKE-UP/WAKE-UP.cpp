#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstdio>
#include<easyx.h>
#include <stdlib.h>
#include <process.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <graphics.h>
#include <mmsystem.h>
#include "resource.h"
#include <Digitalv.h>
#include <MMSystem.h>
#include "Vfw.h"
#pragma comment (lib, "Vfw32.lib")
#pragma comment(lib,"winmm.lib")
#define PI 3.1415926


IMAGE SCENE[7];//场景

IMAGE PROP[7][15];//物品

IMAGE FRAGMENT[7];//拼图

IMAGE LINE,LINEOP;//线索图标

IMAGE buffer(400, 500);//华容道绘图窗口

IMAGE RETURN;//返回按钮

IMAGE mainmenu,set1,set2;

IMAGE STEP,STEP1, STEP2, STEP3, STEP4, STEP5, STEP6;

IMAGE BLACKp, WHITEp;

//景一元素
IMAGE BEDBOARD_BIG;
IMAGE BOARD_BIG;
IMAGE ROBOT;
IMAGE FLOWER;
IMAGE JUICER;
IMAGE PASSWORD;
IMAGE PASSWORDOPEN;
IMAGE IDCARD;

//迷宫
IMAGE MAZE;
IMAGE MAZEMAN;

//景二元素
IMAGE TVBOARDVOID;
IMAGE TVBOARDYOU;
IMAGE TVBOARDZUO;
IMAGE TV;
IMAGE SOFA;
IMAGE LETTER;


//景三元素
IMAGE MIRROR;
IMAGE TOWEL;
IMAGE BOARD3ZUO;
IMAGE BOARD3YOUOFF;
IMAGE BOARD3YOUON;
IMAGE BANTHTUB;
IMAGE PHOTO2;

int propbool[7][20];//判断线索是否找到
bool lineopen = false;//线索界面开关
bool bgmopen = true;
bool newgame = true;
int nowscene=1;
int linebag[130];


void InitGame();
void Start();
void Startani();
void Mainmenu();
void Scenebk();
void Scene1();
void Scene2();
void Scene3();
void Scene4();
void Scene5();
void Scene6();
void Set();
void Bag();
void printprop(int num, int scenekey, int propkey);
void Loadimage();
void PrintReturn();
void Switch();


//华容道游戏
class Klotski {
public:
    IMAGE General1; //竖将
    IMAGE General5;//横将
    IMAGE Soldier;//小兵
    IMAGE Lead;//主角
    IMAGE Bk;
    IMAGE Empty;
    enum BLOCK { BORDER = 0, EMPTY = 1, LEAD = 2, GENERAL5 = 3, GENERAL1 = 4, GENERAL2 = 5, GENERAL3 = 6, GENERAL4 = 7, SOLDEIER = 8 };
    BLOCK map[6][7];
    struct BLock//点结构体
    {
        int x;
        int y;
    };
    int msmode, mapnum, movenum;
    char mapname[11];
    void ladimage();
    void ladmap();
    BLock FindBlock(BLOCK block);
    void move(BLOCK block, int dx, int dy);
    void draw();
    void win();//胜利
    void game();//核心函数：执行游戏
    void printmap();
};

Klotski Klotski1;

//迷宫游戏
class Maze {
public:
    void move();
    void Initimage();
};

Maze Maze1;

IMAGE MAZEWIN(625, 700);

void Maze::Initimage()
{
    SetWorkingImage(&MAZEWIN);
    putimage(0, 0, &MAZE);
    putimage(10, 40, &MAZEMAN);
    SetWorkingImage();
    putimage(50, 50, &MAZEWIN);
    move();
}

void Maze::move()
{
    char ch;
    int w = getpixel(1, 1);
    int x = 0, y = 0;
    MOUSEMSG m;
    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            if (m.x >= 1270 && m.x <= 1330 && m.y >= 670 && m.y <= 730)
            {
                Mainmenu();
            }
        }
    }
    while (ch=_getch())
    {
        SetWorkingImage(&MAZEWIN);
        if (ch == 'w' && getpixel(35,36)==w)//上
        {
            y+=5;
            putimage(x, y, &MAZE);
            putimage(10, 40, &MAZEMAN);
            SetWorkingImage();
            putimage(50, 50, &MAZEWIN);
        }
        if (ch == 's' && getpixel(35, 106 ) == w)//下
        {
            y -= 5;
            putimage(x, y, &MAZE);
            putimage(10, 40, &MAZEMAN);
            SetWorkingImage();
            putimage(50, 50, &MAZEWIN);
        }
        if (ch == 'a' && getpixel(9, 67) == w)//左
        {
            x += 5;
            putimage(x, y, &MAZE);
            putimage(10, 40, &MAZEMAN);
            SetWorkingImage();
            putimage(50, 50, &MAZEWIN);
        }
        if (ch == 'd' && getpixel(68,68) == w)//右
        {
            x -= 5;
            putimage(x, y, &MAZE);
            putimage(10, 40, &MAZEMAN);
            SetWorkingImage();
            putimage(50, 50, &MAZEWIN);
        }
        if (x < -2280 && y < -2180)
        {
            MessageBox(NULL, "过关", "提示", MB_OK);
            return;
        }
    }
}

int main()
{
    InitGame();
    return 0;
}

void InitGame()
{
    Loadimage();
    memset(propbool, 0, sizeof(propbool));
    initgraph(1400, 800);
    setbkcolor(WHITE);
    cleardevice();
    Start();
}

void Start()
{
    /*HWND hwnd = MCIWndCreate(GetHWnd(), NULL, WS_CHILD | WS_VISIBLE | MCIWNDF_NOMENU | MCIWNDF_NOPLAYBAR, NULL);
    SetWindowPos(hwnd, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW);
    MCIWndOpen(hwnd, "video\\裸男wmv.wmv", NULL);
    MCIWndPlay(hwnd);
    while (1)
    {
        ;
    }*/
    mciSendString("play music\\BGM.mp3 repeat", 0, 0, 0);
    Mainmenu();
    //Startani();
    /*Scene1();
    Scenebk();*/
}

void Startani()
{
    cleardevice();
    settextcolor(BLACK);
    LOGFONT f;
    gettextstyle(&f);						// 获取当前字体设置
    f.lfHeight = 40;						// 设置字体高度为 48
    _tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
    f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
    settextstyle(&f);						// 设置字体样式
    outtextxy(200, 50, _T("我是一个奇怪的人"));
    Sleep(1500);
    outtextxy(200, 150, _T("我的生物钟和正常人不同"));
    Sleep(1500);
    outtextxy(200, 250, _T("我从不记得我是怎样从一个地方到另一个地方"));
    Sleep(1500);
    outtextxy(200, 350, _T("我每天经过的场景几乎都相同"));
    Sleep(1500);
    outtextxy(200, 450, _T("我经常能听到好像有人在我耳边说话"));
    Sleep(1500);
    outtextxy(200, 550, _T("按任意键继续。。。"));
    _getch();
    Scene1();
}

void Loadimage()
{
    loadimage(&LINE, "image//线索.png");
    loadimage(&LINEOP, "image//线索展开.png");
    loadimage(&mainmenu,"image\\mainmenu.bmp");
    loadimage(&SCENE[1], "image\\scene1.png");
    loadimage(&SCENE[2], "image\\scene2.png");
    loadimage(&SCENE[3], "image\\scene3.png");
    loadimage(&SCENE[4], "image\\scene4.png");
    loadimage(&SCENE[5], "image\\scene5.png");
    loadimage(&SCENE[6], "image\\scene6.png");
    loadimage(&set1, "image\\set1.bmp");
    loadimage(&set2, "image\\set2.bmp");
    loadimage(&RETURN, "image\\return.png");
    loadimage(&BLACKp, "image\\black.png");
    loadimage(&WHITEp, "image\\white.png");
    loadimage(&STEP, "image\\step.png");
    loadimage(&STEP1, "image\\step1.png");
    loadimage(&STEP2, "image\\step2.png");
    loadimage(&STEP3, "image\\step3.png");
    loadimage(&STEP4, "image\\step4.png");
    loadimage(&STEP5, "image\\step5.png");
    loadimage(&STEP6, "image\\step6.png");
    //景一
    loadimage(&BOARD_BIG, "image\\scene1\\bigboard.png");//左上柜子
    loadimage(&BEDBOARD_BIG, "image\\scene1\\bigbedboard.png");//床头柜
    loadimage(&ROBOT, "image\\scene1\\开箱机器人.png");
    loadimage(&FLOWER, "image\\scene1\\flower.png");//花盆
    loadimage(&JUICER, "image\\scene1\\juicer.png");//榨汁机
    loadimage(&PASSWORD, "image\\scene1\\password.png");//密码箱
    loadimage(&PASSWORDOPEN, "image\\scene1\\passwordopen.png");
    loadimage(&IDCARD, "image\\scene1\\名片.png");
    loadimage(&PROP[1][1], "image\\scene1\\water.png");
    loadimage(&PROP[1][2], "image\\scene1\\药丸.png");
    loadimage(&PROP[1][3], "image\\scene1\\种子.png");
    loadimage(&PROP[1][4], "image\\scene1\\营养包.png");
    loadimage(&PROP[1][5], "image\\scene1\\食物.png");
    loadimage(&PROP[1][6], "image\\scene1\\果实.png");
    //迷宫
    loadimage(&MAZE, "image\\maze.png");
    loadimage(&MAZEMAN, "image\\mazeman.png");
    //景二
    loadimage(&TVBOARDVOID, "image\\scene2\\电视抽屉空.png");
    loadimage(&TVBOARDYOU, "image\\scene2\\电视抽屉右剪刀.png");
    loadimage(&TVBOARDZUO, "image\\scene2\\电视抽屉左需钥匙.png");
    loadimage(&TV, "image\\scene2\\电视扩展.png");
    loadimage(&SOFA, "image\\scene2\\沙发裂缝.png");
    loadimage(&LETTER, "image\\scene2\\信封展开.png");
    loadimage(&PROP[2][1], "image\\scene2\\剪刀.png");
    loadimage(&PROP[2][2], "image\\scene2\\钥匙.png");
    loadimage(&PROP[2][3], "image\\scene2\\遥控器.png");
    //loadimage(&PROP[2][4], "image\\scene2\\.png");
    //景三
    loadimage(&MIRROR, "image\\scene3\\镜子.png");
    loadimage(&TOWEL, "image\\scene3\\毛巾.png");
    loadimage(&BOARD3ZUO, "image\\scene3\\柜子左.png");
    loadimage(&BOARD3YOUOFF, "image\\scene3\\柜子右密码.png");
    loadimage(&BOARD3YOUON, "image\\scene3\\柜子右.png");
    loadimage(&PROP[3][1], "image\\scene3\\播放器.png");
    loadimage(&BANTHTUB, "image\\scene3\\浴缸.png");
    loadimage(&PHOTO2, "image\\scene3\\全家福2.png");
}

void Transition()
{

}

void Mainmenu()
{
    cleardevice();
    putimage(50, 50, &mainmenu);
    Scenebk();
    MOUSEMSG m;
    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg==WM_LBUTTONDOWN)
        {
            if (m.x >= 230 && m.x <= 490 && m.y >= 388 && m.y <= 460)
            {
                if (newgame==true)
                { 
                    newgame = false;
                    Startani();
                    Scene1();
                    //Maze1.Initimage();
                    //Scene4();
                }
                else
                {
                    if (nowscene == 1)
                        Scene1();
                    if (nowscene == 2)
                        Scene2();
                    if (nowscene == 3)
                        Scene3();
                    if (nowscene == 4)
                        Scene4();
                    if (nowscene == 5)
                        Scene5();
                }
            }
            if (m.x >= 270 && m.x <= 430 && m.y >= 510 && m.y <= 580)
            {
                Set();
            }
        }
    }
}

void Set()
{
    cleardevice();
    
    if (bgmopen)
        putimage(50, 50, &set1);
    else
        putimage(50, 50, &set2);
    putimage(613, 688, &RETURN);
    Scenebk();
    MOUSEMSG m;
    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            if (m.x >= 215 && m.x <= 555 && m.y >= 400 && m.y <= 480)//关闭/开启bgm
            {
                if (bgmopen)
                {
                    mciSendString("close music\\BGM.mp3", 0, 0, 0);
                    putimage(50, 50, &set2);
                    putimage(613, 688, &RETURN);
                    Scenebk();
                    bgmopen = false;
                }
                else
                {
                    mciSendString("play music\\BGM.mp3 repeat", 0, 0, 0);
                    putimage(50, 50, &set1);
                    putimage(613, 688, &RETURN);
                    Scenebk();
                    bgmopen = true;
                }
            }
            if (m.x >= 260 && m.x <= 520 && m.y >= 520 && m.y <= 600)//退出游戏
            {
                exit(0);
            }
            if (m.x >= 613 && m.x <= 673 && m.y >= 688 && m.y <= 748)//返回
            {
                Mainmenu();
            }
        }
    }
}

void Bag(int scenekey)
{
    if (lineopen)
    {
        clearrectangle(745,65,1330, 270);
        putimage(1270, 70, &LINE);
        lineopen = false;
    }
    else
    {
        putimage(750, 70, &LINEOP);
        memset(linebag, 0, sizeof(linebag));
        int temp = 1;
        for(int i=1;i<15;i++)
        {
            if (propbool[scenekey][i])
            {
                printprop(temp, scenekey,i);
                temp++;
            }
        }
        lineopen = true;
    }
}

void printprop(int num, int scenekey,int propkey)
{
    if(num<=6)
        putimage((num-1) * 78 + 808, 105, &PROP[scenekey][propkey]);
    else
        putimage((num-7) * 78 + 808, 174, &PROP[scenekey][propkey]);
    linebag[num] = propkey;
}

void Switch()
{

}

void Scenebk()
{
   // cleardevice();
    setlinecolor(BLACK);
    setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 3);//绘制画框
    rectangle(50, 50, 675, 750);
    rectangle(725, 50, 1350, 750);
    //Klotski1.game();华容道游戏

}

void Scene1()
{
    double open = 0;
    bool openpassword = false,havedrug=false,haveseed=false,seeduse=false;
    cleardevice();
    putimage(970, 760, &STEP1);
    putimage(50, 50,&SCENE[1]);
    putimage(1270, 70, &LINE);
    putimage(1270, 670, &RETURN);
    Scenebk();
    nowscene = 1;
    MOUSEMSG m;		// 定义鼠标消息
    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            if (abs(m.x - 1300) <= 30 && abs(m.y - 100) <= 30)//是否点击背包
        {
            Bag(1);
        }
        if (m.x>=1270&&m.x<=1330 && m.y>=670&&m.y<=730)
        {
            Mainmenu();
        }
        if (m.x >= 80 && m.x <=264 && m.y >= 93 && m.y <= 354)//左上柜子  1
        {
            if (open!=1)
            {
                putimage(770, 300, &BOARD_BIG);
                open = 1;
            }
            else
            {
                clearrectangle(770, 300, 1310, 650);
                open = 0;
            }
        }
        if (open == 1 && m.x >= 891 && m.x <= 932 && m.y >= 435 && m.y <= 470)//拿食物
        {
            loadimage(&BOARD_BIG, "image\\scene1\\bigboard2.png");
            putimage(770, 300, &BOARD_BIG);
            propbool[1][5] = 1;
            Bag(1);
            Bag(1);
        }
        if (open == 1 && m.x >= 970 && m.x <=1300&& m.y >= 533 && m.y <= 640)//打开密码箱界面密码箱
        {
            if(!openpassword)
            putimage(770, 300, &PASSWORD);
            else
                putimage(770, 300, &PASSWORDOPEN);
            open = 1.1;
        }
        else if (open == 1.1 && m.x >= 770 && m.x <= 1310 && m.y >= 300 & m.y <= 650)
        {
            if (!openpassword)
            {
                putimage(770, 300, &PASSWORD);
                char s[10];
            InputBox(s, 10, "请输入六位密码");
            int r;
            sscanf_s(s, "%d", &r);
            if (r != 181231)
            {
                MessageBox(NULL, "密码错误",  "提示",MB_OK);
            }
            else
            {
            MessageBox(NULL,  "密码正确","提示", MB_OK);
            openpassword = true;
            putimage(770, 300, &PASSWORDOPEN);
            }
            }
            else
            {
                putimage(770, 300, &PASSWORDOPEN);
            }
        }
        if (openpassword&&open == 1.1 )//拿种子，药
        {
            if (m.x >= 917 && m.x <= 940 && m.y >= 580 && m.y <= 615)
            {
                if (!haveseed)
                {
                     loadimage(&PASSWORDOPEN, "image\\scene1\\passwordopen2.png");
                     putimage(770, 300, &PASSWORDOPEN);
                     
                }
                if (haveseed)
                {
                    loadimage(&PASSWORDOPEN, "image\\scene1\\passwordopen3.png");
                    putimage(770, 300, &PASSWORDOPEN);
                }
                propbool[1][2] = 1;
                havedrug = true;
                Bag(1);
                Bag(1);
            }
            if (m.x >= 1090 && m.x <= 1124 && m.y >= 580 && m.y <= 615)
            {
                if (!havedrug)
                {
                    loadimage(&PASSWORDOPEN, "image\\scene1\\passwordopen4.png");
                    putimage(770, 300, &PASSWORDOPEN);
                    
                }
                if (havedrug)
                {
                    loadimage(&PASSWORDOPEN, "image\\scene1\\passwordopen3.png");
                    putimage(770, 300, &PASSWORDOPEN);
                }
                propbool[1][3] = 1;
               haveseed = true;
               Bag(1);
               Bag(1);
            }
        }
        if (m.x >= 600 && m.x <= 663 && m.y >= 337 && m.y <= 390)//床头柜 2
        {
            if (open!=2)
            {
                putimage(770, 300, &BEDBOARD_BIG);
                open = 2;
            }
            else
            {
                clearrectangle(770, 300, 1310, 650);
                open = 0;
            }
        }
        if (open == 2 && m.x >= 868 && m.x <= 965 && m.y >= 394 && m.y <= 440)//打开名片
        {
            putimage(770, 300, &IDCARD);
            open = 2.1;
        }
        if (open == 2 && m.x >= 1107 && m.x <= 1153 && m.y >= 371 && m.y <= 459)//拿走水
        {
            loadimage(&BEDBOARD_BIG, "image\\scene1\\bigbedboard2.png");
            putimage(770, 300, &BEDBOARD_BIG);
            propbool[1][1] = 1;
            Bag(1);
            Bag(1);
        }
        if (m.x >= 565 && m.x <= 625 && m.y >= 195 && m.y <= 325)//机器人  3
        {
            if (open != 3)
            {
                putimage(770, 300, &ROBOT);
                open = 3;
            }
            else
            {
                clearrectangle(770, 300, 1310, 650);
                open = 0;
            }
        }
        if (open == 3 && linebag[((m.x - 730) / 78) + 6 *( (m.y - 105) / 66)] == 4)
        {
            Switch();
            Scene2();
        }
        if (m.x >= 285 && m.x <= 340 && m.y >= 305 && m.y <= 360)//花盆  4
        {
            if (open != 4)
            {
                putimage(770, 300, &FLOWER);
                open = 4;
            }
            else
            {
                clearrectangle(770, 300, 1310, 650);
                open = 0;
            }
        }
        if (lineopen&&open == 4 && linebag[((m.x - 730) / 78) + 6 * ((m.y - 105) / 66)] ==3)
        {
            propbool[1][3] = 0;
            loadimage(&FLOWER, "image\\scene1\\flower2.png");
            putimage(770, 300, &FLOWER);
            seeduse = true;
            Bag(1);
            Bag(1);
        }
        if (seeduse&&lineopen && open == 4 && linebag[((m.x - 730) / 78) + 6 * ((m.y - 105) / 66)] == 1)
        {
            propbool[1][1] = 0;
            propbool[1][6] = 1;
            loadimage(&FLOWER, "image\\scene1\\flower2.png");
            putimage(770, 300, &FLOWER);
            Bag(1);
            Bag(1);
        }
        if (m.x >= 75 && m.x <= 220 && m.y >= 500 && m.y <= 650)//榨汁机 5
        {
            if (open != 5)
            {
                putimage(770, 300, &JUICER);
                open = 5;
            }
            else
            {
                clearrectangle(770, 300, 1310, 650);
                open = 0;
            }
        }
        if (open == 5 && m.x >= 770 && m.x <= 770 + 540 && m.y >= 300 && m.y <= 650)
        {
            if (propbool[1][6] && propbool[1][2] && propbool[1][5])
            {
                propbool[1][4] = 1;
                propbool[1][2] = 0;
                propbool[1][5] = 0;
                propbool[1][6] = 0;
                Bag(1);
                Bag(1);
            }
            
        }
        }
        
    }
}

void Scene2()//客厅
{
    double open = 0;
    bool opentvboard = false;
    cleardevice();
    putimage(970, 760, &STEP2);
    putimage(50, 50, &SCENE[2]);
    putimage(1270, 70, &LINE);
    putimage(1270, 670, &RETURN);
    nowscene = 2;
    Scenebk();
    MOUSEMSG m;
    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            if (abs(m.x - 1300) <= 30 && abs(m.y - 100) <= 30)//是否点击背包
            {
                Bag(2);
            }
            if (m.x >= 1270 && m.x <= 1330 && m.y >= 670 && m.y <= 730)
            {
                Mainmenu();
            }
            if (m.x >= 510 && m.x <= 638 && m.y >= 654 && m.y <= 684)//电视柜右柜  1
            {
                if (open != 1)
                {
                    putimage(770, 300, &TVBOARDYOU);
                    open = 1;
                }
                else
                {
                    clearrectangle(770, 300, 1310, 650);
                    open = 0;
                }
            }
            if (open == 1 && m.x >= 800 && m.x <= 942 && m.y >= 380 && m.y <= 436)//拿剪刀
            {
                loadimage(&TVBOARDYOU, "image\\scene2\\电视抽屉空.png");
                putimage(770, 300, &TVBOARDYOU);
                propbool[2][1] = 1;
                Bag(2);
                Bag(2);
            }
            if (m.x >= 345 && m.x <= 471 && m.y >= 655 && m.y <= 680)//左电视柜 2
            {
                if (open != 2)
                {
                    putimage(770, 300, &TVBOARDZUO);
                    open = 2;
                }
                else
                {
                    clearrectangle(770, 300, 1310, 650);
                    open = 0;
                }
            }
            if (open == 2 && linebag[((m.x - 730) / 78) + 6 * ((m.y - 105) / 66)] == 2)//开锁
            {
                loadimage(&TVBOARDZUO, "image\\scene2\\电视抽屉左遥控器.png");
                putimage(770, 300, &TVBOARDZUO);
                propbool[2][2] = 0;
                Bag(2);
                Bag(2);
                open = 2.1;
            }
            else if (open == 2.1 && m.x>=887&&m.y>=393&&m.x<=984&&m.y<=428)//拿遥控器
            {
                propbool[2][3] = 1;
                loadimage(&TVBOARDZUO, "image\\scene2\\电视抽屉空.png");
                putimage(770, 300, &TVBOARDZUO);
                Bag(2);
                Bag(2);
            }
            if (m.x >= 514 && m.x <= 546 && m.y >= 307 && m.y <= 324)//3沙发裂缝
            {
                if (open != 3)
                {
                    putimage(770, 300, &SOFA);
                    open = 3;
                }
                else
                {
                    clearrectangle(770, 300, 1310, 650);
                    open = 0;
                }
            }
            if (open == 3 && linebag[((m.x - 730) / 78) + 6 * ((m.y - 105) / 66)] == 1)
            {
                loadimage(&SOFA, "image\\scene2\\沙发剪开.png");
                putimage(770, 300, &SOFA);
                propbool[2][1] = 0;
                Bag(2);
                Bag(2);
                open = 3.1;
            }
            if (open == 3.1&&m.x>=1000&&m.y>=460&&m.x<=1086&&m.y<=490)
            {
                propbool[2][2] = 1;
                loadimage(&SOFA, "image\\scene2\\沙发剪开空.png");
                putimage(770, 300, &SOFA);
                Bag(2);
                Bag(2);
            }
            if (m.x >=406 && m.x <= 586 && m.y >= 504 && m.y <= 633)//4电视
            {
                if (open != 4)
                {
                    putimage(770, 300, &TV);
                    open = 4;
                }
                else
                {
                    clearrectangle(770, 300, 1310, 650);
                    open = 0;
                }
            }
            if (open == 4 && linebag[((m.x - 730) / 78) + 6 * ((m.y - 105) / 66)] ==3)
            {
                loadimage(&TV, "image\\scene2\\全家福1.png");
                putimage(770, 300, &TV);
                Sleep(2000);
                Scene3();
                return;
            }
            if (m.x >= 174 && m.x <= 193 && m.y >= 430 && m.y <= 444)//5信
            {
                if (open != 5)
                {
                    putimage(770, 300, &LETTER);
                    open = 5;
                }
                else
                {
                    clearrectangle(770, 300, 1310, 650);
                    open = 0;
                }
            }
        }
    }
}

void Scene3()//浴室
{
    double open = 0;
    bool openpassword = false;
    cleardevice();
    putimage(970, 760, &STEP3);
    putimage(50, 50, &SCENE[3]);
    putimage(1270, 70, &LINE);
    putimage(1270, 670, &RETURN);
    nowscene = 3;
    Scenebk();
    MOUSEMSG m;
    while (true)
    {
         m = GetMouseMsg();
         if (m.uMsg == WM_LBUTTONDOWN)
         {
                if (abs(m.x - 1300) <= 30 && abs(m.y - 100) <= 30)//是否点击背包
                {
                    Bag(3);
                }
                if (m.x >= 1270 && m.x <= 1330 && m.y >= 670 && m.y <= 730)
                {
                    Mainmenu();
                }
                if (m.x >= 236 && m.x <= 316 && m.y >= 118 && m.y <= 234)//镜子  1
                {
                    if (open != 1)
                    {
                        putimage(770, 300, &MIRROR);
                        open = 1;
                    }
                    else
                    {
                        clearrectangle(770, 300, 1310, 650);
                        open = 0;
                    }
                }
                if (m.x >= 468 && m.x <= 595 && m.y >= 193 && m.y <= 257)//毛巾  2
                {
                    if (open != 2)
                    {
                        putimage(770, 300, &TOWEL);
                        open = 2;
                    }
                    else
                    {
                        clearrectangle(770, 300, 1310, 650);
                        open = 0;
                    }
                }
                if (m.x >= 106 && m.x <= 226 && m.y >= 322 && m.y <= 382)//柜子左  3
                {
                    if (open != 3)
                    {
                        putimage(770, 300, &BOARD3ZUO);
                        open = 3;
                    }
                    else
                    {
                        clearrectangle(770, 300, 1310, 650);
                        open = 0;
                    }
                }
                if (m.x >= 235 && m.x <= 357 && m.y >= 322 && m.y <= 382)//柜子右  4
                {
                    if (open != 4)
                    {
                        putimage(770, 300, &BOARD3YOUOFF);
                        open = 4;
                    }
                    else
                    {
                        clearrectangle(770, 300, 1310, 650);
                        open = 0;
                    }
                }
                if (open == 4 && m.x >= 770 && m.x <= 1310 && m.y >= 300 & m.y <= 650)
                {
                    if (!openpassword)
                    {
                        putimage(770, 300, &BOARD3YOUOFF);
                        char s[10];
                        InputBox(s, 10, "请输入密码");
                        int r;
                        sscanf_s(s, "%d", &r);
                        if (r != 520)
                        {
                            MessageBox(NULL, "密码错误", "提示", MB_OK);
                        }
                        else
                        {
                            MessageBox(NULL, "密码正确", "提示", MB_OK);
                            openpassword = true;
                            putimage(770, 300, &BOARD3YOUON);
                        }
                    }
                    else
                    {
                        putimage(770, 300, &BOARD3YOUON);
                    }
                }
                if (open == 4 && openpassword && m.x >= 966 && m.x <= 1093 && m.y >= 490 & m.y <= 594)
                {
                    putimage(770, 300, &PHOTO2);
                    Sleep(3000);
                    Scene4();
                }
                if (m.x >= 88 && m.x <= 459 && m.y >= 519 && m.y <= 632)//柜子右  5
                {
                    if (open != 5)
                    {
                        putimage(770, 300, &BANTHTUB);
                        open = 5;
                    }
                    else
                    {
                        clearrectangle(770, 300, 1310, 650);
                        open = 0;
                    }
                }
         }
    }
}

void Scene4()//教室
{
    double open = 0;
    cleardevice();
    putimage(970, 760, &STEP4);
    putimage(50, 50, &SCENE[4]);
    putimage(1270, 70, &LINE);
    putimage(1270, 670, &RETURN);
    nowscene = 4;
    Scenebk();
    MOUSEMSG m;
    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            if (abs(m.x - 1300) <= 30 && abs(m.y - 100) <= 30)//是否点击背包
            {
                Bag(4);
            }
            if (m.x >= 1270 && m.x <= 1330 && m.y >= 670 && m.y <= 730)
            {
                Mainmenu();
            }
            if (m.x >= 536 && m.x <= 563 && m.y >= 586 && m.y <= 595)//游戏机  1
            {
                Klotski1.game()
                    ;
            }
        }
    }
}

void Scene5()//户外
{
    double open = 0;
    cleardevice();
    putimage(970, 760, &STEP5);
    putimage(50, 50, &SCENE[5]);
    putimage(1270, 70, &LINE);
    putimage(1270, 670, &RETURN);
    nowscene = 5;
    Scenebk();
    //Maze1.Initimage();
    MOUSEMSG m;
    while (true)
    {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN)
        {
            if (abs(m.x - 1300) <= 30 && abs(m.y - 100) <= 30)//是否点击背包
            {
                Bag(5);
            }
            if (m.x >= 1270 && m.x <= 1330 && m.y >= 670 && m.y <= 730)
            {
                Mainmenu();
            }
        }
    }
}


void Klotski::ladimage()//加载图片
{
    loadimage(&General1, _T("image\\general1.png"));//100*200
    loadimage(&General5, _T("image\\general5.png"));//200*100
    loadimage(&Soldier, _T("image\\soldier.png"));//100*100
    loadimage(&Empty, _T("image\\empty.png"));//100*100
    loadimage(&Lead, _T("image\\lead.png"));//200*200
    loadimage(&Bk, _T("image\\bk.png"));//406*506
}

void Klotski::ladmap()//初始化map
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            map[i][j] = BORDER;
        }      
    }
    map[1][1] = GENERAL1;
    map[1][2] = GENERAL1;
    map[4][1] = GENERAL2;
    map[4][2] = GENERAL2;
    map[1][3] = GENERAL3;
    map[1][4] = GENERAL3;
    map[4][3] = GENERAL4;
    map[4][4] = GENERAL4;
    map[2][1] = LEAD;
    map[3][1] = LEAD;
    map[2][2] = LEAD;
    map[3][2] = LEAD;
    map[2][3] = GENERAL5;
    map[3][3] = GENERAL5;
    map[1][5] = SOLDEIER;
    map[4][5] = SOLDEIER;
    map[2][4] = SOLDEIER;
    map[3][4] = SOLDEIER;
    map[2][5] = EMPTY;
    map[3][5] = EMPTY;
}

void Klotski::printmap()
{
    putimage(827, 137, &Bk);
    for (int i = 1; i < 5; i++)
    {
        for (int j = 1; j < 6; j++)
        {
            switch (map[i][j])
            {
            case 1:
            {
                putimage((i-1)*100+830,(j-1)*100+140,&Empty);
            break; 
            }
            case 2:
            {
                if(map[i][j-1]!=2&&map[i-1][j]!=2)
                putimage((i - 1) * 100 + 830, (j - 1) * 100 + 140, &Lead);
                break;
            }
            case 3:
            {
                if(map[i-1][j]!=3)
                putimage((i - 1) * 100 + 830, (j - 1) * 100 + 140, &General5);
                break;
            }
            case 4:
            case 5:
            case 6:
            case 7:
            {
                if(map[i][j-1]!=map[i][j])
                putimage((i - 1) * 100 + 830, (j - 1) * 100 + 140, &General1);
                break;
            }
            case 8:
            {
                putimage((i - 1) * 100 + 830, (j - 1) * 100 + 140, &Soldier);
                break;
            }
            }
        }
    }
}

void Klotski::game()
{
    ladmap();
    ladimage();
    printmap();
    MOUSEMSG msg;
    int pmx, pmy;
    while (true)
    {
        while (MouseHit())
        {
            msg = GetMouseMsg();
            if (msg.uMsg == WM_LBUTTONDOWN)//按下时
            {
                //在游戏区
                if (msg.x <= 1230 && msg.x >= 830 && msg.y >= 140 && msg.y <= 640)
                {
                    //记录下开始按下的坐标
                    pmx = msg.x;
                    pmy = msg.y;
                    if (map[(pmx-730) / 100][(pmy-40) / 100] != EMPTY && map[(pmx - 730) / 100][(pmy - 40) / 100] != SOLDEIER)//鼠标之前没选中过
                    {
                        msmode = map[(pmx - 730) / 100][(pmy - 40) / 100];
                    }
                    else if (map[(pmx - 730) / 100][(pmy - 40) / 100] == SOLDEIER)//选中兵
                    {
                        msmode = ((pmx - 730) / 100) * 10 + (pmy - 40) / 100;
                    }
                    
                }
                if (msg.x >= 1270 && msg.x <= 1330 && msg.y >= 670 && msg.y <= 730)
                {
                    Mainmenu();
                }
            }
            else if (msg.uMsg == WM_LBUTTONUP)//鼠标弹起
            {
                //根据鼠标拖动轨迹移动
                //左右动
                if (abs(msg.x - pmx) >= abs(msg.y - pmy) && abs(msg.x - pmx) > 30)
                {
                    if (msg.x - pmx > 0)
                    {
                        move((BLOCK)msmode, 1, 0);
                    }
                    else
                    {
                        move((BLOCK)msmode, -1, 0);
                    }
                }
                //上下动
                if (abs(msg.x - pmx) < abs(msg.y - pmy) && abs(msg.y - pmy) > 30)
                {
                    if (msg.y - pmy > 0)
                    {
                        move((BLOCK)msmode, 0, 1);
                    }
                    else
                    {
                        move((BLOCK)msmode, 0, -1);
                    }
                }
            }
        }
        draw();
    }
}

Klotski::BLock Klotski::FindBlock(BLOCK block)
{
    struct BLock Block = { 0,0 };
    int x, y;
    for (x = 1; x <5;x++)
    {
        for (y = 1; y <6;y++)
        {
            if (map[x][y] == block)
            {
                Block.x = x;
                Block.y = y;
                return Block;
            }
        }
    }
    return Block;
}

void Klotski::draw()
{
    int i, j;
    BLock BLOCK1;
    SetWorkingImage(&buffer);
    //clearrectangle(830, 140, 1230, 640);
    //画兵，方格
    for (i = 1; i < 5; i++)
    {
        for (j = 1; j < 6; j++)
        {
            if (map[i][j] == 1)
            {
                putimage((i - 1) * 100 , (j - 1) * 100 , &Empty);
            }
            if (map[i][j] == 8)
            {
                putimage((i - 1) * 100, (j - 1) * 100 , &Soldier);
            }
        }
    }   
    //把每个木块画一遍
    BLOCK1 = FindBlock(LEAD);
    putimage((BLOCK1.x-1) * 100, (BLOCK1.y-1) * 100, &Lead);
    BLOCK1 = FindBlock(GENERAL5);
    putimage((BLOCK1.x - 1) * 100, (BLOCK1.y - 1) * 100, &General5);
    BLOCK1 = FindBlock(GENERAL1);
    putimage((BLOCK1.x - 1) * 100, (BLOCK1.y - 1) * 100, &General1);
    BLOCK1 = FindBlock(GENERAL2);
    putimage((BLOCK1.x - 1) * 100, (BLOCK1.y - 1) * 100, &General1);
    BLOCK1 = FindBlock(GENERAL3);
    putimage((BLOCK1.x - 1) * 100, (BLOCK1.y - 1) * 100, &General1);
    BLOCK1 = FindBlock(GENERAL4);
    putimage((BLOCK1.x - 1) * 100, (BLOCK1.y - 1) * 100, &General1);
    SetWorkingImage();
    putimage(830, 140, &buffer);
    BLOCK1 = FindBlock(LEAD);
    if (BLOCK1.x == 2 && BLOCK1.y == 4)
        win();
}

void Klotski::move(BLOCK block, int dx, int dy)
{
    bool  moved = false;
    //兵
    if (msmode > 10)
    {
        if (map[msmode / 10 + dx][msmode % 10 + dy] == 1)
        {
            map[msmode / 10][msmode % 10] = EMPTY;
            map[msmode / 10 + dx][msmode % 10 + dy] = SOLDEIER;
            msmode += dx * 10 + dy;
            moved = true;
        }
    }
    //竖将
    if (block >= GENERAL1&& block <= GENERAL4)
    {
        BLock blk;
        blk = FindBlock(block);
        if (dx != 0)
        {
            if (map[blk.x + dx][blk.y] == EMPTY && map[blk.x + dx][blk.y + 1] == EMPTY)
            {
                map[blk.x][blk.y] = EMPTY;
                map[blk.x][blk.y + 1] = EMPTY;
                map[blk.x + dx][blk.y] = block;
                map[blk.x + dx][blk.y + 1] = block;
                moved = true;
            }
        }
        if (dy == 1)
        {
            if (map[blk.x][blk.y + 2] == EMPTY)
            {
                map[blk.x][blk.y] = EMPTY;
                map[blk.x][blk.y + 2] = block;
                moved = true;
            }
        }
        if (dy == -1)
        {
            if (map[blk.x][blk.y - 1] == EMPTY)
            {
                map[blk.x][blk.y + 1] = EMPTY;
                map[blk.x][blk.y - 1] = block;
                moved = true;
            }
        }
    }
    //横G5
    if (block == GENERAL5)
    {
        BLock blk2;
        blk2 = FindBlock(block);
        if (dy != 0)
        {
            if (map[blk2.x][blk2.y + dy] == EMPTY && map[blk2.x + 1][blk2.y + dy] == EMPTY)
            {
                map[blk2.x][blk2.y] = EMPTY;
                map[blk2.x + 1][blk2.y] = EMPTY;
                map[blk2.x][blk2.y + dy] = GENERAL5;
                map[blk2.x + 1][blk2.y + dy] = GENERAL5;
                moved = true;
            }
        }
        if (dx == 1)
        {
            if (map[blk2.x + 2][blk2.y] == EMPTY)
            {
                map[blk2.x + 2][blk2.y] = GENERAL5;
                map[blk2.x][blk2.y] = EMPTY;
                moved = true;
            }
        }
        if (dx == -1)
        {
            if (map[blk2.x - 1][blk2.y] == EMPTY)
            {
                map[blk2.x - 1][blk2.y] = GENERAL5;
                map[blk2.x + 1][blk2.y] = EMPTY;
                moved = true;
            }
        }
    }
    //LEAD
    if (block == LEAD)
    {
        BLock blk3;
        blk3 = FindBlock(block);
        if (dx == 1)
        {
            if (map[blk3.x + 2][blk3.y]== EMPTY && map[blk3.x + 2][blk3.y + 1] == EMPTY)
            {
                map[blk3.x + 2][blk3.y] = LEAD;
                map[blk3.x + 2][blk3.y + 1] = LEAD;
                map[blk3.x][blk3.y] = EMPTY;
                map[blk3.x][blk3.y + 1] = EMPTY;
                moved = true;
            }
        }
        if (dx == -1)
        {
            if (map[blk3.x - 1][blk3.y] == EMPTY && map[blk3.x - 1][blk3.y + 1] == EMPTY)
            {
                map[blk3.x - 1][blk3.y] = LEAD;
                map[blk3.x - 1][blk3.y + 1] = LEAD;
                map[blk3.x + 1][blk3.y] = EMPTY;
                map[blk3.x + 1][blk3.y + 1] = EMPTY;
                moved = true;
            }
        }
        if (dy == 1)
        {
            if (map[blk3.x][blk3.y + 2] == EMPTY && map[blk3.x + 1][blk3.y + 2] == EMPTY)
            {
                map[blk3.x][blk3.y + 2] = LEAD;
                map[blk3.x + 1][blk3.y + 2] = LEAD;
                map[blk3.x][blk3.y] = EMPTY;
                map[blk3.x + 1][blk3.y] = EMPTY;
                moved = true;
            }
        }
        if (dy == -1)
        {
            if (map[blk3.x][blk3.y - 1] == EMPTY && map[blk3.x + 1][blk3.y - 1] == EMPTY)
            {
                map[blk3.x][blk3.y - 1] = LEAD;
                map[blk3.x + 1][blk3.y - 1] = LEAD;
                map[blk3.x][blk3.y + 1] = EMPTY;
                map[blk3.x + 1][blk3.y + 1] = EMPTY;
                moved = true;
            }
        }
    }
    //移动成功处理
    //return win;
}

void Klotski::win()
{
    settextcolor(BLACK);
    MessageBox(NULL, "恭喜过关！", "提示", MB_OK);
    Scene5();
    return;
}

