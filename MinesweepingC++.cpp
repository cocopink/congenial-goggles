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
    int all;//��ʼ������  
    char ans;  
    char guess;  
} f[21][21];  
  
//������¼�Ľṹ��  
typedef struct  
{  
    int key;  
} treeone;  
//��¼��Ľṹ��  
typedef struct  
{  
    treeone r[MAX];  
    int length;  
} treeall;  
  
  
void Color(int num);  
int  Beginning ();  
int Prepare (int dif, char*puser); //ָ��  
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
  
  
void Color(int num) //������ɫ  
{  
    HANDLE hout;  
    hout = GetStdHandle(STD_OUTPUT_HANDLE);  
    SetConsoleTextAttribute(hout, num);  
}  
  
void Menu()  
{  
  
    Color(11);//0 ��ɫ��1 ���������ɫ 2 ���� 3 ����4 ���� 5 ��ɫ 6 ���� 7 �� 8 �ң�����̫�壩 9 ����10 ���� 11 ����12 �� 13�� 14���� 15 �� ��16�Ժ��Ǳ�����ɫ��  
    //Color(30); //��������ɫ�Ļ�ɫ����  
    printf("\t\t��ӭ����ɨ����Ϸ!\n");  
  
    Color(14);  
    printf("=======================*******************===========================\n" );  
    printf("\t     ��ѡ���Ѷȣ�(����������)\n");  
    printf(" ��ģʽ��3*3��--1\t") ;  
    printf("   һ��ģʽ��7*7��--2\t") ;  
    printf("   ����ģʽ��10*10��--3\n") ;  
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
    printf("ѧ����120L021306����Ʒ~��лʹ�ã�") ;  
    system("pause");  
  
    return 0;  
}  
int  Beginning ()  
{  
    char user[21];  
    printf("�������������(���ļ���)��");  
    scanf("%s", user);  
    /*FILE *fp; 
    fp=fopen("1.txt","a"); 
    fprintf(fp,"%s\n",user); 
    fclose(fp);*/  
    printf("\t\t������������Hello,%s!������������\n��������ѡ����Ѷȣ�\n", user);  
  
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
            printf("�������룡����������(���������֣�1/2/3):");  
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
            if (random(8) < 1) //���ȡ��0~7֮������������С��һ��ô��Ǹõ�����  
            {  
                f[i][j].all = 1; //1��������  
                SUMMINE++;  
            }  
            else  
            {  
                f[i][j].all = 0; //����  
            }  
        }  
    }  
    //��ֹ��������  
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
        f[(int)random(r) + 1][(int)random(r) + 1].all = 1;    //����ѡһ������������  
        SUMMINE = 1;  
    }  
  
    //�������ɱ��ε���ȷ��  
    for (int i = 1; i <= r + 1; i++)  
    {  
        for (int j = 1; j <= r + 1; j++)  
        {  
            f[i][j].guess = '#';  
            if (f[i][j].all == 1)  
            {  
  
                f[i][j].ans = '*'; //���λ������  
  
            }  
            else  
            {  
                //ͳ����������  
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
  
    printf("��������������������ʾ��ѡ����λ�õ����꣬������ 3 2 ��ʾ��ѡ�������еڶ��� \n");  
    Playing(r, SUMMINE);  
  
    return SUMMINE;  
}  
//�����Ϸ����  
void  Output(int r, int times, int* pSUMMINE) //ָ��  
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
    long i = 10000000L; //����ʱ�俪ʼ  
    clock_t start, finish;  
    double duration;  
    start = clock();  
    while (i--);  
    Color(30);  
    printf("����ɨ�׹���%d����\n", SUMMINE);  
    int SUM = SUMMINE;  
    SUMMINE = 0;  
    system("pause");  
    Color(15);  
    while (SUMMINE + SUM != r * r) //�ж��Ƿ�ɨ����������  
    {  
        //�û�����  
        int x, y;  
        char ch;  
        do  
        {  
            int xx;  
            xx = scanf("%d%d", &x, &y);  
            if (xx != 2 || x <= 0 || x > r || y <= 0 || y > r)  
            {  
                printf("����������������룺\n");  
                printf("��������������������ʾ����Ϊ���׵�λ�õ����꣬������ 3 2 ��ʾ��ѡ�������еڶ��� \n");  
                while (getchar() != '\n');  
            }  
            else break;  
        }  
        while (1);  
        finish = clock();  
        //�ж��û�ѡ�еĵط��ǲ�������  
        if (f[x][y].all == 1) //����ط��������  
        {  
  
            printf("������ˣ�\a\n���ǣ�\n");  
  
            for (int i = 1; i <= r; i++)  
            {  
                printf("\t");  
                for (int j = 1; j <= r; j++)  
                {  
                    printf("%c ", f[i][j].ans);  
                }  
                printf("\n");  
            }  
            printf("*��ʾ��\n");  
            Continuing();  
            break;  
            SUMMINE = 0;  
        }  
  
        else if (f[x][y].all == 0) //����ط�û����  
        {  
            SUMMINE++;  
            if (SUMMINE + SUM != r * r) //�����ȫ���ſ���  
  
  
            {  
  
                Opening(x, y, r); //չ��һƬ���׵ĵ���  
                Output(r, 0, &SUMMINE);  
            }  
            if (SUMMINE + SUM == r * r) //�����ȫ���ſ���  
            {  
  
                Color(13);  
                printf("      ��ϲ��ɹ��ˣ�\n������ʱ��%.2fs\n", (finish - start) / 1000.0);  
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
            printf("�õ��ѱ���������������ѡȡһ�㣡\n");  
        }  
        f[x][y].all = -1;  
    }  
  
}  
int Opening (int x, int y, int n) //�ݹ�+�������  
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
    printf("������Ϸ-----1 \t ������Ϸ------0\n");  
    int x;  
    do  
    {  
        int xx = scanf("%d", &x);  
        if (xx != 1 || (x != 1 && x != 0))  
        {  
            printf("����������������룺\n");  
            printf("������Ϸ-----1 \t ������Ϸ------0\n");  
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
    //����  
  
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
//����������¼��λ��  
void swap(treeone *a, treeone *b)  
{  
    int key = a->key;  
    a->key = b->key;  
    b->key = key;  
}  
//�����ѵĹ���  
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
  
    printf("��ǰ�������Ϊ��\n");  
  
    for (int i = 1; i <= 5; i++)  printf("%d.  %.2f\n", i, L->r[i].key / 100.0);  
    //����ǰ�������а�  
    FILE *fp;  
    fp = fopen("1.txt", "w");  
    if (fp == NULL)  
    {  
        printf("�ļ��򿪴��󣡳�����ֹ\n");  
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
