#pragma once
#include <vector>
#include "../../libs/MVS/Common.h"
#include "../../libs/MVS/Scene.h"

using namespace MVS;
typedef PointCloud::Point Point;

static int IID=0;
struct Node{
	int id;
	//Node* father;
	Node* sons[4];

	Scene* pScene;

	AABB3d box;
	Node():pScene(nullptr),id(IID++){}
};


class QuadTree
{
public:
	QuadTree(AABB3d box, int depth);
	virtual ~QuadTree();

	Node* GetRoot(){return root;}

	static void CreateQuadTree(Node* node);

	void Insert(Point& ipoint);
	

private:
	int depth;
	Node* root;
};