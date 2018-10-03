#include "potwory.h"
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include <ctime>

#define M_PI 3.14159265358979323846

potwory::potwory(void)
{
    if(!tekstura.loadFromFile("data/images/enemies/gargant/gargant-move.png") || !teksturaAtak.loadFromFile("data/images/enemies/gargant/gargant-attack.png"))
        MessageBox(NULL, "Texture of monster Gargant not found", "ERROR", NULL);
}

potwory::~potwory(void)
{

}

void potwory::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for(int i=0; i<m_potwory.size(); i++)
    {
        target.draw(m_potwory[i].sprajt);
    }
}

sf::ConvexShape potwory::getShape(int i)
{
    return m_potwory[i].boxKolizyjny;
}

void potwory::dodaj()
{

    potwor pot;

    pot.sprajt.setTexture(tekstura);
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

    m_potwory.push_back(pot);

    zegar_generacji.restart();
}

void potwory::preaktualizacja(int i, bool czyWidzi, sf::Vector2f pozycjaGracza, bool czyAtak)
{
    if(czyWidzi)
    {
        sf::Vector2f cel = pozycjaGracza - m_potwory[i].boxKolizyjny.getPosition();
        float rot = atan2(cel.x,-cel.y) * 180.0f / M_PI;

        m_potwory[i].boxKolizyjny.setRotation(rot);
        m_potwory[i].sprajt.setRotation(rot);

        m_potwory[i].speed.x = sin(rot*M_PI/180.0f)*m_potwory[i].dlugoscSpeed;
        m_potwory[i].speed.y = -cos(rot*M_PI/180.0f)*m_potwory[i].dlugoscSpeed;
    }

    if(!czyAtak)
        m_potwory[i].boxKolizyjny.move(m_potwory[i].speed);
}

void potwory::aktualizacja(int i, bool czyOdbicie, bool czyAtak)
{
    if(m_potwory[i].zegar_animacji.getElapsedTime() > sf::seconds(0.09))
    {
        if(czyAtak)
            m_potwory[i].sprajt.setTexture(teksturaAtak);
        else
            m_potwory[i].sprajt.setTexture(tekstura);

        if(m_potwory[i].klatka > 3)
        {
            if(czyAtak)
                m_potwory[i].klatka = 0;
            else
            {
                if(m_potwory[i].klatka > 6)
                    m_potwory[i].klatka = 0;
                else
                    m_potwory[i].klatka++;
            }
        }
        else
            m_potwory[i].klatka++;

        m_potwory[i].zegar_animacji.restart();
        m_potwory[i].sprajt.setTextureRect(sf::IntRect(64*m_potwory[i].klatka,0,64,64));
    }

    if(czyOdbicie)
    {
        m_potwory[i].sprajt.move(-m_potwory[i].speed);

        if(rand()%2)
            m_potwory[i].speed.x *= -1;
        else
            m_potwory[i].speed.y *= -1;

        float rot = atan2(m_potwory[i].speed.x,-m_potwory[i].speed.y);
        rot = rot*180.0f/M_PI;


        m_potwory[i].sprajt.setRotation(rot);
        m_potwory[i].boxKolizyjny.setRotation(m_potwory[i].sprajt.getRotation());

        m_potwory[i].klatka = 0;
        m_potwory[i].sprajt.setTextureRect(sf::IntRect(0,0,64,64));

        m_potwory[i].boxKolizyjny.setPosition(m_potwory[i].sprajt.getPosition());
    }
    else
        m_potwory[i].sprajt.setPosition(m_potwory[i].boxKolizyjny.getPosition());
}

int potwory::size()
{
    return m_potwory.size();
}

void potwory::usun(int i)
{
    for(int j=i; j<m_potwory.size()-1; j++)
        std::swap(m_potwory[j], m_potwory[j+1]);

    m_potwory.resize(m_potwory.size()-1);
}

void potwory::atak(int i)
{
    m_potwory[i].klatka = 0;
}
