#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>

using namespace std;

template<typename  T>
class Tablica
{
    public:
    int rozmiar;
    T *tab;

    Tablica (int i)
    {
        rozmiar=i;
        tab = new T[rozmiar];
        for (int i=0;i<rozmiar;i++)
        {
            tab[i]= (T)rand();
        }
    }
    ~Tablica(){delete []tab;}
    wypelnij_tab(int i)
        {
        rozmiar=i;
        tab = new T[rozmiar];
        for (int i=0;i<rozmiar;i++)
        {
            tab[i]= (T)rand();
        }
        }
    T & operator [](int i)
    {
        tab [i];
    }
    const T & operator [](int i)const
    {
        tab [i];
    }
    static void swap(T* a, T* b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

    void Przez_Scalanie(T *wskP, T *wskO)
    {

        if(wskO-wskP > 1)
        {
            T *wsk_tmp = wskP + (wskO-wskP)/2;
            Przez_Scalanie(wskP,wsk_tmp);
            Przez_Scalanie(wsk_tmp,wskO);

            T *Bufor = new T[wskO-wskP];

            T *wLewy, *wPrawy;

for (wLewy=wsk_tmp-1; wLewy>=wskP;wLewy--)
            {
               Bufor[wLewy-wskP] = *wLewy;
            }
              for (wPrawy=wsk_tmp; wPrawy<=wskO-1;wPrawy++)
            {
                Bufor[(wskO-wPrawy)+(wsk_tmp-wskP)-1] = *wPrawy;
            }
         wLewy++,wPrawy--;
         for (T *tab=wskP; tab<wskO;tab++)
            {

                *tab = (Bufor[wLewy-wskP] < Bufor[wPrawy-wskP]) ? Bufor[wLewy++ - wskP] : Bufor[wPrawy-- -wskP];
            }
            delete [] Bufor;


        }
    }


     int Szybkie(T *wskP, T *wskO, bool spr)
     {
         if(wskO-wskP>1)
         {
             T * wskB = wskP;
             T *wskA = wskP+1;
             T *wsk_piwot =  wskP;
             for(wskA;wskA<wskO;wskA++)
                 {
                    if(*wskA<*wsk_piwot)
                    {
                        wskB++;
                        swap(wskA,wskB);
                    }
                 }
             if(wskB!=wsk_piwot)
                 {
                    swap(wsk_piwot,wskB);
                 }
            if(spr==true)
                 {
                    Szybkie(wskP,wskB,true);
                    Szybkie(wskB+1,wskO,true);
                 }
            else
                 return wskO-wskB;
        }
     }
    void Odwrotne(T *wskP, T *wskO, bool spr)
     {
         if(wskO-wskP>1)
         {
             T * wskB = wskP;
             T *wskA = wskP+1;
             T *wsk_piwot =  wskP;
             for(wskA;wskA<wskO;wskA++)
                 {
                    if(*wskA>*wsk_piwot)
                    {
                        wskB++;
                        swap(wskA,wskB);
                    }
                 }
             if(wskB!=wsk_piwot)
                 {
                    swap(wsk_piwot,wskB);
                 }
            if(spr==true)
                 {
                    Odwrotne(wskP,wskB-1,true);
                    Odwrotne(wskB+1,wskO,true);
                 }
        }
     }

    void SKopiec ( T *wskP, T *wskO, int k )
    {
	int j,i;
	int n = (wskO-wskP);
	i = *(wskP+k-1);
	while ( k <= n/2 )
        {
		j=2*k;
            if ((j<n) && ( *(wskP+j-1)<*(wskP+j) ) )
                j++;
            if ( i >= *(wskP+j-1) )
                break;
            else
                {
                *(wskP+k-1) = *(wskP+j-1);
                k=j;
                }
        }
	*(wskP+k-1)=i;
    }
    void kopcowanie ( T *wskP, T *wskO)
        {
            int n = (wskO-wskP);
            int i;
            for ( i = n/2; i>0; i-- ) SKopiec (wskP,wskO,i);
                do
                    {
                    swap(wskP,wskO-1);
                    wskO--;
                    SKopiec(wskP,wskO,1);
                    } while ( *wskO - *wskP > 1 );
        }
    void Przez_Wstawiane (T *wskP,T *wskO)
    {
      int i, j;
      T temp;
      for (i=1; i<(wskO-wskP); ++i)
      {
        temp=*(wskP+i);
        for (j=i; j>0 && temp<*(wskP+j-1); --j)
          *(wskP+j)=*(wskP+j-1);
        *(wskP+j)=temp;
      }
    }
    void hybryda_introspektywne  (T *wskP, T *wskO)
    {
          //cout<<(int)floor(2*log2(wskO-wskP))<<endl;
      introspektywne(wskP,wskO,(int)floor(2*log2(wskO-wskP)));
    //  Przez_Wstawiane(wskP,wskO);
    }

    void introspektywne (T *wskP, T *wskO, int M)
    {
        int i;
        int n = wskO-wskP;
        if (M<=0)
          {
            kopcowanie(wskP,wskO);
            return;
          }
         i = Szybkie(wskP,wskO,false);

        if (i>9)
            introspektywne(wskP,wskO,M-1);
        if (n-1-i>9)
            introspektywne(wskP+i+1,wskO-1-i,M-1);
    }
    void QuickSort(T *wskP,T *wskO) { //jako element do porównania wybierana jest mediana

              T pivot = *(wskP+((wskO - wskP) / 2));
            T *wskA = wskP;
            T *wskB = wskO;
              while (wskA<=wskB) {
                    while (*wskA < pivot)
                          wskA++;
                    while (*wskB > pivot)
                          wskB--;
                    if (wskA <= wskB) {
                        swap(wskA,wskB);
                          wskA++;
                          wskB--;
                    }
              }
              if (wskP < wskB)
                    QuickSort(wskP, wskB);
              if (wskA < wskO)
                    QuickSort(wskA, wskO);

    }

};



menu()
{
    cout<<"p - sortowanie poczatkowych elemetow tablicy"<<endl;
    cout<<"o - wszystkie elementy tablicy juz posortowane ale w odwrotnej kolejnosci"<<endl;
    cout<<"t - tworzenie tabilcy o zadanym rozmiarze"<<endl;
    cout<<"s - sortowanie przez scalanie"<<endl;
    cout<<"q - sortowanie quicksort"<<endl;
    cout<<"i - sortowanie introspektywne"<<endl;
    cout<<"k - sortowanie przez kopcowanie"<<endl;
    cout<<"e - zakoncz program"<<endl;
}

int main ()
{
    ofstream plik;
	clock_t StartTime, StopTime;
    double czas;
    unsigned int i;
    float p=0;
    int l;
    bool t = false;
    bool o = false;
srand(time(NULL));
    char wyb;

    menu();
    cout<<"Podaj rozmiar tablicy: ";
    cin>>i;

    Tablica<int> tab(i);
                  // cout<<"tablica"<<endl;for(int j=0;j<i;j++)cout<<tab.tab[j]<<endl;
    while(true)
    {
        cin>>wyb;
        switch(wyb)
        {
            case 's':
                cout<<"Dla ilu tablic ";
                cin>>l;
                plik.open("Przez_Scalane.txt",ios::out);
                  if(t==true)plik<<p<<"%"<<endl;
                  if(o==true)plik<<"odwrotne"<<endl;
                for(int k=0;k<l;k++)
                {
                    if(t==true)tab.Szybkie(tab.tab,tab.tab+(int)(i*p/100),true);
                    if(o==true)tab.Odwrotne(tab.tab,tab.tab+i,true);
                    StartTime = clock();
                    tab.Przez_Scalanie(tab.tab,tab.tab+i);
                    StopTime = clock();
                    czas = (double)(StopTime-StartTime);
                    plik<<dec<<czas<<endl;
                    delete []tab.tab;
                    tab.wypelnij_tab(i);
                }
                break;
            case 'q':
                cout<<"Dla ilu tablic ";
                cin>>l;
                  plik.open("Szybkie.txt",ios::out);
                if(t==true)plik<<p<<"%"<<endl;
                if(o==true)plik<<"odwrotne"<<endl;
                 for(int k=0;k<l;k++)
                {
                if(t==true)tab.Szybkie(tab.tab,tab.tab+(int)(i*p/100),true);
                if(o==true)tab.Odwrotne(tab.tab,tab.tab+i,true);
               //cout<<"tablica1"<<endl;for(int j=0;j<i;j++)cout<<tab.tab[j]<<endl;
                StartTime = clock();
                tab.QuickSort(tab.tab,tab.tab+i-1);
                StopTime = clock();
               // cout<<"tablica"<<endl;for(int j=0;j<i;j++)cout<<tab.tab[j]<<endl;
                czas = (double)(StopTime-StartTime);
                plik<<dec<<czas<<endl;
                delete []tab.tab;
                tab.wypelnij_tab(i);
                }
                break;
            case 'f':
                cout<<"Dla ilu tablic ";
                cin>>l;
                  plik.open("Szybkie_first.txt",ios::out);
                if(t==true)plik<<p<<"%"<<endl;
                if(o==true)plik<<"odwrotne"<<endl;
                 for(int k=0;k<l;k++)
                {
                if(t==true)tab.Szybkie(tab.tab,tab.tab+(int)(i*p/100),true);
                if(o==true)tab.Odwrotne(tab.tab,tab.tab+i,true);
               // cout<<"tablica1"<<endl;for(int j=0;j<i;j++)cout<<tab.tab[j]<<endl;
                StartTime = clock();
                tab.Szybkie(tab.tab,tab.tab+i,true);
                StopTime = clock();
                //cout<<"tablica"<<endl;for(int j=0;j<i;j++)cout<<tab.tab[j]<<endl;
                czas = (double)(StopTime-StartTime);
                plik<<dec<<czas<<endl;
                delete []tab.tab;
                tab.wypelnij_tab(i);
                }
                break;
            case 'k':
                cout<<"Dla ilu tablic ";
                cin>>l;
                plik.open("kopcowanie.txt",ios::out);
                if(t==true)plik<<p<<"%"<<endl;
                if(o==true)plik<<"odwrotne"<<endl;
                for(int k=0;k<l;k++)
                {
                if(t==true)tab.Szybkie(tab.tab,tab.tab+(int)(i*p/100),true);
                if(o==true)tab.Odwrotne(tab.tab,tab.tab+i,true);
                StartTime = clock();
                tab.kopcowanie(tab.tab,tab.tab+i);
                StopTime = clock();
                czas = (double)(StopTime-StartTime);
                plik<<dec<<czas<<endl;
                delete []tab.tab;
                tab.wypelnij_tab(i);
                }
                 break;
            case 'i':
                cout<<"Dla ilu tablic ";
                cin>>l;
                plik.open("Introspektywne.txt",ios::out);
                if(t==true)plik<<p<<"%"<<endl;
                if(o==true)plik<<"odwrotne"<<endl;
                for(int k=0;k<l;k++)
                {
                    if(t==true)tab.Szybkie(tab.tab,tab.tab+(int)(i*p/100),true);
                    if(o==true)tab.Odwrotne(tab.tab,tab.tab+i,true);
                    StartTime = clock();
                    tab.hybryda_introspektywne(tab.tab,tab.tab+i);
                    StopTime = clock();
                    czas = (double)(StopTime-StartTime);
                    plik<<dec<<czas<<endl;
                    delete []tab.tab;
                    tab.wypelnij_tab(i);
                }
                 break;
            case 't':
                delete []tab.tab;
                cout<<"Podaj rozmiar tablicy: ";
                cin>>i;
                tab.wypelnij_tab(i);
                break;
            case 'o':
                o=true;
                break;
            case 'p':
                t=true;
                cout<<"Podaj w procentach, ile elementow tablicy ma byc posortowane"<<endl;
                cin>>p;
                break;
                 case 'e':
                     exit(EXIT_FAILURE);
        }
        plik.close();
        cout<<"\nZapisano \n\n";
    }
}
