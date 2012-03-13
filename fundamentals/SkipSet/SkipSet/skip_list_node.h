#ifndef SKIP_LIST_NODE_H_
#define SKIP_LIST_NODE_H_

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template <typename T>
class SkipListNode
{
public:
    SkipListNode() { nexts = nullptr; }
    SkipListNode(T&, int);

    SkipListNode** nexts;

    T keydata_; // key is data (or inside data)

    ~SkipListNode();

private:
    // Helper function
    void AddNullptr(int num);
};

template <typename T>
SkipListNode<T>::SkipListNode(T& keydata, int lvl)
    : keydata_(keydata)
{
    nexts = new SkipListNode<T>*[lvl+1];

    AddNullptr(lvl);
}

template <typename T>
void SkipListNode<T>::AddNullptr(int iLvl)
{
    for (int i=0; i<=iLvl; ++i)
    {
        nexts[i] = nullptr;
    }
}

template <typename T>
SkipListNode<T>::~SkipListNode()
{
    delete[] nexts;
}

//////////////////////////////////////////////////////////////////////////
}

#endif