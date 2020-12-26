/**@file File Reader header*/
#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>

#include "../gameManager/Parameters.h"

/**@class FileReader
@brief Used to read files*/
class FileReader
{
    public:
        /**@brief Class constructor*/
        FileReader();
        /**@brief Class destructor*/
        ~FileReader();
        /**@brief Reads the file and puts it in a char tab*/
        void readFile(char tab[X_SIZE][Y_SIZE]);
        /**@brief Temporary function, for testing*/
        void readFileTest();

    protected:

    private:

};

#endif // FILEREADER_H
