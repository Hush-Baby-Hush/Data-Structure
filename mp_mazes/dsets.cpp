/* Your code here! */
#include <cmath>
#include "dsets.h"



void DisjointSets::addelements(int num)
{
    for(int i=0 ;i< num; i++)
    {
      elems_.push_back(-1);
    }

}

int DisjointSets::find(int elem)
{
 
    if(elems_[elem]<0)
    {
        return elem;
    }

    else
    {
        int p = find(elems_[elem]);
        elems_[elem] = p;
        return p;
    }
}

void DisjointSets::setunion(int a, int b)
{

    int ra=find(a);
    int rb=find(b);

    if(ra==rb)
    {
        return;
    }
    
    else if(elems_[ra]>elems_[rb])
    {
        elems_[rb] += elems_[ra];
        elems_[ra] = rb;
        return;

    }

    else
    {
        elems_[ra] += elems_[rb];
        elems_[rb] = ra;
        return;
    }
}

int DisjointSets::size(int elem)
{
    int p = find(elem);
    return elems_[p]*-1;
}