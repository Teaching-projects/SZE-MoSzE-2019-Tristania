#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <string>
#include "Dir.hpp"

class File{
    std::string name;
    Dir* parent;
public:
    File(std::string, Dir*);
    std::string getName();
    Dir* getParent();
};

#endif /* File_hpp */
