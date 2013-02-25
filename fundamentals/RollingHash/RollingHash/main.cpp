#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

namespace {
//////////////////////////////////////////////////////////////////////////

// std::unordered_map
// template < class Key,                                    // unordered_map::key_type
// class T,                                      // unordered_map::mapped_type
// class Hash = hash<Key>,                       // unordered_map::hasher
// class Pred = equal_to<Key>,                   // unordered_map::key_equal
// class Alloc = allocator< pair<const Key,T> >  // unordered_map::allocator_type
// > class unordered_map;

using namespace std;

template<typename T>
struct SeedHash {
    void operator()(std::size_t& seed, const T& t) const {
        std::hash<T> hashter;
        seed ^= hashter(t) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
};

template< typename T, class Shash >
class VectorHash {
public:
    size_t operator()(const std::vector<T>& kvec) const {
        size_t seed = 0;
        Shash shasher;
        for (size_t i=0; i<kvec.size(); ++i) {
            shasher(seed, kvec[i]);
        }
        return seed;
    }
};

// std hash-map with customized hash function
template <class T>
inline void combineHash(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

class PairHash {
public:
    size_t operator()(const std::pair<int, int> &k) const{
        // return k.first * 100 + k.second;
        size_t seed = 0;
        combineHash(seed, k.first);
        combineHash(seed, k.second);
        return seed;
    }
};

// Another way is to do std::hash function specialization:
// namespace std {
// //////////////////////////////////////////////////////////////////////////
// template<typename S, typename T> struct hash<pair<S, T>> {
//     inline size_t operator()(const pair<S, T> & v) const {
//         size_t seed = 0;
//         ::combineHash(seed, v.first);
//         ::combineHash(seed, v.second);
//         return seed;
//     }
// };
// //////////////////////////////////////////////////////////////////////////
// }

//////////////////////////////////////////////////////////////////////////
}


int main(int argc, char** argv) {
    // You don't need to define the equal predicate since operator== is defined for std::pair
    // unordered_map<pair<int, int>, int, PairHash, PairEquals> myMap;

    std::unordered_map<std::pair<int,int>, int, PairHash> pair_map;

    std::unordered_map< std::vector<char>, int, VectorHash<char, SeedHash<char> > > vec_map;
    std::vector<char> vec(5, 'a');
    vec_map[vec] = 1;

    return 0;
}