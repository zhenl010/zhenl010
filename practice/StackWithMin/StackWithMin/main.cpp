#include <iostream>
#include <list>

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

template<typename T>
class StackWithMin // A wrapper class that maintains a record of the minimum element
{
public:
    StackWithMin() {}
    bool IsEmpty() { return list_.empty(); }
    void Push(const T&);
    void Pop();
    const T& Top() const;
    const T& Min() const;

private:
    // disable copy and assignment
    StackWithMin(const StackWithMin&);
    StackWithMin& operator=(const StackWithMin&);

    std::list<T> list_;
    std::list<T> mins_;
};

template<typename T>
void StackWithMin<T>::Push(const T& value)
{
    list_.push_front(value);

    if (mins_.empty() || (mins_.front()<value == false))
    {
        mins_.push_front(value);
    }
}

template<typename T>
void StackWithMin<T>::Pop()
{
    if ( (mins_.front()<list_.front()) == false )
    {
        mins_.pop_front();
    }
    list_.pop_front();
}

template<typename T>
const T& StackWithMin<T>::Top() const
{
    return list_.front();
}

template<typename T>
const T& StackWithMin<T>::Min() const
{
    return mins_.front();
}

const int STACK_ELEMENT_NUM = 20;
const int MAX_STACK_ELEMENT = 32;

template<typename T>
void CoutStackWithMin(StackWithMin<T>& instack)
{
    using namespace std;

    while (instack.IsEmpty() != true)
    {
        cout << " " << instack.Top() << ", " << instack.Min() << ";   ";
        instack.Pop();
    }
    cout << endl;
}

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char* argv)
{
    StackWithMin<int> astack;

    for (int i=0; i<STACK_ELEMENT_NUM; ++i)
    {
        astack.Push(rand()%MAX_STACK_ELEMENT); //
    }

    CoutStackWithMin<int>(astack);

    return 0;
}