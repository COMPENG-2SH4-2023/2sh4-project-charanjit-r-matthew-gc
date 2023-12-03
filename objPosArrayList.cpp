#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

// Used to initialize the arrayCapacity and listSize, along with allocating an array on the heap 
objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; //200 elements on the heap
    listsize = 0;                      // no valid element in the list upon startup
    arrayCapacity = ARRAY_MAX_CAP;
}

// Deallocating the heap data members --> defense against memory leakage
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

// Returns the size of the list
int objPosArrayList::getSize()
{
    return listsize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    //still need error check - what if listsize is at max cap
    // check if listsize is equal to arraycap already. If yes, at cap, don't insert
    if (listsize != arrayCapacity)
    {
        for(int i = listsize; i > 0 ; i--)
        {
            aList[i].setObjPos(aList[i-1]); // this will shufle all the elements towards the tail
        }

        aList[0].setObjPos(thisPos);
        listsize++;
    }
    
}

// Inserting thisPos as a new objPos element to the tail of the list
void objPosArrayList::insertTail(objPos thisPos)
{
    // check if listsize is equal to arraycap already. If yes, at cap, don't insert
    if (listsize != arrayCapacity)
    {
        listsize++;
        //Adds the element at the end of the array list
        aList[listsize-1].setObjPos(thisPos);
    }
}


void objPosArrayList::removeHead()
{
        for(int i = 0;i<listsize;i++)
        {
            aList[i].setObjPos(aList[i+1]); // this will shufle all the elements towards the head
            // Doing this will overwrtie the head 
        }
        listsize--;
}

void objPosArrayList::removeTail()
{
    listsize--;
}

// Get the objPos element at the head of the list
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

// Get the objPos element at the tail of the list
void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listsize-1]);
}

// Get the n-th objPos element from the list, where n is specified by index
void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}