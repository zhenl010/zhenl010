//////////////////////////////////////////////////////////////////////////
// Given a stream of inputs and window size, returns sliding window's minimum
// similar to http://home.tiac.net/~cri/2001/slidingmin.html (not stream)
// TODO: optimization?
//////////////////////////////////////////////////////////////////////////
#ifndef SLIDING_WINDOW_MINIMUM_H_
#define SLIDING_WINDOW_MINIMUM_H_

#include <cassert>

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

template<typename T, int WINDOW_SIZE>
class SlidingWindowMin
{
public:
    SlidingWindowMin();
    T PushBack(const T&); // add new and remove oldest
    T CurrentMin();

private:
    struct TimedData { T val_; int death_; };
    TimedData& At(int);
    void Migrate(); // make infinite stream possible;

    TimedData ring_[WINDOW_SIZE]; // fixed ring buffer
    int beginid_; // starting buffer index
    int size_; // filled size
    int last_; // last death
};

template<typename T, int WINDOW_SIZE>
SlidingWindowMin<T, WINDOW_SIZE>::SlidingWindowMin()
    : beginid_(0), size_(0), last_(0)
{
}

template<typename T, int WINDOW_SIZE>
T SlidingWindowMin<T, WINDOW_SIZE>::PushBack(const T& val)
{
    // removing all elements of A greater than or equal to x,
    for (int idx=(size_-1); idx>=0 && val<=At(idx).val_; --idx)
    {
        --size_;
    }
    // appending x to A,
    At(size_).val_ = val;
    At(size_).death_ = last_++;
    ++size_;
    // removing the initial element of A if it is being removed from the window.
    if ((last_-At(0).death_) > WINDOW_SIZE)
    {
        beginid_ = (++beginid_) % WINDOW_SIZE;
        --size_;
    }
    // infinite counter
    Migrate();
    // return current minimum
    return CurrentMin();
}

template<typename T, int WINDOW_SIZE>
inline T SlidingWindowMin<T, WINDOW_SIZE>::CurrentMin()
{
    assert(size_>0);
    return At(0).val_;
}

template<typename T, int WINDOW_SIZE>
inline typename SlidingWindowMin<T, WINDOW_SIZE>::TimedData& SlidingWindowMin<T, WINDOW_SIZE>::At(int idx)
{
    return ring_[(beginid_+idx) % WINDOW_SIZE];
}

template<typename T, int WINDOW_SIZE>
void SlidingWindowMin<T, WINDOW_SIZE>::Migrate()
{
    if (last_ == INT_MAX)
    {
        for (int idx=0; idx<size_; ++idx)
        {
            At(idx).death_ = At(idx).death_ - INT_MAX;
        }
        last_ = last_ - INT_MAX;
    }
}

//////////////////////////////////////////////////////////////////////////
}

#endif