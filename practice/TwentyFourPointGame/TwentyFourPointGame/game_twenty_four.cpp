#include "game_twenty_four.h"
#include "int_fraction.h"
#include "expression_tree.h"

namespace augment_data_structure
{
//////////////////////////////////////////////////////////////////////////

GameTwentyFour::GameTwentyFour(int a, int b, int c, int d)
{
    nums_[0] = a;
    nums_[1] = b;
    nums_[2] = c;
    nums_[3] = d;

    Update();
}

namespace // unnamed namespace
{
    static const IntFraction TARGET_FRACTION = IntFraction(24, 1);

    static const OpPlus      op_plus;
    static const OpMinus     op_minus;
    static const OpMultiply  op_multiply;
    static const OpDivide    op_divide;    
}

void GameTwentyFour::Update() // update answer if found
{
    const OpFunctor* optrs[4];
    optrs[0] = &op_plus;
    optrs[1] = &op_minus;
    optrs[2] = &op_multiply;
    optrs[3] = &op_divide;

    typedef ExpressionTree<IntFraction, OpFunctor> Expression;
    //typedef Merge<IntFraction, OpFunctor> ExMerge;
    Expression exprs[ACTIVE_CARD_NUM];
    for (int i=0; i<ACTIVE_CARD_NUM; ++i)
    {
        exprs[i] = Expression( IntFraction(nums_[i], 1) );
    }

    // loop i,j,k [0, 3]
    for (int i=0; i<VALID_OPERATOR_NUM; ++i) { for (int j=0; j<VALID_OPERATOR_NUM; ++j)
    { for (int k=0; k<VALID_OPERATOR_NUM; ++k) {
        // case 1:
        Expression probe_01 = Merge<IntFraction, OpFunctor>(Merge<IntFraction, OpFunctor>(exprs[0], optrs[i], exprs[1]),
            optrs[j], Merge<IntFraction, OpFunctor>(exprs[2], optrs[k], exprs[3]));
        {
            IntFraction number = probe_01.Calculate();
            number.Simplify();
            if (number == TARGET_FRACTION)
            {
                ans_ = probe_01.GetString();
                return;
            }
        }

        // case 2:
        Expression probe_02 = Merge<IntFraction, OpFunctor>(
            Merge<IntFraction, OpFunctor>(
            Merge<IntFraction, OpFunctor>(exprs[0], optrs[i], exprs[1]),
            optrs[j], exprs[2]), 
            optrs[k], exprs[3]);
        {
            IntFraction number = probe_02.Calculate();
            number.Simplify();
            if (number == TARGET_FRACTION)
            {
                ans_ = probe_02.GetString();
                return;
            }
        }

        // case 3:
        Expression probe_03 = Merge<IntFraction, OpFunctor>(
            Merge<IntFraction, OpFunctor>(exprs[0], optrs[j],
            Merge<IntFraction, OpFunctor>(exprs[1], optrs[i], exprs[2])), 
            optrs[k], exprs[3]);
        {
            IntFraction number = probe_03.Calculate();
            number.Simplify();
            if (number == TARGET_FRACTION)
            {
                ans_ = probe_03.GetString();
                return;
            }
        }

        // case 4:
        Expression probe_04 = Merge<IntFraction, OpFunctor>( exprs[0], optrs[k],
            Merge<IntFraction, OpFunctor>(
            Merge<IntFraction, OpFunctor>(exprs[1], optrs[i], exprs[2]), 
            optrs[j], exprs[3]));
        {
            IntFraction number = probe_04.Calculate();
            number.Simplify();
            if (number == TARGET_FRACTION)
            {
                ans_ = probe_04.GetString();
                return;
            }
        }

        // case 5:
        Expression probe_05 = Merge<IntFraction, OpFunctor>( exprs[0], optrs[k],
            Merge<IntFraction, OpFunctor>(exprs[1], optrs[j],
            Merge<IntFraction, OpFunctor>(exprs[2], optrs[i], exprs[3])));
        {
            IntFraction number = probe_05.Calculate();
            number.Simplify();
            if (number == TARGET_FRACTION)
            {
                ans_ = probe_05.GetString();
                return;
            }
        }
    }}}
}

//////////////////////////////////////////////////////////////////////////
}