#pragma once
#include <vector>
#include "../../libs/MVS/Common.h"
#include "../../libs/MVS/Scene.h"

// use case
 QuadTree tree;
 tree.SetInputScene(&scene);

 PTrait trait;
 trait.PointNumPerpart = 500000;

 tree.PartitionScene(trait);

 tree.save();


// use case

using namespace MVS;
typedef PointCloud::Point Point;


struct Node{
	// unique name
	String name;
	Node* father;
	std::vector<Node*> sons;

	// data
	Scene* pScene;
	AABB3f box;

	Node():pScene(nullptr) {}
};

struct PTrait
{
	size_t PointNumPerpart;
	size_t ProcessorNum;
	size_t MemorySize;
	PTrait():PointNumPerpart(0),ProcessorNum(0),MemorySize(0){}
};


class QuadTree
{
public:
	QuadTree();
	virtual ~QuadTree();

	// set the data
	void SetInputScene(Scene* pScene);
	// partition the scene into a sparse quadtree
	void PartitionScene(PTrait& trait);


	Node* GetRoot(){return root;}

	//static void CreateQuadTree(Node* node);

	// save the scene 
	// the tree to xml file use TinyXML2.h in common.cpp
	// scene save as *.mvs
	void Save();

protected:
	void 	Insert(Point& ipoint);
	size_t 	HowMuchIn(AABB3f& box);

private:
	Scene* 	_pScene;
	Node* 	_root;
	int 	_depth;	
};