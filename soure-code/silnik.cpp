#include "silnik.h"
#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <math.h>
#include <vector>
#include "gra.h"
#include "opcje.h"

#define M_PI 3.14159265358979323846

silnik::silnik(opcje &Opcje)
{
    wczytajMape(Opcje);
}


silnik::~silnik(void)
{

}


void silnik::wczytajMape(opcje &Opcje)
{
    int ileTekstur;
    if(Opcje.czyLSD)
    {
        ileTekstur=168;
    }
    else
    {
        ileTekstur=21;
    }
    for(int i=0; i<ileTekstur; i++)
    {
        int x = i/7;
        int y = i%7;
        x *= poziom::tile_width;
        y *= poziom::tile_height;
        x += i/7+1;
        y += i%7+1;
        if(!tekstura[i].loadFromFile("data/images/tekstury_map.png", sf::IntRect( y, x, Poziom.tile_width, Poziom.tile_height)))
        {
            MessageBox(NULL, "Textures of maps not found!" , "ERROR", NULL);
            return;
        }

    }

    if(!Poziom.wczytajZpliku("map.level", "map_sciany.level"))
    {
        MessageBox(NULL, "Map file not found!" , "ERROR", NULL);
        return;
    }

    for(int i=0; i<Poziom.height; i++)
    {
        for(int j=0; j<Poziom.width; j++)
        {
                sprajt[i][j].setPosition(j*Poziom.tile_width, i*Poziom.tile_height);

            if(Opcje.czyLSD)
            {
                if(i>=12) //dolna polowa
                {
                    if(j>=20) //prawa polowa
                        kolory[i][j] = 15-((i+j)%16)+4;
                    else // lewa polowa
                    {
                        if(i>=j)
                            kolory[i][j] = 15-((i-j)%16)+5 +8;
                        else
                            kolory[i][j] = ((j-i)%16)+4 +8;
                    }
                }
                else //gorna polowa
                {
                    if(j<20) //lewa polowa
                        kolory[i][j] = (i+j)%16+5;
                    else //prawa polowa
                    {
                        if(i>=j)
                            kolory[i][j] = 15-((i-j)%16)+2 +8;
                        else
                            kolory[i][j] = 15-((j-i)%16)+5 +8;
                    }
                }
                if(kolory[i][j]>15)
                    kolory[i][j]=kolory[i][j]%16;
            }
            else
                kolory[i][j]=0;
        }
    }
    kierunek = 1;
}


void silnik::startSilnika(sf::RenderWindow &okno, opcje &Opcje)
{
    bool menu = false;

    srand(time(0));

    fps.restart();
    lsd.restart();

    while(!menu)
    {
        sf::Event zdarzenie;
        sf::Vector2f pozycjaMyszy(sf::Mouse::getPosition(okno));

        interaktywnosc(okno, zdarzenie, menu);

        generujPotwory();
        generujAtaki();

        Gracz.preaktualizacja(pozycjaMyszy);
        aktualizujPotwory();
        Gracz.aktualizacja(pozycjaMyszy, sprawdzKolizje(Gracz.getShape()));

        playerFireBalls.aktualizuj();
        playerIcicles.aktualizuj();
        niszczPotworyAtaki();

        OknoInformacji.aktualizujPaskiPlayera(Gracz.zycie, Gracz.mana, Gracz.XP, Gracz.poziom, Gracz.typAtaku);

        okno.clear();
        rysujMape(okno, Opcje);
        rysujKlatke(okno, Opcje);

        okno.display();
        float FPS = sf::seconds(1.0f) / fps.getElapsedTime();

        while(FPS>60)
        {
            FPS = sf::seconds(1.0f) / fps.getElapsedTime();
        }
        fps.restart();

        if(Gracz.zycie <=0)
        {
            menu = true;
        }
    }
}


void silnik::interaktywnosc(sf::RenderWindow &okno, sf::Event zdarzenie, bool &menu)
{
    while(okno.pollEvent(zdarzenie))
    {
        if(zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Escape)
            menu = true;
        if(zdarzenie.type == sf::Event::KeyReleased && zdarzenie.key.code == sf::Keyboard::Space)
        {
            Gracz.typAtaku++;
            if(2 >= Gracz.poziom || Gracz.typAtaku > 2)
                Gracz.typAtaku = 1;
        }
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        Gracz.idz();
    else
        Gracz.stop();
}


void silnik::generujPotwory()
{
    if(Potwory.zegar_generacji.getElapsedTime() > sf::seconds(1) && Potwory.size()<5)
    {
        Potwory.dodaj();
        int nowyPot = Potwory.size()-1;
        if(sprawdzKolizje(Potwory.getShape(nowyPot)))
            Potwory.usun(nowyPot);
        else
            if(sprawdzKolizje2(Potwory.getShape(nowyPot).getPosition(), Gracz.getPosition(), 2))
                Potwory.usun(nowyPot);
    }
    if(Potwory2.zegar_generacji.getElapsedTime() > sf::seconds(1) && Potwory2.size()<2)
    {
        Potwory2.dodaj();
        Potwory2.zegar_generacji.restart();
        int nowyPot = Potwory2.size()-1;
        if(sprawdzKolizje(Potwory2.getShape(nowyPot)))
            Potwory2.usun(nowyPot);
        else
            if(sprawdzKolizje2(Potwory2.getShape(nowyPot).getPosition(), Gracz.getPosition(), 2))
                Potwory2.usun(nowyPot);
    }
}


void silnik::generujAtaki()
{
    if(Gracz.mana >= 8)
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && Gracz.czasOdAtaku.getElapsedTime() > sf::seconds(Gracz.szybkostrzelnosc))
        {
            if(Gracz.typAtaku==1)
            {
                playerFireBalls.dodaj(Gracz.getPosition(),Gracz.getRotation());
                Gracz.czasOdAtaku.restart();
                Gracz.mana -= 8;
            }
            else
            {
                if(playerIcicles.size()<5)
                {
                    if(Gracz.mana >= 10)
                    {
                        playerIcicles.dodaj(Gracz.getPosition(), Gracz.getRotation());
                        Gracz.czasOdAtaku.restart();
                        Gracz.mana -= 10;
                    }
                }
            }
        }
    }
}


