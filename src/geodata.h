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
    std::vector<unsigned int> indices3D;

    GeoData(const std::string& filePath)
    {
        std::fstream file;
        file.open(filePath, std::ios::in);

        if(file.is_open())
        {
            std::string el;            
            while(std::getline(file, el))
                elevations.push_back(std::stoi(el));
        }

        createIndicesVector();
        createXVector();
        createZVector();
        create3DVector();
    }

    float* vecArr3D()
    {
        float* newVertices3D = new float[positions3D.size()];
        std::copy(positions3D.begin(), positions3D.end(), newVertices3D);
        
        return newVertices3D;
    }

    void fillVecArr3D(float* verticesArray) 
    {
        std::copy(positions3D.begin(), positions3D.end(), verticesArray);
    }

    unsigned int sizeOfVecArr3D()
    {
        return positions3D.size() * sizeof(float);
    }

    void fillDataIndices(unsigned int* indicesArray)
    {
        std::copy(indices3D.begin(), indices3D.end(), indicesArray);
    }

    unsigned int sizeOfIndices3D()
    {
        return indices3D.size() * sizeof(unsigned int);
    }

private:
    std::vector<int> elevations;

    void createIndicesVector()
    {
        indices3D.clear();

        for (int j = 0; j < vertSideNum - 1; j++)
        {
            for (int i = 0; i < vertSideNum - 1; i++)
            {
                unsigned int rowOffset = j * vertSideNum;

                indices3D.push_back(i + rowOffset);
                indices3D.push_back(i + 1 + rowOffset);
                indices3D.push_back(vertSideNum + i + rowOffset); 

                indices3D.push_back(vertSideNum + i + rowOffset);
                indices3D.push_back(vertSideNum + i + rowOffset + 1);
                indices3D.push_back(i + rowOffset + 1); 
            }
        }
    }

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

                positions3D.push_back(0.0f);
                positions3D.push_back(0.0f);
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