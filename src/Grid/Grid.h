#pragma once
#include <SFML/Graphics.hpp>

class Grid {
private:
	sf::RectangleShape gridRect
	sf::Vector2u gridSize;
	struct GridNode{
		sf::RectangleShape rect;
		sf::Vector2f position;
		bool bomb;
		bool opened;
	} nodes*;


public:

	Grid(sf::Vector2u gridSize, sf::Vector2f gridWindowSize, sf::Vector2f gridPosition) {
		this->gridSize = gridSize;
		/*CUIDADO AQUI COM ESSA ALOCAÇÃO*/
		this->nodes = new GridNode[gridSize][gridSize];
		/*CUIDADO AQUI COM ESSA ALOCAÇÃO*/
		
		gridRect.setSize(sf::Vector2f(400, 400));
		gridRect.setOrigin(200, 200);
		gridRect.setPosition(width / 2, height / 2);
		gridRect.setFillColor(sf::Color::Transparent);
		gridRect.setOutlineColor(sf::Color::White);
		gridRect.setOutlineThickness(4);

		for (size_t i = 0; i < size.x; i++)
		{
			for (size_t j = 0; j < size.y; j++)
			{
				GridNode node = nodes[i][j];
				node->bomb = false;
				node->opened = false;
			}
		}



	}

	void RenderGrid(sf::RenderWindow& window) 
	{
		for (size_t i = 0; i < gridSize; i++) {
			for (size_t j = 0; j < gridSize; j++)
			{
				sf::RectangleShape gridCell = nodes[i][j];
				window.draw(gridCell);

			}
		}
	}

};