/**
 * abstractdb.cpp
 * C++ source file that should contain implementation for member functions
 * - loadCSV()
 * - saveCSV()
 * 
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Tasks 4 and 5)
 */

#include "abstractdb.hpp"
#include "vectordb.hpp"

//This function takes a file name as a string and saves all the movies as a csv file
bool AbstractDbTable::saveCSV(string s)
{
    //Open the file and emptie it
    ofstream fsOut(s, ios::trunc);

    //If the file opening failed
    if (!fsOut.is_open())
    {
        return false;
    }

    for (int i = 0; i < rows(); i++)
    {
        movie *m = get(i);

        //Write to fsOut
        fsOut << m->id << ",\"" << m->title << "\"," << m->year << ",\"" << m->director << "\"" << endl;

        //Check for errors
        if (!fsOut.good())
        {
            return false;
        }
    }

    fsOut.close();
    return true;
}

bool AbstractDbTable::loadCSV(string s)
{
    //Open the file for reading
    ifstream fsIn(s);

    //Check the file was opened correctly
    if (!fsIn.is_open())
    {
        return false;
    }

    string line;
    string cell;
    stringstream lineStream;

    while (getline(fsIn, line))
    {
        string inputs[4];
        lineStream.clear();
        lineStream.str(line);
        //Read each lines and split using the , delimiter
        int count = 0;
        while (getline(lineStream, cell, ','))
        {
            inputs[count] = cell;
            count++;
        }

        //Make sure that all 4 element were present to construct the table
        if (count < 4)
        {
            return false;
        }
        //Make a new movie object
        movie m;

        //Convert and assign each value to the m movie
        m.id = stoul(inputs[0], nullptr, 10);
        strcpy(m.title, inputs[1].c_str());
        m.year = stoul(inputs[2], nullptr, 10);
        strcpy(m.director, inputs[3].c_str());

        //Finally add it to the data base using the add fucntion
        add(m);
    }

    //Close if all was succesful and return true
    fsIn.close();
    return true;
}