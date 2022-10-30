#include<iostream>
#include<stdio.h>          
#include<stdlib.h>
#include<time.h>

using namespace std;

typedef struct                         // 单个个体的结构；
{
    short int bit[6];
    int fit;
}chrom;                                        


void evpop(chrom popcurrent[4]);              // 随机生成初始种群；
int bin2dec(chrom popcurrent);                // 将二进制换算为十进制；
int fitness(int x);                           // 求个体的适应度；
void pickchroms(chrom popcurrent[4]);         // 选择个体；
void crossover(chrom popnext[4]);             // 交叉操作；
void mutation(chrom popnext[4]);              // 变异操作；

int main()                                   
{
    srand(time(0));
	int num;                                            // 迭代次数；
    int i,j,Max=-5e8,k;
    cout << "求函数最大值  y = -x^3 + 5" << endl;
    cout << "请输入您要设定的迭代数: ";
    cin >> num;                                         // 输入迭代次数；
    chrom popcurrent[4];                                // 初始种群规模为4；
    evpop(popcurrent);                                  // 随机产生初始种群；
    for(i=0; i<num; i++)                                // 开始迭代；
    {
        cout << endl;
        cout << "当前迭代次数：" << i+1 << endl;         // 输出当前迭代次数；
        pickchroms(popcurrent);                         // 挑选优秀个体；
        crossover(popcurrent);                          // 交叉得到新个体；
        mutation(popcurrent);                           // 变异得到新个体；
    }
    for(j=0; j<4; j++)
    {
        if(popcurrent[j].fit > Max)
        {
            Max=popcurrent[j].fit;
            k=bin2dec(popcurrent[j]);
        }
    }
    cout << endl <<"当 x=" << k << " 时，函数最大值为：" << Max << endl;
    return 0;
}                                              

 
void evpop(chrom popcurrent[4])                        // 函数：随机生成初始种群；
{
    cout << "生成种群，个体数为 4" << endl;
    int i,j,k,value;
    int random;
    for(i=0; i<4; i++)                                 // 种群中的每个个体
    {
        for(j=0; j<6; j++)                             // 每个个体的编码
        {
            random = rand() % 2;                       // 产生一个随机值
            popcurrent[i].bit[j] = random;             // 随机产生个体的编码值，0或1；
        }
        value = bin2dec(popcurrent[i]);                // 将二进制换算为十进制；
        popcurrent[i].fit = fitness(value);            // 计算个体的适应度；
        cout << "个体 [";
        for (k=0; k<6; k++)
            {cout << popcurrent[i].bit[k];}
	    cout << "]     ";                              // 输出整个种群的个体编码情况
        cout << "适应度：" << popcurrent[i].fit;
    	cout << endl;                                      
    }
}                          


int bin2dec(chrom popcurrent)                          // 函数：将二进制换算为十进制；
{
    int z;
    z = (popcurrent.bit[1]*1)+(popcurrent.bit[2]*2)+(popcurrent.bit[3]*4)+(popcurrent.bit[4]*8)+(popcurrent.bit[5]*16);
    if(popcurrent.bit[0] == 1)
        z = z*(-1);                                    // 考虑到正负；
    return z;                            
}               
 
int fitness(int x)                                     // 函数：求个体的适应度；
{
    int y;
    y = -(x*x*x)+5;                                    // 目标函数： y= - ( x^3 ) +5；
    return y;              
}                                     

void pickchroms(chrom popcurrent[4])                   // 函数：选择个体；
{
    int i,j;
    chrom temp;                               
    for(i=0; i<3; i++)                                 // 根据个体适应度来排序
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
    cout << "按适应度排序：" << endl;
    for(i=0; i<4; i++)
    {   
        cout << "个体 [";
        for (j=0; j<6; j++)
        {   cout << popcurrent[i].bit[j];   }
        cout << "]     ";                              // 输出整个种群的个体编码情况
        cout << "适应度：" << popcurrent[i].fit << endl;
    }
}                                          

void crossover(chrom popnext[4])                       // 函数：交叉操作；
{
    int random;
    int i,j;
    random = rand();                                   // 随机产生交叉点；
    random = (random%5)+1;                             // 交叉点控制在1到5之间；
    for(i=0; i<random; i++)                    
    {
        popnext[2].bit[i] = popnext[0].bit[i];         // 交叉产生子代
        popnext[3].bit[i] = popnext[1].bit[i];
    } 
    for(i=random; i<6; i++)
    {
        popnext[2].bit[i] = popnext[1].bit[i];
        popnext[3].bit[i] = popnext[0].bit[i];
    }   
    for(i=2; i<4; i++)                                 // 为新个体计算适应度值；
        popnext[i].fit = fitness(bin2dec(popnext[i]));
    cout << "交叉操作：" << endl;
    for(i=0; i<4; i++)
    {   
        cout << "个体 [";
        for (j=0; j<6; j++)
            cout << popnext[i].bit[j];
        cout << "]     ";                              // 输出整个种群的个体编码情况
        cout << "适应度：" << popnext[i].fit << endl;
    }
}                                           

void mutation(chrom popnext[4])                        // 函数：变异操作；
{
    int j;
    int random;
    int row,col;  
    random = rand() % 2;
    if(random == 1)                                    // random==1的概率，即变异率为1/3；
    {
        cout << "变异操作：" << endl;
        col = rand()%6;                                // 随机选择要变异的编码位；
        row = rand()%4;                                // 随机选择要变异的个体；
        cout << "个体 [";
        for (j=0; j<6; j++)
            cout << popnext[row].bit[j];
        cout << "] 变异为 [";                          // 输出变异前个体的编码情况
        popnext[row].bit[col] = popnext[row].bit[col] ^ 1;			// 反转编码位
        popnext[row].fit = fitness(bin2dec(popnext[row]));          // 计算变异后的适应度值；
        for (j=0; j<6; j++)
            cout << popnext[row].bit[j];                            // 输出变异后的新个体；
        cout << "]  " << "适应度：" << popnext[row].fit << endl;
    }
}   