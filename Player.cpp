#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"


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

    //For debugging purpose - insert another 4 segments
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
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

    // new current head should be inserted to the head of the list
    playerPosList->insertHead(currHead);

    playerPosList->removeTail();
}

