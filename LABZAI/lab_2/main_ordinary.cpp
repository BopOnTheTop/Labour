#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>

//#define N 3
using namespace std;

int main()
{
 int N=0,zero,worked_out;
 long double **L, **U, **A;//Ніби матрички. Ніби квадратні.
 long double *b,*y,*x;
 zero=clock();//Почали розклад матриці
 ifstream inside("inputs");
 inside >> N;
 A=new long double*[N];
 y = new long double[N];
 for(int i = 0; i< N;i++)
 {
    A[i]=new long double[N];
 }
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            inside >> A[i][j];
        }
    for(int i = 0; i < N; i++)
    {
        inside >> y[i];
    }
 long double *l=new long double[N*N];//Створення двовимірного масиву одним шматком. Ну і його нуління.
 L=new long double*[N];
 for(int i = 0; i< N;i++)
    L[i]=new long double[N];

 U=new long double*[N];
 for(int i = 0; i< N;i++)
    U[i]=new long double[N];

for(int i = 0; i<N; i++)
    for(int j = 0; j<N; j++){U[i][j]=0;L[i][j]=0;}

x = new long double[N];
for(int i = 0; i< N; i++)
{
    //b[i]=0;
    x[i]=0;
}
//zero=clock();//Почали розклад матриці
for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    U[0][i] = A[0][i];
                    L[i][0] = A[i][0]/U[0][0];
                    double sum = 0;
                    for (int k = 0; k < i; k++)
                    {
                        sum += L[i][k] * U[k][j];
                    }
                    U[i][j] = A[i][j]-sum;
                    if (i > j)
                    {
                        L[j][i] = 0;
                    }
                    else
                    {
                        sum = 0;
                        for (int k = 0; k < i; k++)
                        {
                            sum += L[j][k] * U[k][i];
                        }
                        L[j][i] = (A[j][i] - sum) / U[i][i];
                    }
                }
            }

for(int i = N-1; i>=0;i--)
    {   long double tempo = y[i];
        for(int k=0;k<i;k++)
            tempo-=U[i][k]*x[i];
        tempo/=U[i][i];
        x[i]=tempo;
    }
worked_out=clock();//Закінчили розклад матриці.
cout << "Введено матрицю \n";
for(int i = 0; i<N; i++)
{
    for(int j = 0; j<N; j++)
        cout << A[i][j] << " ";
    cout << " | " << y[i];
    cout << "\n";
}
cout << "Розв’язком СЛАР є вектор:\n";
for(int i = 0 ; i < N; i++)
    cout << x[i] << " ";
cout << "\n";
cout << "Розклад матриці тривав: " <<fabs((worked_out-zero)*1.0)/CLOCKS_PER_SEC << "с\n" ;
return 0;
}
