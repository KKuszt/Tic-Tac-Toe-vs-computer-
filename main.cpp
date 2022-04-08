#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
#define WIN 1
#define DEF -1
#define NIC 0
int wynik_ruch_kompa;
int rek1;

int t; //trudnosc

void wczytaj_s(int wygrana)
{   float liczba_gier_p[5];
    float wygrane_x_p[5];
    int liczba_gier_suma;
    fstream dane;
    dane.open("dane.txt",ios::in);
    if(!dane.good())
    {
        cout<<"NIE UDALO SIE WCZYTAC STATYSTYK[1]"<<endl;
    }
     fstream dane1;
    dane1.open("dane1.txt",ios::in);
    if(!dane1.good())
    {
        cout<<"NIE UDALO SIE WCZYTAC STATYSTYK[2]"<<endl;
    }

    for(int i=0;i<5;i++)
    {   dane>>wygrane_x_p[i];
        if(i==t-1&&wygrana==1) wygrane_x_p[i]++;
    }

    dane1>>liczba_gier_suma;
    liczba_gier_suma++;

     for(int i=0;i<5;i++)
    {   dane1>>liczba_gier_p[i];
        if(i==t-1) liczba_gier_p[i]++;
    }
    dane.close();
    dane1.close();

    cout<<"LICZBA GIER: "<<liczba_gier_suma<<endl;
    cout<<"POZIOM;  % WYGRANYCH DLA X:"<<endl;
    for(int i=0;i<5;i++)
    {
    cout<<"   "<<i+1<<"          ";
    if(liczba_gier_p[i]==0) cout<<" 0"<<endl;
    else cout<<" "<<wygrane_x_p[i]/liczba_gier_p[i]*100<<endl;
    }

    dane.open("dane.txt",ios::out);
    for(int i=0;i<5;i++)
    {   dane<<wygrane_x_p[i]<<endl;
    }
    dane.close();

    dane1.open("dane1.txt",ios::out);
    dane1<<liczba_gier_suma<<endl;
    for(int i=0;i<5;i++)
    {   dane1<<liczba_gier_p[i]<<endl;
    }
    dane1.close();

}
void zmien_kolor(char a)
{   HANDLE u;
    u = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute( u, a);
}

bool poziom_trudnosci()
{
    cout<<"PODAJ POZIOM TRUDNOSCI (1-5):"<<endl;
    cin>>t;
   switch(t)
{
    case 1:
        rek1=1;
        return true;
    break;
    case 2:
        rek1=3;
        return true;
    break;
    case 3:
        rek1=5;
        return true;
    break;
    case 4:
        rek1=7;
        return true;
    case 5:
        rek1=9;
        return true;
    default:
        cout<<">POZA ZAKRESEM<"<<endl;
        return false;
    break;
}
}
void wyczysc_plan(char plansza[])
{
    for(int i=0;i<9;i++)
    {
        plansza[i]=' ';
    }
}
void stan_planszy(char plansza[])
{
  cout<<endl<<"  "<<plansza[0]<<" | "<<plansza[1]<<" | "<<plansza[2]<<"  "<<endl;
  cout<<" ---+---+---"<<endl;
  cout<<"  "<<plansza[3]<<" | "<<plansza[4]<<" | "<<plansza[5]<<"  "<<endl;
  cout<<" ---+---+---"<<endl;
  cout<<"  "<<plansza[6]<<" | "<<plansza[7]<<" | "<<plansza[8]<<"  "<<endl;
}
int wynik_gry(char plansza[])
{   //X
    if(plansza[0]=='x' && plansza[1]=='x' && plansza[2]=='x')
    {
        return WIN;
    }
    if(plansza[3]=='x' && plansza[4]=='x' && plansza[5]=='x')
    {
        return WIN;
    }
    if(plansza[6]=='x' && plansza[7]=='x' && plansza[8]=='x') //poziomo
    {
        return WIN;
    }
    if(plansza[0]=='x' && plansza[3]=='x' && plansza[6]=='x')
    {
        return WIN;
    }
    if(plansza[1]=='x' && plansza[4]=='x' && plansza[7]=='x')
    {
        return WIN;
    }
    if(plansza[2]=='x' && plansza[5]=='x' && plansza[8]=='x')//pionowo
    {
        return WIN;
    }
    if(plansza[0]=='x' && plansza[4]=='x' && plansza[8]=='x')
    {
        return WIN;
    }
    if(plansza[2]=='x' && plansza[4]=='x' && plansza[6]=='x')//przekatne
    {
        return WIN;
    }

   if(plansza[0]=='x' && plansza[1]=='x' && plansza[2]=='x')
    {
        return WIN;
    }
    //O
    if(plansza[3]=='o' && plansza[4]=='o' && plansza[5]=='o')
    {
        return DEF;
    }
    if(plansza[6]=='o' && plansza[7]=='o' && plansza[8]=='o') //poziomo
    {
        return DEF;
    }
    if(plansza[0]=='o' && plansza[3]=='o' && plansza[6]=='o')
    {
        return DEF;
    }
    if(plansza[1]=='o' && plansza[4]=='o' && plansza[7]=='o')
    {
        return DEF;
    }
    if(plansza[2]=='o' && plansza[5]=='o' && plansza[8]=='o')//pionowo
    {
        return DEF;
    }
    if(plansza[0]=='o' && plansza[4]=='o' && plansza[8]=='o')
    {
        return DEF;
    }
    if(plansza[2]=='o' && plansza[4]=='o' && plansza[6]=='o')//przekatne
    {
        return DEF;
    }
    return NIC;
}

