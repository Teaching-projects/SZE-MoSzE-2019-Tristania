//
//  File.cpp
//  Terminal
//
//  Created by Gábor Horváth on 2019. 10. 05..
//  Copyright © 2019. Gábor Horváth. All rights reserved.
//

#include "File.hpp"


File::File(std::string filename, std::string parent,std::string content) : name(filename), parent(parent) {}

std::string File::getName() { return name; }

std::string File::getParent() { return parent; }

std::string File::getContent() {return content;}

void File::setContent(std::string content){
    this->content=content;
}
