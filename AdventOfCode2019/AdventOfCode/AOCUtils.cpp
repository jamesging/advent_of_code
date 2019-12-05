//
//  AOCUtils.cpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#include <istream>
#include <fstream>

#include "AOCUtils.hpp"

void AOCUtils::openAndReadFile(const std::string &fileName, std::vector<std::string> &fileContents) {
    std::filebuf fb;
    if (fb.open(fileName, std::ios::in)) {
        std::istream fileStream(&fb);
        std::string currLine;
        while(std::getline(fileStream, currLine)) {
            fileContents.push_back(currLine);
        }
        fb.close();
    }
}
