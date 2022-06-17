//
// Created by pablo on 15/06/22.
//
#include <iostream>
#include <string.h>
#include <string>
#include <queue>
#include <bits/stdc++.h>

using namespace std;

int main() {

    string str_output;
    int n = 0;
    int m = 0;
    string temp;
    vector<int> vector_input;

    str_output = "1-12121-12-1-2-3-3434-34-3";
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

    for (int i = 0; i < vector_input.size(); i++) {
        cout << vector_input[i]<<" ";
    }


}