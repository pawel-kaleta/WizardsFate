#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

class gracz: public sf::Drawable, sf::Transformable
{
public:
    gracz(void);
    ~gracz(void);

    enum statusGracza {IDZ, STOJ};

    sf::Vector2f getPosition();
    float getRotation();
    statusGracza getStatus();
    sf::Vector2f getSpeed();
    sf::ConvexShape getShape();
    sf::Vector2f getPointPosition(int i);

    void aktualizacja(sf::Vector2f pozycjaMyszy, bool czyKolizja);
    void preaktualizacja(sf::Vector2f pozycjaMyszy);

    void ran();

    sf::Clock czasZranienia;
    sf::Clock czasOdAtaku;


    int zycie;
    int mana;
    int XP;
    int poziom;
    int typAtaku;
    float szybkostrzelnosc;

    void stop();
    void idz();

private:
    sf::Sprite sprajt;
    sf::Texture tekstura;
    sf::Clock odnowienieMany;
    sf::ConvexShape boxKolizyjny;

    statusGracza stanGracza;

    float predkosc;
    size_t klatka;

    sf::Clock zegar_animacji;

    virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};
