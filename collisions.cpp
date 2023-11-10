//This serves as the main code for the program. This is where the world is created and the particles being generated
#include <SFML/Graphics.hpp>
#include "cParticles.h"
#include <iostream>

int main()
{
	//This generates the world at the size 800, 600 and has a selectedParticle at nothing, just so it will not confuse the program
	World* world = new World(800, 600);
	Particles* selectedParticle = nullptr;

	//This renders the window and names it Assignment 2: Resub with a framerate of 60 FPS
	sf::RenderWindow window(sf::VideoMode(world->getWidth(), world->getHeight()), "Assignment 2: Resub");
	window.setFramerateLimit(60);
	//This generates 10 random particles into the world
	for (int i = 0; i < 10; i++)
	{
		world->addParticle();
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//If the user presses the close button or the Escape key, the program will end
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
			//If the user clicks the left mouse button, the selected particle will move to the position that our mouse is at using the x,y coordinates
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					float mouseX = event.mouseButton.x;
					float mouseY = event.mouseButton.y;
					selectedParticle = world->getParticle(mouseX, mouseY);
					std::cout << "Button Pressed" << std::endl;
				}
			}
			//Once the button has been released, the selected particle will fall where the x,y is
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					selectedParticle = nullptr;
				}
			}
		}
		//This clears the window and updates the world
		window.clear();

		world->update();
		//This moves the particle to the mouse's location
		if (selectedParticle)
		{
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;
			selectedParticle->moveTo(mouseX, mouseY);
		}
		//This draws the particles into the window in the shape of circles and gets the size that is randomly generated
		for (int i = 0; i < world->getParticles().size(); i++)
		{
			Particles* particle = world->getParticles()[i];
			sf::CircleShape circle(particle->getSize());
			circle.setOrigin(particle->getSize(), particle->getSize());
			circle.setPosition(particle->getX(), particle->getY());
			window.draw(circle);
		}
		//This displays the outcome
		window.display();
	}

	return EXIT_SUCCESS;
}