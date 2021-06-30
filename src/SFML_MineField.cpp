// SFML_MineField.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <Views/View.h>
#include <Views/GameView.h>
#include <SFML/Graphics.hpp>

class MineFieldApp 
{
private:
// Window Properties
    // Window Object
    sf::RenderWindow window;
    // Window Size
    sf::Vector2u size;

    // The current view in the application
    View* currentView;
    // The current view type
    enum ViewType { MENU, OPTIONS, GAME, GAMEOVER } 
    viewType;

// Game Properties
    // Number of bombs
    size_t numBombs;
    // Size of the grid in number of cells
    sf::Vector2u gridSize;

    void ProcessEvent(sf::Event event) 
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            switch (viewType)
            {
            case MENU:
                break;
            case OPTIONS:
                break;
            case GAME:
            {
                sf::Vector2u index;
                GameView* gameView = (GameView*)this->currentView;
                bool nodeClicked = gameView->NodeClicked(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), index);
                if (nodeClicked)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // If player clicked on a bomb cell and it is not marked, then it is a Game Over
                        if (!gameView->isMarked(index)) 
                        {
                            if (gameView->isBomb(index))
                                std::cout << "GAME OVER" << std::endl;
                            else
                                gameView->OpenNode(index);
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        gameView->ToggleMarkNode(index);
                    }
                }
                break;
            }
            case GAMEOVER:
                break;
            default:
                break;
            }
            
        }
    }

public:
    MineFieldApp(sf::Vector2u size) : size(size) 
    { 

    }

    int MainLoop() {
        // Clock for measuring deltaTime in each frame
        sf::Clock clock;

        // Window Creation
        size_t width = size.x, height = size.y;
        window.create(sf::VideoMode(width, height), "Campo Minado", sf::Style::Close | sf::Style::Titlebar);
        


        this->currentView = new GameView(sf::Vector2u(10, 20), 400, sf::Vector2f(width/2, height/2), 20);
        this->viewType = GAME;

        while (window.isOpen())
        {
            // Calculate the time between each frame
            sf::Time deltaTime = clock.restart();

            sf::Event event;
            while (window.pollEvent(event))
            {
                this->ProcessEvent(event);
            }

            window.clear(sf::Color(235, 235, 235));

            this->currentView->RenderView(window);

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