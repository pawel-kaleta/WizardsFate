#include "fireBall.h"
#include <windows.h>
#include <math.h>
#include <iostream>

#define M_PI 3.14159265358979323846

fireBalls::fireBalls()
{
    if(!tekstura.loadFromFile("data/images/attacks/fireball_0.png"))
    {
        MessageBox(NULL, "Texture of fire ball not found!", "ERROR", NULL);
        return;
    }
}

fireBalls::~fireBalls()
{

}

void fireBalls::dodaj(sf::Vector2f pos, float rot)
{

    fireBall fB;

    fB.klatka = 0;

    fB.sprajt.setTexture(tekstura);
    fB.sprajt.setTextureRect(sf::IntRect(0,0,64,64));
    fB.sprajt.setOrigin(32,32);
    fB.sprajt.setRotation(rot+90);

    fB.zegar_animacji.restart();

    fB.sprajt.setPosition(pos);

    fB.speed.x = sin((rot * M_PI) / 180.0f);
    fB.speed.y = -cos((rot * M_PI) / 180.0f);

    fB.boxKolizyjny.setPosition(pos + fB.speed*22.0f);

    fB.speed *= predkosc;

    int punktyKolizyjne = 32;
    fB.boxKolizyjny.setPointCount(punktyKolizyjne);
    float kat = (360*M_PI)/(punktyKolizyjne*180.0f);
    for(int i=0; i<punktyKolizyjne; i++)
        fB.boxKolizyjny.setPoint(i, sf::Vector2f((sin(i*kat)*5),-cos(i*kat)*5));
    fB.boxKolizyjny.setOrigin(0,0);

    m_fireBalls.push_back(fB);
}

void fireBalls::usun(int i)
{
    for(int j=i; j<m_fireBalls.size()-1; j++)
        std::swap(m_fireBalls[j],m_fireBalls[j+1]);

    m_fireBalls.resize(m_fireBalls.size()-1);
}

void fireBalls::aktualizuj()
{
    for(int i=0; i<m_fireBalls.size(); i++)
    {
        if(m_fireBalls[i].zegar_animacji.getElapsedTime() > sf::seconds(0.07f))
        {
            if(m_fireBalls[i].klatka < 7)
                m_fireBalls[i].klatka++;
            else
                m_fireBalls[i].klatka = 0;
            m_fireBalls[i].sprajt.setTextureRect(sf::IntRect(m_fireBalls[i].klatka*64,0,64,64));
            m_fireBalls[i].zegar_animacji.restart();
        }

        m_fireBalls[i].boxKolizyjny.move(m_fireBalls[i].speed);
        m_fireBalls[i].sprajt.move(m_fireBalls[i].speed);
    }
}

void fireBalls::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

    states.transform *= getTransform();

    for(int i=0; i<m_fireBalls.size(); i++)
    {
        target.draw(m_fireBalls[i].sprajt,states);
    }
}

sf::ConvexShape fireBalls::getShape(int i)
{
    return m_fireBalls[i].boxKolizyjny;
}

int fireBalls::size()
{
    return m_fireBalls.size();
}
