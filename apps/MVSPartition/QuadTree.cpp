#include "QuadTree.h"
#include "../../libs/MVS/Common.h"


QuadTree::QuadTree():depth(idepth)
,_pScene(nullptr)
,_root(nullptr)
{
	_root = new Node();
}

QuadTree::~QuadTree()
{
	if(_root) delete _root;
}

void QuadTree::SetInputScene(Scene* pScene)
{
	_pScene = pScene;
}

void QuadTree::PartitionScene(PTrait& trait)
{
	
}


void QuadTree::Insert(Point& ipoint)
{
	
}