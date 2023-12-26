#ifndef GEODATA_H
#define GEODATA_H

#include <iostream>
#include <fstream>
#include <vector>

class GeoData {
public:
    void readElevation(const std::string& filePath) {
        std::fstream file;
        file.open(filePath, std::ios::in);

        if(file.is_open())
        {
            std::string el;
            unsigned int a = 0;
            
            while(std::getline(file, el))
            {   
                elevations.push_back(std::stoi(el));
            }
        }
    }

private:
    std::vector<int> elevations;
};

#endif