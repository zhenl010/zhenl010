#ifndef TIME_TESTER_H_
#define TIME_TESTER_H_

class Customer;
class TimeTester
{
public:
    TimeTester(int maxtime, int maxcomps) : MAX_TIME_(maxtime), MAX_COMPLAINS_(maxcomps) {}
    virtual ~TimeTester() {}

    virtual int FindTime(int mintime, int maxtime, int complains, Customer& someone) = 0;

protected:
    const int MAX_TIME_;
    const int MAX_COMPLAINS_;
};

#endif