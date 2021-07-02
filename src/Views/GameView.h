#pragma once
#include <SFML/Graphics.hpp>
#include <Views/View.h>
#include <string>
#include <random>
#include <set>
#include <unordered_map>

// Class that manages and render a grid of rectangle cells that can contain bombs
// This class also implements the logics of the Mine Field Game
class GameView final : public View {
private:
/* Grid Attributes */
	// Rectangle that act as the "container" of the grid
	sf::RectangleShape gridRect;
	
	// The size of the grid in number of cells
	sf::Vector2u gridSize;

	// The font used to draw texts
	sf::Font* textFont;
	
	// The structure that defines the grid nodes
	struct GridNode{
		sf::RectangleShape rect;
		sf::Text nodeChar;
		sf::Vector2f position;
		int neighBombs = 0;
		bool bomb = false;
		bool opened = false;
		bool marked = false;
	};	
	// The unique pointer that will be initialized as the grid
	// the std::unique_ptr class ensures that the pointer/array is deallocated after the unique_ptr is destroyed (in this case, when this view is destroyed);
	std::unique_ptr<GridNode[]> nodes; 

	// The number of bombs in this grid
	float bombNumber;

/* Stats Attributes */
	// Rectangle Shape drawed in the bottom of the view as a frame to the text bellow
	sf::RectangleShape bottomRect;
	
	// Text shape to render the text 'number of bombs marked / number of bombs' and 'elapsed time' in the bottom of the view
	sf::Text bombsMarkedText;

	// Time elapsed since the start of the game
	sf::Clock elapsedClock;

	// The bool that defines if the elapsed time will be updated when the view is rendered
	bool updateClock = true;
	
	// Bombs marked by the player
	size_t cellsMarked;
	
	// The number of cells already opened. Used to check the victory condition
	size_t cellsOpened;



/* Utilities Methods */

	// MACRO that calculate the index of an array based on a matrix indexation
	// 'i' represents the line and 'j' the column
	#define convertIndex(i, j) ((i) * gridSize.x + (j))

	// Method that populates the grid with the number of bombs defined by the player.
	// It populates the grid with bombs in a uniform distribution.
	void PopulateBombs() 
	{
		// Obtain a random number from hardware
		std::random_device rd;

		// Seed the generator with the random_device number
		std::mt19937 gen(rd());

		// Define distribution the range
		std::uniform_int_distribution<int> xDistr(0, gridSize.x - 1);
		std::uniform_int_distribution<int> yDistr(0, gridSize.y - 1);

		// Fill the bombs in a uniform distribution trough the grid
		for (size_t i = 0; i < bombNumber;)
		{
			int x = xDistr(gen);
			int y = yDistr(gen);
			GridNode& node = nodes[convertIndex(y, x)];
			// If there isn't a bomb in this node, add one. If there is, the loop will iterate without incrementing 'i'
			if (!node.bomb)
			{
				node.bomb = true;
				i++;
			}
		}

		
	}

	// Method that populates all cells that are neighbors to bombs with the number of bomb neighbors.
	void PopulateBombNeighbors() 
	{
		for (size_t i = 0; i < gridSize.y; i++)
		{
			for (size_t j = 0; j < gridSize.x; j++)
			{
				GridNode& node = nodes[convertIndex(i, j)];
				if (node.bomb)
					continue;

				// Check the neighbors for bombs
				// ↖
				if (i > 0 && j > 0 && nodes[convertIndex(i - 1, j - 1)].bomb)
					node.neighBombs++;

				// ↑
				if (i > 0 && nodes[convertIndex(i - 1, j)].bomb)
					node.neighBombs++;

				// ↗
				if (i > 0 && j < gridSize.x - 1 && nodes[convertIndex(i - 1, j + 1)].bomb)
					node.neighBombs++;

				// ←
				if (j > 0 && nodes[convertIndex(i, j - 1)].bomb)
					node.neighBombs++;

				// →
				if (j < gridSize.x - 1 && nodes[convertIndex(i, j + 1)].bomb)
					node.neighBombs++;

				// ↙
				if (i < gridSize.y - 1 && j > 0 && nodes[convertIndex(i + 1, j - 1)].bomb)
					node.neighBombs++;

				// ↓
				if (i < gridSize.y - 1 && nodes[convertIndex(i + 1, j)].bomb)
					node.neighBombs++;

				// ↘
				if (i < gridSize.y - 1 && j < gridSize.x - 1 && nodes[convertIndex(i + 1, j + 1)].bomb)
					node.neighBombs++;

			}
		}
	}

public:

