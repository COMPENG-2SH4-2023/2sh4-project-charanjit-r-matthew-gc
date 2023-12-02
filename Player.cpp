#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "MacUILib.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,
                      mainGameMechsRef->getBoardSizeY() / 2, 
                      '@');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
    
    srand(time(NULL));
    mainGameMechsRef->generateFood(playerPosList);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos()
{
    return playerPosList;
    // return the reference to the playerPos arrray list

}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic   

    // Where do I get input?? How do I check for inputs??
    //Hint 1. definitley not by calling MacUILib_getchar()!!
    //      2. coordinate with your team member who's designing gamemechism class
    //      3. there will be a method in gamemech class that collectivly checks input
    //          and stores it

    // char input = mainGameMechsRef->getInput();
    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'w':  
            if (myDir != DOWN)
                myDir = UP;
            break;

            // Add more key processing here
        
        case 's':
            if (myDir != UP)  
                myDir = DOWN;
            break;
            // Add more key processing here    
        
        case 'a': 
            if (myDir != RIGHT)  
                myDir = LEFT;
            break;

        case 'd': 
            if (myDir != LEFT)  
                myDir = RIGHT;
            break;

        default:
            break;
    }    


}

void Player::movePlayer()
{

    objPos currHead;
    playerPosList->getHeadElement(currHead);

    objPos tempFoodPos;
    // PPA3 Finite state Machine logic
    if (myDir == UP){
        currHead.y--; 
    }

    else if(myDir == DOWN){
        currHead.y++;
    }

    else if(myDir == LEFT){
        currHead.x--;
    }

    else if(myDir == RIGHT){
        currHead.x++;
    }

    if (currHead.x == mainGameMechsRef->getBoardSizeX()-1)
        currHead.x = 1;
    if (currHead.x == 0)
        currHead.x = mainGameMechsRef->getBoardSizeX()-2;
    if (currHead.y == mainGameMechsRef->getBoardSizeY()-1)
        currHead.y = 1;
    if (currHead.y == 0)
        currHead.y = mainGameMechsRef->getBoardSizeY()-2;

    // Iteration 3:
    // Check if the new head position collides with any element in the playerPosList
    for (int i = 1; i < playerPosList -> getSize(); i++)
    {

        objPos player_element;
        playerPosList -> getElement(player_element, i);


        // If yes, set both lose flag and exit flag in the gameMechanics object
        if (currHead.isPosEqual(&player_element))
        {

            // This will force the game to shut down, and trigger the different exit message with the lose flag set to true
            mainGameMechsRef -> setLoseTrue();
            mainGameMechsRef -> setExitTrue();

            // If not, carry forward with movement and food consumption detection 
        }
    }

    
    // new current head should be inserted to the head of the list
    playerPosList->insertHead(currHead);
    playerPosList->getHeadElement(currHead);
    mainGameMechsRef->getFoodPos(tempFoodPos);

    if (currHead.x == tempFoodPos.x && currHead.y == tempFoodPos.y)
    {
        mainGameMechsRef->generateFood(playerPosList);
        mainGameMechsRef->incrementScore();
    }
    else
        playerPosList->removeTail();
        
}

