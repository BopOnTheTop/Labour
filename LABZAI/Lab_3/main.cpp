#include <iostream>
#include <cstdlib>
#include <thread>
#include <cmath>
#include <ctime>
#define N 500000
#define TH 3
/**  9.Визначити, який елемент найчастіше трапляється у масиві цілих чисел.*/
int mass[N]={0}, base[N][2]={0}, entries[TH]={0};// Масив згенерених чисел, ну і база унікальних чисел.
int Rez[TH][2]={0},maxi[TH]={0},winner[TH]={0};
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
void threader(int PID, int THREADS)
{
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

}
int main( int argc, char **argv)
{
int zero,worked_out;
int P, PID;
int rez = 0, globalres = 0;
for(int i = 0; i < N; i++) mass[i]=rand()%100;//Ініціалізували випадковий масив
zero = clock();
////// Код який залежить від потоку

thread first (threader,0,TH);
thread second (threader,1,TH);
thread third (threader,2,TH);


first.join();
second.join();
third.join();
worked_out=clock();
for(int i = 0; i< TH; i++)
    if(globalres<entries[i])globalres=entries[i],rez=winner[i];
cout << "Result: " << rez << "\n";
cout << "Процес працював " << fabs((worked_out-zero)*1.0)/CLOCKS_PER_SEC << " с\n";

return 0;
}
