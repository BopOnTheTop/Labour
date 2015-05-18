#include <iostream>
#include <cstdlib>
#include <mpi.h>
#include <cmath>
#include <ctime>
#define N 500000
#define THREADS 10
/**  9.Визначити, який елемент найчастіше трапляється у масиві цілих чисел.*/

using namespace std;
int seek_the_number(int mass[],int number)
{
int entries = 0;
for(int i=0;i<N;i++)
    {
        if(mass[number]==mass[i])entries++;//Прохід по всьому масиву. Вираховуємо кількість входжень.
    }
return entries;
}

int confirm_number(int base[][2],int entries, int number)//підтвердження наявності конкретної циферки в "базі"
{
for(int i = 0 ; i<entries ;i++)
    {
        if(number==base[i][0])return 1;
    }
return 0;
}
int main( int argc, char **argv)
{
int zero,worked_out[THREADS];
int P, PID;
int rez = 0, globalres = 0;
int mass[N]={0}, base[N][2]={0}, entries[THREADS]={0};// Масив згенерених чисел, ну і база унікальних чисел.
int Rez[THREADS][2]={0},maxi[THREADS]={0},winner[THREADS]={0};
for(int i = 0; i < N; i++) mass[i]=rand()%100;//Ініціалізували випадковий масив
zero = clock();
MPI_Init(&argc, &argv);//понеслась паралелізація
MPI_Comm_size( MPI_COMM_WORLD, &P);//кількість потоків у Р
MPI_Comm_rank( MPI_COMM_WORLD, &PID);//номерок поточного потоку.
////// Код який залежить від потоку

int lo = N/THREADS*PID, hi = N/THREADS*PID + N/THREADS;  //діапазон значень - N/THREADS*PID + N/THREADS
for(int i = lo; i < hi; i++)
        if(!confirm_number(base,entries[PID],mass[i]))
            {
                base[entries[PID]][0]=mass[i];
                base[entries[PID]][1]=seek_the_number(mass,mass[i]);
                entries[PID]++;
            }
for(int i = lo; i < hi; i++)
        {
            if(maxi[PID]<base[i][1])maxi[PID] = base[i][1],winner[PID]=base[i][0];
        }
MPI_Barrier(MPI_COMM_WORLD);
worked_out[PID]=clock();
for(int i = 0; i< THREADS; i++)
    if(globalres<entries[i])globalres=entries[i],rez=winner[i];
if( PID == 0 )
{
cout << "Result: " << rez << "\n";
for(int i = 0; i< THREADS;i++)
    cout << "Процес №"<< i << " працював " << fabs((worked_out[i]-zero)*1.0)/CLOCKS_PER_SEC << " с\n";
}

MPI_Finalize();

return 0;
}
