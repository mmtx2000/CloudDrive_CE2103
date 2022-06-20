//
// Created by carlos on 16/06/22.
//

#ifndef LZ78_ALGORITHM_PCRFILE_H
#define LZ78_ALGORITHM_PCRFILE_H


#include <vector>
#include <string>

using namespace std;
/* This structure holds some information about the original file, like the
   file extension, the most occurred char and the method of compression. */
typedef struct {
    unsigned char compressedChar;
    char fileExtension[4];
    int method;
} FileInfo;

/* This structure was created to suppress the truly structure, witch is vary large. */
typedef vector<pair<int, unsigned char> > BMP;

/**
  * \brief gets the extension of a given file.
  * \param fileName.
  * \return the string with the file extension.
  */
string getFileExtension (string fileName);

/**
  * \brief changes a file extension.
  * \param fileName.
  * \param newExtension.
  * \return the new file name.
  */
string changeFileExtension (string fileName, string newExtension);

/**
  * \brief Counts how many times each char occurs in a file.
  * \param fileName.
  * \param myFile - pointer to the struct that will hold the information of the file.
  * \return a vector with pairs of number of occurrences and the char.
  */
BMP generateBitMap (const char *fileName, FileInfo *myFile);


string getFileName (string fileName);


#endif //LZ78_ALGORITHM_PCRFILE_H
