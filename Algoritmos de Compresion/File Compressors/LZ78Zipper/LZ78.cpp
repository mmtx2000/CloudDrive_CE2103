

#include "LZ78.h"
#include <math.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <map>

#include "PCRFile.h"
#include "LZ78.h"

using namespace std;
bool compressLZ78 (const char *fileName, FileInfo *myFile, const char *fileOutput) { ///////////////
    /* Open input file in binary mode */
    ifstream inputStream(fileName, ifstream::in | ifstream::binary);
    if (!inputStream.good()) return false;

    /* Open output file in binary mode */
    //changeFileExtension(fileName, "hu3").c_str()
    //changeFileExtension(fileOutput, "txt").c_str()
    ofstream outputStream(fileOutput + getFileName(fileName) + "." + "zip", ifstream::out | ifstream::binary); //////////////////
    if (!outputStream.good()) return false;

    unsigned char byte, id;
    vector<string> dict;
    string chain = "", aux = "";

    /* Inserts the empty string to the dict */
    dict.push_back(chain);

    /* Since the LZ78 will always be the last method of compression utilized, we need to save the head of information */
    outputStream.write((const char*) myFile, sizeof(FileInfo));
    cout << myFile->compressedChar << endl;
    while (inputStream.good()) {
        byte = inputStream.get();

        if (inputStream.good()) {
            /* The pseudocode can be found at Wikipedia.com */

            /* The auxiliary string is the actual chain concatenated with the read byte */
            aux = chain + static_cast<char>(byte);
            /* If this auxiliary string is found in the dict, we search for a bigger sequence */
            if (find(dict.begin(), dict.end(), aux) != dict.end())
                chain = aux;
            else {
                /* Find the position of the chain in the dict and puts writes in the output file */
                id = distance(dict.begin(), find(dict.begin(), dict.end(), chain));
                outputStream.write((const char*) &id, 1);
                outputStream.write((const char*) &byte, 1);

                /* Limits the dictionary to 256 entries */
                if (dict.size() < 256)
                    dict.push_back(aux);

                /* Reset the variables */
                chain = "";
            }
        }
    }

    inputStream.close();
    outputStream.close();

    return true;
}

bool decompressLZ78 (const char *fileName, FileInfo *myFile, const char *fileOutput) { ///////////////////////////////
    /* Open input file in binary mode */
    ifstream inputStream(fileName, ifstream::in | ifstream::binary);
    if (!inputStream.good()) return false;

    /* Open output file in binary mode */
    string extension = (myFile->method == 3) ? myFile->fileExtension : "huf";
    ofstream outputStream(fileOutput + getFileName(fileName) + "." + myFile->fileExtension, ifstream::out | ifstream::binary); ///////////////////////////
    if (!outputStream.good()) return false;

    unsigned char byte;
    vector<string> dict;
    string chain = "";

    /* In the decompression the dict is constructed again */
    dict.push_back(chain);

    /* Reads the information about the original file */
    inputStream.read((char*) myFile, sizeof(FileInfo));

    while (inputStream.good()) {
        byte = inputStream.get();

        if (inputStream.good()) {
            /* find string in the dict that corresponds to the read byte */
            if (byte < dict.size())
                outputStream.write((const char*) dict[byte].c_str(), dict[byte].size());

            /* Save the string */
            chain = dict[byte];

            /* Read the next byte */
            byte = inputStream.get();

            outputStream.write((const char*) &byte, 1);

            /* Put the chain into the dict */
            chain += static_cast<char>(byte);
            dict.push_back(chain);
        }
    }

    inputStream.close();
    outputStream.close();

    return true;
}
