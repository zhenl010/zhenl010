#ifndef SKIP_LIST_NODE_H_
#define SKIP_LIST_NODE_H_

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template <typename KeyType, typename Obj>
class SkipListNode
{
public:
    SkipListNode() { nexts = NULL; }
    SkipListNode(KeyType&, Obj&, int);

    SkipListNode** nexts;

    KeyType key_;
    Obj data_;

    ~SkipListNode();

private:
    // Helper function
    void AddNullPtr(int num);
};

template <typename KeyType, typename Obj>
SkipListNode<KeyType, Obj>::SkipListNode(KeyType& key, Obj& data, int lvl)
    : key_(key), data_(data)
{
    // lvl starts from zero
    nexts = new SkipListNode<KeyType, Obj>*[lvl+1];

    AddNullPtr(lvl);
}

template <typename KeyType, typename Obj>
void SkipListNode<KeyType, Obj>::AddNullPtr(int iLvl)
{
    for (int i=0; i<=iLvl; ++i)
    {
        nexts[i] = NULL;
    }
}

template <typename KeyType, typename Obj>
SkipListNode<KeyType, Obj>::~SkipListNode()
{
    delete[] nexts;
}

//////////////////////////////////////////////////////////////////////////
}

#endif