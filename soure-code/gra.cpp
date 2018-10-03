#include "gra.h"
#include "silnik.h"
#include <iostream>

sf::RenderWindow okno(sf::VideoMode(1280,768), "Wizard's Fate", sf::Style::Fullscreen);


gra::gra(void)
{
    stanGry = KONIEC;

    if(!czcionka.loadFromFile("data/mecha.ttf"))
    {
        MessageBox(NULL, "Font not found.", "ERROR", NULL);
        return;
    }

    stanGry = MENU;
}

gra::~gra(void)
{
}

void gra::startGry()
{
    while(stanGry != KONIEC)
    {
        switch(stanGry)
        {
        case MENU:
            menu();
            break;
        case GRA:
            single();
            break;
        case EDYTOR_MAP:
            edytormap();
            break;
        }
    }
}

void gra::menu()
{
    sf::Text nazwaGry("Wizard's Fate", czcionka, 80);
    nazwaGry.setStyle(sf::Text::Bold);
    nazwaGry.setColor(sf::Color::Cyan);

    nazwaGry.setPosition(1280/2 - nazwaGry.getGlobalBounds().width/2, 20);

    const int liczbaOpcjiMenu = 4;

    sf::Text opcjeMenu[liczbaOpcjiMenu];

    string str[] = {"Play", "LSD", "Edytor Map", "Exit"};
    for(int i=0; i<liczbaOpcjiMenu; i++)
    {
        opcjeMenu[i].setFont(czcionka);
        opcjeMenu[i].setCharacterSize(65);

        opcjeMenu[i].setString(str[i]);
        opcjeMenu[i].setPosition(1280/2 - opcjeMenu[i].getGlobalBounds().width/2, 250 + i*120);
    }
    if(Opcje.czyLSD)
        opcjeMenu[1].setString("LSD ON");
    else
        opcjeMenu[1].setString("LSD OFF");

    while(stanGry == MENU)
    {
        sf::Vector2f pozycjaMyszy(sf::Mouse::getPosition());
        sf::Event zdarzenie;

        while(okno.pollEvent(zdarzenie))
        {
            if(zdarzenie.type == sf::Event::Closed || (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape))
                stanGry = KONIEC;
            else
                {
                    for(int i=0; i<liczbaOpcjiMenu; i++)
                    {
                        if(opcjeMenu[i].getGlobalBounds().contains(pozycjaMyszy) && zdarzenie.type == sf::Event::MouseButtonReleased && zdarzenie.key.code == sf::Mouse::Left)
                        {
                            switch(i)
                            {
                            case 0:
                                stanGry = GRA;
                                break;
                            case 1:
                                if(Opcje.czyLSD == 1)
                                {
                                    Opcje.czyLSD = 0;
                                    opcjeMenu[1].setString("LSD OFF");
                                }
                                else
                                {
                                    Opcje.czyLSD = 1;
                                    opcjeMenu[1].setString("LSD ON");
                                }
                                break;
                            case 2:
                                stanGry = EDYTOR_MAP;
                                break;
                            case 3:
                                stanGry = KONIEC;
                            }
                        }
                    }
                }
        }
        for(int i=0; i<liczbaOpcjiMenu; i++)
        {
            if(opcjeMenu[i].getGlobalBounds().contains(pozycjaMyszy))
                opcjeMenu[i].setColor(sf::Color::Cyan);
            else
                opcjeMenu[i].setColor(sf::Color::White);
        }

        okno.clear();

        okno.draw(nazwaGry);
        for(int i=0; i<liczbaOpcjiMenu; i++)
            okno.draw(opcjeMenu[i]);

        okno.display();
    }
}

void gra::single()
{

    silnik silnikGry(Opcje);
    silnikGry.startSilnika(okno, Opcje);

    stanGry = MENU;
}