	~GameView() 
	{
		delete textFont;
	}

	// gridSize -> grid size in number of cells
	// windowSize -> the size of the window the grid is being placed
	// gridFrameSize -> grid size in the screen (pixels)
	// gridPosition -> the position of the grid on the screen
	// bombNumber -> the number of bombs on the grid
	GameView(sf::Vector2u gridSize, sf::Vector2f windowSize, float gridFrameSize, sf::Vector2f gridPosition, int bombNumber) 
	{
		// Store the grid size (number of cells)
		this->gridSize = gridSize;
		// Allocate the grid array
		this->nodes = std::unique_ptr<GridNode[]>(new GridNode[gridSize.x * gridSize.y]);
		// Store the number of bombs
		this->bombNumber = bombNumber;
		// Initialized the cellsOpened and cellsMarked counters
		this->cellsOpened = this->cellsMarked =  0;
		
		// Initialize the rectangle that act as the grid container
		gridRect.setSize(sf::Vector2f(gridFrameSize, gridFrameSize));
		gridRect.setOrigin(gridFrameSize/2, gridFrameSize/2);	// Set the origin to the middle of the rectangle
		gridRect.setPosition(gridPosition);
		gridRect.setFillColor(sf::Color::Transparent);	// The rect is not filled. Only it's outline is rendered
		gridRect.setOutlineColor(sf::Color::White);
		gridRect.setOutlineThickness(4);

		bottomRect.setSize(sf::Vector2f(windowSize.x, 50));
		bottomRect.setOrigin(windowSize.x / 2, 25);
		bottomRect.setPosition(windowSize.x / 2, windowSize.y - 25);
		bottomRect.setFillColor(sf::Color(120, 120, 120));

		textFont = new sf::Font();
		textFont->loadFromFile("arial.ttf");

		bombsMarkedText.setFont(*textFont);
		bombsMarkedText.setCharacterSize(16);
		bombsMarkedText.setPosition(50, 565);


		this->PopulateBombs();	// Populate the grid with bombs
		this->PopulateBombNeighbors();	// Populate the cells with the number of bomb neighbors

		// Calculate the cell size to fit in the 
		sf::Vector2f cellSize = sf::Vector2f(gridFrameSize / gridSize.x, gridFrameSize / gridSize.y);
		for (size_t i = 0; i < gridSize.y; i++)
		{
			for (size_t j = 0; j < gridSize.x; j++)
			{
				GridNode& node = nodes[convertIndex(i,j)];

				node.opened = false;
				node.marked = false;

				// Initialize the position and attributes of the cell rectangle that graphically represents this cell
				sf::Vector2f relativePos = sf::Vector2f( ((int)j - (int)gridSize.x / 2) * cellSize.x + cellSize.x / 2 * (1.0f - (gridSize.x % 2)),
														 ((int)i - (int)gridSize.y / 2) * cellSize.y + cellSize.y / 2 * (1.0f - (gridSize.y % 2)) );
				node.position = gridPosition + relativePos;
				node.rect.setOrigin(sf::Vector2f(cellSize.x / 2, cellSize.y / 2));	// Set the origin to the middle of the rectangle
				node.rect.setPosition(node.position);
				node.rect.setSize(cellSize);
				node.rect.setFillColor(sf::Color(180, 180, 180));
				node.rect.setOutlineColor(sf::Color::White);
				node.rect.setOutlineThickness(1);



				// Initialize the text shape which will render the number of adjecent bombs, if there is any, when the cell is opened by the player
				std::string str = "";
				node.nodeChar.setString(str);
				node.nodeChar.setFont(*textFont);
				float charSize = std::floor(std::min(cellSize.x / 1.4f, cellSize.y / 1.4f)); // Calculate the character size to fit in the cell
				node.nodeChar.setCharacterSize(charSize);
				node.nodeChar.setOrigin(sf::Vector2f(charSize/2, charSize/2));
				node.nodeChar.setPosition(node.position);
				node.nodeChar.setFillColor(sf::Color::Red);
			}
		}
		elapsedClock = sf::Clock();
		
	}

