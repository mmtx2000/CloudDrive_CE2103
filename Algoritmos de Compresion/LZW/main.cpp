#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <string.h>
#include <unordered_map>
#include <bits/stdc++.h>


using namespace std;
vector<int> encoding(string s1)
{
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

string decoding(vector<int> op)
{
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
    for (int i = 0; i < op.size() - 1; i++) {
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
vector<int> string_to_vector(string str_output){

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
int main() {
    string filedata;
    string entrada_original;
    string salida_comprimida;
    filedata = "WYS*WYGWYS*WYSWYSG";
    vector<int> output_code = encoding(filedata);
    for (int i = 0; i < output_code.size(); i++) {
        salida_comprimida += to_string(output_code[i]);
        if(i!= output_code.size()-1){
            salida_comprimida +="-";
        }
    }
    entrada_original = decoding(string_to_vector(salida_comprimida));

    cout << salida_comprimida;
    cout << "\n" << "\n";
    cout << entrada_original;
}
