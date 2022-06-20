
#ifndef LZ78_ALGORITHM_HANDLER_H
#define LZ78_ALGORITHM_HANDLER_H

#define COMPRESS   1
#define METHOD 3

#include <iostream>
#include <string.h>
#include <fstream>

#include "PCRFile.h"

class Handler {
private:
    static Handler *instance;

public:
    /**
     * ALlows compress a file just having the rute
     * @param fileRute
     * @return
     */
    bool compress(char fileRute[100], char outputRute[100]);


    /**
     * ALlows decompress a file just having the rute
     * @param fileRute
     * @return
     */
    bool decompress(char fileRute[100], char outputRute[100]);


    /**
     *
     * @return
     */
    static Handler* getInstance();
};


#endif //LZ78_ALGORITHM_HANDLER_H
