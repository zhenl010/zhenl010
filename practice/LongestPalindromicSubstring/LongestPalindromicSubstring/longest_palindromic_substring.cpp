#include "longest_palindromic_substring.h"
#include <string>

namespace
{
//////////////////////////////////////////////////////////////////////////

class RecBase
{
public:
    RecBase() {}
    RecBase(int n) : exts_(n, 0), cnt_(0), rtedge_(0) {}

    int At(int i) const { return exts_[i]; }
    void Set(int i, int extd) { exts_[i]=extd; }
    int Size() const { return exts_.size(); }
    int LpIdx() const;

    virtual int Left(int idx) const = 0;
    virtual int Right(int idx) const = 0;

    int PredInit(int rti, int lfi, int edge) const { return (edge > rti) ? std::min(edge-rti, At(lfi)) : 0; }
    int Mirror(int rti) const { return Left(cnt_) + Right(cnt_) - rti; }
    void SetCtr(int cnt, int rtedge) { cnt_=cnt; rtedge_=rtedge; }

    int cnt_; // center of covering palindrome
    int rtedge_; // right most covered

private:
    std::vector<int> exts_;
};

class EvenRec : public RecBase
{
public:
    EvenRec(const std::string& str) : RecBase(str.size()) {} // -1?
    int Left(int idx) const;
    int Right(int idx) const;
};

class OddRec : public RecBase
{
public:
    OddRec(const std::string& str) : RecBase(str.size()) {}
    int Left(int idx) const;
    int Right(int idx) const;
};

int RecBase::LpIdx() const
{
    int longest = 0;
    int lidx = 0;
    for (int i=0; i<Size(); ++i)
    {
        if (At(i) > longest)
        {
            lidx = i;
            longest = At(i);
        }
    }
    return lidx;
}

int EvenRec::Left(int idx) const
{
    return idx - At(idx) + 1;
}

int EvenRec::Right(int idx) const
{
    return idx + At(idx);
}

int OddRec::Left(int idx) const
{
    return idx - At(idx);
}

int OddRec::Right(int idx) const
{
    return idx + At(idx);
}

void UpdateRec(RecBase& recd, int idx, int lfi,
    RecBase* ctrptr, const std::string& str)
{
    int rtedge = ctrptr->rtedge_;
    int extd = recd.PredInit(idx, lfi, rtedge);
    recd.Set(idx, extd);
    int rt = recd.Right(idx);
    if (rtedge <= rt) // edge crossed?
    {
        int lf = recd.Left(idx);
        while (--lf>=0 && ++rt<str.size() && str[lf]==str[rt])
        {
            ++extd;
        }
        recd.Set(idx, extd);

        if (extd>0 && recd.Right(idx)>rtedge)
        {
            recd.SetCtr(idx, rtedge);
            ctrptr = &recd;
        }
    }
}

//////////////////////////////////////////////////////////////////////////
}

std::string LpsSolver::LongestPalindrome(const std::string& str)
{
    using namespace std;
    if (str.empty()) return string();

    OddRec oddrec(str);
    EvenRec evenrec(str);

    RecBase* ctrptr = &oddrec;
    for (int i=1; i<str.size(); ++i)
    {
        UpdateRec(evenrec, i-1, ctrptr->Mirror(i), ctrptr, str);
        UpdateRec(oddrec, i, ctrptr->Mirror(i), ctrptr, str);
    }

    int evenidx = evenrec.LpIdx();
    int oddidx = oddrec.LpIdx();

    return (evenrec.Right(evenidx)-evenrec.Left(evenidx)) > (oddrec.Right(oddidx)-oddrec.Left(oddidx)) ? 
        str.substr(evenrec.Left(evenidx), evenrec.Right(evenidx)-evenrec.Left(evenidx)+1) :
    str.substr(oddrec.Left(oddidx), oddrec.Right(oddidx)-oddrec.Left(oddidx)+1);
}