#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //200 elements on the heap
    listsize = 0;                      // no valid element in the list upon startup
    arrayCapacity = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return listsize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //still need error check - what if listsize is at max cap
    // check if listsize is equal to arraycap already. If yes, at cap, don't insert
    for(int i = listsize;i>0;i--)
    {
        aList[i].setObjPos(aList[i-1]); // this will shufle all the elements towards the tial
    }

    aList[0].setObjPos(thisPos);
    listsize++;
}

void objPosArrayList::insertTail(objPos thisPos)
{

}

void objPosArrayList::removeHead()
{
    
}

void objPosArrayList::removeTail()
{

}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listsize-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    
}