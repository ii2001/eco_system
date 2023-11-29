#include "EcoSystem.h"
#include "Camera.h"
#include "Entity.h"
#include "Animal.h"
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
	Camera camera;

	for (int i = 0; i < 20; i++) {
		world.add_entity(new grass(rand() % 1200, rand() % 800, 500 + rand() % 1000));
	}
	for (int i = 0; i < 10; i++) {
		world.add_entity(new Rabbit(rand() % 1200, rand() % 800));
		//rabbits.push_back(Rabbit(rand() % 1200, rand() % 800));
	}
	world.add_entity(new Wolf(600.0, 800.0));

	// SELECT
	Entity* selected = world.get_entity(30);

	sf::RectangleShape select_rect(sf::Vector2f(0.0, 0.0));
	select_rect.setSize(sf::Vector2f(40.0, 40.0));
	select_rect.setOutlineColor(sf::Color::Red);
	select_rect.setOutlineThickness(2.0);
	select_rect.setFillColor(sf::Color::Transparent);

	// MOUSE
	sf::Vector2i mouse_position;
	bool is_clicked = false;

	// MAIN LOOP
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			camera.update(event);
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				mouse_position = sf::Mouse::getPosition(window);
				is_clicked = true;
			}

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
		}

		curr_clock = clock();
		clock_delta = curr_clock - prev_clock;
		prev_clock = curr_clock;

		// update all
		world.update(clock_delta);
		//for (int i = 0; i < rabbits.size(); i++) {
		//    rabbits[i].update(update_clock_delta);

		//    // change slected
		//    if (is_clicked) {
		//        float distance = sqrt(pow(rabbits[i].getPos().x - mouse_position.x, 2) + pow(rabbits[i].getPos().y - mouse_position.y, 2));
		//        if (distance <= 50) {
		//            selected = (Animal*)&rabbits[i];
		//            is_clicked = false;
		//        }
		//    }

		//}
		//is_clicked = false;

		select_rect.setPosition(selected->getPos().x, selected->getPos().y);
		camera.setCenter(select_rect.getPosition());

		fps = 1000.0 / clock_delta;

		// clear the window with black color
		window.clear(color_grass);

		// draw Game Screen here
		camera.setView(GAME);

		// draw everything here...
		/*for (r_iter = rabbits.begin(); r_iter != rabbits.end(); r_iter++) {
			r_iter->draw();
		}*/
		world.draw();

		window.draw(select_rect);


		// draw Interface here (independent from game view)
		camera.setView(INTERFACE);

		// debug
		debug.print("selected_x", selected->getPos().x);
		debug.print("selected_y", selected->getPos().y);
		debug.print("selected_state", ((Animal*)selected)->get_state());
		debug.print("selcted_hunger", ((Animal*)selected)->get_hunger());
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