/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    MosaicCanvas * mCanvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> vector_p;
    for (vector<TileImage>::iterator it = theTiles.begin(); it != theTiles.end(); it++) 
    {
        Point<3> XYZ_ (convertToXYZ((*it).getAverageColor()));
        vector_p.push_back(XYZ_);
    }
    KDTree<3> temp_ (vector_p);
    for (int x = 0; x < theSource.getRows(); x++) 
    {
        for (int y = 0; y < theSource.getColumns(); y++) 
        {
            Point<3> NN_p (convertToXYZ(theSource.getRegionColor(x, y)));
            Point<3> N_p = temp_.findNearestNeighbor(NN_p);
            int count = 0;
            for (int i = 0; vector_p[i] != N_p; i++) 
            {
                count = i;
            }
            count++;
            TileImage & img_ = theTiles[count];
            mCanvas->setTile(x, y, &img_);
        }
    }
    return mCanvas;
}
