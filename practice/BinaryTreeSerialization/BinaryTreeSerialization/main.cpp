#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "binary_tree_node.h"

namespace // unnamed
{
//////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace augment_data_structure;

typedef string DataType;

class BinaryTreeSerializabler {
public:
    void SerializeBinaryTree(BinaryTreeNode<DataType>* root, ostream& outstream) {
        isnull_.clear();
        SerializeBinaryTreeRec(root, outstream);
    }

    BinaryTreeNode<DataType>* DeserializeToBinaryTree(istream& instream) {
        vector<bool>::iterator itr=isnull_.begin();
        return DeserializeToBinaryTreeRec(instream, itr);
    }

private:
    void SerializeBinaryTreeRec(BinaryTreeNode<DataType>* root, ostream& outstream) {
        if (root == NULL) {
            isnull_.push_back(true);
            return;
        }

        outstream << root->val_;
        isnull_.push_back(false);

        SerializeBinaryTreeRec(root->left, outstream);
        SerializeBinaryTreeRec(root->right, outstream);
    }

    BinaryTreeNode<DataType>* DeserializeToBinaryTreeRec(istream& instream, vector<bool>::iterator& itr) {
        bool isnull = *itr;
        ++itr;
        if (isnull == true) { return NULL; }

        DataType val;
        instream >> val;
        BinaryTreeNode<DataType>* node = new BinaryTreeNode<DataType>(val);
        node->left = DeserializeToBinaryTreeRec(instream, itr);
        node->right = DeserializeToBinaryTreeRec(instream, itr);
        return node;
    }

    vector<bool> isnull_;
};

const std::string DEFAULT_INPUT_FILENAME = "default_input.txt";
const std::string DEFAULT_OUTPUT_FILENAME = "default_output.txt";

//////////////////////////////////////////////////////////////////////////
}

int main(int argc, char** argv) {
    string inputFileName = DEFAULT_INPUT_FILENAME;
    string outputFilename = DEFAULT_OUTPUT_FILENAME;
    if (argc < 2)  {
        cout << "Usage: blah.exe filename.xxx" << endl;
    } else {
        inputFileName = argv[1];
        if (argc == 3) { outputFilename = argv[2]; }
    }
    cout << "importing from FILE:   " << inputFileName  << endl;
    cout << "SAVING RESULT TO FILE: " << outputFilename << endl;

    // read input file and process along
    ifstream inFile(inputFileName, ios::in);
    if (inFile.is_open()) {
        string line_str;
        // Read in line by line
        while (getline(inFile, line_str)) {
            stringstream line_stream(line_str);
            string text;
            line_stream >> text;
            int rownum;
            line_stream >> rownum;
            string expectedstr;
            line_stream >> expectedstr;
        }
        inFile.close();
    }

    //////////////////////////////////////////////////////////////////////////
    // more complex example:
    //////////////////////////////////////////////////////////////////////////
    class DemoType {
        int    key;
        double value;
    };

    DemoType x;
    DemoType *y = new DemoType[10];

    fstream myFile ("data.bin", ios::in | ios::out | ios::binary);

    streampos location;
    location=myFile.tellp();
    myFile.seekp (location);
    myFile.write ((char*)&x, sizeof (DemoType));
    //...
    myFile.seekg (0);
    myFile.read ((char*)y, sizeof (DemoType) * 10);

    // get length of file:
    // is.seekg (0, ios::end);
    // length = is.tellg();
    // is.seekg (0, ios::beg);

    BinaryTreeNode<DataType>* root = new BinaryTreeNode<DataType>("30");
    root->left = new BinaryTreeNode<DataType>("10");
    root->left->left = new BinaryTreeNode<DataType>("50");
    root->right = new BinaryTreeNode<DataType>("20");
    root->right->left = new BinaryTreeNode<DataType>("45");
    root->right->right = new BinaryTreeNode<DataType>("35");

    stringstream strstream;

    BinaryTreeSerializabler helper;
    helper.SerializeBinaryTree(root, strstream);

    string serizedbtstr = strstream.str();


    BinaryTreeNode<DataType>* node = helper.DeserializeToBinaryTree(strstream);

    stringstream examstrm;
    helper.SerializeBinaryTree(node, examstrm);
    string exams = examstrm.str();

    return 0;
}