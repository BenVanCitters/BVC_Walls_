//
//  TileSetter.cpp
//  BVCWall
//
//  Created by Ben Van CItters on 10/10/13.
//
//

#include "TileSetter.h"
#include "TileSetTile.h"
TileSetter::TileSetter()
{
    TileSetter::TileSetter(1,1);
}

TileSetter::TileSetter(int width, int height)
{
    tiles.resize(width);
    for(int i = 0; i < tiles.size(); i++)
    {
        tiles[i].resize(height);
        for(int j = 0; j < tiles[i].size(); j++)
        {
            tiles[i][j].tileRight = NULL;
            tiles[i][j].tileAbove = NULL;
            tiles[i][j].tileLeft = NULL;
            tiles[i][j].tileBelow= NULL;

            if(i > 0)
            {
                tiles[i][j].tileAbove = &tiles[i-1][j];
                tiles[i-1][j].tileBelow = &tiles[i][j];
                if(j < tiles[i].size()-1)
                {
                    tiles[i][j].tileRight = &tiles[i-1][j+1];
                    tiles[i-1][j+1].tileRight = &tiles[i][j];
                }
            }
        }
    }
}

//
bool TileSetter::getNewRect(ofVec2f * pos, ofVec2f* sz)
{
    //find an empty starting space;
    ofVec2f newPos;
    bool foundAnEmpty = false;
    for(int i = 0; i < tiles.size() && !foundAnEmpty; i++)
        for(int j = 0; j < tiles[i].size() && !foundAnEmpty; j++)
        {
            if(!tiles[i][j].isOccupied)
            {
                newPos.x = j;
                newPos.y = i;
                foundAnEmpty = true;
            }
        }
    //found no empty rectangles
    if(!foundAnEmpty)
        return false;


    ofVec2f maxSz(MIN(25+newPos.x,tiles[0].size()),
                  MIN(25+newPos.y, tiles.size()));
    
    std::vector<ofVec2f> boxSzs;
    for(int i = newPos.y; i < maxSz.y; i++)
        for(int j = newPos.x; j < maxSz.x && (!tiles[i][j].isOccupied); j++)
        {
            boxSzs.push_back(ofVec2f(j-newPos.x+1,i-newPos.y+1));
        }
    //found no usable sizes
    if(boxSzs.size() < 1)
        return false;

    int rndIndex =(int)ofRandom(boxSzs.size());
    ofVec2f randomSz = boxSzs[rndIndex];
    
    //'occupy' all the used up tiles
    for(int i = newPos.y; i < randomSz.y+newPos.y; i++)
        for(int j = newPos.x; j < randomSz.x+newPos.x; j++)
        {
            tiles[i][j].isOccupied = true;
        }
    
    sz->x =randomSz.x;
    sz->y =randomSz.y;
    pos->x = newPos.x;
    pos->y = newPos.y;
    return true;
}
