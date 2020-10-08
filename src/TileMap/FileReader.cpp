#include "FileReader.h"
#include "TileMap.h"
#include <iostream>
#include <fstream>

using namespace std;

FileReader::FileReader()
{

}

FileReader::~FileReader()
{

}

void FileReader::readFile(char tab[10][10])
{
    string line;
    int line_index=0;
    ifstream tilemap_file ("src/tilemap.txt");
    if (tilemap_file.is_open())
    {
        while (getline (tilemap_file,line))
        {
            for(int i=0;i<=9;++i)
            {
                tab[line_index][i]=line[i];
            }
            line_index++;
        }
        tilemap_file.close();

    }

    else cout << "Unable to open file";
}

void FileReader::readFileTest()
{
    cout<<"test"<<endl;
}
