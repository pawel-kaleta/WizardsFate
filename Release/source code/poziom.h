#pragma once

#include <fstream>
#include <string>

using namespace std;

class poziom
{
public:

    poziom();
    poziom(string nazwaPliku, string nazwaPlikuScian);

    bool wczytajZpliku(string nazwaPliku, string nazwaPlikuScian);

    ~poziom(void);

    struct kafel
    {
        int typPola;
        bool czySciana;
    };

    const static int width = 40;
    const static int height = 24;

    const static int tile_width = 32;
    const static int tile_height = 32;

    kafel level[height][width];
};
