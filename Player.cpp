#include "Player.h"
#include "GameMechs.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX() / 2,
                        mainGameMechsRef->getBoardSizeY() / 2, 
                        '@');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    // PPA3 Finite state Machine logic
    if (myDir == UP){
        playerPos.y--; 
    }

    else if(myDir == DOWN){
        playerPos.y++;
    }

    else if(myDir == LEFT){
        playerPos.x--;
    }

    else if(myDir == RIGHT){
        playerPos.x++;
    }

    // clearInput();
}

