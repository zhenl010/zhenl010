#ifndef NAIVE_TIME_TESTER_H_
#define NAIVE_TIME_TESTER_H_

#include "time_tester.h"

class NaiveTimeTester : public TimeTester
{
public:
    NaiveTimeTester(int maxtime, int maxcomps) : TimeTester(maxtime, maxcomps), timer_(0) { Init(); }
    ~NaiveTimeTester();

    void ResetTimer() { timer_ = 0; }
    int FindTime(int mintime, int maxtime, int complains, Customer& someone);
    int GetTimer() { return timer_; }

private:
    struct ReqTimePlus
    {
        int req_time_;
        int choice_;
    };

    // helper functions
    void Init();
    int RequiredTime(int mintime, int maxtime, int complains);
    int SavedChoice(int mintime, int maxtime, int complains);
    void SetData(int mintime, int maxtime, int complains, const ReqTimePlus& val);

    // private data
    int timer_;
    ReqTimePlus*** data_;
};


#endif