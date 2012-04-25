#include <iostream>
#include <vector>
#include <string>

namespace // unnamed
{
    using namespace std;

    class Solution
    {
    public:
        vector<string> GenerateParentheses(int n)
        {
            vector<string> results;
            string cmb(2*n, '\n');
            GenerateParentheses(results, n, cmb, 0, 0, 0);
            return results;
        }

    private:
        void GenerateParentheses(vector<string>& results, int lvl, string& cmb, int idx, int nlf, int nrt)
        {
            if (nrt == lvl)
            {
                results.push_back(cmb);
                return;
            }

            if (nlf > nrt)
            {
                cmb[idx] = ')';
                GenerateParentheses(results, lvl, cmb, idx+1, nlf, nrt+1);
            }

            if (nlf < lvl)
            {
                cmb[idx] = '(';
                GenerateParentheses(results, lvl, cmb, idx+1, nlf+1, nrt);
            }
        }
    };
}


int main(int argc, char** argv)
{
    Solution solver;

    vector<string> parentheses = solver.GenerateParentheses(3);

    return 0;
}