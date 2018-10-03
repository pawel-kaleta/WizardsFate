#include <windows.h>
#include <iostream>
#include "oknoInformacji.h"
#include <string>
#include <fstream>
#include <sstream>

oknoInformacji::oknoInformacji(void)
{
    if(!teksturaMana.loadFromFile("data/images/bars/player_bars/BlueBar.png"))
        MessageBox(NULL, "Texture of mana bar not found", "ERROR", NULL);
    if(!teksturaZycie.loadFromFile("data/images/bars/player_bars/RedBar.png"))
        MessageBox(NULL, "Texture of health bar not found", "ERROR", NULL);
    if(!teksturaPusta.loadFromFile("data/images/bars/player_bars/EmptyBar.png"))
        MessageBox(NULL, "Texture of empty bar not found", "ERROR", NULL);
    if(!teksturaXP.loadFromFile("data/images/bars/player_bars/GreenBar.png"))
        MessageBox(NULL, "Texture of expirience bar not found", "ERROR", NULL);

    pasekZycia.setTexture(teksturaZycie);
    pasekZycia.setPosition(sf::Vector2f(75,5));

    pasekMany.setTexture(teksturaMana);
    pasekMany.setPosition(sf::Vector2f(75,36));

    pasekXP.setTexture(teksturaXP);
    pasekXP.setPosition(sf::Vector2f(75, 67));

    pustyPasekZycia.setTexture(teksturaPusta);
    pustyPasekZycia.setPosition(sf::Vector2f(75,5));

    pustyPasekMany.setTexture(teksturaPusta);
    pustyPasekMany.setPosition(sf::Vector2f(75,36));

    pustyPasekXP.setTexture(teksturaPusta);
    pustyPasekXP.setPosition(sf::Vector2f(75, 67));

    if(!czcionka.loadFromFile("data/mecha.ttf"))
        MessageBox(NULL, "Font not found.", "ERROR", NULL);

    level.setString("Tekst bez znaczenia");
    level.setFont(czcionka);
    level.setCharacterSize(25);
    level.setStyle(sf::Text::Bold);
    level.setPosition(sf::Vector2f(7, 5));

    if(!teksturaAtak1.loadFromFile("data/images/attacks/fireball_0.png"))
        MessageBox(NULL, "Texture of Fire Ball not found", "ERROR", NULL);
    if(!teksturaAtak2.loadFromFile("data/images/attacks/icicle_0.png"))
        MessageBox(NULL, "Texture of icicle attack not found", "ERROR", NULL);

    atak1.setTexture(teksturaAtak1);
    atak1.setTextureRect(sf::IntRect(0,0,64,64));
    atak1.setPosition(sf::Vector2f(5, 25));

    atak2.setTexture(teksturaAtak2);
    atak2.setTextureRect(sf::IntRect(0,0,64,64));
    atak2.setPosition(sf::Vector2f(5, 70));

    klatka = 0;
}

oknoInformacji::~oknoInformacji(void)
{

}

void oknoInformacji::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(level);
    target.draw(pustyPasekZycia);
    target.draw(pasekZycia);
    target.draw(pustyPasekMany);
    target.draw(pasekMany);
    target.draw(pustyPasekXP);
    target.draw(pasekXP);
    target.draw(atak1);
    target.draw(atak2);
}

void oknoInformacji::aktualizujPaskiPlayera(int zycie, int mana, int XP, int poziom, int typAtaku)
{
    int czescZycia = 206*zycie/(50+(poziom-1)*4);
    pasekZycia.setTextureRect(sf::IntRect(0,0,czescZycia,28));

    int czescMany = 206*mana/(50+(poziom-1)*4);
    pasekMany.setTextureRect(sf::IntRect(0,0,czescMany,28));

    int czescXP = (206*XP) / (10+((poziom-1)*(poziom-1)));
    pasekXP.setTextureRect(sf::IntRect(0,0,czescXP,28));

    std::ostringstream ss;
    ss << poziom;
    std::string pom = ss.str();
    std::string napis = "Lvl: " + pom;
    level.setString(napis);

    if(zegarAnimacji.getElapsedTime() > sf::seconds(0.07f))
    {
        if(klatka < 7)
            klatka++;
        else
            klatka = 0;

        switch(typAtaku)
        {
        case 1:
            atak1.setTextureRect(sf::IntRect(klatka*64,0,64,64));
            break;
        case 2:
            atak2.setTextureRect(sf::IntRect(klatka*64,0,64,64));
            break;
        }

        zegarAnimacji.restart();
    }
}
