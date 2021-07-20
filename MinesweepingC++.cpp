#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#include<windows.h>  
#define MAX 9  
#include<time.h>  
#define random(x)(rand()%x)  
#define MAXN  
int still = 1;  
int  Max (int a, int b)  
{  
    return a > b ? a : b;  
}  
int  Min (int a, int b)  
{  
    return a < b ? a : b;  
}  
  
struct anonymous  
{  
    int all;//初始化埋雷  
    char ans;  
    char guess;  
} f[21][21];  
  
//单个记录的结构体  
typedef struct  
{  
    int key;  
} treeone;  
//记录表的结构体  
typedef struct  
{  
    treeone r[MAX];  
    int length;  
} treeall;  
  
  
void Color(int num);  
int  Beginning ();  
int Prepare (int dif, char*puser); //指针  
void Output (int r, int times, int *SUMMINE);  
int Playing(int r, int SUMMINE);  
int Opening(int x, int y, int n);  
int Count(int x, int y, int n);  
void Continuing();  
void Rank();  
void swap(treeone *a, treeone *b);  
int Outputlist(double a[]) ;  
void HeapSort(treeall *H);  
void HeapAdjust(treeall * H, int s, int m);  
  
  
void Color(int num) //设置颜色  
{  
    HANDLE hout;  
    hout = GetStdHandle(STD_OUTPUT_HANDLE);  
    SetConsoleTextAttribute(hout, num);  
}  
  
void Menu()  
{  
  
    Color(11);//0 黑色！1 看不清的蓝色 2 草绿 3 淡蓝4 暗红 5 紫色 6 暗黄 7 灰 8 灰（看不太清） 9 深蓝10 翠绿 11 蓝绿12 红 13粉 14亮黄 15 白 （16以后是背景颜色）  
    //Color(30); //背景是蓝色的黄色字体  
    printf("\t\t欢迎来到扫雷游戏!\n");  
  
    Color(14);  
    printf("=======================*******************===========================\n" );  
    printf("\t     请选择难度：(仅输入数字)\n");  
    printf(" 简单模式（3*3）--1\t") ;  
    printf("   一般模式（7*7）--2\t") ;  
    printf("   困难模式（10*10）--3\n") ;  
}  
  
int main()  
{  
    Menu();  
    do  
    {  
        Color(14);  
        Beginning();  
        system("pause");  
  
    }  
    while (still) ;  
  
    Color(2) ;  
    printf("学号是120L021306的作品~感谢使用！") ;  
    system("pause");  
  
    return 0;  
}  
int  Beginning ()  
{  
    char user[21];  
    printf("请输入你的姓名(中文即可)：");  
    scanf("%s", user);  
    /*FILE *fp; 
    fp=fopen("1.txt","a"); 
    fprintf(fp,"%s\n",user); 
    fclose(fp);*/  
    printf("\t\t——————Hello,%s!——————\n请输入你选择的难度：\n", user);  
  
    int diff[4] = {0, 3, 7, 10};  
    int dif;  
    int xxx;  
    do  
    {  
        xxx = scanf("%d", &dif);  
        if (dif == 1 || dif == 2 || dif == 3)  
        {  
            break;  
        }  
        else  
        {  
            printf("错误输入！请重新输入(仅输入数字：1/2/3):");  
        }  
        while (getchar() != '\n');  
    }  
    while (1);  
    return Prepare(diff[dif], user);  
}  
int Prepare (int r, char *puser)  
{  
    int SUMMINE = 0;  
  
  
    srand((int)time(0));  
    for (int i = 1; i <= r; i++)  
    {  
        for (int j = 1; j <= r; j++)  
        {  
            if (random(8) < 1) //随机取到0~7之间的数，如果数小于一那么标记该点有雷  
            {  
                f[i][j].all = 1; //1代表有雷  
                SUMMINE++;  
            }  
            else  
            {  
                f[i][j].all = 0; //无雷  
            }  
        }  
    }  
    //防止无雷生成  
    int flag = 1;  
    for (int i = 1; i <= r; i++)  
    {  
        for (int j = 1; j <= r; j++)  
        {  
            if (f[i][j].all)  
            {  
                flag = 0;  
                break;  
            }  
        }  
        if (!flag)break;  
    }  
    if (flag)  
    {  
        f[(int)random(r) + 1][(int)random(r) + 1].all = 1;    //任意选一个点让它有雷  
        SUMMINE = 1;  
    }  
  
    //以下生成本次的正确答案  
    for (int i = 1; i <= r + 1; i++)  
    {  
        for (int j = 1; j <= r + 1; j++)  
        {  
            f[i][j].guess = '#';  
            if (f[i][j].all == 1)  
            {  
  
                f[i][j].ans = '*'; //这个位置有雷  
  
            }  
            else  
            {  
                //统计四周雷数  
                int cnt = 0;  
                for (int ii = i - 1; ii <= i + 1; ii++)  
                {  
                    for (int jj = j - 1; jj <= j + 1; jj++)  
                    {  
                        if (f[ii][jj].all == 1)  
                            cnt++;  
  
                    }  
                }  
                f[i][j].ans = cnt + 48;  
            }  
        }  
    }  
  
    Output (r, 1, NULL);  
  
    printf("请输入两个正整数来表示你选定的位置的坐标，如输入 3 2 表示你选定第三行第二列 \n");  
    Playing(r, SUMMINE);  
  
    return SUMMINE;  
}  
//输出游戏界面  
void  Output(int r, int times, int* pSUMMINE) //指针  
{  
  
    for (int i = 1; i <= r; i++)printf("--");  
    printf(">y\n");  
    int cou = 0;  
    if (!times)  
        cou = 0;  
    for (int i = 1; i <= r; i++)  
    {  
        for (int j = 1; j <= r; j++)  
        {  
            if (j == 1)printf("|");  
            if (times)  f[i][j].guess = '#';  
            else    if (f[i][j].guess != '#')  
            {  
                cou++;  
                f[i][j].all = -1;  
            }  
            printf("%c ", f[i][j].guess);  
  
        }  
        printf("\n");  
    }  
    printf("V\nx\n");  
    if (!times) *pSUMMINE = cou;  
  
}  
  
