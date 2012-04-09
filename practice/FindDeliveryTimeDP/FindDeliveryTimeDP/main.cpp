// 变体题是这样的，从A地发货到B地，所需要时间是某个常数x, 1 <= x <= 100, 怎么找
// 出x的准确值？
// 
// 方法是寄东西给顾客(顾客的数量不限制)．对每个顾客都承诺货物能在天数t内到达, 如果按
// 时或者提前收到货物，顾客就默认。如果迟到了，则顾客就一定会立即投诉。
// 
// 现在要求你用这个方法求出x的准确值, 使得等待的总天数最短(用最短的时间求得x),  要求
// 最多只准收到两次投诉，收到第三次投诉就告失败
#include <iostream>
#include "naive_time_tester.h"
#include "customer.h"

int main(int argc, char** argv)
{
    using namespace std;

    int DELIVER_TIME_MAX = 100;
    int ALLOWED_COMPLAINS = 2;

    // TimeTester* tester = new NaiveTimeTester(DELIVER_TIME_MAX, ALLOWED_COMPLAINS);
    // delete tester;
    NaiveTimeTester tester_one(DELIVER_TIME_MAX, ALLOWED_COMPLAINS);
    for (int i=0; i<DELIVER_TIME_MAX+1; ++i)
    {
        if (i==100)
        {
            bool debug_here = true;
        }
        Customer acustomer(i);
        tester_one.ResetTimer();
        int t = tester_one.FindTime(1, DELIVER_TIME_MAX, ALLOWED_COMPLAINS, acustomer);
        cout << i << " th test,  result:  " << t << " used time: " << tester_one.GetTimer() << endl;
    }

    return 0;
}