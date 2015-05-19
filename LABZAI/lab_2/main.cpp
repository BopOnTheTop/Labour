#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>
#include <cmath>
#include <ctime>
#define THREADS 4
using namespace std;

int main( int argc, char **argv)
{
 int N=0, zero, worked_out[THREADS]={0};
 double **L, **U, **A;//Ніби матрички. Ніби квадратні.
 double *b,*y,*x;
 int P, PID;
 //zero=clock();//Почали розклад матриці
 ifstream inside("inputs");
 inside >> N;
 A=new double*[N];
 y = new double[N];
 for(int i = 0; i< N;i++)
 {
    A[i]=new double[N];
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
 double *l=new double[N*N];//Створення двовимірного масиву одним шматком. Ну і його нуління.
 L=new double*[N];
 for(int i = 0; i< N;i++)
    L[i]=new double[N];

 U=new double*[N];
 for(int i = 0; i< N;i++)
    U[i]=new double[N];

for(int i = 0; i<N; i++)
    for(int j = 0; j<N; j++){U[i][j]=0;L[i][j]=0;}

x = new double[N];
for(int i = 0; i< N; i++)
{
    //b[i]=0;
    x[i]=0;
}
zero=clock();//Почали розклад матриці
MPI_Init(&argc, &argv);//понеслась паралелізація
MPI_Comm_size( MPI_COMM_WORLD, &P);//кількість потоків у Р
MPI_Comm_rank( MPI_COMM_WORLD, &PID);//номерок поточного потоку.
int lo = N/THREADS*PID, hi = N/THREADS*PID + N/THREADS;  //діапазон значень - N/THREADS*PID + N/THREADS
for (int i = lo; i < hi; i++)
            {
                for (int j = lo; j < hi; j++)
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
                        for (int k = lo; k < i; k++)
                        {
                            sum += L[j][k] * U[k][i];
                        }
                        L[j][i] = (A[j][i] - sum) / U[i][i];
                    }
                }
            }
worked_out[PID]=clock();
MPI_Barrier(MPI_COMM_WORLD);
if( PID == 0 )
{
for(int i = N-1; i>=0;i--)
    {   double tempo = y[i];
        for(int k=0;k<i;k++)
            tempo-=U[i][k]*x[i];
        tempo/=U[i][i];
        x[i]=tempo;
    }
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
for(int i = 0; i< THREADS;i++)
    cout << "Процес №"<< i << " працював " << fabs((worked_out[i]-zero)*1.0)/CLOCKS_PER_SEC << " с\n";
}
MPI_Finalize();
return 0;
}
