//
//  puzzle6.hpp
//  AdventOfCode
//
//  Created by James Ging on 12/9/18.
//  Copyright © 2018 James Ging. All rights reserved.
//

#ifndef puzzle6_hpp
#define puzzle6_hpp

#include <string>
#include <vector>
#include <map>
#include <set>

#include "puzzle.hpp"

class puzzle6 : puzzle {
public:
    static void runPuzzle(...);
    
private:
    struct orbital_body {
        std::string name;
        std::vector<std::string> orbiting;
        std::vector<std::string> orbited_by;
        
        orbital_body() {};
        orbital_body(std::string _name): name(_name) {};
        
        bool is_orbiting(const std::string &other_body) {
            for (auto &body_name : orbiting) {
                if (body_name == other_body) {
                    return true;
                }
            }
            
            return false;
        }
        
        bool is_orbited_by(const std::string &other_body) {
            for (auto &body_name : orbited_by) {
                if (body_name == other_body) {
                    return true;
                }
            }
            
            return false;
        }

        int count_orbits(const std::map<std::string, orbital_body> &orbits) const;
        int count_orbits_until(const std::map<std::string, orbital_body> &orbits, const std::string &destination) const;
        void get_orbit_names(const std::map<std::string, orbital_body> &orbits,
                                              std::set<std::string> &acc) const;
    };
    
    void parseOrbitalBodies(const std::vector<std::string> &fileContents, std::map<std::string, orbital_body> &orbits);
    
    void runPartOne(const std::map<std::string, orbital_body> &orbits);
    void runPartTwo(const std::map<std::string, orbital_body> &orbits);
};

#endif /* puzzle6_hpp */
