#pragma once
#include <Views/View.h>
#include <SFML/Graphics.hpp>

class OptionsView : public View 
{
	// Font used to draw texts
	sf::Font* textFont;

	// Message to be Displayed
	sf::Text optionsTitle;

	/* Grid Size option elements*/
	size_t gridSize;
	sf::Text sizeOption;
	sf::Text sizeValue;
	// A text to describe 
	sf::RectangleShape addSizeButton;
	sf::Text addSizeText;

	// Rectangle and text forming the menu button
	sf::RectangleShape decSizeButton;
	sf::Text decSizeText;

	/* Bomb Number option elements*/
	size_t nBombs;
	sf::Text bombOption;
	sf::Text bombValue;
	// A text to describe 
	sf::RectangleShape addBombButton;
	sf::Text addBombText;

	// Rectangle and text forming the menu button
	sf::RectangleShape decBombButton;
	sf::Text decBombText;

/* Menu Button */
	sf::RectangleShape menuButton;
	sf::Text menuText;
public:

	~OptionsView()
	{
		delete textFont;
	}


	OptionsView(sf::Vector2f windowSize, sf::Vector2u gridSize, size_t bombNumber)
	{
		this->gridSize = gridSize.x;
		this->nBombs = bombNumber;
		textFont = new sf::Font();
		textFont->loadFromFile("arial.ttf");

		// Initialize the Menu Title text
		optionsTitle.setFont(*textFont);
		optionsTitle.setCharacterSize(50);
		optionsTitle.setString("Options");
		optionsTitle.setOrigin(optionsTitle.getLocalBounds().width / 2, optionsTitle.getLocalBounds().height / 2);
		optionsTitle.setPosition(windowSize.x / 2, windowSize.y / 4);
		optionsTitle.setFillColor(sf::Color(120, 50, 50));


/* Size Options Initialization */
		{
			// Initialize the size option description, value and increase/decrease buttons and it's texts
			sizeOption.setFont(*textFont);
			sizeOption.setCharacterSize(16);
			sizeOption.setString("Field Size");
			sizeOption.setOrigin(sizeOption.getLocalBounds().width / 2, sizeOption.getLocalBounds().height / 2);
			sizeOption.setPosition(windowSize.x / 2, 1.2f * windowSize.y / 3);
			sizeOption.setFillColor(sf::Color::Black);

			// Initialize size value text
			sizeValue.setFont(*textFont);
			sizeValue.setCharacterSize(16);
			sizeValue.setString(std::to_string(this->gridSize));
			sizeValue.setOrigin(sizeValue.getLocalBounds().width / 2, sizeValue.getLocalBounds().height / 2);
			sizeValue.setPosition(windowSize.x / 2, 1.5f * windowSize.y / 3);
			sizeValue.setFillColor(sf::Color::Black);

			// Initialize the increase size button
			addSizeButton.setSize(sf::Vector2f(windowSize.x / 10, windowSize.y / 10));
			addSizeButton.setOrigin(windowSize.x / 20, windowSize.y / 20);
			addSizeButton.setPosition(3.5f * windowSize.x / 5, 1.5f * windowSize.y / 3);
			addSizeButton.setFillColor(sf::Color(0, 180, 0));

			addSizeText.setFont(*textFont);
			addSizeText.setCharacterSize(32);
			addSizeText.setString("+");
			addSizeText.setOrigin(addSizeText.getLocalBounds().width / 2, addSizeText.getLocalBounds().height / 2);
			addSizeText.setPosition(3.5f * windowSize.x / 5, 1.45f * windowSize.y / 3);
			addSizeText.setFillColor(sf::Color::White);

			// Initialize the decrease size button
			decSizeButton.setSize(sf::Vector2f(windowSize.x / 10, windowSize.y / 10));
			decSizeButton.setOrigin(windowSize.x / 20, windowSize.y / 20);
			decSizeButton.setPosition(1.5f * windowSize.x / 5, 1.5f * windowSize.y / 3);
			decSizeButton.setFillColor(sf::Color::Red);

			decSizeText.setFont(*textFont);
			decSizeText.setCharacterSize(32);
			decSizeText.setString("-");
			decSizeText.setOrigin(decSizeText.getLocalBounds().width / 2, decSizeText.getLocalBounds().height / 2);
			decSizeText.setPosition(1.5f * windowSize.x / 5, 1.43f * windowSize.y / 3);
			decSizeText.setFillColor(sf::Color::White);
		}
/* Bomb Options Initialization */
		{
			// Initialize the bomb option description, value and increase/decrease buttons and it's texts
			bombOption.setFont(*textFont);
			bombOption.setCharacterSize(16);
			bombOption.setString("Mines Number");
			bombOption.setOrigin(bombOption.getLocalBounds().width / 2, bombOption.getLocalBounds().height / 2);
			bombOption.setPosition(windowSize.x / 2, 1.8f * windowSize.y / 3);
			bombOption.setFillColor(sf::Color::Black);

			// Initialize size value text
			bombValue.setFont(*textFont);
			bombValue.setCharacterSize(16);
			bombValue.setString(std::to_string(this->nBombs));
			bombValue.setOrigin(bombValue.getLocalBounds().width / 2, bombValue.getLocalBounds().height / 2);
			bombValue.setPosition(windowSize.x / 2, 2.1f * windowSize.y / 3);
			bombValue.setFillColor(sf::Color::Black);

			// Initialize the increase size button
			addBombButton.setSize(sf::Vector2f(windowSize.x / 10, windowSize.y / 10));
			addBombButton.setOrigin(windowSize.x / 20, windowSize.y / 20);
			addBombButton.setPosition(3.5f * windowSize.x / 5, 2.1f * windowSize.y / 3);
			addBombButton.setFillColor(sf::Color(0, 180, 0));

			addBombText.setFont(*textFont);
			addBombText.setCharacterSize(32);
			addBombText.setString("+");
			addBombText.setOrigin(addBombText.getLocalBounds().width / 2, addBombText.getLocalBounds().height / 2);
			addBombText.setPosition(3.5f * windowSize.x / 5, 2.05f * windowSize.y / 3);
			addBombText.setFillColor(sf::Color::White);

			// Initialize the decrease size button
			decBombButton.setSize(sf::Vector2f(windowSize.x / 10, windowSize.y / 10));
			decBombButton.setOrigin(windowSize.x / 20, windowSize.y / 20);
			decBombButton.setPosition(1.5f * windowSize.x / 5, 2.1f * windowSize.y / 3);
			decBombButton.setFillColor(sf::Color::Red);

			decBombText.setFont(*textFont);
			decBombText.setCharacterSize(32);
			decBombText.setString("-");
			decBombText.setOrigin(decBombText.getLocalBounds().width / 2, decBombText.getLocalBounds().height / 2);
			decBombText.setPosition(1.5f * windowSize.x / 5, 2.05f * windowSize.y / 3);
			decBombText.setFillColor(sf::Color::White);
		}
/* Menu Button Initialization*/
		{
			menuButton.setSize(sf::Vector2f(windowSize.x / 3, windowSize.y / 10));
			menuButton.setOrigin(windowSize.x / 6, windowSize.y / 20);
			menuButton.setPosition(windowSize.x / 2, 0.9f * windowSize.y);
			menuButton.setFillColor(sf::Color::Blue);

			menuText.setFont(*textFont);
			menuText.setCharacterSize(32);
			menuText.setString("Main Menu");
			menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
			menuText.setPosition(windowSize.x / 2, 0.88f * windowSize.y);
			menuText.setFillColor(sf::Color::White);
		}
	}

