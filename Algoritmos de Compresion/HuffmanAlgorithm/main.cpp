#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

using namespace  std;

//Node del arbol
struct Node{
    char character;
    int freq;
    Node * left, * right;
};
//Funcion para asignar un nuevo nodo en el arbol
Node* getNode(char character, int freq, Node* left, Node* right){
    Node* nodo = new Node();

    nodo->character = character;
    nodo->freq = freq;
    nodo->left = left;
    nodo->right = right;
    return nodo;
}
// Objeto de comparacion qye sera usado para ordenar la pila

struct comp{
    bool operator ()(Node* i, Node * d){
        return i->freq > d->freq;
    }
};
//Revisa el arbol de Huffman y guarda los códigos en un mapa
void encode(Node * root, string str, unordered_map < char, string> & HuffmanCode){
    if (root == nullptr){
        return;
    }
    if (!root ->left && !root->right){
        HuffmanCode[root->character]=str;
    }
    encode(root->left,str+"0",HuffmanCode);
    encode(root->right, str + "1", HuffmanCode);
}
//Rervisa el arbol y decodifica los simbolos codificados
void decode(Node* root, int &index, string str){
    if (root == nullptr){
        return;
    }
    if (!root->left && !root->right){
        cout << root->character;
        return;
    }
    index++;
    if (str[index]=='0'){
        decode(root->left, index, str);
    }
    else{
        decode(root->right, index, str);
    }
}
//Crea el arbol de Huffman y decodifica todos los simbolos
void CrearArbol(string text){
    //Cuenta la cantidad de veces que aparece cada simbolo y la guarda en el mapa
    unordered_map <char, int> freq;
    for (char character: text){
        freq [character]++;
    }
    // Crea una cola de prioridadad para guardar los nodos del arbol
    priority_queue<Node *, vector <Node*>, comp>pq;
    // Agrega a la cola de prioridad los nodos de cada simbolo
    for (auto pair: freq){
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }
    //Hacer tod0  el proceso hasta que haya mas de 1 nodo en la cola
    while (pq.size() != 1){
        Node * left = pq.top(); pq.pop();
        Node * right = pq.top(); pq.pop();
        int sum = left->freq + right -> freq;
        pq.push(getNode('\0', sum,left,right));
    }
    Node * root = pq.top();
    // Imprime los codigos para cada simbolo
    unordered_map <char, string> HuffmanCode;
    encode(root, "",HuffmanCode);
    cout <<"\nEl mensaje original era: \n"<< text<<'\n';
    string str = "";
    for (char character: text){
        str += HuffmanCode [character];
    }
    cout << "\n El texto codificado es: \n"<<str<<"\n";
    int index = -1;
    cout << "\n El texto decodificado es: \n";
    while ( index <(int)str.size() - 2){
        decode(root, index,str);
    }
    cout << "\n\n\n";
};
int main() {
    cout << "\n\n\n----------------------------------------------------------------------";
    string text;
    cout << "\n\nIngrese el mensaje que desea comprimir: ";
    getline(cin, text);
    CrearArbol(text);
    cout << "\n";
    return 0;
}