bool wpisz_o(char plansza[])
{   int a;
    cout<<"PODAJ RUCH (1-9):"<<endl;
    cin>>a;
    if((a>0 && a<10)&&plansza[a-1]==' ')
    {
        plansza[a-1]='o';
        return 1;
    }
    else cout<<">BLEDNY RUCH<"<<endl;
    return 0;
}

int ruch_komp(char plansza[], int rek)
{
    int ruch=0 ;
    int najlepszy_ruch;
    int zajete_pola=0;
    if (rek == 0 || wynik_gry(plansza)==WIN || wynik_gry(plansza)==DEF)
    {
        return wynik_gry(plansza);
    }

    if(rek%2==1) //potencjalne ruchy komputera
    {
        najlepszy_ruch=-2;

            for(int i=0;i<9;i++)
            {
                if(plansza[i]==' ')
                {
                    plansza[i]='x';
                    ruch = ruch_komp(plansza, rek-1);
                    if(ruch>najlepszy_ruch)
                    {
                        najlepszy_ruch=ruch;
                        if(rek == rek1)
                        {
                            wynik_ruch_kompa = i; //koncowy wynik

                        }
                    }
                    plansza[i]=' ';
                }
                else
                {
                    zajete_pola++;
                }
            }

    }
    else
    {
        najlepszy_ruch=2;

            for(int i=0;i<9;i++)
            {
                if(plansza[i]==' ')
                {
                    plansza[i]='o';
                    ruch = ruch_komp(plansza, rek-1);
                    if(ruch<najlepszy_ruch)
                    {
                        najlepszy_ruch=ruch;
                    }
                    plansza[i]=' ';
                }
                else
                {
                    zajete_pola++;
                }
            }
            if(zajete_pola==9)
    {
        return wynik_gry(plansza);
    }
    return najlepszy_ruch;

    }

    if(zajete_pola==9)
    {
        return wynik_gry(plansza);
    }
    return najlepszy_ruch;
}
int main()
{   zmien_kolor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    int i=0;
    char plansza[9];
    wyczysc_plan(plansza);
    while(!poziom_trudnosci());
while(wynik_gry(plansza)==NIC&&i<=9)
{   ruch_komp(plansza,rek1);
    plansza[wynik_ruch_kompa]='x';
    i++;
    stan_planszy(plansza);
    if(wynik_gry(plansza)!=NIC||i==9) break;
    while(!wpisz_o(plansza));
    i++;
}

switch(wynik_gry(plansza))
{
    case WIN:
    zmien_kolor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout<<"----------------------------------"<<endl<<"           X WYGRYWA!"<<endl<<"----------------------------------"<<endl;
    break;
    case DEF:
    zmien_kolor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout<<"----------------------------------"<<endl<<"           O WYGRYWA"<<endl<<"----------------------------------"<<endl;
    break;
    case NIC:
        zmien_kolor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout<<"----------------------------------"<<endl<<"           REMIS"<<endl<<"----------------------------------"<<endl;
    break;
}
wczytaj_s(wynik_gry(plansza));
   return 0;
}
