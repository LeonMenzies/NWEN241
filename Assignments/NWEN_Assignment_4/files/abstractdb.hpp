/**
 * abstractdb.hpp
 * C++ header file that should contain declaration for
 * - struct movie (given)
 * - AbstractDbTable abstract class
 * 
 * You need to modify this file to declare AbstractDbTable abstract class 
 * as specified in the hand-out (Task 1)
 */

#ifndef __ABSTRACT_DB_HPP__
#define __ABSTRACT_DB_HPP__

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstring>

namespace nwen
{
    //Struct to store the informationa bout each movie
    struct movie
    {
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };
}

using namespace std;
using namespace nwen;

//Abstract class for representing a database table
class AbstractDbTable
{
public:
    //Pure virtual functions
    virtual int rows() = 0;
    virtual movie *get(int i) = 0;
    virtual bool add(struct movie m) = 0;
    virtual bool update(unsigned long l, struct movie m) = 0;
    virtual bool remove(unsigned long l) = 0;

    //Functions for loading and saving
    bool loadCSV(string s);
    bool saveCSV(string s);
};

#endif /* __ABSTRACT_DB_HPP__ */
