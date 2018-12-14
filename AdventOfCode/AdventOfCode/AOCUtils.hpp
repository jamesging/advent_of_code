//
//  AOCUtils.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef AOCUtils_hpp
#define AOCUtils_hpp

#include <stdio.h>
#include <string>
#include <vector>

class AOCUtils {
public:
    static void openAndReadFile(const std::string &fileName, std::vector<std::string> &fileContents);
};

#endif /* AOCUtils_hpp */
