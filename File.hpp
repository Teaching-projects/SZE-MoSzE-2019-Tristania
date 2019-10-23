//
//  File.hpp
//  Terminal
//
//  Created by Gábor Horváth on 2019. 10. 05..
//  Copyright © 2019. Gábor Horváth. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <string>

class File{
    std::string name;
    std::string parent;
    std::string content;
public:
    File(std::string, std::string,std::string="");
    std::string getName();
    std::string getParent();
    std::string getContent();
    void setContent(std::string);
};

#endif /* File_hpp */
