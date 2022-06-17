//
// Created by pablo on 15/06/22.
//
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <string.h>
#include <unordered_map>
#include <bits/stdc++.h>
#ifndef LZW_LZW_H
#define LZW_LZW_H
using namespace std;


class LZW {
public:
    void compressTofile(string fileName, string compressedFileName);
    void decompressTofile(string compressedFileName, string decompressedFileName);
    vector<int> encoding(string s1);
    string decoding(vector<int> op);
    vector<int> string_to_vector(string str_output);

};


#endif //LZW_LZW_H
