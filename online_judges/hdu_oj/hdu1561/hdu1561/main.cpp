#include <iostream>
#include "Solution.h"
// #include "SlowerSolution.h"

int main() {
    using namespace std;

    // SlowerSolution solver;
	Solution solver;
    int N, M;
    // SlowerSolution::Target targets[SlowerSolution::MAX_N];
	Solution::Target targets[Solution::MAX_N];
    cin >> N >> M;
	while(!(N==0 && M==0)) {
		for (int i=1; i<=N; ++i) { // start from line one
			cin >> targets[i].pre >> targets[i].val;
		}
		cout << solver.FindMostValue(targets, N, M) << endl;
	    cin >> N >> M;
	}
    
    return 0;
}