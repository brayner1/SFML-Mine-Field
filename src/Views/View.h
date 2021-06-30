#pragma once
#include <SFML/Graphics.hpp>

class View 
{
public:
	virtual void RenderView(sf::RenderWindow& window) = 0;
};