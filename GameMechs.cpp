#include "GameMechs.h"
#include "MacUILib.h"
#include "objPos.h"

//Think about where to seed the RNG.

GameMechs::GameMechs()
{
    input = '\n';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 20;    //Defult board size
    boardSizeY = 10;  

    // ***
    // foodPos.setObjPos(-1,-1,'o');
    // srand(time(NULL));
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\n';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;    
    boardSizeY = boardY;

    // ***
    // srand(time(NULL));
    // foodPos.setObjPos(-1,-1,'o');
}

// do you need a destructor?
GameMechs::~GameMechs()
{

    // ***Generating the initial position of:
    // generateFood(objPos(-1,-1, 'o'));
}

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseTrue()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\n';
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(objPos blockOff)
{
    // generate random x and y coord, and make sure they are NOT border or blockOff pos.
    //check x and y against 0 and boardSizeX/Y
    //remember, in objPos class you have an isPosEqual() method. Use this instead of comparing element by element
    //for your convencince
    // int randX;
    // int randY;
    // ***

    objPos random_coordinates;

    while ((foodPos.x < 1 || foodPos.y < 1 ||  foodPos.x >= (boardSizeX - 1) || foodPos.y >= (boardSizeY - 1))) {

        // to randomly generate coordinates
        random_coordinates.x = rand() % (boardSizeX - 2) + 1;
        random_coordinates.y = rand() % (boardSizeY - 2) + 1;

        if(random_coordinates.isPosEqual(&blockOff)) // Regenerate if random coordinates match player position
        { 
            random_coordinates.x = rand() % (boardSizeX - 2) + 1;
            random_coordinates.y = rand() % (boardSizeY - 2) + 1;
        }
        else // If not, assign food position
        {
          foodPos.x = random_coordinates.x;
          foodPos.y = random_coordinates.y;
        }

    }

}

void GameMechs::getFoodPos(objPos &returnPos)
{

    // obtaining current position of food
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
    
}
