//
// Created by pablo on 16/06/22.
//

#ifndef LZ78_LZ78_H
#define LZ78_LZ78_H


#include <unordered_map>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <fstream>


using namespace std;
class LZ78 {
public:
    //bool inMap(std::unordered_map<string, int> map, std::__cxx11::basic_string<char> key);


    int getLowestIndex(std::vector<int> values, int number);

    string decoder(string encodedString, string dictionaryString);

    void compressTofile(string fileName, string compressedFileName);

    void decompressTofile(string compressedFileName, string decompressedFileName);
};


#endif //LZ78_LZ78_H
