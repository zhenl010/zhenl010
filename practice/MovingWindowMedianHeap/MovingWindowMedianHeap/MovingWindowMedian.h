//////////////////////////////////////////////////////////////////////////
// class designed to solve The median of a moving window problem
//////////////////////////////////////////////////////////////////////////
#ifndef MOVING_WINDOW_MEDIAN_H_
#define MOVING_WINDOW_MEDIAN_H_

#include <vector>

class MovingWindowMedian
{
public:
    typedef int DataType;
    MovingWindowMedian(const std::vector<DataType>&);

    void PushBack(DataType);
    DataType Median();

private:
    // disable copy and assignment:
    MovingWindowMedian(const MovingWindowMedian&);
    MovingWindowMedian& operator=(const MovingWindowMedian&);

    typedef int IndexType;
    struct SequenceElement
    {
        DataType data;
        IndexType heapindex;
    };

    // helper functions:
    void DoubleHeapifyFrom(IndexType idx);
    void HeapSwap(IndexType idxone, IndexType idxtwo);
    bool IsValidIndex(IndexType idx);
    IndexType MaxHeapChildOne(IndexType idx);
    IndexType MaxHeapChildTwo(IndexType idx);
    IndexType MaxHeapParent(IndexType idx);
    IndexType MinHeapChildOne(IndexType idx);
    IndexType MinHeapChildTwo(IndexType idx);
    IndexType MinHeapParent(IndexType idx);

    // private data:
    IndexType min_idx_;
    IndexType max_idx_;
    std::vector<SequenceElement> circular_;
    IndexType insert_index_;
    std::vector<SequenceElement*> refheap_;
    IndexType heap_center_;
};

inline bool MovingWindowMedian::IsValidIndex(IndexType idx)
{
    return min_idx_ <= idx && idx <= max_idx_;
}
inline MovingWindowMedian::IndexType MovingWindowMedian::MaxHeapChildOne(MovingWindowMedian::IndexType idx)
{
    return heap_center_ - (heap_center_-idx) * 2 - 1;
}
inline MovingWindowMedian::IndexType MovingWindowMedian::MaxHeapChildTwo(MovingWindowMedian::IndexType idx)
{
    return heap_center_ - (heap_center_-idx) * 2 - 2;
}
inline MovingWindowMedian::IndexType MovingWindowMedian::MaxHeapParent(MovingWindowMedian::IndexType idx)
{
    return heap_center_ - (heap_center_-idx - 1) / 2;
}
inline MovingWindowMedian::IndexType MovingWindowMedian::MinHeapChildOne(MovingWindowMedian::IndexType idx)
{
    return heap_center_ + (idx - heap_center_) * 2 + 1;
}
inline MovingWindowMedian::IndexType MovingWindowMedian::MinHeapChildTwo(MovingWindowMedian::IndexType idx)
{
    return heap_center_ + (idx - heap_center_) * 2 + 2;
}
inline MovingWindowMedian::IndexType MovingWindowMedian::MinHeapParent(IndexType idx)
{
    return heap_center_ + (idx - heap_center_ - 1) / 2;
}

#endif