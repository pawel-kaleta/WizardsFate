#pragma once

#include<SFML\Graphics.hpp>
#include<vector>

class fireBalls: public sf::Drawable, sf::Transformable
{
public:
    fireBalls(void);
    ~fireBalls(void);

    void dodaj(sf::Vector2f pos, float rot);
    void usun(int i);

    void aktualizuj();

    sf::ConvexShape getShape(int i);
    int size();

private:

    sf::Texture tekstura;


    float predkosc = 4.0f;

    struct fireBall
    {
        sf::ConvexShape boxKolizyjny;
        sf::Sprite sprajt;
        sf::Clock zegar_animacji;
        int klatka;
        sf::Vector2f speed;
    };

    std::vector <fireBall> m_fireBalls;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
