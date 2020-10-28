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

void FileReader::readFile(char tab[TM_X_TAB][TM_Y_TAB])
{
    string line;
    int line_index=0;
    if(!ifstream tilemap_file ("data/tilemap.txt"))
    {
        if(!ifstream tilemap_file ("../data/tilemap.txt"))
        {
            cout<<"unable to open file";
        } 
    }
    if (tilemap_file.is_open())
    {
        while (getline (tilemap_file,line))
        {
            for(int i=0;i<TM_X_TAB;++i)
            {
                tab[line_index][i]=line[i];
            }
            line_index++;
        }
        tilemap_file.close();
    }
}

void FileReader::readFileTest()
{
    cout<<"test"<<endl;
}
