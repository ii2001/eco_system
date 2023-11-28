#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Debug {
private:

    int count;
    Text debug[10];
    Font font;

public:
    Debug();
    ~Debug();
    void print(const char name[], int value);
    void finish();
};

extern Debug debug;