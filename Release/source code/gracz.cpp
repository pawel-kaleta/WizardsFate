#include "gracz.h"
#include <Windows.h>
#include <math.h>
#include <iostream>

#define M_PI 3.14159265358979323846

gracz::gracz(void)
{
    if(!tekstura.loadFromFile("data/images/player/player-move.png"))
    {
        MessageBox(NULL, "Sprite of player not found!" , "ERROR", NULL);
        return;
    }

    zycie = 50;
    mana = 50;
    XP = 0;
    poziom = 1;
    typAtaku = 1;
    szybkostrzelnosc = 1;

    sprajt.setTexture(tekstura);
    sprajt.setTextureRect(sf::IntRect(0,0,64,64));

    sprajt.setOrigin(32,32);

    stanGracza = STOJ;

    klatka = 0;
    predkosc = 2.0f;

    sprajt.setPosition(1280/2,720/3);
    zegar_animacji.restart();
    czasZranienia.restart();
    odnowienieMany.restart();
    czasOdAtaku.restart();

    int punktyKolizyjne = 128;
    boxKolizyjny.setPointCount(punktyKolizyjne);
    float kat = (360*M_PI)/(punktyKolizyjne*180.0f);

    for(int i=0; i<punktyKolizyjne; i++)
        boxKolizyjny.setPoint(i, sf::Vector2f(sin(i*kat)*20,-cos(i*kat)*20));

    boxKolizyjny.setOrigin(0,0);
}

gracz::~gracz(void)
{

}

void gracz::preaktualizacja(sf::Vector2f pozycjaMyszy)
{
    sf::Vector2f cel = pozycjaMyszy - sprajt.getPosition();
    float rot = atan2(cel.y,cel.x);
    rot = rot * 180.f/M_PI;
    rot += 90;

    boxKolizyjny.setRotation(rot);
    if(stanGracza == IDZ)
        boxKolizyjny.move(getSpeed());

    if(odnowienieMany.getElapsedTime() > sf::seconds(0.25) && mana<50+(poziom-1)*4)
    {
        mana += 1+(poziom-1)/4;
        odnowienieMany.restart();
    }
    if(XP >= 10+((poziom-1)*(poziom-1)))
    {
        poziom++;
        XP = 0;
        zycie += 4;
        mana += 4;
        szybkostrzelnosc -= 0.1/poziom;
    }
}

void gracz::aktualizacja(sf::Vector2f pozycjaMyszy, bool czyKolizja)
{
     if(!czyKolizja)
     {
        sprajt.setRotation(boxKolizyjny.getRotation());

        if((sprajt.getPosition().x - pozycjaMyszy.x)*(sprajt.getPosition().x - pozycjaMyszy.x) + (sprajt.getPosition().y - pozycjaMyszy.y)*(sprajt.getPosition().y - pozycjaMyszy.y) > 800)
        {
            if(zegar_animacji.getElapsedTime() > sf::seconds(0.15f))
            {
                if(stanGracza == STOJ)
                    return;
                if(klatka < 7)
                    klatka++;
                else
                    klatka = 0;

                sprajt.setTextureRect(sf::IntRect(klatka*64,0,64,64));
                zegar_animacji.restart();
            }

            sprajt.move(getSpeed());
        }
    }

    boxKolizyjny.setPosition(sprajt.getPosition());
    sprajt.setRotation(boxKolizyjny.getRotation());
}

void gracz::stop()
{
    stanGracza = STOJ;
    klatka = 0;
}

void gracz::idz()
{
    stanGracza = IDZ;
}

void gracz::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(sprajt);
}

sf::Vector2f gracz::getPosition()
{
    return sprajt.getPosition();
}

gracz::statusGracza gracz::getStatus()
{
    return stanGracza;
}

sf::Vector2f gracz::getSpeed()
{
    float rotacja = sprajt.getRotation();
    float vx = sin((rotacja * M_PI) / 180.0f);
    float vy = -cos((rotacja * M_PI) / 180.0f);

    return sf::Vector2f(vx*predkosc, vy*predkosc);
}

sf::ConvexShape gracz::getShape()
{
    return boxKolizyjny;
}

float gracz::getRotation()
{
    return boxKolizyjny.getRotation();
}

void gracz::ran()
{
    if(czasZranienia.getElapsedTime() > sf::seconds(0.05))
    {
        zycie--;
        czasZranienia.restart();
    }
}
