#include <iostream>
#include <list>
#include <vector>

std::vector<unsigned int> PrimeFactors(unsigned int x) {
    std::vector<unsigned int> factors;
    if (x==0 || x==1) { 
        factors.push_back(x);
        return factors;
    }

    unsigned int num = 2;
    while (num <= x) {
        if (x%num==0) {
            x /= num;
            factors.push_back(num);
        } else {
            ++num;
        }
    }

    return factors;
}

int main(int argc, char** argv) {
    std::vector<unsigned int> fastors = PrimeFactors(12);
    return 0;
}