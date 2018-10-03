#include "potwory2.h"
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <ctime>

#define M_PI 3.14159265358979323846

potwory2::potwory2(void)
{
    if(!teksturaRuch.loadFromFile("data/images/enemies/scorpion/scorpion-move.png") || !teksturaAtak.loadFromFile("data/images/enemies/scorpion/scorpion-attack.png"))
        MessageBox(NULL, "Textures of monster Scorpion not found", "ERROR", NULL);
    if(!teksturaRuchRanny.loadFromFile("data/images/enemies/scorpion/scorpion-move-wounded.png") || !teksturaAtakRanny.loadFromFile("data/images/enemies/scorpion/scorpion-attack-wounded.png"))
        MessageBox(NULL, "Textures of monster wounded Scorpion not found", "ERROR", NULL);
}

potwory2::~potwory2(void)
{

}

void potwory2::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for(int i=0; i<m_potwory2.size(); i++)
    {
        target.draw(m_potwory2[i].sprajt);
    }
}

sf::ConvexShape potwory2::getShape(int i)
{
    return m_potwory2[i].boxKolizyjny;
}

void potwory2::dodaj()
{

    potwor pot;

    pot.zycie = 2;

    pot.sprajt.setTexture(teksturaRuch);
    pot.sprajt.setTextureRect(sf::IntRect(0,0,64,64));
    pot.sprajt.setOrigin(32,32);
    pot.klatka = 0;
    pot.sprajt.setRotation(rand()%360);
    pot.zegar_animacji.restart();

    pot.speed.x = sin((pot.sprajt.getRotation() * M_PI) / 180.0f) * predkosc;
    pot.speed.y = -cos((pot.sprajt.getRotation() * M_PI) / 180.0f) * predkosc;

    pot.dlugoscSpeed = predkosc;

    pot.sprajt.setPosition((rand()%1280),(rand()%720));

    int punktyKolizyjne = 128;
    pot.boxKolizyjny.setPointCount(punktyKolizyjne);
    float kat = (360*M_PI)/(punktyKolizyjne*180.0f);
    for(int i=0; i<punktyKolizyjne; i++)
        pot.boxKolizyjny.setPoint(i, sf::Vector2f((sin(i*kat)*23),-cos(i*kat)*23));
    pot.boxKolizyjny.setOrigin(0,0);
    pot.boxKolizyjny.setPosition(pot.sprajt.getPosition());

    m_potwory2.push_back(pot);

    zegar_generacji.restart();
}

void potwory2::preaktualizacja(int i, bool czyWidzi, sf::Vector2f pozycjaGracza, bool czyAtak)
{
    if(czyWidzi)
    {
        sf::Vector2f cel = pozycjaGracza - m_potwory2[i].boxKolizyjny.getPosition();
        float rot = atan2(cel.x,-cel.y) * 180.0f / M_PI;

        m_potwory2[i].boxKolizyjny.setRotation(rot);
        m_potwory2[i].sprajt.setRotation(rot);

        m_potwory2[i].speed.x = sin(rot*M_PI/180.0f)*m_potwory2[i].dlugoscSpeed;
        m_potwory2[i].speed.y = -cos(rot*M_PI/180.0f)*m_potwory2[i].dlugoscSpeed;
    }

    if(!czyAtak)
        m_potwory2[i].boxKolizyjny.move(m_potwory2[i].speed);
}

void potwory2::aktualizacja(int i, bool czyOdbicie, bool czyAtak)
{
    if(m_potwory2[i].zegar_animacji.getElapsedTime() > sf::seconds(0.09))
    {
        if(czyAtak)
        {
            if(m_potwory2[i].zycie == 2)
                m_potwory2[i].sprajt.setTexture(teksturaAtak);
            else
                m_potwory2[i].sprajt.setTexture(teksturaAtakRanny);
        }
        else
        {
            if(m_potwory2[i].zycie == 2)
                m_potwory2[i].sprajt.setTexture(teksturaRuch);
            else
                m_potwory2[i].sprajt.setTexture(teksturaRuchRanny);
        }

        if(czyAtak)
        {
            if(m_potwory2[i].klatka>6)
                m_potwory2[i].klatka=0;
            else
                m_potwory2[i].klatka++;
        }
        else
        {
            if(m_potwory2[i].klatka>2)
                m_potwory2[i].klatka = 0;
            else
                m_potwory2[i].klatka++;
        }

        m_potwory2[i].zegar_animacji.restart();
        m_potwory2[i].sprajt.setTextureRect(sf::IntRect(64*m_potwory2[i].klatka,0,64,64));
    }

    if(czyOdbicie)
    {
        m_potwory2[i].sprajt.move(-m_potwory2[i].speed);

        if(rand()%2)
            m_potwory2[i].speed.x *= -1;
        else
            m_potwory2[i].speed.y *= -1;

        float rot = atan2(m_potwory2[i].speed.x,-m_potwory2[i].speed.y);
        rot = rot*180.0f/M_PI;


        m_potwory2[i].sprajt.setRotation(rot);
        m_potwory2[i].boxKolizyjny.setRotation(m_potwory2[i].sprajt.getRotation());

        m_potwory2[i].klatka = 0;
        m_potwory2[i].sprajt.setTextureRect(sf::IntRect(0,0,64,64));

        m_potwory2[i].boxKolizyjny.setPosition(m_potwory2[i].sprajt.getPosition());
    }
    else
        m_potwory2[i].sprajt.setPosition(m_potwory2[i].boxKolizyjny.getPosition());
}

int potwory2::size()
{
    return m_potwory2.size();
}

void potwory2::usun(int i)
{
    for(int j=i; j<m_potwory2.size()-1; j++)
        std::swap(m_potwory2[j], m_potwory2[j+1]);

    m_potwory2.resize(m_potwory2.size()-1);
}

void potwory2::atak(int i)
{
    m_potwory2[i].klatka = 0;
}

void potwory2::ran(int i)
{
    m_potwory2[i].zycie -= 1;

    if(m_potwory2[i].zycie == 0)
        usun(i);
}
