#pragma once

#include <SFML/Graphics.hpp>

class oknoInformacji: public sf::Drawable, sf::Transformable
{
public:
    oknoInformacji(void);
    ~oknoInformacji(void);

    void aktualizujPaskiPlayera(int zycie, int mana, int XP, int poziom, int typAtaku);

private:
    sf::RectangleShape tlo;
    sf::Sprite pasekZycia;
    sf::Sprite pasekMany;
    sf::Sprite pasekXP;

    sf::Sprite pustyPasekXP;
    sf::Sprite pustyPasekMany;
    sf::Sprite pustyPasekZycia;

    sf::Texture teksturaPusta;
    sf::Texture teksturaZycie;
    sf::Texture teksturaMana;
    sf::Texture teksturaXP;

    sf::Font czcionka;
    sf::Text level;

    sf::Sprite atak1;
    sf::Sprite atak2;

    sf::Texture teksturaAtak1;
    sf::Texture teksturaAtak2;

    int klatka;
    sf::Clock zegarAnimacji;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};
