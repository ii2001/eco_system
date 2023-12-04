#include "EcoSystem.h"
#include "Camera.h"
#include "Entity.h"
#include "Animal.h"
#include "Rabbit.h"
#include "Wolf.h"
#include "World.h"
#include "Debug.h"
#include "Environment.h"

int main()
{
	// RANDOM SEED
	srand((unsigned int)time(NULL));

	// CLOCK
	clock_t curr_clock;
	clock_t prev_clock = clock();
	int clock_delta;
	int fps;

	// COLORS
	sf::Color color_grass = sf::Color(94, 161, 82);

	// INIT
	RenderWindow window(sf::VideoMode(1200, 800), "My window");
	world.setWindow(&window);

	for (int i = 0; i < 20; i++) {
		world.add_entity(new grass(rand() % 1200, rand() % 800, 500 + rand() % 1000), GRASS);
	}
	for (int i = 0; i < 10; i++) {
		world.add_entity(new Rabbit(rand() % 1200, rand() % 800), RABBIT);
		//rabbits.push_back(Rabbit(rand() % 1200, rand() % 800));
	}
	world.add_entity(new Wolf(600.0, 800.0), WOLF);

	camera.setFocus((Animal*)world.get_entity(0, WOLF));

	// MOUSE
	Vector2i mouse_position;
	//bool is_clicked = false;

	// MAIN LOOP
	while (window.isOpen())
	{
		camera.setView(GAME);

		// check all the window's events that were triggered since the last iteration of the loop
		Event event;

		while (window.pollEvent(event))
		{
			camera.handleEvent(event);
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();

			/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mouse_position = sf::Mouse::getPosition(window);
				is_clicked = true;
			}*/

			//speed
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				world.set_speed(0);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
				world.set_speed(1);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
				world.set_speed(2);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
				world.set_speed(3);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
				world.set_speed(4);
			}

			Vector2i mousePos = Mouse::getPosition(*world.window);
			
			Vector2f worldPos = (*world.window).mapPixelToCoords(mousePos);

			if (Keyboard::isKeyPressed(Keyboard::R)) {
				world.add_entity(new Rabbit(worldPos.x, worldPos.y), RABBIT);
			}
			else if (Keyboard::isKeyPressed(Keyboard::W)) {
				world.add_entity(new Wolf(worldPos.x, worldPos.y), RABBIT);
			}
		}

		curr_clock = clock();
		clock_delta = curr_clock - prev_clock;

		if (clock_delta < MIN_FRAME_TIME)
			continue;

		prev_clock = curr_clock;

		// update all
		world.update(clock_delta);
		camera.update(clock_delta);
		
		//camera.setCenter(select_rect.getPosition());

		fps = 1000.0 / clock_delta;

		// clear the window with black color
		window.clear(color_grass);

		// draw everything here...
		/*for (r_iter = rabbits.begin(); r_iter != rabbits.end(); r_iter++) {
			r_iter->draw();
		}*/
		world.draw();

		// debug
		if (camera.getFocus() != NULL) {
			Animal* selected = camera.getFocus();

			debug.print("selected_x", selected->getPos().x);
			debug.print("selected_y", selected->getPos().y);
			debug.print("selected_state", selected->get_state());
			debug.print("selcted_hunger", selected->get_hunger());
		}
		debug.print("fps", fps);
		debug.finish();

		//console output
		//cout << "day: " << world.get_day() << std::endl;
		//cout << "time: " << world.get_time() << std::endl;
		//cout << "frame: " << world.get_frame() << std::endl;
		// end the current frame

		window.display();
	}
	return 0;
}