	// Return if there is bomb in the given index
	bool isBomb(sf::Vector2u nodeIndex) { return nodes[convertIndex(nodeIndex.x, nodeIndex.y)].bomb; }
	// Return if the node was already opened in the given index
	bool isOpened(sf::Vector2u nodeIndex) { return nodes[convertIndex(nodeIndex.x, nodeIndex.y)].opened; }
	// Return if the node is marked by the player. Tipically, this is used to not allow the player to click a marked node.
	bool isMarked(sf::Vector2u nodeIndex) { return nodes[convertIndex(nodeIndex.x, nodeIndex.y)].marked; }
	// Return if the victory condition is met. Checks if the number of opened cells is the number of clear cells
	bool victoryCondition() { return cellsOpened == gridSize.x * gridSize.y - bombNumber; }
	// Return the number of opened cells
	size_t numOpened() { return this->cellsOpened; }

	// Calculate the index of a node in a given screen position. Return true in case the click was in one of the nodes, false otherwise
	// The clicked node index is returned by the reference parameter 'nodeIndex'
	bool NodeClicked(sf::Vector2f clickPos, sf::Vector2u& nodeIndex) 
	{
		for (size_t i = 0; i < gridSize.y; i++)
		{
			for (size_t j = 0; j < gridSize.x; j++)
			{
				GridNode& node = nodes[convertIndex(i, j)];
				sf::RectangleShape& gridCell = node.rect;
				if (gridCell.getGlobalBounds().contains(clickPos)) 
				{
					nodeIndex = sf::Vector2u(i, j);
					return true;
				}

			}
		}
		return false;
	}

	// Open the node in the given Index. If the node is not neighbor to any bomb, it opens it's neighbors nodes.
	void OpenNode(sf::Vector2u nodeIndex) 
	{
		// Get the line and column, where 'nodeIndex.x' is actually the line and 'nodeIndex.y' the column
		size_t i = nodeIndex.x, j = nodeIndex.y;


		GridNode& node = nodes[convertIndex(i, j)];
		// If the node is opened or is a bomb, ignore. (clicking on bomb is handled by the MineFieldApp class
		if (node.opened || node.bomb)
			return;
		
		node.opened = true;
		// Change the color of the rectangle to indicate the cell is open
		node.rect.setFillColor(sf::Color(210, 210, 210));
		
		// Increment the number of cells opened
		cellsOpened++;

		if (node.neighBombs == 0) 
		{
			node.nodeChar.setString("");
			// ↖
			if (i > 0 && j > 0)
				OpenNode(sf::Vector2u(i - 1, j - 1));

			// ↑
			if (i > 0)
				OpenNode(sf::Vector2u(i - 1, j));

			// ↗
			if (i > 0 && j < gridSize.x - 1)
				OpenNode(sf::Vector2u(i - 1, j + 1));

			// ←
			if (j > 0)
				OpenNode(sf::Vector2u(i, j - 1));

			// →
			if (j < gridSize.x - 1)
				OpenNode(sf::Vector2u(i, j + 1));

			// ↙
			if (i < gridSize.y - 1 && j > 0)
				OpenNode(sf::Vector2u(i + 1, j - 1));

			// ↓
			if (i < gridSize.y - 1)
				OpenNode(sf::Vector2u(i + 1, j));

			// ↘
			if (i < gridSize.y - 1 && j < gridSize.x - 1)
				OpenNode(sf::Vector2u(i + 1, j + 1));
		}
		else 
		{
			node.nodeChar.setString(std::to_string(node.neighBombs));
		}
		return;
	}

