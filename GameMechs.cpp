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

    foodPos.setObjPos(-1,-1,'o');
    srand(time(NULL));
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\n';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;    //Given board size
    boardSizeY = boardY;

    foodPos.setObjPos(-1,-1,'o');
    srand(time(NULL));
}

// do you need a destructor?
GameMechs::~GameMechs()
{

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
    
    objPos randomCoords;

    while ((foodPos.x < 1 || foodPos.y < 1 ||  foodPos.x >= (boardSizeX - 1) || foodPos.y >= (boardSizeY - 1))) 
    {
        //The while conditions allows the while to run if food is not on the board
        //After food is collect we should set foodPos to -1,-1 again to run this function again
        // to randomly generate coordinates
        randomCoords.x = rand()%(boardSizeX - 2) + 1;
        randomCoords.y = rand()%(boardSizeY - 2) + 1;

        if(randomCoords.isPosEqual(&blockOff)) // Run code again if the fooPos is on the same pos as the snake
        { 
            randomCoords.x = rand()%(boardSizeX - 2) + 1;
            randomCoords.y = rand()%(boardSizeY - 2) + 1;
        }
        else //If foodPos doesn't conflict with anything the foodPos is set
        {
          foodPos.x = randomCoords.x;
          foodPos.y = randomCoords.y;
        }

    }

}

void GameMechs::getFoodPos(objPos &returnPos)
{

    // Returns the current Pos of food
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
    
}
