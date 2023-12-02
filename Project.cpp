#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 100000
#define ASCII_ESC 27

// OOD Benefit - very limited global var declaration
//  In advance OOD, you don't even need global variables
GameMechs* myGM;
Player* myPlayer;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(30, 15);
    myPlayer = new Player(myGM);

    // Think about when to generate new food...
    //Think about whether you want to set up a debug to call te food gen routine for verification
    //remember, generateFood() requires player reference. You will need to provide it after object is instaniated

}

void GetInput(void)
{
    myGM->setInput(myGM->getInput());
}

void RunLogic(void)
{
    if (myGM->getInput() == ASCII_ESC)
        myGM->setExitTrue();
    
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos food;
    myGM->getFoodPos(food);  //Get the food pos.
    
    for(int i = 0;i<myGM->getBoardSizeY();i++)
    {
        for(int j = 0;j<myGM->getBoardSizeX();j++) 
        {
            drawn = false;
            // iterate through every element in the list
            for(int k = 0;k<playerBody->getSize();k++)
            {
                playerBody->getElement(tempBody, k);
                if(tempBody.x == j && tempBody.y == i)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue;
            // if playerBody is drawn don't draw anything below

            if(i==0||j==0||i==myGM->getBoardSizeY()-1||j==myGM->getBoardSizeX()-1)
                MacUILib_printf("#");
            else if (i == food.y && j == food.x)
                MacUILib_printf("%c", food.symbol);
            else    
                MacUILib_printf(" ");   
        }
        MacUILib_printf("\n");
    }


    MacUILib_printf("Score: %d\n", myGM->getScore());

    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    if(myGM->getLoseFlagStatus())
    {
       MacUILib_printf("You Lost :( \n"); 
       MacUILib_printf("Your Final Score!!!: %d\n", myGM->getScore());
    }
    MacUILib_uninit();
    
    // Remove heap instances
    delete myGM;
    delete myPlayer;
}
