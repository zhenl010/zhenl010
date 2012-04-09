#ifndef CUSTOMER_CLASS_H_
#define CUSTOMER_CLASS_H_

class Customer
{
public:
    Customer(int days) : time_(days) {}

    bool Complain(int promised) { return promised < time_; }

private:
    int time_; // days needed for delivery
};

#endif