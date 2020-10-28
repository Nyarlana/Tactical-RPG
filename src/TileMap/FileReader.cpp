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
    ifstream tilemap_file ("data/tilemap.txt");
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
    else
    {
        ifstream tilemap_file2 ("../data/tilemap.txt");
        if (tilemap_file2.is_open())
        {
            while (getline (tilemap_file2,line))
            {
                for(int i=0;i<TM_X_TAB;++i)
                {
                    tab[line_index][i]=line[i];
                }
                line_index++;
            }
            tilemap_file2.close();
        }
        else
        {
            cout<<"unable to open file";
        }
    }
}

void FileReader::readFileTest()
{
    cout<<"test"<<endl;
}
