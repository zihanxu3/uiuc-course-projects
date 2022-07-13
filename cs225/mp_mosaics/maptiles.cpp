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
    map<Point<3>, TileImage*> map_;
    vector<Point<3>> input;
    for (TileImage &i : theTiles) {
        Point<3> point = convertToXYZ(i.getAverageColor());
        input.push_back(point);
        map_[point] = &i;
    }
    KDTree<3> tree_(input);
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    for (int i = 0; i < canvas->getRows(); i++) {
        for (int j = 0; j < canvas->getColumns(); j++) {
            LUVAPixel col = theSource.getRegionColor(i, j);
            Point<3> point_tile = tree_.findNearestNeighbor(convertToXYZ(col));
            // find ways to map back to the Tile
            canvas->setTile(i, j, map_[point_tile]);
        }
    }

    return canvas;
}

