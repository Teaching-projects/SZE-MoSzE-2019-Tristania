#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <string>
#include "Node.hpp"

class File : public Node{
public:
    File(std::string, Node*);
};

#endif /* File_hpp */
