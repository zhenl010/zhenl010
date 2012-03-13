#ifndef SKIP_LIST_SET_H_
#define SKIP_LIST_SET_H_

#include <cstdlib>
#include <ctime>

#include "skip_list_node.h"
#include "skip_list_rand.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template <typename T>
class SkipListSet
{
public:
    // A very specific skip list type with predefined parameters
    static const int MAX_LEVEL = 10;
    static const int SKIP_LIST_PINV = 4;

    SkipListSet();
    ~SkipListSet();

    bool Insert(T);
    bool Remove();
    bool Contains();

private:
    int currLvl_;
    SkipListNode<T>* heads[MAX_LEVEL];
    int lvl_distri_[2][MAX_LEVEL];

    // Helper functions
    int RandomLvl();
    void InitRands();
    void Addnullptr();
};

template <typename T>
SkipListSet<T>::SkipListSet()
    : currLvl_(0)
{
    InitRands();
    Addnullptr();
}

template <typename T>
SkipListSet<T>::~SkipListSet()
{
    // go through level 0 nodes and delete all
    SkipListNode<T>* currNode;
    SkipListNode<T>* nextNode;

    currNode = heads[0];
    while(currNode != nullptr)
    {
        nextNode = currNode->nexts[0];
        delete currNode;
        currNode = nextNode;
    }
}

template <typename T>
bool SkipListSet<T>::Insert(T keydata)
{
    // locate the destination
    SkipListNode<T>* refNodes[MAX_LEVEL];
    SkipListNode<T>* probeNode = heads[currLvl_];
    for (int probeLvl = currLvl_; probeLvl >= 0; --probeLvl)
    {
        while ( probeNode != nullptr && probeNode->nexts[probeLvl] != nullptr && probeNode->nexts[probeLvl]->key_ < key)
        {
            probeNode = probeNode->nexts[probeLvl];
        }
        refNodes[probeLvl] =  probeNode;
    }
    if (probeNode != nullptr)
    {
        probeNode = probeNode->nexts[0];
    }

    // fail if key already exist
    if ( probeNode != nullptr && probeNode->key_ == key )
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
        SkipListNode<T>* newNode = new SkipListNode<T> (key, data, newLvl);
        for (int i=0; i<=newLvl; ++i)
        {
            if (refNodes[i] == nullptr)
            {
                // Init if nullptr
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

template <typename T>
int SkipListSet<T>::RandomLvl()
{
    int iRnd = SkipListRand();
    int iLvl = 0;
    while(iRnd > lvl_distri_[0][iLvl] && iLvl < (MAX_LEVEL-1))
    {
        ++iLvl;
    }

    return iLvl;
} 

template <typename T>
void SkipListSet<T>::InitRands()
{
    SetSkipListRandSeed(static_cast<unsigned int>(time(nullptr)));

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

template <typename T>
void SkipListSet<T>::Addnullptr()
{
    for (int i=0; i<MAX_LEVEL; ++i)
    {
        heads[i] = nullptr;
    }
}

//////////////////////////////////////////////////////////////////////////
}

#endif