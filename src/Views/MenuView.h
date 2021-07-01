#pragma once
#include <Views/View.h>


class MenuView final : public View
{
	// Message to be Displayed
	sf::Text menuTitle;

	// Rectangle and text forming the play again button
	sf::RectangleShape playButton;
	sf::Text playText;

	// Rectangle and text forming the menu button
	sf::RectangleShape optionsButton;
	sf::Text optionsText;

public:

	MenuView(sf::Vector2f windowSize)
	{
		sf::Font* textFont = new sf::Font();
		textFont->loadFromFile("arial.ttf");

		// Initialize the Menu Title text
		menuTitle.setFont(*textFont);
		menuTitle.setCharacterSize(50);
		menuTitle.setString("Mine Field");
		menuTitle.setOrigin(menuTitle.getLocalBounds().width / 2, menuTitle.getLocalBounds().height / 2);
		menuTitle.setPosition(windowSize.x / 2, windowSize.y / 3);
		menuTitle.setFillColor(sf::Color(120, 50, 50));

		// Initialize the Play button and it's text
		playButton.setSize(sf::Vector2f(windowSize.x / 3, windowSize.y / 10));
		playButton.setOrigin(windowSize.x / 6, windowSize.y / 20);
		playButton.setPosition(windowSize.x / 2, 2 * windowSize.y / 3);
		playButton.setFillColor(sf::Color(0, 180, 0));

		playText.setFont(*textFont);
		playText.setCharacterSize(32);
		playText.setString("Play Game");
		playText.setOrigin(playText.getLocalBounds().width / 2, playText.getLocalBounds().height / 2);
		playText.setPosition(windowSize.x / 2, 2 * windowSize.y / 3);
		playText.setFillColor(sf::Color::White);

		// Initialize the Options button and it's text
		optionsButton.setSize(sf::Vector2f(windowSize.x / 3, windowSize.y / 10));
		optionsButton.setOrigin(windowSize.x / 6, windowSize.y / 20);
		optionsButton.setPosition(windowSize.x / 2, 2.5f * windowSize.y / 3);
		optionsButton.setFillColor(sf::Color::Red);

		optionsText.setFont(*textFont);
		optionsText.setCharacterSize(32);
		optionsText.setString("Options");
		optionsText.setOrigin(optionsText.getLocalBounds().width / 2, optionsText.getLocalBounds().height / 2);
		optionsText.setPosition(windowSize.x / 2, 2.5f * windowSize.y / 3);
		optionsText.setFillColor(sf::Color::White);
	}

	// Return true if the Play button is clicked
	bool PlayClicked(sf::Vector2f clickPosition) { return playButton.getGlobalBounds().contains(clickPosition); }
	// Return true if the Options button is clicked
	bool OptionsClicked(sf::Vector2f clickPosition) { return optionsButton.getGlobalBounds().contains(clickPosition); }

	// Draw the Main Menu elements
	void RenderView(sf::RenderWindow& window) override
	{
		window.draw(menuTitle);

		window.draw(playButton);
		window.draw(playText);

		window.draw(optionsButton);
		window.draw(optionsText);
	}
};