int Playing(int r, int SUMMINE)  
{  
    long i = 10000000L; //计算时间开始  
    clock_t start, finish;  
    double duration;  
    start = clock();  
    while (i--);  
    Color(30);  
    printf("本次扫雷共有%d颗雷\n", SUMMINE);  
    int SUM = SUMMINE;  
    SUMMINE = 0;  
    system("pause");  
    Color(15);  
    while (SUMMINE + SUM != r * r) //判断是否扫完了所有雷  
    {  
        //用户猜雷  
        int x, y;  
        char ch;  
        do  
        {  
            int xx;  
            xx = scanf("%d%d", &x, &y);  
            if (xx != 2 || x <= 0 || x > r || y <= 0 || y > r)  
            {  
                printf("输入错误！请重新输入：\n");  
                printf("请输入两个正整数来表示你认为无雷的位置的坐标，如输入 3 2 表示你选定第三行第二列 \n");  
                while (getchar() != '\n');  
            }  
            else break;  
        }  
        while (1);  
        finish = clock();  
        //判断用户选中的地方是不是有雷  
        if (f[x][y].all == 1) //这个地方真的有雷  
        {  
  
            printf("你踩雷了！\a\n答案是：\n");  
  
            for (int i = 1; i <= r; i++)  
            {  
                printf("\t");  
                for (int j = 1; j <= r; j++)  
                {  
                    printf("%c ", f[i][j].ans);  
                }  
                printf("\n");  
            }  
            printf("*表示雷\n");  
            Continuing();  
            break;  
            SUMMINE = 0;  
        }  
  
        else if (f[x][y].all == 0) //这个地方没有雷  
        {  
            SUMMINE++;  
            if (SUMMINE + SUM != r * r) //如果雷全部排空了  
  
  
            {  
  
                Opening(x, y, r); //展开一片非雷的地区  
                Output(r, 0, &SUMMINE);  
            }  
            if (SUMMINE + SUM == r * r) //如果雷全部排空了  
            {  
  
                Color(13);  
                printf("      恭喜你成功了！\n本次用时：%.2fs\n", (finish - start) / 1000.0);  
                FILE *fp;  
                fp = fopen("1.txt", "a");  
                fprintf(fp, "%.2f\n", (finish - start) / 1000.0);  
                fclose(fp);  
                Rank();  
                Continuing();  
  
            }  
        }  
        else  
        {  
            printf("该点已被翻开过，请重新选取一点！\n");  
        }  
        f[x][y].all = -1;  
    }  
  
}  
int Opening (int x, int y, int n) //递归+深度搜索  
{  
    int cnt = Count(x, y, n);  
    if (cnt == 0)  
    {  
        f[x][y].guess = ' ';  
        if (x - 1 > 0 && y - 1 > 0 && f[x - 1][y - 1].all == 0)  
        {  
            if (f[x - 1][y - 1].guess != ' ')   Opening(x - 1, y - 1, n);  
        }  
        if (x - 1 > 0 && f[x - 1][y].all == 0)  
        {  
            if (f[x - 1][y].guess != ' ')       Opening(x - 1, y, n);  
        }  
        if (y - 1 > 0 && f[x][y - 1].all == 0)  
        {  
            if (f[x ][y - 1].guess != ' ')  Opening(x, y - 1, n);  
        }  
        if (x + 1 <= n && y + 1 <= n && f[x + 1][y + 1].all == 0)  
        {  
            if (f[x + 1][y + 1].guess != ' ')   Opening(x + 1, y + 1, n);  
        }  
        if (x + 1 <= n && f[x + 1][y].all == 0)  
        {  
            if (f[x + 1][y].guess != ' ')   Opening(x + 1, y, n);  
        }  
        if (y + 1 <= n && f[x][y + 1].all == 0)  
        {  
            if (f[x][y + 1].guess != ' ')   Opening(x, y + 1, n);  
        }  
        if (y + 1 <= n && x - 1 > 0 && f[x - 1][y + 1].all == 0)  
        {  
            if (f[x - 1][y + 1].guess != ' ')   Opening(x - 1, y + 1, n);  
        }  
        if (y - 1 > 0 && x + 1 <= n && f[x + 1][y - 1].all == 0)  
        {  
            if (f[x + 1][y - 1].guess != ' ')   Opening(x + 1, y - 1, n);  
        }  
    }  
    else  
    {  
        f[x][y].guess = cnt + '0';  
    }  
    return 0;  
}  
int Count(int x, int y, int n)  
{  
    int sum = 0;  
    for (int i = Max(0, x - 1); i <= Min(x + 1, n); i++)  
        for (int j = Max(0, y - 1); j <= Min(y + 1, n); j++)  
        {  
            if (f[i][j].all == 1)sum++;  
        }  
    return sum;  
}  
void Continuing()  
{  
    Color(15);  
    printf("继续游戏-----1 \t 结束游戏------0\n");  
    int x;  
    do  
    {  
        int xx = scanf("%d", &x);  
        if (xx != 1 || (x != 1 && x != 0))  
        {  
            printf("输入错误！请重新输入：\n");  
            printf("继续游戏-----1 \t 结束游戏------0\n");  
            while (getchar() != '\n');  
        }  
        else break;  
    }  
    while (1);  
    if (x == 0)still = 0;  
    for (int i = 1; i <= 21; i++)  
        for (int j = 1; j <= 21; j++)  
        {  
            f[i][j].all = 0;  
            f[i][j].guess = '*';  
            f[i][j].ans = ' ';  
        }  
  
}  
void Rank()  
{  
    char name[60][21];  
    double a[60] = {0};  
    memset(a, 0, sizeof(a));  
    FILE *fp;  
    fp = fopen("1.txt", "r");  
    int cnt;  
    for ( cnt = 1; cnt <= 6; cnt++)  
    {  
        int x = fscanf(fp, "%lf", &a[cnt]);  
  
    }  
  
  
    fclose(fp);  
    //排序  
  
    Outputlist(a);  
}  
void HeapAdjust(treeall * H, int s, int m)  
{  
    treeone rc = H->r[s];  
    for (int j = 2 * s; j <= m; j *= 2)  
    {  
  
        if (j + 1 < m && (H->r[j].key < H->r[j + 1].key))  
        {  
            j++;  
        }  
  
        if (!(rc.key < H->r[j].key))  
        {  
            break;  
        }  
  
        H->r[s] = H->r[j];  
        s = j;  
    }  
    H->r[s] = rc;  
}  
//交换两个记录的位置  
void swap(treeone *a, treeone *b)  
{  
    int key = a->key;  
    a->key = b->key;  
    b->key = key;  
}  
//构建堆的过程  
void HeapSort(treeall *H)  
{  
  
    for (int i = H->length / 2; i > 0; i--)  
    {  
        HeapAdjust(H, i, H->length);  
    }  
  
    for (int i = H->length; i > 1; i--)  
    {  
  
        swap(&(H->r[1]), &(H->r[i]));  
  
        HeapAdjust(H, 1, i - 1);  
    }  
}  
int Outputlist(double a[])  
{  
  
    treeall * L = (treeall*)malloc(sizeof(treeall));  
    L->length = 6;  
  
    for (int i = 1; i <= 6; i++)  
    {  
        L ->r[i].key = a[i] * 100;  
    }  
  
    HeapSort(L);  
    HeapSort(L);  
    for (int i = 1; i <= 5; i++)  
        for (int j = i + 1; j <= 6; j++)  
            if (L->r[i].key > L->r[j].key)  
            {  
                int temp = L->r[i].key;  
                L->r[i].key = L->r[j].key;  
                L->r[j].key = temp;  
            }  
  
    printf("当前排名情况为：\n");  
  
    for (int i = 1; i <= 5; i++)  printf("%d.  %.2f\n", i, L->r[i].key / 100.0);  
    //更新前五名排行榜  
    FILE *fp;  
    fp = fopen("1.txt", "w");  
    if (fp == NULL)  
    {  
        printf("文件打开错误！程序终止\n");  
        system("pause");  
        exit(0);  
    }  
    else  
    {  
        for (int i = 1; i <= 5; i++)  
            fprintf(fp, "%.2f\n", L->r[i].key / 100.0);  
        fclose(fp);  
    }  
    return 0;  
}  
