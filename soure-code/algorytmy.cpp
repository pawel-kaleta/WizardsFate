#include "silnik.h"
#include <math.h>

bool silnik::sprawdzKolizje(sf::ConvexShape ksztalt)
{
    int x,y;
    for(int i=0; i<ksztalt.getPointCount(); i++)
    {
        x = ksztalt.getTransform().transformPoint(ksztalt.getPoint(i)).x;
        y = ksztalt.getTransform().transformPoint(ksztalt.getPoint(i)).y;

        x /= poziom::tile_width;
        y /= poziom::tile_height;

        if(Poziom.level[y][x].czySciana)
            return true;
    }

    return false;
}

bool silnik::sprawdzWidocznosc(sf::Vector2f pozycja1, sf::Vector2f pozycja2)
{
    sf::Vector2f cel = pozycja2 - pozycja1;
    float kat = atan2(cel.x,cel.y);
    sf::Vector2f wektor1;
    sf::Vector2f wektor2;


    wektor1.x = sin(kat)*25;
    wektor1.y = cos(kat)*25;

    wektor2.x = sin(kat)*22;
    wektor2.y = cos(kat)*22;

    int a = wektor1.x;
    wektor1.x = -wektor1.y;
    wektor1.y = a;

    a = wektor2.x;
    wektor2.x = -wektor2.y;
    wektor2.y = a;

    if(sprawdzWidocznosc2(pozycja1+wektor1, pozycja2+wektor2))
        if(sprawdzWidocznosc2(pozycja1-wektor1, pozycja2-wektor2))
            return true;

    return false;
}

bool silnik::sprawdzWidocznosc2(sf::Vector2f pozycja1, sf::Vector2f pozycja2)
{
    sf::Vector2f cel;
    cel = pozycja2 - pozycja1;

    if(cel.x*cel.x+cel.y*cel.y < 10)
        return true;
    else
    {
        sf::Vector2f srodek = pozycja1+pozycja2;
        srodek.x /= 2;
        srodek.y /= 2;
        int x = srodek.x / poziom::tile_width;
        int y = srodek.y / poziom::tile_height;
        if(Poziom.level[y][x].czySciana)
            return false;
        else
        {
            if(sprawdzWidocznosc2(pozycja1,srodek))
                if(sprawdzWidocznosc2(srodek,pozycja2))
                    return true;
            return false;
        }
    }
}

bool silnik::sprawdzKolizje2(sf::Vector2f ksztalt1, sf::Vector2f ksztalt2, int i)
{

    int x = ksztalt1.x - ksztalt2.x;
    int y = ksztalt1.y - ksztalt2.y;

    x *= x;
    y *= y;

    int odl;

    if(i==2)
        odl = 1849;
    else
        odl = 784;


    if(odl > x + y)
        return true;
    else
        return false;
}
