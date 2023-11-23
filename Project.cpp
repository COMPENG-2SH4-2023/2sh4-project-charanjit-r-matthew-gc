#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000
#define ASCII_ESC 27

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
    
    for(int i = 0;i<myGM->getBoardSizeY();i++)
    {
        for(int j = 0;j<myGM->getBoardSizeX();j++) 
        {
            if (i==tempPos.y && j==tempPos.x)
                MacUILib_printf("%c", tempPos.symbol);
            else if(i==0||j==0||i==myGM->getBoardSizeY()-1||j==myGM->getBoardSizeX()-1)
                MacUILib_printf("#"); 
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

    delete myGM;
    delete myPlayer;
}
