//
// Created by zawawy on 12/25/18.
//

#include "HuffmanUtility.h"

#define INTERNAL_NODE_CHARACTER char(128)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(130)
#define HEADER_ENTRY_SEPERATOR char(131)
#define HEADER_TEXT_SEPERATOR char(132)
/**
 *
 * @param outputStream Es la variable fstream que se usa ára generear el archivo resultante de la compresion.
 * @param codeMap Este unordered_map se usa para codificar y almacenar los caracteres guardados en el arbol de Huffman en el archivo comprimido.
 */
void HuffmanUtility::writeHeader(ofstream &outputStream,unordered_map<char,string> codeMap) {
    for (const auto &item : codeMap)
        outputStream << item.first << CHARACTER_CODE_SEPERATOR << item.second << HEADER_ENTRY_SEPERATOR;
    outputStream << HEADER_TEXT_SEPERATOR;
}
/**
 *
 * @param inputStream es la variable de tipo fstream que se utiliza para extraer el byte array con los datos del archivo a descomprimir
 * en este metodo se extraen los datos parta reconstruir el arbol de Huffman para decodificar los datos almacenados y hacer la descompresion.
 * @return es un unordered_map que se utiliza para codificar los datos almacenados en el archivo comprimido y crear el arbol de Huffman.
 */
unordered_map<char,string> HuffmanUtility::readHeader(ifstream &inputStream) {
    //codeMap.clear();
    unordered_map<char,string> codeMap;
    char character;
    inputStream.get(character);
    char key = character;
    while(character != HEADER_TEXT_SEPERATOR){
        if(character == CHARACTER_CODE_SEPERATOR)
        {
            inputStream.get(character);
            while(character != HEADER_ENTRY_SEPERATOR)
            {
                codeMap[key] += character;
                inputStream.get(character);
            }
        }
        else
            key = character;
        inputStream.get(character);
    }
    return codeMap;
}
