#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
// #include "objPosArrayList.h"

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

    // ***
    objPos tempPos(-1 , -1, 'o');
    myGM -> generateFood(tempPos);
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

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos); //get the player pos.

    objPos food;
    myGM->generateFood(tempPos); // Gen random pos for food
    myGM->getFoodPos(food);  //Get the food pos.
    
    for(int i = 0;i<myGM->getBoardSizeY();i++)
    {
        for(int j = 0;j<myGM->getBoardSizeX();j++) 
        {
            if (i==tempPos.y && j==tempPos.x)
                MacUILib_printf("%c", tempPos.symbol);
            else if(i==0||j==0||i==myGM->getBoardSizeY()-1||j==myGM->getBoardSizeX()-1)
                MacUILib_printf("#");
            else if (i == food.y && j == food.x)
                MacUILib_printf("%c", food.symbol);
            else    
                MacUILib_printf(" ");   
        }
        MacUILib_printf("\n");
    }


    MacUILib_printf("Score: %d\n\nBoardSize: %dx%d\nPlayer Pos: <%d, %d>\nPlayer Symbol: %c\n", 
    myGM->getScore(), 
    myGM->getBoardSizeX(), 
    myGM->getBoardSizeY(),
    tempPos.x, tempPos.y, tempPos.symbol);

    if(myGM->getLoseFlagStatus())
    {
       MacUILib_printf("You Lost :("); 
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    // Remove heap instances
    delete myGM;
    delete myPlayer;
}
