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

<<<<<<< HEAD
#define MIN_FRAME_TIME	30

=======
>>>>>>> e5fc5190a27c6593d4bc1f228d3bb974446cbb10
using namespace sf;
using namespace std;

enum AnimalState {
	IDLE, SLEEP, EATING, MOVING
};