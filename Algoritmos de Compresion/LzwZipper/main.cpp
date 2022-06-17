#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <string.h>
#include <unordered_map>
#include <bits/stdc++.h>
#include "LZW.h"

using namespace std;

int main() {
    LZW lzw;
    string workingMode;
    workingMode = "decompress";
    if(workingMode == "compress")
    {
        lzw.compressTofile("/home/pablo/CLionProjects/Proyecto_3/prueba.jpg",
                               "/home/pablo/CLionProjects/Proyecto_3/salida_comprimida.txt");
    }
    else if(workingMode == "decompress")
    {
        lzw.decompressTofile("/home/pablo/CLionProjects/Proyecto_3/salida_comprimida.txt",
                           "/home/pablo/CLionProjects/Proyecto_3/salida_descomprimida.jpg");
    }
    return 0;
}
