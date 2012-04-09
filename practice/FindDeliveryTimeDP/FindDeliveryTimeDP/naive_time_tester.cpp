#include "naive_time_tester.h"
#include <climits>
#include <algorithm>
// #include "boost/multi_array.hpp"
#include "customer.h"

NaiveTimeTester::~NaiveTimeTester()
{
    // release memory:
    for (int i=0; i<MAX_COMPLAINS_; ++i)
    {
        for (int j=0; j<MAX_TIME_; ++j)
        {
            delete [] data_[i][j];
        }
        delete[] data_[i];
    }
    delete[] data_;
}

//////////////////////////////////////////////////////////////////////////
// returns the desired time on road
//////////////////////////////////////////////////////////////////////////
int NaiveTimeTester::FindTime(int mintime, int maxtime, int complains, Customer& customer)
{
    if (maxtime < mintime)
    {
        return mintime; // choice?
    }

    if (complains == 1) // base case
    {
        for (int probe=maxtime-1; probe>=mintime; --probe)
        {
            timer_ += probe;
            if (customer.Complain(probe))
            {
                return probe+1; // found
            }
        }
        return mintime; // if never complained
    }

    int x = SavedChoice( mintime, maxtime, complains);
    timer_ += x; // keep counting time consumed!

    if (customer.Complain(x)) // delivered late
    {
        return FindTime(x+1, maxtime, complains-1, customer);
    } 
    else
    {
        return FindTime(mintime, x, complains, customer); // include x here
    }
}

void NaiveTimeTester::Init()
{
    // allocate memory:
    data_ = new ReqTimePlus**[MAX_COMPLAINS_];
    for (int i=0; i<MAX_COMPLAINS_; ++i)
    {
        data_[i] = new ReqTimePlus*[MAX_TIME_];
        for (int j=0; j<MAX_TIME_; ++j)
        {
            data_[i][j] = new ReqTimePlus[j+1];
        }
    }

    // prepare base cases (m=1)
    for (int n=MAX_TIME_; !(n<1); --n)
    {
        ReqTimePlus record = { 0, INT_MAX };
        SetData(n, n, 1, record);
        for (int l=n-1; !(l<1); --l)
        {
            ReqTimePlus curr = { RequiredTime(l+1,n,1)+l, l };
            SetData(l, n, 1, curr);
        }
    }

    // prepare cases (m>=2)
    for (int m=2; m<=MAX_COMPLAINS_; ++m)
    {
        for (int l=1, n=l; l<=MAX_TIME_; ++l)
        {
            ReqTimePlus record = { n-1, n-1 }; // 
            SetData(n, n, m, record);
        }

        for (int diff=0; diff<MAX_TIME_; ++diff)
        {
            for (int l=1, n=l+diff; l<=(MAX_TIME_-diff); ++l, ++n)
            {
                int req_time = INT_MAX;
                // central comparison here:
                for (int x=l; x<n; ++x)
                {
                    int curr_time = x + std::max(RequiredTime(l,x,m), RequiredTime(x+1,n,m-1));
                    if (curr_time < req_time)
                    {
                        ReqTimePlus curr = { curr_time, x };
                        SetData(l, n, m, curr);
                        req_time = curr_time;
                    }
                }
            }
        }
    }

    int req_time = RequiredTime(1, MAX_TIME_, MAX_COMPLAINS_);
}

int NaiveTimeTester::RequiredTime(int mintime, int maxtime, int complains)
{
    if (maxtime < mintime)
    {
        return 0; //INT_MAX;
    }

    // notice there's some shifts
    return data_[complains-1][maxtime-1][maxtime-mintime].req_time_;
}

int NaiveTimeTester::SavedChoice(int mintime, int maxtime, int complains)    
{
    return data_[complains-1][maxtime-1][maxtime-mintime].choice_;
}

void NaiveTimeTester::SetData(int mintime, int maxtime, int complains, const ReqTimePlus& val)
{
    data_[complains-1][maxtime-1][maxtime-mintime] = val;
}