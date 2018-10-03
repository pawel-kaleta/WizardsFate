#pragma once

#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "silnik.h"
#include "opcje.h"

using namespace std;


class gra
{
public:
    gra(void);
    ~gra(void);

    void startGry();

protected:
    enum statusGry {MENU, GRA, KONIEC_GRY, KONIEC, EDYTOR_MAP};
    statusGry stanGry;

private:
    sf::Font czcionka;

    opcje Opcje;
    void menu();
    void single();
    void edytormap();
    void zmienPole(silnik &silnikGry, int x, int y, bool dal);
};
