// SFML_MineField.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <Views/View.h>
#include <Views/GameView.h>
#include <Views/MessageView.h>
#include <Views/MenuView.h>
#include <Views/OptionsView.h>
#include <SFML/Graphics.hpp>


class MineFieldApp 
{
private:
/*  Window Properties */
    // Window Object
    sf::RenderWindow window;
    // Window Size
    sf::Vector2u size;

    // The current view in the application
    View* currentView;
    // The current view type
    enum class ViewType
    {
        MENU, OPTIONS, GAME, MESSAGE
    };
    ViewType viewType;

/*  Game Properties */
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
            case ViewType::GAME:
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
                            // If the player clicked on a mined cell, then the MessageView with Game Over message appears after some time showing the bombs.
                            if (gameView->isBomb(index))
                            {
                                // Show the bombs and render the view for 5 seconds
                                gameView->ShowBombs();
                                gameView->RenderViewForSecs(window, 5, sf::Color(160, 20, 20));

                                // Delete the Game View and create the Message View with the Game Over message.
                                delete gameView;
                                this->currentView = new MessageView(sf::Vector2f(size.x, size.y), "GAME OVER!");
                                this->viewType = ViewType::MESSAGE;
                                return;
                            }
                            // Otherwise, the cell is opened
                            else
                                gameView->OpenNode(index);

                            // If the player cleared the last non-mined cell, then the MessageView with Victory message appears.
                            if (gameView->victoryCondition())
                            {
                                // Show the bombs and render the view for 5 seconds
                                gameView->ShowBombs();
                                gameView->RenderViewForSecs(window, 5, sf::Color(20, 160, 20));

                                delete gameView;
                                this->currentView = new MessageView(sf::Vector2f(size.x, size.y), "You Win!");
                                this->viewType = ViewType::MESSAGE;
                                return;
                            }
                        }
                        return;
                    }
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        gameView->ToggleMarkNode(index);
                        return;
                    }
                }
                break;
            }
            case ViewType::MENU:
            {
                MenuView* menuView = (MenuView*)this->currentView;
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    // If clicked on the Play button, then the game is started
                    if (menuView->PlayClicked(clickPosition)) 
                    {
                        delete menuView;
                        this->currentView = new GameView(sf::Vector2u(gridSize.x, gridSize.y), sf::Vector2f(size.x, size.y), size.x - 100, sf::Vector2f(size.x / 2, size.y / 2), this->numBombs);
                        this->viewType = ViewType::GAME;
                    }
                    // If clicked in the Options button, then the Options view is started
                    else if (menuView->OptionsClicked(clickPosition))
                    {
                        delete menuView;
                        this->currentView = new OptionsView(sf::Vector2f(size.x, size.y), this->gridSize, this->numBombs);
                        this->viewType = ViewType::OPTIONS;
                    }
                }
                break;
            }
            case ViewType::OPTIONS:
            {
                OptionsView* optionsView = (OptionsView*)this->currentView;
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    // Check if the AddSize button is clicked
                    if (optionsView->AddSizeClicked(clickPosition))
                    {
                        // If it is, and the incremented size is valid, the increment is done
                        if (optionsView->setSize(this->gridSize.x + 1))
                            this->gridSize += sf::Vector2u(1, 1);
                        return;
                    }
                    // Check if the DecSize button is clicked
                    if (optionsView->DecSizeClicked(clickPosition))
                    {
                        // If it is, and the decrement size is valid, the decrement is done
                        if (optionsView->setSize(this->gridSize.x - 1))
                            this->gridSize -= sf::Vector2u(1, 1);
                        return;
                    }
                    // Check if the AddBomb button is clicked
                    if (optionsView->AddBombClicked(clickPosition)) 
                    {
                        // If it is, and the increment size is valid, the increment is done
                        if (optionsView->setBomb(this->numBombs + 1))
                            this->numBombs++;
                        return;
                    }
                    // Check if the DecBomb button is clicked
                    if (optionsView->DecBombClicked(clickPosition))
                    {
                        // If it is, and the decrement size is valid, the decrement is done
                        if (optionsView->setBomb(this->numBombs - 1))
                            this->numBombs--;
                        return;
                    }
                    // Check if the Menu button is clicked
                    if (optionsView->MenuClicked(clickPosition))
                    {
                        // If it is, then the view is changed to the MenuView
                        delete optionsView;
                        this->currentView = new MenuView(sf::Vector2f(size.x, size.y));
                        this->viewType = ViewType::MENU;
                        return;
                    }
                }
                break;
            }
            case ViewType::MESSAGE:
            {
                MessageView* messageView = (MessageView*)this->currentView;
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f clickPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    // Check if the Restart button is clicked
                    if (messageView->RestartClicked(clickPosition))
                    {
                        // If it is, then the view is changed to the GameView and the game is started
                        delete messageView;
                        this->currentView = new GameView(sf::Vector2u(gridSize.x, gridSize.y), sf::Vector2f(size.x, size.y), size.x - 100, sf::Vector2f(size.x / 2, size.y / 2), this->numBombs);
                        this->viewType = ViewType::GAME;
                        return;
                    }
                    // Check if the Main Menu button is clicked
                    else if (messageView->MainMenuClicked(clickPosition))
                    {
                        // If it is, then the view is changed to the MenuView
                        delete messageView;
                        this->currentView = new MenuView(sf::Vector2f(size.x, size.y));
                        this->viewType = ViewType::MENU;
                        return;
                    }
                }
                break;
            }
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
        
        // Grid size and bomb number default initialization
        this->gridSize = sf::Vector2u(18, 18);
        this->numBombs = 30;


        /*this->currentView = new GameView(sf::Vector2u(gridSize.x, gridSize.y), sf::Vector2f(size.x, size.y), size.x - 100, sf::Vector2f(size.x / 2, size.y / 2), 20);
        this->viewType = ViewType::GAME;*/
        // Initialize start view as Menu View
        this->currentView = new MenuView(sf::Vector2f(size.x, size.y));
        this->viewType = ViewType::MENU;

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