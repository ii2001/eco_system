#include "Debug.h"
#include "World.h"

Debug::Debug() {
    count = 0;

    font.loadFromFile("arial.ttf");
    for (int i = 0; i < 10; i++) {
        debug[i] = Text();
        debug[i].setFont(font);
        debug[i].setPosition(0, i * 24);
        debug[i].setCharacterSize(24);
        debug[i].setFillColor(Color::White);
        debug[i].setOutlineColor(Color::Black);
        debug[i].setOutlineThickness(2);
        debug[i].setStyle(Text::Bold);
    }
}

Debug::~Debug() {}

void Debug::print(const char name[], int value) {
    debug[count].setString((string)name + ':' + to_string(value));
    world.window->draw(debug[count]);
    count++;
};

void Debug::finish() {
    count = 0;
}

Debug debug;