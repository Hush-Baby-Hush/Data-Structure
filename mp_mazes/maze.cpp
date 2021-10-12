/* Your code here! */
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "maze.h"
#include "dsets.h"
#include <vector>
#include <math.h>
#include <queue>
#include <map>
#include <iostream>
#include <list>

PNG * SquareMaze::drawCreativeMaze()
{
  maze.resize(4*4);
	width_ = 4;
	height_ = 4;
	maze[0] = 1;
	maze[1] = 0;
	maze[2] = 1;
	maze[3] = 1;
	maze[4] = 0;
	maze[5] = 3;
	maze[6] = 2;
	maze[7] = 3;
	maze[8] = 0;
	maze[9] = 1;
	maze[10] = 0;
	maze[11] = 0;
	maze[12] = 1;
	maze[13] = 3;
	maze[14] = 0;
	maze[15] = 0;

	PNG * creative = new PNG(width_*10+1, height_*10+1);
	for(int x = 0; x < width_*10+1; x++)
  {
    for(int y = 0; y < height_*10+1; y++)
    {
			HSLAPixel& pix = creative->getPixel(x,y);
			if(pix.l != 0)
      {
				pix.h = x*y % 360;
				pix.s = 1;
				pix.l = .5;
				pix.a = 1;
      }
		}
	}

	for(int i = 10; i<width_*10+1; i++)
  {
    HSLAPixel& pix = creative->getPixel(i, 0);
    pix.l = 0;
  }
  for(int i=0; i<height_*10+1; i++)
  {
    HSLAPixel& pix = creative->getPixel(0, i);
    pix.l = 0;
  }

  for(int x = 0; x < width_; x++)
  {
    for(int y = 0; y < height_; y++)
    {
      int value = maze[(y*width_) + x];	
      if(value == 3 || value == 1)
      {
          for(int k = 0; k <= 10; k++)
          {
              HSLAPixel& pix = creative->getPixel((x+1)*10, y*10+k);
              pix.l = 0;
          }
      }
      if(value == 3 || value == 2)
      {		 
          for(int k = 0; k <= 10; k++)
          {	
              HSLAPixel& pix = creative->getPixel(x*10+k, (y+1)*10);
              pix.l = 0;
          }
      }
    }
  }
	vector<int> bestpath;
	int x = 5;
	int y = 5;
	bestpath = solveMaze();
	for (int dir : bestpath)
  {
    for (int p = 1; p < 11; ++p)
    {
			HSLAPixel& pix = creative->getPixel(x,y);
			pix.h = 0;
			pix.s = 1;
			pix.l = .5;
			pix.a = 1;

			if (dir == 0)
      {
				x++;
			}
			if (dir == 1)
      {	
				y++;
			}
			if (dir == 2)
      {	
				x--;
			}
			if (dir == 3)
      {	
				y--;
			}
		}
		HSLAPixel& pix = creative->getPixel(x,y);
		pix.h = 0;
		pix.s = 1;
		pix.l = .5;
		pix.a = 1;
	}

	for(int k =1; k < 10; k++)
  {
		HSLAPixel& pix = creative->getPixel(x+k-5, y+5);
		pix.l = 1;
	}

	return creative;

}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
	if ((0 <= x) && (x < width_) && (0 <= y) && (y < height_))
    {
		int value = maze[(y*width_) + x];
		if ((dir == 0) && ((x+1) < width_))
        {
			if (value == 0 || value == 2)
            {
                return true;
            }
		}
		else if ((dir == 1) && ((y+1) < height_))
        {
			if (value == 0 || value == 1)
            {
                return true;
            }
		}
		else if ((dir == 2) && (0 <= (x-1)))
        {
			if (maze[(y*width_) + x-1] == 0 || maze[(y*width_) + x-1] == 2)
            {
                return true;
            }
		}
		else if ((dir == 3) && (0 <= (y-1)))
        {
			if (maze[(y-1)*(width_) + x] == 0 || maze[(y-1)*(width_) + x] == 1)
            {
                return true;
            }
		}
	}
	return false;
}

void SquareMaze::makeMaze(int width, int height)
{
	maze.clear();
	maze.resize(width * height);
	width_ = width;
	height_ = height;
	for(int i=0; i < width*height; i++)
    {
		maze[i] = 3;
	}

	cycle_detection.addelements(width * height);
	while((width * height) > cycle_detection.size(0))
    {
		int element = rand() % (width * height);
		int rando = rand() % 2;
		if(rando == 0)
        {
			rando = width;
        }
		if((element+1) % width == 0)
        {
			rando = width;
		}
		if( width* (height-1)<=element)
        {
			rando = 1;
		}
		if(element == width * height -1)
        {
			continue;
        }

		int a = cycle_detection.find(element);
		int b = cycle_detection.find(element + rando);
		if(a != b)
        {
			cycle_detection.setunion(a, b);
			if(rando == 1)
            {
				setWall(element%width, element/width, 0, false);
			}
			else
            {
				setWall(element%width, element/width, 1, false);
			}
		}
	}
}


