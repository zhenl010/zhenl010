#ifndef MAXIMAL_RECTANGLE_H_
#define MAXIMAL_RECTANGLE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

namespace maximal_rectangle
{
//////////////////////////////////////////////////////////////////////////

template<typename T>
class Histogram
{
public:
    Histogram() {} // raw without any data
    Histogram(const std::vector<T>& hights)  { hights_ = hights; UpdateMaximalRect(); }

    static const int HEADER_LINE_NUM = 3;
    // Take care that every time read from file the old data get lost
    bool ReadFromFile(const std::string& filename);
    bool WriteToFile(const std::string& filename) const;

    T max_rect_area() const { return max_rect_area_; }
    typename std::vector<T>::size_type max_rect_start_index() const { return max_rect_start_index_; }
    typename std::vector<T>::size_type max_rect_end_index() const {return max_rect_end_index_; }
    T max_rect_height() const { return max_rect_height_; }

private:
    Histogram(const Histogram&); // = delete;
    Histogram& operator=(const Histogram&); // = delete;

    // Helper functions
    void InitArea() { max_rect_area_ = static_cast<T> (0); }
    T Area(typename std::vector<T>::size_type, typename std::vector<T>::size_type, T);
    void UpdateArea(typename std::vector<T>::size_type, typename std::vector<T>::size_type, T);
    void UpdateMaximalRect();

    // maximal rectangle:
    typename std::vector<T>::size_type max_rect_start_index_;
    typename std::vector<T>::size_type max_rect_end_index_;
    T max_rect_height_;
    T max_rect_area_;

    std::vector<T> hights_; // defines histogram by heights
};

template<typename T>
bool Histogram<T>::ReadFromFile(const std::string& filename)
{
    using namespace std;
    hights_.clear();

    ifstream inFile(filename, ifstream::in);
    if (inFile.is_open())
    {
        string line_str;
        // skip header lines
        for (int i=0; i<HEADER_LINE_NUM && getline(inFile, line_str); ++i);
        while (getline(inFile, line_str))
        {
            // delim ','
            for (string::size_type i=0; i<line_str.size(); ++i)
            {
                if (line_str[i] == ',')
                {
                    line_str[i] = ' ';
                }
            }

            stringstream line_stream(line_str);
            int value_in;
            while (line_stream >> value_in)
            {
                hights_.push_back(value_in);
            }

            line_str.clear();
        }

        inFile.close();
    }

    UpdateMaximalRect();

    return true;
}

template<typename T>
bool Histogram<T>::WriteToFile(const std::string& filename) const
{
    using namespace std;

    ofstream outfile(filename);
    if (outfile.is_open())
    {
        outfile << "Histogram with maximal rect of size: " << max_rect_area() << endl;
        outfile << "Maximal Rectangle from " << max_rect_start_index() << " to " << max_rect_end_index() << endl;
        outfile << "Maximal Rectangle height: "<< max_rect_height() << endl;

        std::vector<T>::const_iterator itor = hights_.begin();
        outfile << (*itor);
        for (++itor; itor!=hights_.end(); ++itor)
        {
            outfile << ", " << *itor;
        }

        outfile.close();
    }

    return false;
}

template<typename T>
T Histogram<T>::Area(typename std::vector<T>::size_type idx_small, typename std::vector<T>::size_type idx_large, T height)
{
    return height * (idx_large-idx_small+1);
}

template<typename T>
void Histogram<T>::UpdateArea(typename std::vector<T>::size_type idx_small, typename std::vector<T>::size_type idx_large, T height)
{
    if (max_rect_area_ < Area(idx_small, idx_large, height))
    {
        max_rect_area_ = Area(idx_small, idx_large, height);
        max_rect_start_index_ = idx_small;
        max_rect_end_index_ = idx_large;
        max_rect_height_ = height;
    }
}

template<typename T>
void Histogram<T>::UpdateMaximalRect()
{
    using namespace std;
    typedef std::vector<T>::size_type IndexType;
    struct RectCorner { IndexType index; T h; };

    T max_area = static_cast<T> (0);
    stack<RectCorner> corners;
    for (vector<T>::size_type idx=0; idx<hights_.size(); ++idx)
    {
        RectCorner new_corner;
        new_corner.index = idx;
        new_corner.h = hights_[idx];

        if (corners.empty())
        {
            corners.push(new_corner);
        }
        else
        {
            while (corners.empty() != true && new_corner.h < corners.top().h)
            {
                UpdateArea(corners.top().index, new_corner.index-1, corners.top().h);
                new_corner.index = corners.top().index;
                corners.pop();
            }

            if (corners.empty() || corners.top().h < new_corner.h)
            {
                corners.push(new_corner);
            } 
        }
    }

    // finish processing
    RectCorner last_corner;
    last_corner.index = hights_.size()-1;
    last_corner.h = hights_[last_corner.index];
    while (corners.empty() != true)
    {
        UpdateArea(corners.top().index, last_corner.index, corners.top().h);
        corners.pop();
    }
}

//////////////////////////////////////////////////////////////////////////
}

#endif