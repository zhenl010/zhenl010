#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long AnyComboNum(int choices, int blanks);
long long UniqueComboNum(int choices, int blanks);
long long UniqueSortedComboNum(int choices, int blanks);
long long SortedComboNum(int choices, int blanks);

class Rule
{
public:
    Rule() {}
    Rule(string ruleStr)
    {
        stringstream strStream(ruleStr);
        char nameCh = '\0';
        for ( strStream >> noskipws >> nameCh; nameCh != ':'; strStream >> noskipws >> nameCh)
        {
            name_ += nameCh;
        }
        strStream >> skipws >> choices_;
        strStream >> skipws >> blanks_;
        char logicCh = '\0';
        strStream >> skipws >> logicCh;
        isSorted_ = logicCh == 'T' || logicCh == 't';
        strStream >> skipws >> logicCh;
        isUnique_ = logicCh == 'T' || logicCh == 't';

        UpdateOdds();
    }

    string Name() const { return name_; }
    long long Combos() const { return combos_; }

private:
    string name_;
    int choices_;
    int blanks_;
    bool isSorted_;
    bool isUnique_;
    long long combos_;

    void UpdateOdds()
    {
        if (isUnique_)
        {
            if (isSorted_)
            {
                combos_ = UniqueSortedComboNum(choices_, blanks_);
            } 
            else
            {
                combos_ = UniqueComboNum(choices_, blanks_);
            }
        } 
        else
        {
            if (isSorted_)
            {
                combos_ = SortedComboNum(choices_, blanks_);
            } 
            else
            {
                // no restriction case
                combos_ = AnyComboNum(choices_, blanks_);
            }
        }
    }
};

long long AnyComboNum(int choices, int blanks)
{
    long long combos = 1;
    for (int i=0; i<blanks; ++i)
    {
        combos *= choices;
    }
    return combos;
}

long long UniqueComboNum(int choices, int blanks)
{
    long long combos = 1;
    long long newChoices = choices;
    for (int i=0; i<blanks; ++i)
    {
        combos *= newChoices;
        --newChoices;
    }
    return combos;
}

long long SortedComboNum(int choices, int blanks)
{
    // dynamic programming
    vector< vector<long long> > comboTable;
    comboTable.resize(choices);
    for (int i=0; i<choices; ++i)
    {
        comboTable[i].resize(blanks);
    }

    for (int j=0; j<blanks; ++j)
    {
        comboTable[0][j] = 1;
    }

    for (int i=0; i<choices; ++i)
    {
        comboTable[i][0] = i+1;
    }

    for (int j=1; j<blanks; ++j)
    {
        for (int i=1; i<choices; ++i)
        {
            // init from one choices case
            comboTable[i][j]=1;

            for (int k=0; k<i; ++k)
            {
                comboTable[i][j] += comboTable[i-k][j-1];
            }
        }
    }

    return comboTable[choices-1][blanks-1];
}

long long UniqueSortedComboNum(int choices, int blanks)
{
    long long combos = 1;
    long long newChoices = choices;
    for (int i=0; i<blanks; ++i)
    {
        combos *= newChoices;
        --newChoices;
    }
    for (int i=2; i<blanks+1; ++i)
    {
        combos /= i;
    }
    return combos;
}

bool IsBetterRule(const Rule &ruleOne, const Rule &ruleTwo)
{
    if ( ruleOne.Combos() < ruleTwo.Combos() )
    {
        return true;
    } 
    else if (ruleOne.Combos() > ruleTwo.Combos())
    {
        return false;
    }
    else // tie breaker
    {
        return ruleOne.Name() < ruleTwo.Name();
    }
}

class Lottery
{
public:
    static vector <string> sortByOdds(vector <string> rules);

private:
};

vector <string> Lottery::sortByOdds(vector <string> rules)
{
    vector <Rule> lottery_rules(rules.size());
    for (size_t i=0; i<rules.size(); ++i)
    {
        lottery_rules[i] = Rule(rules[i]);
    }
    sort (lottery_rules.begin(), lottery_rules.end(), IsBetterRule);

    vector <string> sortedRules(rules.size());
    for (size_t i=0; i<rules.size(); ++i)
    {
        sortedRules[i] = lottery_rules[i].Name();
    }

    return sortedRules;
}

int main()
{
    string ruleStr00[] = {"PICK ANY TWO: 10 2 F F"
        ,"PICK TWO IN ORDER: 10 2 T F"
        ,"PICK TWO DIFFERENT: 10 2 F T"
        ,"PICK TWO LIMITED: 10 2 T T"};

    string ruleStr01[] = {"INDIGO: 93 8 T F",
        "ORANGE: 29 8 F T",
        "VIOLET: 76 6 F F",
        "BLUE: 100 8 T T",
        "RED: 99 8 T T",
        "GREEN: 78 6 F T",
        "YELLOW: 75 6 F F"};

    size_t ruleCount = sizeof(ruleStr00) / sizeof(ruleStr00[0]);

    vector <string> ruleStrings(ruleCount);
    for (size_t i=0; i<ruleCount; ++i)
    {
        ruleStrings[i] = ruleStr00[i];
    }

    vector <string> sorted_rules;
    sorted_rules = Lottery::sortByOdds(ruleStrings);

    return 0;
}