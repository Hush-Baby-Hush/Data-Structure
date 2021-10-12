/* Your code here! */
#pragma once

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "dsets.h"
#include <stdio.h>
#include <vector>
#include <list>
#include <math.h>
#include <tuple>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;
using namespace cs225;

class SquareMaze
{
	public:
    
		void makeMaze(int width, int height);
		void makeCreativeMaze(int width, int height);
		void makeMazeI(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		vector<int> solveMaze();
		PNG * drawMaze() const;
        PNG * drawCreativeMaze();
		PNG * drawMazeWithSolution();
		
	private:
		int width_ = 0;
		int height_ = 0;
		DisjointSets cycle_detection;
		vector<int> maze;
		vector<pair<bool,bool>> wbool;
		vector<tuple<int, int, int>> xyverts;
};

