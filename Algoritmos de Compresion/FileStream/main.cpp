#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream file;
    ofstream  copy_file;
    file.open("/home/pablo/CLionProjects/BorradorProyecto3/cmake-build-debug/copia_prueba.zip");
    //copy_file;
    copy_file.open("/home/pablo/CLionProjects/BorradorProyecto3/prueba.jpg");

    copy_file << file.rdbuf();
    if (!copy_file.is_open()){
        cout << "Error del archivo" << endl;
        return 1;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
