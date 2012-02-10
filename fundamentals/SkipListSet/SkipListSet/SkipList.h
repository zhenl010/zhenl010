#ifndef SKIP_LIST_H_
#define SKIP_LIST_H_

#include <cstdlib>
#include <ctime>

#include "SkipListNode.h"
#include "SkipListRand.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template <typename KeyType, typename Obj>
class SkipList
{
public:
    // A very specific skip list type with predefined parameters
    static const int MAX_LEVEL = 10;
    static const int SKIP_LIST_PINV = 4;

    SkipList();
    ~SkipList();

    bool Insert(KeyType, Obj);
    bool Remove();
    bool Contains();

private:
    int currLvl_;
    SkipListNode<KeyType, Obj>* heads[MAX_LEVEL];
    int lvl_distri_[2][MAX_LEVEL];

    // Helper functions
    int RandomLvl();
    void InitRands();
    void AddNullPtr();
};

template <typename KeyType, typename Obj>
SkipList<KeyType, Obj>::SkipList()
    : currLvl_(0)
{
    InitRands();
    AddNullPtr();
}

template <typename KeyType, typename Obj>
SkipList<KeyType, Obj>::~SkipList()
{
    // go through level 0 nodes and delete all
    SkipListNode<KeyType, Obj>* currNode;
    SkipListNode<KeyType, Obj>* nextNode;

    currNode = heads[0];
    while(currNode != NULL)
    {
        nextNode = currNode->nexts[0];
        delete currNode;
        currNode = nextNode;
    }
}

template <typename KeyType, typename Obj>
bool SkipList<KeyType, Obj>::Insert(KeyType key, Obj data)
{
    // locate the destination
    SkipListNode<KeyType, Obj>* refNodes[MAX_LEVEL];
    SkipListNode<KeyType, Obj>* probeNode = heads[currLvl_];
    for (int probeLvl = currLvl_; probeLvl >= 0; --probeLvl)
    {
        while ( probeNode != NULL && probeNode->nexts[probeLvl] != NULL && probeNode->nexts[probeLvl]->key_ < key)
        {
            probeNode = probeNode->nexts[probeLvl];
        }
        refNodes[probeLvl] =  probeNode;
    }
    if (probeNode != NULL)
    {
        probeNode = probeNode->nexts[0];
    }

    // fail if key already exist
    if ( probeNode != NULL && probeNode->key_ == key )
    {
        return false;
    } 
    else
    {
        // generate new level
        int newLvl = RandomLvl();
        if (newLvl > currLvl_)
        {
            for (int incLvl = currLvl_+1; incLvl <= newLvl; ++incLvl)
            {
                refNodes[incLvl] = heads[incLvl];
            }
            currLvl_ = newLvl;
        }

        // Create new node and insert
        SkipListNode<KeyType, Obj>* newNode = new SkipListNode<KeyType, Obj> (key, data, newLvl);
        for (int i=0; i<=newLvl; ++i)
        {
            if (refNodes[i] == NULL)
            {
                // Init if NULL
                heads[i] = newNode;
            } 
            else
            {
                newNode->nexts[i] =  refNodes[i]->nexts[i];
                refNodes[i]->nexts[i] = newNode;
            }
        }

        return true;
    }
}

template <typename KeyType, typename Obj>
int SkipList<KeyType, Obj>::RandomLvl()
{
    int iRnd = SkipListRand();
    int iLvl = 0;
    while(iRnd > lvl_distri_[0][iLvl] && iLvl < (MAX_LEVEL-1))
    {
        ++iLvl;
    }

    return iLvl;
} 

template <typename KeyType, typename Obj>
void SkipList<KeyType, Obj>::InitRands()
{
    SetSkipListRandSeed(static_cast<unsigned int>(time(NULL)));

    //2147483647
    lvl_distri_[0][0] = SkipListRandMax()-SkipListRandMax()/SKIP_LIST_PINV;
    for (int i=1; i<MAX_LEVEL; ++i)
    {
        lvl_distri_[0][i] = SkipListRandMax() - (SkipListRandMax()-lvl_distri_[0][i-1])/SKIP_LIST_PINV;
    }
    for (int i=0; i<MAX_LEVEL; ++i)
    {
        lvl_distri_[1][i] = 0;
    }
}

template <typename KeyType, typename Obj>
void SkipList<KeyType, Obj>::AddNullPtr()
{
    for (int i=0; i<MAX_LEVEL; ++i)
    {
        heads[i] = NULL;
    }
}

//////////////////////////////////////////////////////////////////////////
}

#endif