

#include "PCRFile.h"
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
string getFileExtension (string fileName) {
    string fileExtension = "", word;
    stringstream stream(fileName);

    /* divide the file name on the dots */
    while (getline(stream, word, '.'));

    /* returns the last string separated by a dot */
    return word;
}

string getFileName (string fileName){
    string word, name;
    stringstream stream(fileName);

    while(getline(stream, word, '/'));

    name = word.erase(word.find("."));

    return name;
}


string changeFileExtension (string fileName, string newExtension) {
    string fileExtension = getFileExtension(fileName);
    /* Cut the extension of the original file and add the new extension in the end */
    string name = getFileName(fileName);
    return fileName.substr(0, fileName.size() - fileExtension.size()) + name + newExtension;
}

vector<pair<int, unsigned char> > generateBitMap (const char *fileName, FileInfo *myFile) {
    unsigned char byte;
    vector<pair<int, unsigned char> > data;
    int occur[256], i;

    /* Every char occurs 0 times */
    for (i = 0; i < 256; i++)
        occur[i] = 0;

    /* Open the file in binary mode */
    ifstream file(fileName, ifstream::in | ifstream::binary);
    if (!file.good()) return data;

    /* Get every byte on the file e increment the number of occurrences */
    while (file.good()) {
        byte = file.get();
        if (file.good())
            occur[byte]++;
    }

    file.close();

    /* Put every byte with more than 0 occurrences in the vector */
    for (i = 0; i < 256; i++)
        if (occur[i] > 0)
            data.push_back(make_pair(occur[i], i));

    /* Reversely sort the vector */
    sort(data.begin(), data.end());
    reverse(data.begin(), data.end());

    /* Save some information about the file */
    myFile->compressedChar = data[0].second;
    strcpy(myFile->fileExtension, getFileExtension(fileName).c_str());

    return data;
}