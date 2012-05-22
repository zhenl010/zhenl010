#include <iostream>

class Solution {
public:
    bool isPalindrome(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if(x<0) return false;

        int digit = 1;
        int y = x;
        while(y>9) {
            ++digit;
            y /= 10;
        }
        if(digit<2) return true;

        int div = 1;
        for(int i=1; i<digit; ++i) { div *= 10; }
        while(x>9) {
            int lfd = x/div;
            int rtd = x%10;
            if(lfd != rtd) return false;
            x = (x-(x/10)*10)/10;
            div /= 10;
        }

        return true;
    }
};

int main(int argc, char** argv)
{
    Solution solver;

    int num = 10;
    bool ispal = solver.isPalindrome(num);

    return 0;
}