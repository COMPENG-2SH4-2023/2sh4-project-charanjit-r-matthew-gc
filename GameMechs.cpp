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
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\n';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;    
    boardSizeY = boardY;

    foodPos.setObjPos(-1,-1,'o');
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
    //chekc x and y against 0 and boardSizeX/Y
    //remeber, in objPos class you have an isPosEqual() method. Use this instead of comparing element by element
    //for your convencince
}

void GameMechs::getFoodPos(objPos &returnPos)
{

}
