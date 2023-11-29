#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //200 elements on the heap
    sizeList = 0;                      // no valid element in the list upon startup
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //still need error check - what if sizeList is at max cap
    // check if sizeList is equal to arraycap already. If yes, at cap, don't insert
    if (sizeList != sizeArray)
    {
        for(int i = sizeList;i>0;i--)
        {
            aList[i].setObjPos(aList[i-1]); // this will shufle all the elements towards the tail
        }

        aList[0].setObjPos(thisPos);
        sizeList++;
    }
    
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList != sizeArray)
    {
        sizeList++;
        aList[sizeList-1].setObjPos(thisPos);
    }
}

void objPosArrayList::removeHead()
{
        for(int i = 0;i<sizeList;i++)
        {
            aList[i].setObjPos(aList[i+1]); // this will shufle all the elements towards the head
        }
        sizeList--;
}

void objPosArrayList::removeTail()
{
    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}