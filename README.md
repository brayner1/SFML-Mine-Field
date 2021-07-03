# SFML Mine Field

Mine Field game made using the SFML library. Program made as an internship test for C++ programming.  
Below is an explanation of the classes and it's basic functionalities. SFML-related code and attributes are not explained.  
The code is also well commented.

## Class Diagram

![Class Diagram](https://user-images.githubusercontent.com/18320203/124340506-1211e880-db8c-11eb-851d-dba6395beb8d.png)

### MineFieldApp
Class that handles the application main functionalities and the Views flow.
#### Attributes
* **window** -> SFML window responsible for isntancing a system window and draw into it.
* **windowSize** -> Vector2 of unsigned int storing the window size.
* **currentView** -> The current View instance being displayed in the window.
* **currentViewType** -> The current View type instanced.
* **numBombs** -> Unsigned int storing the number of bombs that will be created in a new game.
* **gridSize** -> The size of the mine field grid in number of cells.
* **powerupOn** -> Boolean indicating if the Power Up mechanic is toggled

#### Methods
* **ProcessEvent(event)** -> Process one window event, handling it according to the event and the actual View type.
* **MainLoop()** -> Handles the program main loop, processing the polled events, drawing the actual View and displaying it in the screen.


### View
Class that serves as base class for the implementation of the virtual method 'RenderView'.
#### Methods
* **RenderView(window)** -> Virtual method that serves as interface for the implementation of the application views.

### GameView : View
The view class that handles the game visualization and interactions. Also provides some utilities functions to check the status of the game.

#### Attributes
* **gridSize** -> Variable that stores the grid size of the game.
* **nodes[]** -> Array of type **'GridNode'**, storing all the nodes of the game grid and it's state.
  * **GridNode**
    * position -> Store the position of the node
    * neighBombs -> Store the number of neighbor bomb nodes in the node.
    * bomb -> Boolean that stores if the node is a bomb or not
    * opened -> Boolean that stores if the node was opened or not.
    * marked -> Boolean that stores if the node is marked by the player or not.
* **bombNumber** -> Stores the number of bombs in the game.
* **elapsedClock** -> SFML clock used to calculate and show the time elapsed since the start of the game.
* **updateClock** -> Boolean that sets if the elpsedClock will be updated.
* **cellsMarked** -> Stores the number of grid cells already marked by the player.
* **cellsOpened** -> Stores the number of grid cells already opened by the player.

#### Methods
* **PopulateBombs()** -> Method that populates the grid with bombs randomly in a uniform distribution.
* **PopulateBombNeighbors()** -> Method that calculate and store the number of neighbor bombs for each node.
* **IsBomb(nodeIndex)** -> Return true if the 'nodeIndex' is the index of a bomb.
* **IsOpened(nodeIndex)** -> Return true if the 'nodeIndex' is the index of a opened node.
* **IsMarked(nodeIndex)** -> Return true if the 'nodeIndex' is the index of a marked node.
* **VictoryCondition()** -> Return true if the victory condition of the game is met.
* **NumOpened()** -> Return the number of opened nodes.
* **NodeClicked(clickPos, out nodeIndex)** -> Return true and save the index in 'nodeIndex' if a node is clicked at 'clickPos'. Return false otherwise.
* **OpenNode(nodeIndex)** -> Open the node in the 'nodeIndex', revealing the number of neighbor bombs if there is any or opening it's neghbor nodes if there is not.
* **ToggleMarkNode(nodeIndex)** -> Toggle On/Off the marking of a node indicated by the 'nodeIndex'.
* **ShowBombs()** -> Reveal all bombs in the grid with an 'X' in it.
* **ShowBomb(bombIndex)** -> Reveal one bomb indicated by 'bombIndex' in the grid with an 'X'.
* **RenderViewForSces(window, seconds, bgColor)** -> Render this view for 'seconds' seconds with the provided 'bgColor'. This method is used to show the bombs in the grid when the game is over (either Victory or Defeat).

### Options, Message and Menu Views
All these Views have very similar methods, used by the application to check if a button in the view was clicked.
