#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.
        void updatePlayerDir();

        void movePlayer();
        // Need more actions in here:
        // - after inserting the head but before removing the tail do the following
        // - check if new head position collides with food
        // - if yes, increment the score in GM, generate new food, 
        //   and do not remove tail
        // otherwise, remove tail and move on.


        // Lastly, add self collision check
        // - if self-collided
        // set loseFlag and exitFlag both to true (though GM)
        // this will break the porgram loop and end the game

        // if ending, you need to differentiate the end game state
        // LOST - display LOST message
    

    private:
        objPosArrayList *playerPosList;   // Upgrade this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;

};

#endif