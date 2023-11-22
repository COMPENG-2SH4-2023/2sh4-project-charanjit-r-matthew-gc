#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

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
    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
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


    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", 
    myGM->getBoardSizeX(), 
    myGM->getBoardSizeY(),
    tempPos.x, tempPos.y, tempPos.symbol);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
