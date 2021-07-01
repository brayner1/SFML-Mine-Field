#pragma once
#include <Views/View.h>

class MessageView : public View
{
private:
	// Message to be Displayed
	sf::Text message;

	// Rectangle and text forming the play again button
	sf::RectangleShape playAgainButton;
	sf::Text playAgainText;

	// Rectangle and text forming the menu button
	sf::RectangleShape menuButton;
	sf::Text menuText;

public:

	MessageView(sf::Vector2f windowSize, std::string messageStr, sf::Color color = sf::Color::Black) 
	{
		sf::Font* textFont = new sf::Font();
		textFont->loadFromFile("arial.ttf");

		// Initialize the message text
		message.setFont(*textFont);
		message.setCharacterSize(50);
		message.setString(messageStr);
		message.setOrigin(message.getLocalBounds().width / 2, message.getLocalBounds().height / 2);
		message.setPosition(windowSize.x / 2, windowSize.y / 3);
		message.setFillColor(color);
		message.setOutlineColor(sf::Color::Red);
		message.setOutlineThickness(1);

		// Initialize the Play Again button and it's text
		playAgainButton.setSize(sf::Vector2f(windowSize.x / 3, windowSize.y / 10));
		playAgainButton.setOrigin(windowSize.x / 6, windowSize.y / 20);
		playAgainButton.setPosition(3.5f * windowSize.x / 5, 2 * windowSize.y / 3);
		playAgainButton.setFillColor(sf::Color(0, 180, 0));

		playAgainText.setFont(*textFont);
		playAgainText.setCharacterSize(32);
		playAgainText.setString("Play Again");
		playAgainText.setOrigin(playAgainText.getLocalBounds().width / 2, playAgainText.getLocalBounds().height / 2);
		playAgainText.setPosition(3.5f * windowSize.x / 5, 2 * windowSize.y / 3);
		playAgainText.setFillColor(sf::Color::White);

		// Initialize the Menu button and it's text
		menuButton.setSize(sf::Vector2f(windowSize.x / 3, windowSize.y / 10));
		menuButton.setOrigin(windowSize.x / 6, windowSize.y / 20);
		menuButton.setPosition(1.5f * windowSize.x / 5, 2 * windowSize.y / 3);
		menuButton.setFillColor(sf::Color::Red);

		menuText.setFont(*textFont);
		menuText.setCharacterSize(32);
		menuText.setString("Main Menu");
		menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
		menuText.setPosition(1.5f * windowSize.x / 5, 2 * windowSize.y / 3);
		menuText.setFillColor(sf::Color::White);
	}

	bool RestartClicked(sf::Vector2f clickPosition) { return playAgainButton.getGlobalBounds().contains(clickPosition); }
	bool MainMenuClicked(sf::Vector2f clickPosition) { return menuButton.getGlobalBounds().contains(clickPosition); }

	void RenderView(sf::RenderWindow& window) override
	{
		window.draw(message);

		window.draw(playAgainButton);
		window.draw(playAgainText);

		window.draw(menuButton);
		window.draw(menuText);
	}
};