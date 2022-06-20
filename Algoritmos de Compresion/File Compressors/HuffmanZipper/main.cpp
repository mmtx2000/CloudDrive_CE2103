#include "FrequencyCounter.h"
#include "Huffman.h"

std::ifstream::pos_type filesize(const char* filename);

int main()
{
    FrequencyCounter frequencyCounter ;
    Huffman huffman;
    string workingMode;
    workingMode = "compress";
    if(workingMode == "compress")
    {
        clock_t tStart = clock();
        frequencyCounter.readFile("/home/pablo/CLionProjects/Proyecto_3/BorradorProyecto3/cmake-build-debug/prueba_1.jpg");
        huffman.huffer(frequencyCounter.getFrequencyMap());
        huffman.compressTofile("/home/pablo/CLionProjects/Proyecto_3/BorradorProyecto3/cmake-build-debug/prueba_1.jpg",
                               "/home/pablo/CLionProjects/Proyecto_3/BorradorProyecto3/cmake-build-debug/salida23.zip");

         }
    else if(workingMode == "decompress")
    {
        clock_t tStart = clock();
        huffman.deHuffer("/home/pablo/CLionProjects/Proyecto_3/BorradorProyecto3/cmake-build-debug/salida23.zip",
                         "/home/pablo/CLionProjects/Proyecto_3/BorradorProyecto3/cmake-build-debug/salida2333.jpg");

         }


    return 0;
}

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}