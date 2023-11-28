#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <math.h>
#include <random>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH    1200
#define WINDOW_HEIGHT   800

#define PI				3.1415926

using namespace sf;
using namespace std;

enum AnimalState {
	IDLE, SLEEP, EATING, MOVING
};