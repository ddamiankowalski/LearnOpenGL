#ifndef GEODATA_H
#define GEODATA_H

#include <iostream>
#include <fstream>
#include <vector>

class GeoData {
public:
    unsigned int vertSideNum = 100;
    
    std::vector<float> xPositions;
    std::vector<float> zPositions;
    std::vector<float> positions3D;

    float* vecArr3D()
    {
        return positions3D.data();
    }

    void readElevation(const std::string& filePath) {
        std::fstream file;
        file.open(filePath, std::ios::in);

        if(file.is_open())
        {
            std::string el;            
            while(std::getline(file, el))
                elevations.push_back(std::stoi(el));
        }

        createXVector();
        createZVector();
        
        create3DVector();
    }

private:
    std::vector<int> elevations;

    void create3DVector()
    {
        positions3D.clear();

        for (int i = 0; i < vertSideNum; i++)
        {
            float zPos = zPositions.at(i);

            for (int j = 0; j < vertSideNum; j++)
            {
                float xPos = xPositions.at(j);
                
                positions3D.push_back(xPos);
                positions3D.push_back(0.0f);
                positions3D.push_back(zPos);

                positions3D.push_back(0.0f);
                positions3D.push_back(1.0f);
                positions3D.push_back(0.0f);

                positions3D.push_back(1.0f);
                positions3D.push_back(1.0f);
            }
        }
    }

    void createXVector()
    {
        xPositions.clear();
        float delta = 10.0f / (vertSideNum - 1);
        
        for (int i = 0; i < vertSideNum; i++)
            xPositions.push_back(-5.0f + delta * i);
    }

    void createZVector()
    {
        zPositions.clear();
        float delta = 10.0f / (vertSideNum - 1);

        for (int i = 0; i < vertSideNum; i++)
            zPositions.push_back(-5.0f + delta * i);
    }
};

#endif