

#include "Huffman.h"

#define INTERNAL_NODE_CHARACTER char(128)
#define PSEUDO_EOF char(129)
#define CHARACTER_CODE_SEPERATOR char(130)
#define HEADER_ENTRY_SEPERATOR char(131)
#define HEADER_TEXT_SEPERATOR char(132)
/**
 *
 * @param node1
 * @param node2
 * @return
 */
int Huffman::myCompartor::operator()(Node *node1, Node *node2) {
    return node1->getFrequency() > node2->getFrequency();
}
/**
 *
 * @param frequencyMap
 */
void Huffman::huffer(unordered_map<char, int> frequencyMap) {
    priority_queue <Node *, vector<Node *>, myCompartor> HufferQueue;
    string tempString;
    Node *leftNode, *rightNode, *newNode;
    for (const auto &item : frequencyMap)
        HufferQueue.push(new Node(item.first, item.second));
    HufferQueue.push(new Node(PSEUDO_EOF, 1));
    while (HufferQueue.size() != 1) {
        leftNode = HufferQueue.top();
        HufferQueue.pop();
        rightNode = HufferQueue.top();
        HufferQueue.pop();
        newNode = new Node(INTERNAL_NODE_CHARACTER, leftNode->getFrequency() + rightNode->getFrequency());
        HufferQueue.push(newNode);
        newNode->setLeft(leftNode);
        newNode->setRight(rightNode);
    }
    encodeCharacters(HufferQueue.top(), tempString);
}
/**
 *
 * @param rootNode Los Nodos que forman parte del Arbol de Huffman
 * @param codeString Asigna el valor binario correspondiente a las ramas u hojas del nodo.
 */
void Huffman::encodeCharacters(Node *rootNode, string codeString) {

    if (!rootNode)
        return;
    if (rootNode->getCharacter() != INTERNAL_NODE_CHARACTER) {
        codeMap[rootNode->getCharacter()] = codeString;

    }
    encodeCharacters(rootNode->getLeft(), codeString + "0");
    encodeCharacters(rootNode->getRight(), codeString + "1");
}
/**
 *
 * @param InputfileName ALmacena la direccion del archivo que se quiere comprimir.
 * @param OutputfileName Almacena la direccion donde se va almacenar el archivo resultante de la copmpresión.
 */
void Huffman::compressTofile(string InputfileName ,string OutputfileName) {

    char character;
    string file;
    ifstream inputStream;
    ofstream outputStream;
    outputStream.open(OutputfileName, ios::out);
    inputStream.open(InputfileName, ios::in);
    writeHeader(outputStream);
    while (inputStream.get(character))
        file += codeMap[character];
    inputStream.close();
    file += codeMap[PSEUDO_EOF];
    unsigned long remainder = (file.size() - 1) % 8;
    for (int i = 0; i < 8 - remainder; ++i)
        file += '0';
    stringstream stringStream(file);

    while (stringStream.good()) {
        bitset<8> bits;
        stringStream >> bits;
        char c = char(bits.to_ulong());
        outputStream << c;
    }


    outputStream.flush();
    outputStream.close();
}
/**
 * En este metodo se agregan los datos del nodo raiz que genera el arbol de Huffman
 * @param outputStream Este parametro apunta al archivo de dsalida en la ejecucion de la compresionm
 */
void Huffman::writeHeader(ofstream &outputStream) {
    for (const auto &item : codeMap)
        outputStream << item.first << CHARACTER_CODE_SEPERATOR << item.second << HEADER_ENTRY_SEPERATOR;
    outputStream << HEADER_TEXT_SEPERATOR;
}

void Huffman::deHuffer(string compressedFileName, string decompressedFileName) {
    char character;
    string codeString;
    ifstream inputStream;
    inputStream.open(compressedFileName, ios::in);
    readHeader(inputStream);
    while (inputStream.get(character)) {
        bitset<8> bits(character);
        codeString += bits.to_string();


    }
    Node *rootNode = buildDecodingTree(codeMap);
    decompressToFile(codeString, rootNode, decompressedFileName);


}
/**
 *
 * @param inputStream Es la varibale de tipo fstream que se usa para generar el archivo resultante de la descompresion.
 */
void Huffman::readHeader(ifstream &inputStream) {
    codeMap.clear();
    char character;
    inputStream.get(character);
    char key = character;
    while (character != HEADER_TEXT_SEPERATOR) {
        if (character == CHARACTER_CODE_SEPERATOR) {
            inputStream.get(character);
            while (character != HEADER_ENTRY_SEPERATOR) {
                codeMap[key] += character;
                inputStream.get(character);
            }
        } else
            key = character;
        inputStream.get(character);
    }
}
/**
 *
 * @param encodingMap Es el map que se usa para reconstruir el arbol de Huffman necesario para decodificar el codigo binario de Huiffman.
 * @return EL arbol de Huffman
 */
Node *Huffman::buildDecodingTree(unordered_map<char, string> encodingMap) {
    Node *rootNode = new Node(INTERNAL_NODE_CHARACTER);
    Node *previousNode;

    for (const auto &item : encodingMap) {
        previousNode = rootNode;
        Node *newNode = new Node(item.first);
        string characterCode = item.second;
        for (int i = 0; i < characterCode.size(); ++i) {
            if (characterCode[i] == '0') {
                if (i == characterCode.size() - 1)
                    previousNode->setLeft(newNode);
                else {
                    if (!previousNode->getLeft()) {
                        previousNode->setLeft(new Node(INTERNAL_NODE_CHARACTER));
                        previousNode = previousNode->getLeft();
                    } else previousNode = previousNode->getLeft();
                }
            } else {
                if (i == characterCode.size() - 1)
                    previousNode->setRight(newNode);
                else {
                    if (!previousNode->getRight()) {
                        previousNode->setRight(new Node(INTERNAL_NODE_CHARACTER));
                        previousNode = previousNode->getRight();
                    } else previousNode = previousNode->getRight();
                }
            }
        }

    }
    return rootNode;
}
/**
 *
 * @param codeString Es el string que almacena los datos del archivo que se va descomprimir.
 * @param rootNode Es la raiz del arbol que se necesita para hacer la decodificacion de Huffman.
 * @param decompressedFileName Este metodo recibe como parametros el codigo de Huffman que se almaceno en
 *
 */
void Huffman::decompressToFile(string codeString, Node *rootNode, string decompressedFileName) {
    ofstream outputStream;
    outputStream.open(decompressedFileName, ios::out);
    Node *traversingPointer = rootNode;
    for (int i = 0; i < codeString.size() + 1; ++i) {
        if (codeString[i] == '0')
            traversingPointer = traversingPointer->getLeft();
        else
            traversingPointer = traversingPointer->getRight();

        if (traversingPointer->getCharacter() != INTERNAL_NODE_CHARACTER) {
            if (traversingPointer->getCharacter() == PSEUDO_EOF)
                break;
            outputStream << traversingPointer->getCharacter();
            traversingPointer = rootNode;
        }
    }
    outputStream.flush();
    outputStream.close();

}

