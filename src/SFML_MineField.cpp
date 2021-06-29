// SFML_MineField.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <SFML/Graphics.hpp>

class MineFieldApp 
{
private:
    // Window Object
    sf::RenderWindow window;
    // Window Size
    sf::Vector2u size;
    // Window Aspect Ratio
    float aspect;

    // Public Methods
public:
    MineFieldApp(sf::Vector2u size) : size(size) { aspect = (float)size.x / size.y; }

    int MainLoop() {
        // Clock for measuring deltaTime in each frame
        sf::Clock clock;

        // Window Creation
        size_t width = size.x, height = size.y;
        window.create(sf::VideoMode(width, height), "Campo Minado", sf::Style::Close | sf::Style::Titlebar);

        

        const int gridSize = 10;
        const float cellSize = 400.0f / gridSize;
        std::cout << "cell size: " << cellSize << std::endl;
        sf::RectangleShape grid[gridSize][gridSize];
        for (int i = 0; i < gridSize; i++) {
            for (size_t j = 0; j < gridSize; j++)
            {
                sf::RectangleShape* gridCell = &grid[i][j];
                gridCell->setSize(sf::Vector2f(cellSize, cellSize));
                gridCell->setOrigin(cellSize / 2, cellSize / 2);
                gridCell->setPosition((width / 2 - 200) + i * cellSize + cellSize/2, (height / 2 - 200) + j * cellSize + cellSize / 2);
                gridCell->setFillColor(sf::Color(180, 180, 180));
                gridCell->setOutlineColor(sf::Color::Black);
                gridCell->setOutlineThickness(1);
                std::cout << "cell[" << i << ", " << j << "]: " << gridCell->getPosition().x << ", " << gridCell->getPosition().y << std::endl;
            }
        }

        while (window.isOpen())
        {
            // Calculate the time between each frame
            sf::Time deltaTime = clock.restart();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color(220, 220, 220));

            

            window.display();

        }
        return 0;
    }

    // Private Methods
private:

};

int main()
{
    
    //size_t circleSize = (width < height) ? width / 2 : height / 2;
    //sf::CircleShape shape(circleSize);
    //shape.setPosition(width/2 - circleSize, 0);
    //std::cout << shape.getPosition().x << std::endl;
    //shape.setFillColor(sf::Color::White);

    MineFieldApp app(sf::Vector2u(500, 600));

    return app.MainLoop();
}