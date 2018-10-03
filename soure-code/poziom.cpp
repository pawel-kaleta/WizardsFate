#include "poziom.h"
#include <iostream>
#include <Windows.h>

using namespace std;

poziom::poziom(void)
{

}

poziom::poziom(string nazwaPliku, string nazwaPlikuScian)
{
    wczytajZpliku(nazwaPliku, nazwaPlikuScian);
}

poziom::~poziom(void)
{

}

bool poziom::wczytajZpliku(string nazwaPliku, string nazwaPlikuScian)
{
    fstream plik;
    fstream plik2;
    string s_nazwa = "data/levels/" + nazwaPliku;
    string s_nazwa2 = "data/levels/" + nazwaPlikuScian;
    const char * c_nazwa2 = s_nazwa2.c_str();
    const char * c_nazwa = s_nazwa.c_str();

    plik.open(c_nazwa, ios::in);
    plik2.open(c_nazwa2, ios::in);

    if(!plik.is_open())
    {
        s_nazwa = "Level file " + nazwaPliku + " not found";
        c_nazwa = s_nazwa.c_str();
        MessageBox(NULL, c_nazwa, "ERROR", NULL);
        return 0;
    }
    else
    {
        if(!plik2.is_open())
        {
            s_nazwa = "Level file " + nazwaPlikuScian + " not found";
            c_nazwa = s_nazwa.c_str();
            MessageBox(NULL, c_nazwa, "ERROR", NULL);
            return 0;
        }
        else
        {
            for(int y=0; y<height; y++)
            {
                for(int x=0; x<width; x++)
                {
                    int typ;
                    plik >> typ;
                    level[y][x].typPola = typ-1;
                    plik2 >> level[y][x].czySciana;
                }
            }
        }
    }

    plik.close();
    plik2.close();

    return 1;
}
