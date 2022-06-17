//
// Created by pablo on 15/06/22.
//

#include "LZW.h"
vector<int> LZW::encoding(string s1) {
    // cout << "Encoding\n";
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    //cout << "String\tOutput_Code\tAddition\n";
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            //cout << p << "\t" << table[p] << "\t\t"
            //   << p + c << "\t" << code << endl;
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    //cout << p << "\t" << table[p] << endl;
    output_code.push_back(table[p]);
    return output_code;
}

string LZW::decoding(vector<int> op) {
    string salida;
    //cout << "\nDecoding\n";
    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    //cout << s;
    salida += s;
    int count = 256;
    for (int i = 0; i < op.size() - 2; i++) {
        n = op[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }
        //cout << s;
        salida += s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
    return salida;
}

vector <int> LZW::string_to_vector(string str_output) {

    int n = 0;
    string temp;
    vector<int> vector_input;
    while(str_output[n]!='\0'){
        if(str_output[n] == '-'){
            int int_temp = stoi(temp);
            vector_input.push_back(int_temp);
            temp = "";
        }
        else{
            temp+=str_output[n];
        }
        if(str_output[n+1]=='\0'){
            int int_temp = stoi(temp);
            vector_input.push_back(int_temp);
            temp = "";
        }
        n++;
    }
    return vector_input;
}

void LZW::compressTofile(string fileName, string compressedFileName) {
    ifstream inputStream;
    ofstream outputStream;
    char character;
    vector <int> output_code;
    string  fileData;
    string salida_comprimida;
    outputStream.open(compressedFileName, ios::binary);
    inputStream.open(fileName, ios::binary);

    while (!inputStream.eof()) {
        character = inputStream.get();
        fileData += character;
    }

    output_code = encoding(fileData);

    for (int i = 0; i < output_code.size(); i++) {
        salida_comprimida += to_string(output_code[i]);
        if(i!= output_code.size()-1){
            salida_comprimida +="-";
        }
    }
    outputStream << salida_comprimida;
    outputStream.flush();
    outputStream.close();
}


void LZW::decompressTofile(string compressedFileName, string decompressedFileName) {
    ifstream inputStream;
    ofstream outputStream;
    char character;
    vector <int> output_code;
    string  fileData;
    string salida_descomprimida;
    outputStream.open(decompressedFileName, ios::binary);
    inputStream.open(compressedFileName, ios::binary);
    while (!inputStream.eof()) {
        character = inputStream.get();
        fileData += character;
    }
    //cout << fileData;
    salida_descomprimida = decoding(string_to_vector(fileData));
    outputStream << salida_descomprimida;
    //cout << salida_descomprimida.length();
    outputStream.flush();
    outputStream.close();
}