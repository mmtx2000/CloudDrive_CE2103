
#ifndef LZ78_ALGORITHM_LZ78_H
#define LZ78_ALGORITHM_LZ78_H

#include "PCRFile.h"

/**
  * \brief Compress a file using a dictionary of string occurrences.
  * \param fileName - A string that holds the file name to be compressed.
  * \param myFile - The informations about the original file.
  * \return true if the compression goes right, else otherwise.
  */
bool compressLZ78 (const char *fileName, FileInfo *myFile, const char *fileOutput);

/**
  * \brief Decompress a file using a dictionary of string occurrences.
  * \param fileName - A string that holds the file name to be compressed.
  * \param myFile - The informations about the original file.
  * \return true if the decompression goes right, else otherwise.
  */
bool decompressLZ78 (const char *fileName, FileInfo *myFile, const char *fileOutput);


#endif //LZ78_ALGORITHM_LZ78_H
