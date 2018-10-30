// DaveTanks.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h" // required
#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Scene.h"
#include "LoadingScene.h"
#include "Resources.h"

sf::RenderWindow window(sf::VideoMode(1280, 720), "Dave's Tanks", sf::Style::Close);

int main() {
	// Set initial scene
	currentScene = new LoadingScene();

	const float FPS = 60.0f; //The desired FPS. (The number of updates each second).
	bool redraw = true;      //Do I redraw everything on the screen?
	sf::Clock clock;
	sf::Event ev;

	sf::View view = window.getView();

	loadTexture("bg");

	sf::Sprite bg;
	bg.setTexture(getTexture("bg"));
	bg.setScale(0.5, 0.5);
	int background_size = getTexture("bg").getSize().x * bg.getScale().x;
	float bg_offset = 1;

	while (window.isOpen()) {
		//Wait until 1/60th of a second has passed, then update everything.
		if (clock.getElapsedTime().asSeconds() >= 1.0f / FPS) {
			redraw = true;
		} else {
			//Sleep until next 1/60th of a second comes around
			sf::Time sleepTime = sf::seconds((1.0f / FPS) - clock.getElapsedTime().asSeconds());
			sleep(sleepTime);
		}
		// Poll Events
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) window.close();
		}

		if (redraw) {
			window.clear();

			if (resourcesLoaded) {
				// Apply a default view
				view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
				window.setView(view);
				bg_offset = (bg_offset + 1);
				if (bg_offset >= background_size) bg_offset -= background_size;

				// Draw BG
				for (int xx = bg_offset; xx < window.getSize().x + background_size + 32; xx += background_size) {
					for (int yy = 0; yy < window.getSize().y + background_size; yy += background_size) {
						bg.setPosition(sf::Vector2f(xx - background_size, yy));
						window.draw(bg);
					}
				}
			}

			// Apply shake
			view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
			window.setView(view);
			// Draw the current scene
			currentScene->render(&window);

			window.display();
		}
	}

	return 0;
}
