#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class icicles: public sf::Drawable, sf::Transformable
{
public:
    icicles(void);
    ~icicles(void);

    void dodaj(sf::Vector2f poz, float rot);
    void usun(int i);

    void aktualizuj();

    sf::ConvexShape getShape(int i);

    int size();

private:
    sf::Texture tekstura;

    float predkosc = 6.0f;

    struct icicle
    {
        sf::ConvexShape boxKolizyjny;
        sf::Sprite sprajt;
        sf::Clock zegarAnimacji;
        int klatka;
        sf::Vector2f speed;
    };

    std::vector<icicle> m_icicles;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
