#ifndef AUGMENT_HEAP_FUNCTIONS_H_
#define AUGMENT_HEAP_FUNCTIONS_H_
#include <vector>
#include <functional> // std::hash Defined in this header

namespace augment_hash_functions
{
//////////////////////////////////////////////////////////////////////////

// boost::hash_combine
template<typename T>
void hash_combine(size_t& seed, const T& v) {
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
class VectorHash {
public:
    size_t operator()(const std::vector<T>& cmb) const {
        size_t hval = 0; // empty
        for (std::vector<int>::const_iterator itr=cmb.cbegin(); itr!=cmb.cend(); ++itr) {
            hash_combine<T>(hval, *itr);
        }
        return hval;
    }
};

//////////////////////////////////////////////////////////////////////////
}

#endif