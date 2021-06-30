// SFML_MineField.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <Grid/Grid.h>
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
        
        
        Grid grid(sf::Vector2u(10, 20), 400, sf::Vector2f(width/2, height/2), 10);

        while (window.isOpen())
        {
            // Calculate the time between each frame
            sf::Time deltaTime = clock.restart();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        //std::cout << "the left button was pressed" << std::endl;
                        //std::cout << "\tmouse x: " << event.mouseButton.x << std::endl;
                        //std::cout << "\tmouse y: " << event.mouseButton.y << std::endl;
                        sf::Vector2u index;
                        if (grid.NodeClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), index))
                        {
                            grid.OpenNode(index);
                        }
                        
                    }
                }
            }

            window.clear(sf::Color(235, 235, 235));

            grid.RenderGrid(window);

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