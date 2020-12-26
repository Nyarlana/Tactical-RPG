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

void FileReader::readFile(char tab[X_SIZE][Y_SIZE])
{
    string line;
    int line_index=0;
    ifstream tilemap_file ("data/tilemap.txt");
    if (tilemap_file.is_open())
    {
        while (getline (tilemap_file,line))
        {
            // cout<<(line_index+1)<<" - ";
            for(int i=0;i<X_SIZE;++i)
            {
                tab[i][line_index]=line[i];
                // cout<<tab[line_index][i];
            }
            // cout<<endl;
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
                for(int i=0;i<X_SIZE;++i)
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
