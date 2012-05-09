#include <iostream>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    int longestValidParentheses(const string& str) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return longestValidParentheses(str, 0, str.size()-1);
    }

private:
    int longestValidParentheses(const string& str, int lfi, int rti)
    {
        while (lfi<str.size() && str[lfi]==')') ++lfi; // minor optimization
        while (rti>lfi && str[rti]=='(') --rti; // minor optimization

        int maxleng = 0;
        stack<int> recs;
        stack<int> last;
        last.push(0);
        while (lfi<=rti)
        {
            char ch = str[lfi];
            if(str[lfi] == '(')
            {
                recs.push(lfi);
                last.push(0);
            }
            else if(str[lfi] == ')')
            {
                if (recs.empty()) // invalid
                {
                    last.top() = 0;
                } 
                else
                { // valid parentheses
                    last.pop();
                    last.top() += lfi-recs.top()+1;
                    maxleng = max(maxleng, last.top());
                    recs.pop();
                }
            }
            ++lfi;
        }

        return maxleng;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    string str = "()()(()"; // ))))())

    int pareleng = solver.longestValidParentheses(str);

    return 0;
}