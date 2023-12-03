#include "GameMechs.h"
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"

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

// Used to initialize the game-mechanics related parameters
GameMechs::GameMechs(int boardX, int boardY)
{
    input = '\n';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;    //Given board size
    boardSizeY = boardY;
    foodPos.setObjPos(-1,-1,'o');
}

// Destructor to deallocate all the heap data members
GameMechs::~GameMechs()
{

}

// Getter of the exit flag
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

// Getter of the lose flag
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

// To collect ASCII character inputs
char GameMechs::getInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input;
}

// Board dimensions:
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

// Setter of the exit flag
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

// Setter of the lose flag
void GameMechs::setLoseTrue()
{
    loseFlag = true;
}

// To set the most recently collected ASCII character inputs
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

// To clear the most recently collected ASCII character input from the field
void GameMechs::clearInput()
{
    input = '\n';
}

// Getter method for the game score
int GameMechs::getScore()
{
    return score;
}

// Increment the score by one, every time food is collected
void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    // generate random x and y coord, and make sure they are NOT border or blockOff pos.
    // check x and y against 0 and boardSizeX/Y
    // remember, in objPos class you have an isPosEqual() method. Use this instead of comparing element by element
    // for your convencince
    
    // Declare Variables
    objPos randomCoords;
    objPos tempBody;
    blockOff->getHeadElement(tempBody);
    bool samePos;
    
    // Keep generating new coordinates until a valid position is found, EX. that is within boarders
    while (foodPos.x < 1 || foodPos.y < 1 ||  foodPos.x >= (boardSizeX - 1) || foodPos.y >= (boardSizeY - 1) 
           || (tempBody.x == foodPos.x && tempBody.y == foodPos.y)) 
    {
        //The while conditions allows the while to run if food is not on the board
        //After food is collect we should set foodPos to -1,-1 again to run this function again
        // to randomly generate coordinates
        randomCoords.x = rand()%(boardSizeX - 2) + 1;
        randomCoords.y = rand()%(boardSizeY - 2) + 1;

        // The following checks if the random coordinates generated conflict with any blocked positions
        samePos = false;
        for(int i = 0;i<blockOff->getSize();i++)
        {
            blockOff->getElement(tempBody, i);
            if(randomCoords.isPosEqual(&tempBody))
            {
                // Exiting the loop if the positions are the same
                samePos == true;
                continue;
            }
        }

        // New coordinates are generated if there is a conflict or overlapping with player element
        if(samePos)
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

    // Returns the current position of the food
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
    
}