	// Return true if the AddSize button is clicked
	bool AddSizeClicked(sf::Vector2f clickPosition) { return addSizeButton.getGlobalBounds().contains(clickPosition); }
	// Return true if the DecSize button is clicked
	bool DecSizeClicked(sf::Vector2f clickPosition) { return decSizeButton.getGlobalBounds().contains(clickPosition); }
	// Return true if the AddBomb button is clicked
	bool AddBombClicked(sf::Vector2f clickPosition) { return addBombButton.getGlobalBounds().contains(clickPosition); }
	// Return true if the DecBinb button is clicked
	bool DecBombClicked(sf::Vector2f clickPosition) { return decBombButton.getGlobalBounds().contains(clickPosition); }
	// Return true if the Menu button is clicked
	bool MenuClicked(sf::Vector2f clickPosition) { return menuButton.getGlobalBounds().contains(clickPosition); }

	// Set the new grid size value if the new size does not generate a grid with more bomb than cells
	bool setSize(size_t size) 
	{ 
		// If the new size is lower or equal to the number of bombs, it does not decrease
		if (size * size <= this->nBombs)
			return false;

		this->gridSize = size;
		return true;
	}

	// Set the new bomb number value if the new bomb number does not generate a grid with more bomb than cells
	bool setBomb(size_t bombs)
	{
		if (bombs >= this->gridSize * this->gridSize)
			return false;

		this->nBombs = bombs;
		return true;
	}

	// Draw the Main Menu elements
	void RenderView(sf::RenderWindow& window) override
	{
		window.draw(optionsTitle);

		sizeValue.setString(std::to_string(this->gridSize));
		window.draw(sizeOption);
		window.draw(sizeValue);
		window.draw(addSizeButton);
		window.draw(addSizeText);
		window.draw(decSizeButton);
		window.draw(decSizeText);

		bombValue.setString(std::to_string(this->nBombs));
		window.draw(bombOption);
		window.draw(bombValue);
		window.draw(addBombButton);
		window.draw(addBombText);
		window.draw(decBombButton);
		window.draw(decBombText);

		window.draw(menuButton);
		window.draw(menuText);
	}
};