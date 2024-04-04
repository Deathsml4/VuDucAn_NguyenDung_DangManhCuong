#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "ResourceManagers.h"
#include "Map.h"
#include "PerlinNoise.h"

std::string GenerateChunk() {
    std::string result;
    const int totalPercentage = 100;
    const int zeroPercentage = 92;
    const int onePercentage = 8;

    srand(time(nullptr));

    for (int i = 0; i < CHUNK_SIZE; ++i) {
        int randNum = rand() % totalPercentage;
        if (randNum < zeroPercentage) {
            result += '0';
        }
        else if (randNum < zeroPercentage + onePercentage) {
            result += '1';
        }
    }

    return result;
}

// Adjust density for river length and threashold for water percentage
std::string GenerateChunk(int width, int height, double density, double threshold) {
    PerlinNoise perlinNoise;

    std::string map;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double value = perlinNoise.noise(x / 10.0, y / 10.0); // Adjust the divisor to change the scale of the noise
            if (value < threshold - density || (value > threshold && value < threshold + density))
                map += '1'; // River
            else
                map += '0'; // Plain
        }
    }

    return map;
}


std::string GenerateObject(std::string chunkData) {
    std::string result;
    const int totalPercentage = 100;
    const int zeroPercentage = 75;
    const int onePercentage = 5;
    const int twoPercentage = 5;
    const int threePercentage = 5;
    const int fourPercentage = 2;
    const int fivePercentage = 2;
    const int sixPercentage = 1;
    const int sevenPercentage = 5;

    srand(time(nullptr));
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        if (chunkData[i] == '0') {
            int randNum = rand() % totalPercentage;
            if (randNum < zeroPercentage) {
                result += '0';
            }
            else if (randNum < zeroPercentage + onePercentage) {
                result += '1';
            }
            else if (randNum < zeroPercentage + onePercentage + twoPercentage) {
                result += '2';
            }
            else if (randNum < zeroPercentage + onePercentage + twoPercentage + threePercentage) {
                result += '3';
            }
            else if (randNum < zeroPercentage + onePercentage + twoPercentage + threePercentage + fourPercentage) {
                result += '4';
            }
            else if (randNum < zeroPercentage + onePercentage + twoPercentage + threePercentage + fourPercentage + fivePercentage) {
                result += '5';
            }
            else if (randNum < zeroPercentage + onePercentage + twoPercentage + threePercentage + fourPercentage + fivePercentage + sixPercentage) {
                result += '6';
            }
            else {
                result += '7';
            }
        }
        else {
            result += '0';
        }
    }
    return result;
}

MapChunk::MapChunk()
{
    

    std::string data = GenerateChunk(CHUNK_UNITS, CHUNK_UNITS, 0.2, 0.01);
    std::string objectData = GenerateObject(data);

    for (int i = 0; i < CHUNK_SIZE; ++i) {
        auto texture = ResourceManagers::GetInstance()->GetTexture("Forest_Turf_Texture.png");
        plainTerrain = std::make_shared<GridPoint>(texture);
        plainTerrain->terrain = MTerrain::MTERRAIN_PLAIN;
        
        texture = ResourceManagers::GetInstance()->GetTexture("Blue_Fungus_Turf_Texture.png");
        riverTerrain = std::make_shared<GridPoint>(texture);
        riverTerrain->terrain = MTerrain::MTERRAIN_RIVER;

        texture = ResourceManagers::GetInstance()->GetTexture("Blue_Fungus_Turf_Texture.png");
        mObject = std::make_shared<MapObject>(texture);
        mObject->objectType = MObject::MOBJECT_INVALID;

        std::shared_ptr<MapObject> newMObject = mObject;
        std::shared_ptr<GridPoint> newGrid;
        
        if (data[i] == '0') newGrid = plainTerrain;
        else if (data[i] == '1') newGrid = riverTerrain;
      
        if (objectData[i] == '0') newMObject->objectType = MObject::MOBJECT_INVALID;
        else if (objectData[i] == '1') newMObject->objectType = MObject::MOBJECT_TREE;
        else if (objectData[i] == '2') newMObject->objectType = MObject::MOBJECT_BUSH;
        else if (objectData[i] == '3') newMObject->objectType = MObject::MOBJECT_GRASS;
        else if (objectData[i] == '4') newMObject->objectType = MObject::MOBJECT_CROP;
        else if (objectData[i] == '5') newMObject->objectType = MObject::MOBJECT_DEADBUSH;
        else if (objectData[i] == '6') newMObject->objectType = MObject::MOBJECT_CHESS;
        else if (objectData[i] == '7') newMObject->objectType = MObject::MOBJECT_ROCK;
       
        newGrid->gridNumber = i;
        grids.push_back(newGrid);

        if (newMObject != NULL) {
            newMObject->gridNumber = i;
            objects.push_back(newMObject);
        }
        
    }
}

void MapChunk::Draw(SDL_Renderer* renderer)
{
    for (auto it : grids)
    {
        it->Draw(renderer);
    }
    for (auto it : objects) 
    {
        it->Draw(renderer);
    }
}

Map::Map() {
    h = 3;
    v = 3;
    std::shared_ptr<MapChunk> newMapChunk = std::make_shared<MapChunk>();
    chunks.push_back(newMapChunk);
}

void Map::Draw(SDL_Renderer* renderer)
{
    for (auto it : chunks)
    {
        it->Draw(renderer);
    }
}

GridPoint::GridPoint()
{
 }

GridPoint::GridPoint(std::shared_ptr<TextureManager> texture)
{

}

void GridPoint::Draw(SDL_Renderer* renderer)
{
    if(terrain == MTerrain::MTERRAIN_PLAIN) texture = ResourceManagers::GetInstance()->GetTexture("Forest_Turf_Texture.png");
    else texture = ResourceManagers::GetInstance()->GetTexture("Ship_Graveyard_Terrain_Texture.png");
    //Get2DPosition();
    if (texture != nullptr)
    {
        texture->Render(GRID_UNITS * (gridNumber % CHUNK_UNITS), GRID_UNITS * (gridNumber / CHUNK_UNITS), GRID_UNITS, GRID_UNITS, 0, m_flip);
    }
}
