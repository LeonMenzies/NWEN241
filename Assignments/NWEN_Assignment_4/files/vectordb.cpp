/**
 * vectordb.cpp
 * C++ source file that should contain implementation for member functions
 * - rows()
 * - get()
 * - add()
 * - update()
 * - remove()
 * 
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Task 3)
 */

#include "vectordb.hpp"

//This function simply returns the size of the database
int VectorDbTable::rows()
{
    return db.size();
}

//This function used and int that represents the row number in the database
movie *VectorDbTable::get(int i)
{
    //Make sure the raw number is valid
    if (i > db.size())
    {
        return NULL;
    }
    return &db.at(i);
}

//This fucntion takes a movie and puts it on the end of the vector of movies
bool VectorDbTable::add(struct movie m)
{
    //Make sure the given movie is not already stored
    for (vector<movie>::iterator it = db.begin(); it != db.end(); ++it)
    {
        if (it->id == m.id)
        {
            return false;
        }
    }
    db.push_back(m);
    return true;
}

//This function updates a movie using a given id and new informationm in a movie struct
bool VectorDbTable::update(unsigned long l, struct movie m)
{
    //FiND the movie by mathing the id to l and then erase and insert
    for (vector<movie>::iterator it = db.begin(); it != db.end(); ++it)
    {
        if (it->id == l)
        {
            db.erase(it);
            db.insert(it, m);
            return true;
        }
    }
    return false;
}

//This function removes a movie given an id l
bool VectorDbTable::remove(unsigned long l)
{
    //If the movie is found erase it
    for (vector<movie>::iterator it = db.begin(); it != db.end(); ++it)
    {
        if (it->id == l)
        {
            db.erase(it);
            return true;
        }
    }
    return false;
}