void gra::zmienPole(silnik &silnikGry, int x, int y, bool dal)
{
    if(silnikGry.Poziom.level[x][y].czySciana == 0)
    {
        silnikGry.Poziom.level[x][y].typPola = 18;
    }
    else
    {
        int a = 0;
        if(x> 0 && silnikGry.Poziom.level[x-1][y].czySciana == 1)
        {
            a=a+1;
        }
        if(y<39 && silnikGry.Poziom.level[x][y+1].czySciana == 1)
        {
            a=a+10;
        }
        if(x<23 && silnikGry.Poziom.level[x+1][y].czySciana == 1)
        {
            a=a+100;
        }
        if(y> 0 && silnikGry.Poziom.level[x][y-1].czySciana == 1)
        {
            a=a+1000;
        }

        switch(a)
        {
        case 0:
            silnikGry.Poziom.level[x][y].typPola = 8;
            break;
        case 1:
            silnikGry.Poziom.level[x][y].typPola = 14;
            break;
        case 10:
            silnikGry.Poziom.level[x][y].typPola = 15;
            break;
        case 11:
            silnikGry.Poziom.level[x][y].typPola = 9;
            break;
        case 100:
            silnikGry.Poziom.level[x][y].typPola = 16;
            break;
        case 101:
            silnikGry.Poziom.level[x][y].typPola = 0;
            break;
        case 110:
            silnikGry.Poziom.level[x][y].typPola = 2;
            break;
        case 111:
            silnikGry.Poziom.level[x][y].typPola = 4;
            break;
        case 1000:
            silnikGry.Poziom.level[x][y].typPola = 17;
            break;
        case 1001:
            silnikGry.Poziom.level[x][y].typPola = 10;
            break;
        case 1010:
            silnikGry.Poziom.level[x][y].typPola = 1;
            break;
        case 1011:
            silnikGry.Poziom.level[x][y].typPola = 11;
            break;
        case 1100:
            silnikGry.Poziom.level[x][y].typPola = 3;
            break;
        case 1101:
            silnikGry.Poziom.level[x][y].typPola = 12;
            break;
        case 1110:
            silnikGry.Poziom.level[x][y].typPola = 5;
            break;
        case 1111:
            silnikGry.Poziom.level[x][y].typPola = 7;
            break;
        }
    }

    if(dal)
    {
        if(x<23) zmienPole(silnikGry, x+1, y, false);
        if(y<39) zmienPole(silnikGry, x, y+1, false);
        if(x>0) zmienPole(silnikGry, x-1, y, false);
        if(y>0) zmienPole(silnikGry, x, y-1, false);
    }
}

void gra::edytormap()
{
    silnik silnikGry(Opcje);
    sf::Event zdarzenie;

    bool wcisniety = 0;
    bool lewyPrawy = 0;

    while(stanGry == EDYTOR_MAP)
    {
        if(okno.pollEvent(zdarzenie))
        {
            if(zdarzenie.type == sf::Event::Closed || ( (zdarzenie.type == sf::Event::KeyPressed) && (zdarzenie.key.code == sf::Keyboard::Escape) ) )
                stanGry = MENU;
            else
            {
                if(zdarzenie.type == sf::Event::MouseButtonPressed)
                {
                    if(zdarzenie.key.code == sf::Mouse::Left)
                    {
                        wcisniety = 1;
                        lewyPrawy = 1;
                    }
                    else
                    {
                        if(zdarzenie.key.code == sf::Mouse::Right)
                        {
                            wcisniety = 1;
                            lewyPrawy = 0;
                        }
                    }
                }
                else
                {
                    if(zdarzenie.type == sf::Event::MouseButtonReleased)
                    {
                        wcisniety = 0;
                    }
                }
            }
        }

        if(wcisniety)
        {
            sf::Vector2f pozycjaMyszy(sf::Mouse::getPosition());
            int y = pozycjaMyszy.x / 32;
            int x = pozycjaMyszy.y / 32;
            if(lewyPrawy)
            {
                silnikGry.Poziom.level[x][y].czySciana = 1;
                zmienPole(silnikGry, x, y, true);
            }
            else
            {
                if(x>0 && x<23 && y>0 && y<39)
                {
                    silnikGry.Poziom.level[x][y].czySciana = 0;
                    zmienPole(silnikGry, x, y, true);
                }
            }
        }

        okno.clear();

        silnikGry.rysujMape(okno, Opcje);
        okno.display();
    }

    std::fstream plik1( "data/levels/map.level", ios::out );
    std::fstream plik2( "data/levels/map_sciany.level", ios::out );
    if( plik1.good() && plik2.good() )
    {
        for(int i=0; i<24; i++ )
        {
            for(int j=0; j<40; j++)
            {
                if(silnikGry.Poziom.level[i][j].typPola+1 < 10)
                    plik1 << "0";
                plik1 << silnikGry.Poziom.level[i][j].typPola+1 << " ";
                plik2 << silnikGry.Poziom.level[i][j].czySciana << " ";
            }
            plik1 << std::endl;
            plik2 << std::endl;
        }
        plik1.close();
        plik2.close();
    }
}
