#include "MovingWindowMedian.h"
#include <cassert>
#include <iostream>

MovingWindowMedian::MovingWindowMedian(const std::vector<DataType>& initvec)
: insert_index_(0), heap_center_(static_cast<IndexType>(initvec.size()/2))
{
    assert(!initvec.empty());
    circular_.resize(initvec.size());
    for (int i=0; i<static_cast<int>(initvec.size()); ++i)
    {
        circular_[i].data = initvec[i];
    }
    
    refheap_.resize(circular_.size());
    min_idx_ = heap_center_;
    max_idx_ = heap_center_;
    IndexType refheapidx = heap_center_;
    refheap_[refheapidx] = &circular_[0];
    circular_[0].heapindex = refheapidx;

    for (int i=1; i<static_cast<int>(circular_.size()); ++i)
    {
        // calculate next ref heap index
        if (refheapidx < heap_center_)
        {
            refheapidx = heap_center_ + (heap_center_ - refheapidx);
            max_idx_ = refheapidx;
        }
        else
        {
            refheapidx = heap_center_ - (refheapidx - heap_center_) - 1;
            min_idx_ = refheapidx;
        }

        refheap_[refheapidx] = &circular_[i];
        circular_[i].heapindex = refheapidx;

        DoubleHeapifyFrom(refheapidx);
    }
}

void MovingWindowMedian::PushBack(DataType value)
{
    circular_[insert_index_].data = value;
    DoubleHeapifyFrom(circular_[insert_index_].heapindex);
    insert_index_ = (insert_index_ + 1) % circular_.size();
}

MovingWindowMedian::DataType MovingWindowMedian::Median()
{
    ///@TODO: when average two integers the result might be x.5 ...
    return circular_.size()%2==1 ? refheap_[heap_center_]->data :
        (refheap_[heap_center_]->data + refheap_[heap_center_-1]->data) / 2;
}

void MovingWindowMedian::DoubleHeapifyFrom(IndexType heap_index)
{
    if (heap_index <= heap_center_)
    {
        // max-heap
        IndexType parent = MaxHeapParent(heap_index);
        if (refheap_[parent]->data < refheap_[heap_index]->data)
        {
            HeapSwap(heap_index, parent);
            DoubleHeapifyFrom(parent);
        } 
        else
        {
            IndexType child_one = MaxHeapChildOne(heap_index);
            IndexType child_two = MaxHeapChildTwo(heap_index);
            if (IsValidIndex(child_one) && IsValidIndex(child_two))
            {
                if (refheap_[child_two]->data < refheap_[child_one]->data)
                {
                    // compare with the larger child first
                    if (refheap_[heap_index]->data < refheap_[child_one]->data)
                    {
                        HeapSwap(heap_index, child_one);
                        DoubleHeapifyFrom(child_one);
                    }
                    // compare with the smaller child next
                    if (refheap_[heap_index]->data < refheap_[child_two]->data)
                    {
                        HeapSwap(heap_index, child_two);
                        DoubleHeapifyFrom(child_two);
                    }
                }
                else
                {
                    // compare with the larger child first
                    if (refheap_[heap_index]->data < refheap_[child_two]->data)
                    {
                        HeapSwap(heap_index, child_two);
                        DoubleHeapifyFrom(child_two);
                    }
                    // compare with the smaller child next
                    if (refheap_[heap_index]->data < refheap_[child_one]->data)
                    {
                        HeapSwap(heap_index, child_one);
                        DoubleHeapifyFrom(child_one);
                    }
                }
            } 
            else if ( IsValidIndex(child_one) )
            {
                // compare with the only child
                if (refheap_[heap_index]->data < refheap_[child_one]->data)
                {
                    HeapSwap(heap_index, child_one);
                    DoubleHeapifyFrom(child_one);
                }
            } 
            else if ( IsValidIndex(child_two) )
            {
                // compare with the only child
                if (refheap_[heap_index]->data < refheap_[child_two]->data)
                {
                    HeapSwap(heap_index, child_two);
                    DoubleHeapifyFrom(child_two);
                }
            } 
        }
    }

    if (heap_center_ <= heap_index)
    {
        // min-heap
        IndexType parent = MinHeapParent(heap_index);
        if (refheap_[heap_index]->data < refheap_[parent]->data)
        {
            HeapSwap(heap_index, parent);
            DoubleHeapifyFrom(parent);
        } 
        else
        {
            IndexType child_one = MinHeapChildOne(heap_index);
            IndexType child_two = MinHeapChildTwo(heap_index);
            if (IsValidIndex(child_one) && IsValidIndex(child_two))
            {
                if (refheap_[child_one]->data < refheap_[child_two]->data)
                {
                    // compare with the smaller child first
                    if (refheap_[child_one]->data < refheap_[heap_index]->data)
                    {
                        HeapSwap(heap_index, child_one);
                        DoubleHeapifyFrom(child_one);
                    }
                    // compare with the larger child next
                    if (refheap_[child_two]->data < refheap_[heap_index]->data)
                    {
                        HeapSwap(heap_index, child_two);
                        DoubleHeapifyFrom(child_two);
                    }
                }
                else
                {
                    // compare with the smaller child first
                    if (refheap_[child_two]->data < refheap_[heap_index]->data)
                    {
                        HeapSwap(heap_index, child_two);
                        DoubleHeapifyFrom(child_two);
                    }
                    // compare with the larger child next
                    if (refheap_[child_one]->data < refheap_[heap_index]->data)
                    {
                        HeapSwap(heap_index, child_one);
                        DoubleHeapifyFrom(child_one);
                    }
                }
            } 
            else if ( IsValidIndex(child_one) )
            {
                // compare with the only child
                if (refheap_[child_one]->data < refheap_[heap_index]->data)
                {
                    HeapSwap(heap_index, child_one);
                    DoubleHeapifyFrom(child_one);
                }
            } 
            else if ( IsValidIndex(child_two) )
            {
                // compare with the only child
                if (refheap_[child_two]->data < refheap_[heap_index]->data)
                {
                    HeapSwap(heap_index, child_two);
                    DoubleHeapifyFrom(child_two);
                }
            } 
        }
    } 
}

void MovingWindowMedian::HeapSwap(IndexType idxone, IndexType idxtwo)
{
    SequenceElement* reftmp = refheap_[idxone];
    refheap_[idxone] = refheap_[idxtwo];
    refheap_[idxtwo] = reftmp;
    // update the other end
    refheap_[idxone]->heapindex = idxone;
    refheap_[idxtwo]->heapindex = idxtwo;
}
