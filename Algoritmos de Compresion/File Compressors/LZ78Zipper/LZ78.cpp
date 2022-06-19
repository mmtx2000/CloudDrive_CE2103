//
// Created by pablo on 16/06/22.
//

#include "LZ78.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>

using namespace std;

//checks if a key is stored in the map
bool inMap(unordered_map<string, int>map, string key){
    if(map.find(key)==map.end()){
        return false;
    }else{
        return true;
    }
}
//looks for the biggest value for a key in a map
int findBiggest(unordered_map<string, int> map){
    int biggest=(*map.cbegin()).second;
    for(auto it = map.cbegin();it!=map.cend();++it){
        if((*it).second>biggest){
            biggest=(*it).second;
        }
    }
    return biggest;
}
//orders the keys and key's values in two vectors so they can stay organized
auto reorderMap(unordered_map<string, int> badMap){
    vector<int> keyValues;
    vector<string> keys;
    int maxKeys = findBiggest(badMap);
    for(int i=1;i<=maxKeys;i++){
        string key="";
        int value=0;
        for(auto it = badMap.cbegin();it!=badMap.cend();++it){
            if((*it).second==i){
                key=(*it).first;
                value=(*it).second;
                break;
            }
        }
        keyValues.push_back(value);
        keys.push_back(key);

    }
    struct returns{
        vector<int> values;
        vector<string> key;
    };
    return returns {keyValues, keys};
}
//gets the lowest index a number appears in the map
int LZ78::getLowestIndex(vector<int> values, int number){
    int index=-1;
    for(int i=0;i<values.size();i++){
        if(number==values[i]){
            index=i;
            break;
        }
    }
    return index;
}
//decodes an encoded string
string LZ78::decoder(string encodedString, string dictionaryString){

    vector<char> encodedLetters;
    vector<int> encodedNumbers;
    unordered_map<string, int> dictionary;
    int i=0;
    while(i<encodedString.size()) {
        if(encodedString[i]=='}'){
            break;
        }else if(encodedString[i]=='{' || encodedString[i]==',' || encodedString[i]==':'){
            i+=1;
        }else{
            string number;
            number+=encodedString[i];
            int numberInt = stoi(number);
            encodedNumbers.push_back(numberInt);
            encodedLetters.push_back(encodedString[i+2]);
            i+=3;
        }
    }


    //process for saving in the dictionary
    i=0;
    while(i<dictionaryString.size()){
        if((dictionaryString[i]==',')&&(dictionaryString[i+1]=='}')){
            break;
        }else if(dictionaryString[i]=='{'){
            i+=1;
        }else{
            string keyGet;
            int temp=i;
            int extraStr=0;
            while(temp<dictionaryString.size()) {
                if (dictionaryString[temp] == ':') {
                    if(dictionaryString[temp-1]==','){
                        keyGet="NU";
                    }
                    extraStr+=1;
                    break;
                }else{
                    keyGet+=dictionaryString[temp];
                    extraStr+=1;
                    temp+=1;
                }
            }
            i+=extraStr;
            //for storing all int strings as int
            int valueDic;
            char currentInt=dictionaryString[i];
            int extras=0;
            int currentPosInt=i;
            string valueAsStr="";

            while(currentPosInt<dictionaryString.size()){
                if(dictionaryString[currentPosInt]==','){
                    if(dictionaryString[currentPosInt+1]=='}'){
                        extras+=1;
                    }
                    extras+=1;
                    break;
                } else {
                    valueAsStr+=dictionaryString[currentPosInt];
                    extras+=1;
                    currentPosInt++;
                }
            }
            valueDic=stoi(valueAsStr);
            dictionary[keyGet]=valueDic;
            i+=extras;
        }
    }

    i=0;
    vector<string> list;
    auto [values, keys] = reorderMap(dictionary);
    while(i<encodedNumbers.size()){
        if(encodedNumbers[i]!=0){
            vector<string> keysList = keys;
            vector<int> valueList = values;
            list.push_back(keysList[getLowestIndex(valueList,encodedNumbers[i])]);
        }
        char currentChar = encodedLetters[i];
        string charString;
        stringstream ss;
        ss<<currentChar;
        ss>>charString;
        if(charString!=" "){
            list.push_back(charString);
        }

        i++;
    }
    string decompressed;
    for(int cont=0;cont<list.size();cont++){
        decompressed+=list[cont];
    }
    return decompressed;

}
//converts the encoded string into a string
string stringDic(vector<char> letters, vector<int> numbers){
    string tempDic="{"; //creates a temporary dictionary to store values
    for(int i=0;i<numbers.size();i++){
        char currentChar=letters[i];
        string charString;
        stringstream ss;
        ss<<currentChar;
        ss>>charString;
        tempDic+=to_string(numbers[i])+":"+charString+",";
    }
    tempDic+="}";
    return tempDic;
}