void silnik::aktualizujPotwory()
{
    for(int i=0; i<Potwory.size(); i++)
    {
        bool czyWidzi = sprawdzWidocznosc(Potwory.getShape(i).getPosition(), Gracz.getPosition());
        bool czyAtak = sprawdzKolizje2(Gracz.getPosition(), Potwory.getShape(i).getPosition(), 2);
        Potwory.preaktualizacja(i, czyWidzi, Gracz.getPosition(), czyAtak);

        if(czyWidzi)
        {
            if(czyAtak)
                Gracz.ran();
            Potwory.aktualizacja(i, false, czyAtak);
        }
        else
            Potwory.aktualizacja(i, sprawdzKolizje(Potwory.getShape(i)), false);
    }

    for(int i=0; i<Potwory2.size(); i++)
    {
        bool czyWidzi = sprawdzWidocznosc(Potwory2.getShape(i).getPosition(), Gracz.getPosition());
        bool czyAtak = sprawdzKolizje2(Gracz.getPosition(), Potwory2.getShape(i).getPosition(), 2);
        Potwory2.preaktualizacja(i, czyWidzi, Gracz.getPosition(), czyAtak);

        if(czyWidzi)
        {
            if(czyAtak)
                Gracz.ran();
            Potwory2.aktualizacja(i, false, czyAtak);
        }
        else
            Potwory2.aktualizacja(i, sprawdzKolizje(Potwory2.getShape(i)), false);
    }
}


void silnik::niszczPotworyAtaki()
{
    for(int i=0; i<playerFireBalls.size(); i++)
    {
        if(sprawdzKolizje(playerFireBalls.getShape(i)))
            playerFireBalls.usun(i);
        else
        {
            for(int j=0; j<Potwory.size(); j++)
            {
                if(sprawdzKolizje2(playerFireBalls.getShape(i).getPosition(), Potwory.getShape(j).getPosition(), 1))
                {
                    playerFireBalls.usun(i);
                    Potwory.usun(j);
                    Gracz.XP += 2;
                }
            }
        }
    }

    for(int i=0; i<playerIcicles.size(); i++)
    {
        if(sprawdzKolizje(playerIcicles.getShape(i)))
            playerIcicles.usun(i);
        else
            for(int j=0; j<Potwory2.size(); j++)
                if(sprawdzKolizje2(playerIcicles.getShape(i).getPosition(), Potwory2.getShape(j).getPosition(), 1))
                {
                    playerIcicles.usun(i);
                    Potwory2.ran(j);
                    Gracz.XP += 3;
                }
    }
}


void silnik::rysujKlatke(sf::RenderWindow &okno, opcje &Opcje)
{
    okno.draw(playerFireBalls);
    okno.draw(playerIcicles);
    okno.draw(Gracz);
    okno.draw(Potwory);
    okno.draw(Potwory2);
    okno.draw(OknoInformacji);
}

void silnik::rysujMape(sf::RenderWindow &okno, opcje &Opcje)
{
    bool reFreshTiles = 0;
    if( Opcje.czyLSD && (lsd.getElapsedTime()>sf::seconds(0.15)) )
    {
        reFreshTiles = 1;
        lsd.restart();
        if(rand()%100 > 95)
            kierunek =-kierunek;
    }
    for(int i=0; i<Poziom.height; i++)
    {
        for(int j=0; j<Poziom.width; j++)
        {
            if(reFreshTiles)
            {
                kolory[i][j] = kolory[i][j]-kierunek;

                if(kolory[i][j]>15)
                    kolory[i][j]=0;
                else
                    if(kolory[i][j]<0)
                        kolory[i][j] = 15;
            }

            sprajt[i][j].setTexture(tekstura[Poziom.level[i][j].typPola + (21*(kolory[i][j]/2))]);

            okno.draw(sprajt[i][j]);
        }
    }
}
void rysujMape(sf::RenderWindow &okno, opcje &Opcje);
