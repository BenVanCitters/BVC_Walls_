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
    mWidth = width;
    mHeight = height;
    ofSeedRandom();
    mMaxTileSize = ofVec2f(1+ofRandom(mWidth/3.f),1+ofRandom(mHeight/3.f));
    tiles.resize(mHeight);
    for(int i = 0; i < tiles.size(); i++)
    {
        tiles[i].resize(mWidth);
    }
    
    
    for(int i = 0; i < tiles.size(); i++)
    {
        for(int j = 0; j < tiles[i].size(); j++)
        {
            tiles[i][j].tileRight = NULL;
            tiles[i][j].tileAbove = NULL;
            tiles[i][j].tileLeft = NULL;
            tiles[i][j].tileBelow= NULL;
            tiles[i][j].mOwnerTile = NULL;
//            if(i > 0)
            {
                int otherIIndex = (i-1+tiles.size())%tiles.size();
                tiles[i][j].tileAbove = &tiles[otherIIndex][j];
                tiles[otherIIndex][j].tileBelow = &tiles[i][j];
//                if(j < tiles[i].size()-1)
                {
                int otherJIndex = (j+1+tiles[i].size())%tiles[i].size();
                    tiles[i][j].tileRight = &tiles[otherIIndex][otherJIndex];
                    tiles[otherIIndex][otherJIndex].tileRight = &tiles[i][j];
                }
            }
        }
    }
    for(int i = 0; i < tiles.size(); i++)
        for(int j = 0; j < tiles[i].size(); j++)
        {
            availableTiles.insert(&tiles[i][j]);
        }
}

//
bool TileSetter::getNewRect(ofVec2f * pos, ofVec2f* sz, std::vector<TileSetTile*>* tilesPieces)
{
    //find an empty starting space;
    ofVec2f newPos;
    bool foundAnEmpty = false;
//    availableTiles.
    
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

    ofVec2f maxExtent(MIN(mMaxTileSize.x+newPos.x,tiles[0].size()),
                        MIN(mMaxTileSize.y+newPos.y, tiles.size()));

    std::vector<ofVec2f> boxSzs;
    for(int i = newPos.y; i < maxExtent.y; i++)
    {
        if(i == tiles.size()-1)
            i = tiles.size()-1;
        for(int j = newPos.x; j < maxExtent.x; j++)
        {
            if(tiles[i][j].isOccupied)
            {
                maxExtent.x = j-1;
            }
            else
            {
                ofVec2f newSz(j-newPos.x+1,i-newPos.y+1);
                boxSzs.push_back(newSz);
            }
        }
    }
    //found no usable sizes
    if(boxSzs.size() < 1)
        return false;

    //pick a random size
    int rndIndex =(int)ofRandom(boxSzs.size());
    ofVec2f randomSz = boxSzs[rndIndex];

    
    //'occupy' all the used up tiles
    for(int i = newPos.y; i < randomSz.y+newPos.y; i++)
    {
        for(int j = newPos.x; j < randomSz.x+newPos.x; j++)
        {
            tiles[i][j].isOccupied = true;
            tilesPieces->push_back(&tiles[i][j]);
        }
    }
    

    sz->x =randomSz.x;
    sz->y =randomSz.y;
    pos->x = newPos.x + sz->x/2;
    pos->y = newPos.y + sz->y/2;
    return true;
}

void TileSetter::findNeighbors()
{
    for(int i = 0; i < tiles.size(); i++)
        for(int j = 0; j < tiles[i].size(); j++)
        {
            TileSetTile currentTile = tiles[i][j];
            DiamondTile* owner = currentTile.mOwnerTile;
            DiamondTile* neighbor;
            bool foundResult = false;
            if(i > 0)
            {
//                std::set<DiamondTile*> set;
//                set.
                neighbor = tiles[i-1][j].mOwnerTile;
//                foundResult = std::find(owner->mNeighborTiles.begin(),
//                                        owner->mNeighborTiles.end(),
//                                        neighbor) != owner->mNeighborTiles.end();
                if(owner != neighbor)
                    owner->mNeighborTiles.insert(neighbor);
            }
            if(i < tiles.size()-2)
            {
                neighbor = tiles[i+1][j].mOwnerTile;
//                foundResult = std::find(owner->mNeighborTiles.begin(),
//                                       owner->mNeighborTiles.end(),
//                                       neighbor) != owner->mNeighborTiles.end();
                if(owner != neighbor)
                    owner->mNeighborTiles.insert(neighbor);
            }
            
            if(j < tiles[i].size()-2)
            {
                neighbor = tiles[i][j+1].mOwnerTile;
//                foundResult = std::find(owner->mNeighborTiles.begin(),
//                                        owner->mNeighborTiles.end(),
//                                        neighbor) != owner->mNeighborTiles.end();
                if(owner != neighbor)
                    owner->mNeighborTiles.insert(neighbor);
            }
            
            
            if(j > 0)
            {
                neighbor = tiles[i][j-1].mOwnerTile;
//                foundResult = std::find(owner->mNeighborTiles.begin(),
//                                        owner->mNeighborTiles.end(),
//                                        neighbor) != owner->mNeighborTiles.end();
                if(owner != neighbor)
                    owner->mNeighborTiles.insert(neighbor);
            }
        }
}
