

#include "Handler.h"



int main() {
    Handler lz78;
    string workingMode;
    workingMode = "compress";
    if (workingMode == "compress") {
        lz78.compress("/home/pablo/CLionProjects/Proyecto_3/prueba.jpg",
                   "/home/pablo/CLionProjects/Proyecto_3/");

    }
    else if (workingMode == "decompress") {
    lz78.decompress("/home/pablo/CLionProjects/Proyecto_3/prueba.zip",
                 "/home/pablo/CLionProjects/Proyecto_3/");
    }
    return 0;
}

