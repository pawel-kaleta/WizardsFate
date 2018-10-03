#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class potwory2: public sf::Drawable, sf::Transformable
{
public:
    potwory2(void);
    ~potwory2(void);

    sf::ConvexShape getShape(int i);

    sf::Clock zegar_generacji;

    void dodaj();
    void usun(int i);
    void atak(int i);
    void ran(int i);

    void preaktualizacja(int i, bool czyWidzi, sf::Vector2f pozycjaGracza, bool czyAtak);
    void aktualizacja(int i, bool czyOdbicie, bool czyAtak);
    int prom();

    int size();
private:
    sf::Texture teksturaRuch;
    sf::Texture teksturaRuchRanny;
    sf::Texture teksturaAtak;
    sf::Texture teksturaAtakRanny;

    float predkosc = 1.5f;

    struct potwor
    {
        sf::Sprite sprajt;
        sf::Vector2f speed;
        float dlugoscSpeed;
        sf::Clock zegar_animacji;
        int klatka;
        sf::ConvexShape boxKolizyjny;
        int zycie;
    };

    std::vector <potwor> m_potwory2;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
