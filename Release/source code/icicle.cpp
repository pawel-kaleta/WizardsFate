#include "icicle.h"
#include <windows.h>
#include <math.h>

#define M_PI 3.14159265358979323846

icicles::icicles(void)
{
    if(!tekstura.loadFromFile("data/images/attacks/icicle_0.png"))
    {
        MessageBox(NULL, "Texture of icicle attack not found", "ERROR", NULL);
    }
}

icicles::~icicles(void)
{

}

void icicles::dodaj(sf::Vector2f poz, float rot)
{
    icicle ic;

    ic.klatka = 0;

    ic.sprajt.setTexture(tekstura);
    ic.sprajt.setTextureRect(sf::IntRect(0,0,64,64));
    ic.sprajt.setOrigin(32,32);
    ic.sprajt.setRotation(rot + 90);

    ic.zegarAnimacji.restart();

    ic.sprajt.setPosition(poz);

    ic.speed.x = sin((rot * M_PI) / 180.0f) * predkosc;
    ic.speed.y = -cos((rot * M_PI) / 180.0f) * predkosc;

    int punktyKolizyjne = 8;
    ic.boxKolizyjny.setPointCount(punktyKolizyjne);
    float kat = (360*M_PI)/(punktyKolizyjne*180.0f);
    for(int i=0; i<punktyKolizyjne; i++)
        ic.boxKolizyjny.setPoint(i, sf::Vector2f((sin(i*kat)*2),-cos(i*kat)*2));
    ic.boxKolizyjny.setOrigin(0,0);
    ic.boxKolizyjny.setPosition(poz + ic.speed * 2.0f);

    m_icicles.push_back(ic);
}

void icicles::usun(int i)
{
    for(int j=i; j<m_icicles.size()-1; j++)
        std::swap(m_icicles[j],m_icicles[j+1]);

    m_icicles.resize(m_icicles.size()-1);
}

void icicles::aktualizuj()
{
    for(int i=0; i<m_icicles.size(); i++)
    {
        if(m_icicles[i].zegarAnimacji.getElapsedTime() > sf::seconds(0.07f))
        {
            if(m_icicles[i].klatka < 7)
                m_icicles[i].klatka++;
            else
                m_icicles[i].klatka = 0;
            m_icicles[i].sprajt.setTextureRect(sf::IntRect(m_icicles[i].klatka*64,0,64,64));
            m_icicles[i].zegarAnimacji.restart();
        }
        m_icicles[i].sprajt.move(m_icicles[i].speed);
        m_icicles[i].boxKolizyjny.move(m_icicles[i].speed);
    }
}

void icicles::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for(int i=0; i<m_icicles.size(); i++)
    {
        target.draw(m_icicles[i].sprajt, states);
    }
}

sf::ConvexShape icicles::getShape(int i)
{
    return m_icicles[i].boxKolizyjny;
}

int icicles::size()
{
    return m_icicles.size();
}