auto encoding(string stringToEncode){
    int lengthString = stringToEncode.size();
    int i=0;
    int index=1;
    vector<int> encodedNumbers;
    vector<char> encodedLetters;
    string stringToSave="";
    unordered_map<string, int> dictionary;
    while(i<lengthString){
        stringToSave = stringToEncode[i];
        int indexDictionary=0;
        while(inMap(dictionary,stringToSave)){
            indexDictionary=dictionary[stringToSave];
            if(i==(lengthString-1)){
                stringToSave="";
                break;
            }
            i++;
            stringToSave=stringToSave+stringToEncode[i];
        }
        encodedNumbers.push_back(indexDictionary);
        encodedLetters.push_back(stringToSave[stringToSave.size()-1]); //this stores a char

        if(!inMap(dictionary,stringToSave)){
            dictionary[stringToSave]=index;
            index+=1;
        }
        i++;
    }

    string encodedString = stringDic(encodedLetters,encodedNumbers);
    //converts dictionary unordered map into a string format
    string dictionaryString="{";
    for(auto it = dictionary.cbegin();it!=dictionary.cend();++it){
        dictionaryString+=(*it).first+":"+to_string((*it).second)+",";
    }
    dictionaryString+="}";

    struct returns{
        string encoded;
        string dictionary;
    };
    return returns{encodedString,dictionaryString};
}

void LZ78::compressTofile(string fileName, string compressedFileName){
    ifstream inputStream;
    ofstream outputStream;
    char character;
    vector <int> output_code;
    string  fileData;
    string salida_comprimida;
    outputStream.open(compressedFileName, ios::binary);
    inputStream.open(fileName, ios::binary);
    if (outputStream.is_open()) {
        while (!inputStream.eof()) {
            character = inputStream.get();
            fileData += character;
        }
        auto [encodedString, stringDictionary]=encoding(fileData);
        salida_comprimida = encodedString;

    }
    outputStream.flush();
    outputStream.close();
}
void LZ78::decompressTofile(string compressedFileName, string decompressedFileName){
    ifstream inputStream;
    ofstream outputStream;
    char character;
    vector <int> output_code;
    string  fileData;
    outputStream.open(decompressedFileName, ios::binary);
    inputStream.open(compressedFileName, ios::binary);
    while (!inputStream.eof()) {
        character = inputStream.get();
        fileData += character;
    }
    string encodedString;
    string stringDictionary;
    bool next =false;
    for(int i=0;i<fileData.size();i++){
        if(fileData[i]=='}' && !next){
            next=true;
        }else if (fileData[i]!='}' && !next){
            encodedString+=fileData[i];
        }else if(next){
            stringDictionary+=fileData[i];
        }
    }

    string decodedString = decoder(encodedString, stringDictionary);

    outputStream << decodedString;
    //cout << salida_descomprimida.length();
    outputStream.flush();
    outputStream.close();
}