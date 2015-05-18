#include <iostream>
#include <cstdlib>
//#include <mpi.h>
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

int main()
{
    int mass[N]={0}, base[N][2]={0}, entries=0, maxi=0,winner;// Масив згенерених чисел, ну і база унікальних чисел.
    int zero,worked_out;
    for(int i = 0; i < N; i++) mass[i]=rand()%100;
    zero = clock();
    for(int i = 0; i < N; i++)
        if(!confirm_number(base,entries,mass[i]))
            {
                base[entries][0]=mass[i];
                base[entries][1]=seek_the_number(mass,mass[i]);
                entries++;
            }
    /*for(int i = 0; i<entries; i++)
        {
            cout <<"Число " << base[i][0] << " зустрілось " << base[i][1] << " раз\n";
        }*///тестувальний вивід
    for(int i = 0; i < N; i++)
        {
            if(maxi<base[i][1])maxi = base[i][1],winner=base[i][0];
        }
    worked_out=clock();
    cout << "Hello world!" << endl;
    cout << "Найчастіше зустрічається число " << winner << " -- " << maxi << "раз\n" ;
    cout << "Час роботи : " << (worked_out-zero)*1.0/CLOCKS_PER_SEC << " с\n";
    return 0;
}
