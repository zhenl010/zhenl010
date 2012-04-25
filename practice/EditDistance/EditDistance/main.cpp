//////////////////////////////////////////////////////////////////////////
// The Levenshtein distance between two strings is defined as 
// the minimum number of edits needed to transform one string into the other,
// with the allowable edit operations being
// insertion, deletion, or substitution of a single character. 
//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <vector>

int EditDistance(const std::string& strone, const std::string& strtwo)
{
    if (strone.size() < strtwo.size())
    {
        return EditDistance(strtwo, strone);
    }

    using namespace std;
    vector<int> bufferone(strtwo.size()+1);
    vector<int> buffertwo(strtwo.size()+1);
    vector<int>* curr = &bufferone;
    vector<int>* prev = &buffertwo;
    // Init
    for (int j=0; j<=strtwo.size(); ++j)
    {
        curr->at(j) = j;
    }
    // Loop over
    for (int i=1; i<=strone.size(); ++i) // notice the shift
    {
        swap(curr, prev);
        curr->at(0) = i;
        for (int j=1; j<=strtwo.size(); ++j)
        {
            if (strone[i-1]==strtwo[j-1]) // notice the shift here!!!
            {
                curr->at(j) = prev->at(j-1);
            } 
            else
            {
                curr->at(j) = 1 + min(prev->at(j-1), min(curr->at(j-1), prev->at(j)));
            }
        }
    }

    return *(curr->rbegin());
}

int main(int argc, char** argv)
{
    using namespace std;

    string strone = "a";
    string strtwo = "";
    int distance = EditDistance(strone, strtwo);

    // input	output	expected	
    // "", ""	0	0	
    // "", "a"	1	1	
    // "b", ""	1	1	
    // "a", "a"	0	0
    // "a", "b"	1	1
    // "a", "ab"	1	1
    // "ab", "a"	1	1
    // "ab", "bc"	2	2
    // "sea", "ate"	3	3	
    // "sea", "eat"	2	2	
    // "mart", "karma"	3	3	
    // "park", "spake"	3	3	
    // "food", "money"	4	4	
    // "horse", "ros"	3	3	
    // "spartan", "part"	3	3
    // "plasma", "altruism"	6	6	
    // "kitten", "sitting"	3	3	
    // "islander", "islander"	0	0	
    // "islander", "slander"	1	1	
    // "industry", "interest"	6	6	
    // "intention", "execution"	5	5	
    // "prosperity", "properties"	4	4	
    // "algorithm", "altruistic"	6	6	

    return 0;
}