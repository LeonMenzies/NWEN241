/**
 * vectordb.hpp
 * C++ header file that should contain declaration for
 * - VectorDbTable class
 * 
 * You need to modify this file to declare VectorDbTable class 
 * as specified in the hand-out (Task 2)
 */

#include <vector>
#include "abstractdb.hpp"

using namespace std;
using namespace nwen;

//Inherit the abstarct data base class including all the pure virtual functions
class VectorDbTable : public AbstractDbTable
{
    //A vector for soring each movie struct
    vector<movie> db;

    //The pure vurtual functions inherited from AbstactDbTable
public:
    int rows();
    movie *get(int i);
    bool add(struct movie m);
    bool update(unsigned long l, struct movie m);
    bool remove(unsigned long l);
};