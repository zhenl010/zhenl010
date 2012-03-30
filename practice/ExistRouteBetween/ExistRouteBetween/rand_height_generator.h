#ifndef RAND_HEIGHT_GENERATOR_H_
#define RAND_HEIGHT_GENERATOR_H_

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
class VertexHeight
{
public:
    static VertexHeight& Instance();

    int RandomHeight(); // in range [1, MAX_HEIGHT] inclusive

protected:
    // the eighth Mersenne prime, 2**31−1
    static const int LCG_PRIME_M = 2147483647;
    static const int LCG_CONST_A = 16807;
    static const int LCG_CONST_Q = LCG_PRIME_M / LCG_CONST_A;
    static const int LCG_CONST_R = LCG_PRIME_M % LCG_CONST_A;

private:
    VertexHeight();
    ~VertexHeight();

    // not copyable:
    VertexHeight(VertexHeight&);
    VertexHeight& operator=(const VertexHeight&);

    // helper functions
    void InitRands();
    int VertexListRand(); // in range [1, LCG_PRIME_M] inclusive
    void SetVertexListrand_seed_(int newSeed);
    int VertexListRandMax();
    static void Clear();

    // private data:
    int rand_seed_;
    int lvl_distri_[VERTEX_LIST_HEIGHT];
    static VertexHeight* instance_;
};

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>* VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::instance_ = nullptr;

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>& VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::Instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>;
    }

    return *instance_;
}

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
int VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::RandomHeight()
{
    int iRnd = VertexListRand();
    int iLvl = 0;
    while( (iLvl<VERTEX_LIST_HEIGHT-1) && (lvl_distri_[iLvl]<iRnd) )
    {
        ++iLvl;
    }

    return iLvl+1;
}

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::VertexHeight()
: rand_seed_(1)
{
    InitRands();

    atexit(&Clear);
}

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::~VertexHeight()
{
}

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
void VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::InitRands()
{
    lvl_distri_[0] = VertexListRandMax()-VertexListRandMax()/VERTEX_LIST_PINV;
    for (int i=1; i<VERTEX_LIST_HEIGHT; ++i)
    {
        lvl_distri_[i] = VertexListRandMax() - (VertexListRandMax()-lvl_distri_[i-1])/VERTEX_LIST_PINV;
    }
}

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
int VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::VertexListRand()
{
    rand_seed_ = LCG_CONST_A * (rand_seed_ % LCG_CONST_Q) - LCG_CONST_R * (rand_seed_ / LCG_CONST_Q);

    if (rand_seed_ <= 0)
    {
        rand_seed_ += LCG_PRIME_M;
    }

    return rand_seed_;
}

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
void VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::SetVertexListrand_seed_(int newSeed)
{
    rand_seed_ = newSeed;
}

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
int VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::VertexListRandMax()
{
    return LCG_PRIME_M;
}

template<int VERTEX_LIST_HEIGHT, int VERTEX_LIST_PINV>
void VertexHeight<VERTEX_LIST_HEIGHT, VERTEX_LIST_PINV>::Clear()
{
    delete instance_;
    instance_ = nullptr;
}

//////////////////////////////////////////////////////////////////////////
}

#endif