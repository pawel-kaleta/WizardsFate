#pragma once

#include "gracz.h"
#include "poziom.h"
#include "fireBall.h"
#include "icicle.h"
#include "potwory.h"
#include "potwory2.h"
#include "oknoInformacji.h"
#include "opcje.h"


class silnik
{
public:
    silnik(opcje &Opcje);
    ~silnik(void);

    sf::Texture tekstura[168];
    sf::Sprite sprajt[24][40];
    poziom Poziom;
    sf::Clock fps;

    void startSilnika(sf::RenderWindow &okno, opcje &Opcje);
    void rysujKlatke(sf::RenderWindow &okno, opcje &Opcje);
    void rysujMape(sf::RenderWindow &okno, opcje &Opcje);

private:
    bool sprawdzKolizje(sf::ConvexShape ksztalt);
    bool sprawdzKolizje2(sf::Vector2f ksztalt1, sf::Vector2f ksztalt2, int i);
    bool sprawdzWidocznosc(sf::Vector2f pozycja1, sf::Vector2f pozycja2);
    bool sprawdzWidocznosc2(sf::Vector2f pozycja1, sf::Vector2f pozycja2);

    void wczytajMape(opcje &Opcje);
    void interaktywnosc(sf::RenderWindow &okno, sf::Event zdarzenie, bool &menu);
    void generujPotwory();
    void generujAtaki();
    void aktualizujPotwory();
    void niszczPotworyAtaki();


    gracz Gracz;
    fireBalls playerFireBalls;
    icicles playerIcicles;
    potwory Potwory;
    potwory2 Potwory2;

    oknoInformacji OknoInformacji;

    sf::Clock lsd;
    int kierunek;

    int kolory[poziom::height][poziom::width];
};
