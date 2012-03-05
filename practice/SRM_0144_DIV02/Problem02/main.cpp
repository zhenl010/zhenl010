#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class BinaryCode
{
public:
    static vector<string> decode(string message);

protected:
private:
    static bool VecDecode(const vector<int>& qmsg, int initVal, vector<int>& pmsg);
};

vector<string> BinaryCode::decode(string message)
{
    vector<string> dmsgs(2, "NONE");

    // message will contain between 1 and 50 characters, inclusive.
    // Each character in message will be either '0', '1', '2', or '3'.
    size_t msglen = message.length();

    vector<int> qmsg;
    qmsg.resize(msglen);
    for (size_t i = 0; i<msglen; ++i)
    {
        stringstream sstoi(message.substr(i,1));
        if ( (sstoi >> qmsg[i]).fail() )
        {
            // input error
        }       
    }

    vector<int> pmsg;
    pmsg.resize(msglen);

    // starting with '0' case
    if ( VecDecode(qmsg, 0, pmsg) )
    {
        stringstream sstreamq;
        for (size_t i = 0; i<msglen; ++i)
        {
            sstreamq << pmsg[i];
        }
        dmsgs[0] = sstreamq.str();
    }

    // starting with '0' case
    if ( VecDecode(qmsg, 1, pmsg) )
    {
        stringstream sstreamq;
        for (size_t i = 0; i<msglen; ++i)
        {
            sstreamq << pmsg[i];
        }
        dmsgs[1] = sstreamq.str();
    }

    return dmsgs;
}

bool BinaryCode::VecDecode(const vector<int>& qmsg, int initVal, vector<int>& pmsg)
{
    pmsg[0]=initVal;
    size_t msgLen = pmsg.size();
    if (msgLen == 1)
    {
        // special case
        if (qmsg[0] == pmsg[0])
        {
            return true;
        }
        else
        {
            return false;
        }
    } 
    else
    {
        pmsg[1] = qmsg[0] - pmsg[0];
        for (size_t i = 2; i<msgLen; ++i)
        {
            pmsg[i] = qmsg[i-1] - pmsg[i-1] - pmsg[i-2];
        }

        // last item
        if ( qmsg[msgLen-1] != (pmsg[msgLen-1]+pmsg[msgLen-2]) )
        {
            return false;
        }
    }

    // 
    for (size_t i = 1; i<(pmsg.size()); ++i)
    {
        if ( pmsg[i]>1 || pmsg[i]<0 )
        {
            return false;
        }
    }

    return true;
}

int main()
{
    return 0;
}