#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

class potwory: public sf::Drawable, sf::Transformable
{
public:
    potwory(void);
    ~potwory(void);

    sf::ConvexShape getShape(int i);

    sf::Clock zegar_generacji;

    void dodaj();
    void usun(int i);
    void atak(int i);

    void preaktualizacja(int i, bool czyWidzi, sf::Vector2f pozycjaGracza, bool czyAtak);
    void aktualizacja(int i, bool czyOdbicie, bool czyAtak);
    int prom();

    int size();

private:
    sf::Texture tekstura;
    sf::Texture teksturaAtak;

    float predkosc = 1.0f;

    struct potwor
    {
        sf::Sprite sprajt;
        sf::Vector2f speed;
        float dlugoscSpeed;
        sf::Clock zegar_animacji;
        int klatka;
        sf::ConvexShape boxKolizyjny;
    };

    std::vector <potwor> m_potwory;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
