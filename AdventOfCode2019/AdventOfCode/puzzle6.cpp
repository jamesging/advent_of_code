#include "puzzle6.hpp"
#include "AOCUtils.hpp"
#include <math.h>

int puzzle6::orbital_body::count_orbits(const std::map<std::string, orbital_body> &orbits) const {
    size_t count = orbiting.size();
    for (auto &other : orbiting) {
        if (orbits.find(other) == orbits.end()) {
            printf("Missing an orbit! %s is supposed to orbit %s\n", name.c_str(), other.c_str());
        } else {
            count += orbits.at(other).count_orbits(orbits);
        }
    }
    return (int)count;
}

int puzzle6::orbital_body::count_orbits_until(const std::map<std::string, orbital_body> &orbits, const std::string &destination) const {
    if (name == destination) {
        return 1;
    }
    size_t count = 0;
    for (auto &other : orbiting) {
        if (orbits.find(other) == orbits.end()) {
            printf("Missing an orbit! %s is supposed to orbit %s\n", name.c_str(), other.c_str());
        } else {
            int count_from_path = orbits.at(other).count_orbits_until(orbits, destination);
            if (count_from_path > 0) {
                count += count_from_path + 1;
            }
        }
    }
    return (int)count;
}

void puzzle6::orbital_body::get_orbit_names(const std::map<std::string, orbital_body> &orbits,
                                                             std::set<std::string> &acc) const {
    for(auto &orbit_name : orbiting) {
        if (acc.find(orbit_name) != acc.end()) {
            continue;
        }
        acc.insert(orbit_name);
        if (orbits.find(orbit_name) == orbits.end()) {
            printf("Missing an orbit! %s is supposed to orbit %s\n", name.c_str(), orbit_name.c_str());
        } else {
            orbits.at(orbit_name).get_orbit_names(orbits, acc);
        }
    }
}

void puzzle6::parseOrbitalBodies(const std::vector<std::string> &fileContents, std::map<std::string, orbital_body> &orbits) {
    for (auto &line : fileContents) {
        std::vector<std::string> orbit_map;
        orbit_map.push_back(line.substr(0, line.find_first_of(')')));
        orbit_map.push_back(line.substr(line.find_first_of(')')+1));
        if (orbits.find(orbit_map[1]) == orbits.end()) {
            orbits[orbit_map[1]] = orbital_body(orbit_map[1]);
        }
        if (orbits.find(orbit_map[0]) == orbits.end()) {
            orbits[orbit_map[0]] = orbital_body(orbit_map[0]);
        }
        if (orbits[orbit_map[1]].is_orbiting(orbit_map[0])) {
            printf("Duplicate orbit encountered: %s is already orbiting %s\n", orbit_map[1].c_str(), orbit_map[0].c_str());
        }
        if (orbits[orbit_map[0]].is_orbited_by(orbit_map[1])) {
            printf("Duplicate orbit encountered: %s is already orbited by %s\n", orbit_map[0].c_str(), orbit_map[1].c_str());
        }
        orbits[orbit_map[1]].orbiting.push_back(orbit_map[0]);
        orbits[orbit_map[0]].orbited_by.push_back(orbit_map[1]);
    }
}

void puzzle6::runPartOne(const std::map<std::string, orbital_body> &orbits) {
    int total_count = 0;
    for (auto &orbit_data : orbits) {
        total_count += orbit_data.second.count_orbits(orbits);
    }
    printf("Got %d total orbits\n", total_count);
}

void puzzle6::runPartTwo(const std::map<std::string, orbital_body> &orbits) {
    if (orbits.find("YOU") == orbits.end()) {
        printf("Can't find myself on a map\n");
        return;
    }
    if (orbits.find("SAN") == orbits.end()) {
        printf("Can't find Santa on the map\n");
        return;
    }
    std::set<std::string> my_orbits;
    orbits.at("YOU").get_orbit_names(orbits, my_orbits);
    
    std::set<std::string> santa_orbits;
    orbits.at("SAN").get_orbit_names(orbits, santa_orbits);
    
    int min_dist = INT_MAX;
    for (auto &my_orbit_name : my_orbits) {
        if (santa_orbits.find(my_orbit_name) != santa_orbits.end()) {
//            printf("found a common orbit at %s\n", my_orbit_name.c_str());
            int santa_distance = orbits.at("SAN").count_orbits_until(orbits, my_orbit_name) - 2;
            int my_distance = orbits.at("YOU").count_orbits_until(orbits, my_orbit_name) - 2;
//            printf("Distance to destination for Santa: %d, for me: %d, total: %d\n", santa_distance, my_distance, santa_distance+my_distance);
            if (santa_distance+my_distance < min_dist) {
                min_dist = santa_distance+my_distance;
            }
        }
    }
    printf("Minimum distance to santa is %d\n", min_dist);
}

void puzzle6::runPuzzle(...) {
    puzzle6 puzzle;
    std::vector<std::string> fileContents;
    AOCUtils::openAndReadFile("input_data/puzzle6_input.txt", fileContents);
    
    std::map<std::string, orbital_body> orbits;
    puzzle.parseOrbitalBodies(fileContents, orbits);
    
    puzzle.runPartOne(orbits);
    puzzle.runPartTwo(orbits);
}
