#pragma once

#include <iostream>
#include <istream>
#include <queue>
#include <string>
#include <vector>
#include "hashmap.h"
#include "bitstream.h"

typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

using namespace std;

struct HuffmanNode {
    int character;
    int count;
    int order;
    HuffmanNode* zero;
    HuffmanNode* one;
};

//
// This method frees the memory allocated for the Huffman tree.
//
// frees the tree using Recursive function.
void freeTree(HuffmanNode* node) {
    if (node == nullptr)
    	return;

    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}

//
// This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
//
//  first the function checks weather its a file or a string and if its a file
//  then read through the file using get() and push in to the map.
//  and also push EOF at the end of the map.
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
	char character;
	int count = 0;
	if (isFile) {
		ifbitstream inFile(filename);
		while(inFile.get(character)) {
			if (map.containsKey(character)) {
				count = map.get(character);
				map.put(character, ++count);
			} else {
				map.put(character, 1);
			}
		}
		map.put(PSEUDO_EOF, 1);
		inFile.close();
	} else {
		for (size_t i = 0; i < filename.size(); i++) {
			if (map.containsKey(filename[i])) {
				count = map.get(filename[i]);
				map.put(filename[i], ++count);
			} else {
				map.put(filename[i], 1);
			}
		}
		map.put(PSEUDO_EOF, 1);
	}
}

//
// This function builds an encoding tree from the frequency map.
//
//  using the map building the free using the foor loop.
HuffmanNode* buildEncodingTree(hashmapF &map) {
	//  the struct that has the function which orders the priority_queue
	struct CompareCount {
	    bool operator()(HuffmanNode* const& p1, HuffmanNode* const& p2) {
	    	if (p1->count == p2->count) {
	    		return p1->order > p2->order;
	    	}
	        return p1->count > p2->count;
	    }
	};
	// initializing the queue using the struct from above and the vector.
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareCount> HuffQueue;
	vector<int> keys = map.keys();
	int insertOrder = 1;
	// loop through the keys and either make the node right or left of the tree
    for (size_t i = 0; i < keys.size(); i++) {
    	HuffmanNode *node = new HuffmanNode;
    	node->character = keys.at(i);
    	node->count = map.get(keys.at(i));
    	node->zero = nullptr;
    	node->one = nullptr;
    	node->order = insertOrder;
    	HuffQueue.push(node);
    	insertOrder++;
    }

    while (HuffQueue.size() != 1) {
    	HuffmanNode *node = new HuffmanNode;
    	node->zero = HuffQueue.top();
    	HuffQueue.pop();
    	node->one = HuffQueue.top();
    	HuffQueue.pop();
    	node->count = node->zero->count + node->one->count;
    	node->character = NOT_A_CHAR;
    	node->order = insertOrder;
    	HuffQueue.push(node);
    	insertOrder++;
    }

    return HuffQueue.top();
}

//
// Recursive helper function for building the encoding map.
//
//   put everything togather so far using the Recursive function
//  to build the map. so you either go left or right depending on the
//  kye passed in.
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str, HuffmanNode* prev) {

    if (node == nullptr) {
    	if (!str.empty())
    		str.pop_back();
    	return;
    }

    str += "0";
    _buildEncodingMap(node->zero, encodingMap, str, node);
    str.pop_back();
    if (node->character != NOT_A_CHAR) {
    	encodingMap.emplace(node->character, str);
    }
    str += "1";
    _buildEncodingMap(node->one, encodingMap, str, node);
    str.pop_back();
}

//
// This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap;

    _buildEncodingMap(tree, encodingMap, "", nullptr);

    return encodingMap;
}

//
// This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
//  using the input stream we read the stream one at a time and add it to
//  result string. if makefile is true then we loop through the result
//  one at a time and wrtie it in the output stream.
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    char inputChar;
    string bitString;
    string result = "";
    int bit;

    while (input.get(inputChar)) {
    	result += encodingMap.at(int(inputChar));
    }
    result += encodingMap.at(PSEUDO_EOF);

    if (makeFile) {
	    for (size_t i = 0; i < result.size(); i++) {
	    	bit = result[i] - '0';
	    	output.writeBit(bit);
	    }
    }

    size = result.size();
    return result;
}


//
// This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
//  since we are using the tree here to decode we first check weather the
//  first bit is 0 or 1 and depending on it we go left or right all the
//  way untill the leaf with letter appears then we add it to output stream.
//  if we come accross -1 then we break out or if we see EOF.
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    string result = "";
    int bit = input.readBit();
    HuffmanNode * temp = encodingTree;

    while (bit != -1) {
    	if (bit == 0) {
    		temp = temp->zero;
    	} else if (bit == 1) {
    		temp = temp->one;
    	}

    	if (temp->character != NOT_A_CHAR && temp->character != PSEUDO_EOF) {
    		result += temp->character;
    		output.put(temp->character);
    		temp = encodingTree;
    	}

    	if (temp->character == PSEUDO_EOF) {
    		break;
    	}
    	bit = input.readBit();
    }
    return result;
}

//
// This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
//  using the code given in main create a file with .huf extension
//  and also use the encode funtion to compress it. and return it.
string compress(string filename) {
	string result;
    string targetFile = filename + ".huf";
    int size;
    HuffmanNode* tree = nullptr;
    hashmapF map;
    hashmapE encodingMap;
    ofbitstream outFile(targetFile);
    ifstream input(filename);

    buildFrequencyMap(filename, true, map);
    outFile << map;
    tree = buildEncodingTree(map);
    encodingMap = buildEncodingMap(tree);
    size = outFile.size();
    result = encode(input, encodingMap, outFile, size, true);
    freeTree(tree);
    outFile.close();
    input.close();
    return result;
}

//
// This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note this function should reverse what the compress
// function did.
//
//  using the code from main to remove the .huf and to add _unc after which
//  we can use the decode function by simply passing in the file to decode it.
string decompress(string filename) {
    string result;
    hashmapF frequencyMap;
    HuffmanNode* tree = nullptr;

    size_t pos = filename.find(".huf");
    if ((int)pos >= 0) {
        filename = filename.substr(0, pos);
    }
    pos = filename.find(".");
    string ext = filename.substr(pos, filename.length() - pos);
    filename = filename.substr(0, pos);
    ifbitstream input(filename + ext + ".huf");
    ofstream output(filename + "_unc" + ext);
    input >> frequencyMap;

    tree = buildEncodingTree(frequencyMap);
    result = decode(input, tree, output);
    freeTree(tree);

    output.close();
    input.close();
    return result;
}
