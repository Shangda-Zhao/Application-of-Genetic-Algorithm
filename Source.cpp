#include<iostream>
#include<stdio.h>          
#include<stdlib.h>
#include<time.h>

using namespace std;

typedef struct                         // ��������Ľṹ��
{
    short int bit[6];
    int fit;
}chrom;                                        


void evpop(chrom popcurrent[4]);              // ������ɳ�ʼ��Ⱥ��
int bin2dec(chrom popcurrent);                // �������ƻ���Ϊʮ���ƣ�
int fitness(int x);                           // ��������Ӧ�ȣ�
void pickchroms(chrom popcurrent[4]);         // ѡ����壻
void crossover(chrom popnext[4]);             // ���������
void mutation(chrom popnext[4]);              // ���������

int main()                                   
{
    srand(time(0));
	int num;                                            // ����������
    int i,j,Max=-5e8,k;
    cout << "�������ֵ  y = -x^3 + 5" << endl;
    cout << "��������Ҫ�趨�ĵ�����: ";
    cin >> num;                                         // �������������
    chrom popcurrent[4];                                // ��ʼ��Ⱥ��ģΪ4��
    evpop(popcurrent);                                  // ���������ʼ��Ⱥ��
    for(i=0; i<num; i++)                                // ��ʼ������
    {
        cout << endl;
        cout << "��ǰ����������" << i+1 << endl;         // �����ǰ����������
        pickchroms(popcurrent);                         // ��ѡ������壻
        crossover(popcurrent);                          // ����õ��¸��壻
        mutation(popcurrent);                           // ����õ��¸��壻
    }
    for(j=0; j<4; j++)
    {
        if(popcurrent[j].fit > Max)
        {
            Max=popcurrent[j].fit;
            k=bin2dec(popcurrent[j]);
        }
    }
    cout << endl <<"�� x=" << k << " ʱ���������ֵΪ��" << Max << endl;
    return 0;
}                                              

 
void evpop(chrom popcurrent[4])                        // ������������ɳ�ʼ��Ⱥ��
{
    cout << "������Ⱥ��������Ϊ 4" << endl;
    int i,j,k,value;
    int random;
    for(i=0; i<4; i++)                                 // ��Ⱥ�е�ÿ������
    {
        for(j=0; j<6; j++)                             // ÿ������ı���
        {
            random = rand() % 2;                       // ����һ�����ֵ
            popcurrent[i].bit[j] = random;             // �����������ı���ֵ��0��1��
        }
        value = bin2dec(popcurrent[i]);                // �������ƻ���Ϊʮ���ƣ�
        popcurrent[i].fit = fitness(value);            // ����������Ӧ�ȣ�
        cout << "���� [";
        for (k=0; k<6; k++)
            {cout << popcurrent[i].bit[k];}
	    cout << "]     ";                              // ���������Ⱥ�ĸ���������
        cout << "��Ӧ�ȣ�" << popcurrent[i].fit;
    	cout << endl;                                      
    }
}                          


int bin2dec(chrom popcurrent)                          // �������������ƻ���Ϊʮ���ƣ�
{
    int z;
    z = (popcurrent.bit[1]*1)+(popcurrent.bit[2]*2)+(popcurrent.bit[3]*4)+(popcurrent.bit[4]*8)+(popcurrent.bit[5]*16);
    if(popcurrent.bit[0] == 1)
        z = z*(-1);                                    // ���ǵ�������
    return z;                            
}               
 
int fitness(int x)                                     // ��������������Ӧ�ȣ�
{
    int y;
    y = -(x*x*x)+5;                                    // Ŀ�꺯���� y= - ( x^3 ) +5��
    return y;              
}                                     

void pickchroms(chrom popcurrent[4])                   // ������ѡ����壻
{
    int i,j;
    chrom temp;                               
    for(i=0; i<3; i++)                                 // ���ݸ�����Ӧ��������
	{
		for(j=0; j<3-i; j++)
        {
            if(popcurrent[j+1].fit>popcurrent[j].fit)
            {
                temp=popcurrent[j+1];
                popcurrent[j+1]=popcurrent[j];
                popcurrent[j]=temp;
            }   
        }                
	}
    cout << "����Ӧ������" << endl;
    for(i=0; i<4; i++)
    {   
        cout << "���� [";
        for (j=0; j<6; j++)
        {   cout << popcurrent[i].bit[j];   }
        cout << "]     ";                              // ���������Ⱥ�ĸ���������
        cout << "��Ӧ�ȣ�" << popcurrent[i].fit << endl;
    }
}                                          

void crossover(chrom popnext[4])                       // ���������������
{
    int random;
    int i,j;
    random = rand();                                   // �����������㣻
    random = (random%5)+1;                             // ����������1��5֮�䣻
    for(i=0; i<random; i++)                    
    {
        popnext[2].bit[i] = popnext[0].bit[i];         // ��������Ӵ�
        popnext[3].bit[i] = popnext[1].bit[i];
    } 
    for(i=random; i<6; i++)
    {
        popnext[2].bit[i] = popnext[1].bit[i];
        popnext[3].bit[i] = popnext[0].bit[i];
    }   
    for(i=2; i<4; i++)                                 // Ϊ�¸��������Ӧ��ֵ��
        popnext[i].fit = fitness(bin2dec(popnext[i]));
    cout << "���������" << endl;
    for(i=0; i<4; i++)
    {   
        cout << "���� [";
        for (j=0; j<6; j++)
            cout << popnext[i].bit[j];
        cout << "]     ";                              // ���������Ⱥ�ĸ���������
        cout << "��Ӧ�ȣ�" << popnext[i].fit << endl;
    }
}                                           

void mutation(chrom popnext[4])                        // ���������������
{
    int j;
    int random;
    int row,col;  
    random = rand() % 2;
    if(random == 1)                                    // random==1�ĸ��ʣ���������Ϊ1/3��
    {
        cout << "���������" << endl;
        col = rand()%6;                                // ���ѡ��Ҫ����ı���λ��
        row = rand()%4;                                // ���ѡ��Ҫ����ĸ��壻
        cout << "���� [";
        for (j=0; j<6; j++)
            cout << popnext[row].bit[j];
        cout << "] ����Ϊ [";                          // �������ǰ����ı������
        popnext[row].bit[col] = popnext[row].bit[col] ^ 1;			// ��ת����λ
        popnext[row].fit = fitness(bin2dec(popnext[row]));          // �����������Ӧ��ֵ��
        for (j=0; j<6; j++)
            cout << popnext[row].bit[j];                            // ����������¸��壻
        cout << "]  " << "��Ӧ�ȣ�" << popnext[row].fit << endl;
    }
}   