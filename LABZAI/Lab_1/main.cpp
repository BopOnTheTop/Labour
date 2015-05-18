#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#define N 500000
#define THREADS 10
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
int main (int argc, char *argv[])
{
int	PID, nthreads, chunk;
int zero,worked_out[THREADS];
int P;
int rez = 0, globalres = 0;
int mass[N]={0}, base[N][2]={0}, entries[THREADS]={0};// Масив згенерених чисел, ну і база унікальних чисел.
int Rez[THREADS][2]={0},maxi[THREADS]={0},winner[THREADS]={0};
int Rez[THREADS][2]={0},maxi[THREADS]={0},winner[THREADS]={0};
for(int i = 0; i < N; i++) mass[i]=rand()%100;//Ініціалізували випадковий масив
zero = clock();
cout << "PIU!";
chunk = 1;                    /* set loop iteration chunk size */

/*** Spawn a parallel region explicitly scoping all variables ***/
#pragma omp parallel shared(mass,base,entries,winner,worked_out,maxi,nthreads,chunk) private(PID) num_threads(THREADS)
  PID = omp_get_thread_num();
  if (PID == 0)
    {
    nthreads = omp_get_num_threads();
    }
int lo = N/THREADS*PID, hi = N/THREADS*PID + N/THREADS;  //діапазон значень - N/THREADS*PID + N/THREADS
#pragma omp for schedule (static, chunk)
for(int i = lo; i < hi; i++)
        if(!confirm_number(base,entries[PID],mass[i]))
            {
                base[entries[PID]][0]=mass[i];
                base[entries[PID]][1]=seek_the_number(mass,mass[i]);
                entries[PID]++;
            }
#pragma omp for schedule (static, chunk)
for(int i = lo; i < hi; i++)
        {
            if(maxi[PID]<base[i][1])maxi[PID] = base[i][1],winner[PID]=base[i][0];
        }
/*** End of parallel region ***/

for(int i = 0; i< THREADS; i++)
    if(globalres<entries[i])globalres=entries[i],rez=winner[i];
if( PID == 0 )
{
    cout << "Result: " << rez << "\n";
    for(int i = 0; i< THREADS;i++)
        cout << "Процес №"<< i << " працював " << ((worked_out[i]-zero)*1.0)/CLOCKS_PER_SEC << " с\n";
}

}