vector<int> SquareMaze::solveMaze()
{
  vector<int> bestpath;
  queue<int> q;
  q.push(0);
  std::map<int, int> my_map;
  my_map.insert(std::pair<int,int>(0, 0));
  std::map<int, int> parent;
  int count = 0;

  while (!q.empty())
  {
      int element = q.front();
      q.pop();
      int x = element % width_;
      int y = element / width_;
      for (int dir = 0; dir < 4; ++dir){
      	int nelement;
      	if (dir == 0)
        { 
            nelement = (y*width_) + (x+1);
        }
      	if (dir == 1)
        {
            nelement = ((y+1)*width_) + x;
        }
      	if (dir == 2)
        { 
            nelement = (y*width_) + (x-1);
        }
      	if (dir == 3)
        { 
            nelement = ((y-1)*width_) + x;
        }
      	if (canTravel(x,y,dir) && my_map.find(nelement) == my_map.end())
        {
      		q.push(nelement);
      		my_map.insert(std::pair<int, int>(nelement, my_map[element]+1));
      		parent[nelement] = element;
      	}
      }

	}
	unsigned max_dist = 0;
	int bestdest = 0;
	for(int x = 0; x < width_ ; ++x)
    {
		int dest = ((height_-1)*width_) + x;
		vector<int> temppath;
		while(dest != 0)
        {
			int rdir = dest - parent[dest];
			if(rdir == 1)
            {
				temppath.push_back(0);
			}
			else if(rdir == -1)
            {
				temppath.push_back(2);
			}
			else if(rdir == width_)
            {
				temppath.push_back(1);
			}
			else if(rdir == -width_)
            {
				temppath.push_back(3);
			}
			dest = parent[dest];
		}
		if(max_dist < temppath.size())
        {
			max_dist = temppath.size();
			bestpath = temppath;
			bestdest = dest;
		}
	}
  std::reverse(bestpath.begin(), bestpath.end());
  return bestpath;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
  int value = maze[y*width_+x];
  if(exists)
  {
    if(dir == 0)
    {
      if(value == 0 || value == 1)
      {
        maze[y*width_+x] = 1;
        return;
      }
      else
      {
        maze[y*width_+x] = 3;
        return;
      }
    }
    else
    {
      if(value == 0 || value == 2)
      {
        maze[y*width_+x] = 2;
        return;
      }
      else
      {
        maze[y*width_+x] = 3;
        return;
      }
    }
  }
  else
  {
    if(dir == 0)
    {
      if(value == 3)
      {
        maze[y*width_+x] = 2;
        return;
      }
      else if (value == 1)
      {
        maze[y*width_+x] = 0;
        return;
      }
    }
    else
    {
      if(value == 3)
      {
        maze[y*width_+x] = 1;
        return;
      }
      else if (value == 2)
      {
        maze[y*width_+x] = 0;
        return;
      }
    }
  }
}



PNG * SquareMaze::drawMaze() const
{
  PNG * mazePNG = new PNG(width_*10+1, height_*10+1);
  for(int i = 10; i<(width_*10+1); i++)
  {
    HSLAPixel& pix = mazePNG->getPixel(i, 0);
    pix.h = 0;
    pix.s = 0;
    pix.a = 1;
    pix.l = 0;
  }
  for(int i=0; i<(height_*10+1); i++)
  {
    HSLAPixel& pix = mazePNG->getPixel(0, i);
    pix.h = 0;
    pix.s = 0;
    pix.a = 1;
    pix.l = 0;
  }
  for(int x = 0; x < width_; x++)
  {
    for(int y = 0; y < height_; y++)
    {
      int value = maze[(y*width_) + x];
      if(value == 3 || value == 1)
      {
        for(int k = 0; k <= 10; k++)
        {	
          HSLAPixel& pix = mazePNG->getPixel((x+1)*10, y*10+k);
          pix.l = 0;
          pix.h = 0;
          pix.s = 0;
          pix.a = 1;
        }
      }
      if(value == 3 || value == 2)
      {	
        for(int k = 0; k <= 10; k++)
        {
          HSLAPixel& pix = mazePNG->getPixel(x*10+k, (y+1)*10);
          pix.l = 0;
          pix.h = 0;
          pix.s = 0;
          pix.a = 1;
        }
      }
    }
  }

  return mazePNG;
}

PNG * SquareMaze::drawMazeWithSolution()
{
	PNG * sol = drawMaze();
	vector<int> bestpath;
	int x = 5;
  int y = 5;
  bestpath = solveMaze();
	for (int dir : bestpath)
  {
    for (int p = 1; p < 11; ++p)
    {
			HSLAPixel& pix = sol->getPixel(x,y);
			pix.h = 0;
			pix.s = 1;
			pix.l = .5;
			pix.a = 1;

			if (dir == 0)
      {
				x++;
			}
			if (dir == 1)
      {
				y++;
			}
			if (dir == 2)
      {
				x--;
			}
			if (dir == 3)
      {
				y--;
			}
		}
		HSLAPixel&  pix = sol->getPixel(x,y);
		pix.h = 0;
		pix.s = 1;
		pix.l = .5;
		pix.a = 1;
	}

	for(int k =1; k < 10; k++)
  {
		HSLAPixel& pix = sol->getPixel(x+k-5, y+5);
		pix.l = 1;
	}

  return sol;
}