	// Toggle a marker on the node, indicating that the user thinks there is a bomb in this node.
	void ToggleMarkNode(sf::Vector2u nodeIndex)
	{
		// Get the line and column, where 'nodeIndex.x' is actually the line and 'nodeIndex.y' the column
		size_t i = nodeIndex.x, j = nodeIndex.y;

		
		GridNode& node = nodes[convertIndex(i, j)];
		// If the node is opened, it can't be marked
		if (node.opened)
			return;


		// If the node is not marked, mark it with 'M'
		if (!node.marked)
		{
			node.nodeChar.setString("M");
			node.marked = true;
			cellsMarked++;
		}
		// Otherwise, turn it blank
		else
		{
			node.nodeChar.setString("");
			node.marked = false;
			cellsMarked--;
		}
	}

	// Switch the texts of the bomb cells to show an 'X' in it's place, revealing their locations
	void ShowBombs() 
	{
		for (size_t i = 0; i < gridSize.y; i++)
		{
			for (size_t j = 0; j < gridSize.x; j++)
			{
				GridNode& node = nodes[convertIndex(i, j)];
				if (node.bomb)
				{
					sf::Text& nodeChar = node.nodeChar;
					node.nodeChar.setString("X");
				}

			}
		}
	}

	void ShowBomb(sf::Vector2u bombIndex)
	{
		int i = bombIndex.x; int j = bombIndex.y;
		GridNode& node = nodes[convertIndex(i, j)];
		if (!node.bomb)
			return;
		node.nodeChar.setString("X");
	}

	// Render the grid rectangle and its containing cells
	void RenderView(sf::RenderWindow& window) override
	{
		// Render the grid frame
		window.draw(gridRect);
		// Render the grid cells
		for (size_t i = 0; i < gridSize.y; i++)
		{
			for (size_t j = 0; j < gridSize.x; j++)
			{
				// Get the node, it's rectangle shape and text shape, and render both.
				GridNode& node = nodes[convertIndex(i, j)];
				sf::RectangleShape& gridCell = node.rect;
				sf::Text& nodeChar = node.nodeChar;
				window.draw(gridCell);
				window.draw(nodeChar);

			}
		}
		// Get the time elapsed since the start of the game
		sf::Time time = elapsedClock.getElapsedTime();

		if (this->updateClock)
		{
			std::string str = std::to_string(cellsMarked) + " / " + std::to_string((int)bombNumber) + "\tElapsed Time: " + std::to_string(time.asSeconds());
			bombsMarkedText.setString(str);
		}

		window.draw(bottomRect);
		window.draw(bombsMarkedText);

	}

	// Function used to render this view exclusively for 'seconds' seconds.
	// For the time this function is executed, the logic of the application is not processed.
	// It can be skiped with a left click.
	void RenderViewForSecs(sf::RenderWindow& window, float seconds, sf::Color bgColor)
	{
		// The clock used to render the elapsed time in the screen is disabled
		this->updateClock = false;

		// This clock is used to calculate the time the view is rendered
		sf::Clock clock;
		// Render the view for 'seconds' seconds, stopping if the window is closed or the player click in the screen
		while (clock.getElapsedTime().asSeconds() < seconds && window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				// If the left mouse button is clicked, the view will skip the rendering for seconds
				// It does that by setting the variable 'seconds' to 0, forcing the exit of the loop
				if (event.type == sf::Event::MouseButtonPressed)
					if (event.mouseButton.button == sf::Mouse::Left)
						seconds = 0;
			}
			window.clear(bgColor);
			this->RenderView(window);
			window.display();
		}

	}
};