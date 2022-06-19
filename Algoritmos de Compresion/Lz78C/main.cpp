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
int getLowestIndex(vector<int> values, int number){
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
auto getTheNumber(string chain, int position, string iden){
    string number;
    int numberVal;
    int lenNumber=0;
    if(iden=="encode"){
        for(int i=position;i<chain.size();i++){
            if(chain[i]==':'){
                break;
            }else{
                number+=chain[i];
                lenNumber+=1;
            }
        }
    }else if(iden=="dic"){
        for(int i=position;i<chain.size();i++){
            if(chain[i]==','){
                break;
            }else{
                number+=chain[i];
                lenNumber+=1;
            }
        }
    }
    numberVal=stoi(number);

    struct returns{
        int Number;
        int lennumber;
    };

    return returns {numberVal, lenNumber};


}
auto getKey(string chain, int position){
    string key;
    int sizeKey=0;
    for(int i=position;i<chain.size();i++) {
        if (chain[i] == ':') {
            if ((chain[i - 1] == '{') or (chain[i - 1] == ',')) {
                key = "NU";
            }
            break;
        }else if(chain[i]==','){
            sizeKey+=1;
        }else{
            key+=chain[i];
            sizeKey+=1;
        }
    }
    struct returns{
        string Key;
        int size;
    };
    return returns {key,sizeKey};
}

string decoder(string encodedString, string dictionaryString){

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
            auto [numberInt,jumpNum] = getTheNumber(encodedString,i,"encode");
            encodedNumbers.push_back(numberInt);
            encodedLetters.push_back(encodedString[i+jumpNum+1]);
            i+=jumpNum+2;
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
            int temp=i;
            auto [key, lent] = getKey(dictionaryString,i);
            i+=lent+1;

            //for storing all int strings as int
            auto [valueDic, jump]= getTheNumber(dictionaryString,i,"dic");
            dictionary[key]=valueDic;
            i+=jump;
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



int main() {

    string stringToEncode;

    stringToEncode="ABRACADABRARABARABARAASCASCAAASAS";

    //encoded string
    auto [encodedString, dictionaryString]=encoding(stringToEncode);
    cout << "Encoded string value:\n"+encodedString+"\nDictionary:\n"+dictionaryString << endl;

    //decoded message
    string decodedString = decoder(encodedString, dictionaryString);

    cout << "\ndecoded string: "+decodedString<< endl;

    return 0;
}
