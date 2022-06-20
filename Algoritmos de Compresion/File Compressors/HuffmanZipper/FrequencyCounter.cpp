#include "FrequencyCounter.h"
/**
 * En ete metodo se crea la tabala de frecuencia de los caracteres del bytearray que almacena los datos del archivo
 * que se va comprimir.
 * @param fileName es la ruta del archivo que se desea comprimir
 */
void FrequencyCounter::readFile(string fileName) {
    char character;
    ifstream inputFile;

    inputFile.open(fileName, ios::in);

    while(inputFile.get(character))
        frequencyMap[character]++;



    inputFile.close();
}
/**
 *
 * @return
 */
const unordered_map<char, int> &FrequencyCounter::getFrequencyMap() const {
    return frequencyMap;
}
