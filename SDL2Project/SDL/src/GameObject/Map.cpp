#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

#include "GameObject/TextureManager.h"
#include "GameObject/Sprite2D.h"
#include "ResourceManagers.h"
#include "Map.h"

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

std::string GenerateObject(std::string chunkData) {
    std::string result;
    const int totalPercentage = 100;
    const int zeroPercentage = 60;
    const int onePercentage = 9;
    const int twoPercentage = 8;
    const int threePercentage = 5;
    const int fourPercentage = 2;
    const int fivePercentage = 5;
    const int sixPercentage = 2;
    const int sevenPercentage = 8;

    srand(time(nullptr));
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        if (chunkData[i] == 1) {
            int randNum = rand() % totalPercentage;
            if (randNum < onePercentage) {
                result += '1';
            }
            else if (randNum < onePercentage + twoPercentage) {
                result += '2';
            }
            else if (randNum < onePercentage + twoPercentage + threePercentage) {
                result += '3';
            }
            else if (randNum < onePercentage + twoPercentage + threePercentage + fourPercentage) {
                result += '4';
            }
            else if (randNum < onePercentage + twoPercentage + threePercentage + fourPercentage + fivePercentage) {
                result += '5';
            }
            else if (randNum < onePercentage + twoPercentage + threePercentage + fourPercentage + fivePercentage + sixPercentage) {
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
    riverTerrain = GridPoint(texture);
    

    std::string data = GenerateChunk();
    std::string objectData = GenerateObject(data);

    for (int i = 0; i < CHUNK_SIZE; ++i) {
        auto texture = ResourceManagers::GetInstance()->GetTexture("Forest_Turf_Texture.png");
        plainTerrain = std::make_shared<GridPoint>(texture);
        plainTerrain->terrain = MTerrain::MTERRAIN_PLAIN;
        texture = ResourceManagers::GetInstance()->GetTexture("Blue_Fungus_Turf_Texture.png");
        riverTerrain = std::make_shared<GridPoint>(texture);
        riverTerrain->terrain = MTerrain::MTERRAIN_RIVER;

        MObject O = MObject::MOBJECT_INVALID;
        std::shared_ptr<MapObject> newMObject;
        std::shared_ptr<GridPoint> newGrid;
        
        if (data[i] == '0') newGrid = plainTerrain;
        else if (data[i] == '1') newGrid = riverTerrain;
      
        if (objectData[i] == '0') O = MObject::MOBJECT_INVALID;
        else if (objectData[i] == '1') O = MObject::MOBJECT_TREE;
        else if (objectData[i] == '2') O = MObject::MOBJECT_BUSH;
        else if (objectData[i] == '3') O = MObject::MOBJECT_GRASS;
        else if (objectData[i] == '4') O = MObject::MOBJECT_CROP;
        else if (objectData[i] == '5') O = MObject::MOBJECT_CHESS;
        else if (objectData[i] == '6') O = MObject::MOBJECT_ROCK;
       
        newGrid->gridNumber = i;
        grids.push_back(newGrid);
    }
}

void MapChunk::Draw(SDL_Renderer* renderer)
{
    for (auto it : grids)
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
        texture->Render(50 * (gridNumber % CHUNK_UNITS), 50 * (gridNumber / CHUNK_UNITS), 50, 50, 0, m_flip);
    }
}
