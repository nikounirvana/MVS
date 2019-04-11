#include "QuadTree.h"
#include "../../libs/MVS/Common.h"


QuadTree::QuadTree(AABB3d ibox, int idepth):depth(idepth)
{
	root = new Node();
	root->box = ibox;
}

QuadTree::~QuadTree()
{
	if(root) delete root;
}

void QuadTree::CreateQuadTree(Node* node, int level, int depth)
{
	if(node == nullptr) return;
	if(level > depth) return;

	Node** newnode = new Node[4];
	for(int i=0; i<4; i++)
	{
		node->sons[i] = newnode[i];
		CreateQuadTree(node->sons[i], level+1, depth);
		if(level == depth)
		{
			Scene* pscene = new Scene();
			node->pScene = pscene; 		
		}
	}
}

void QuadTree::Insert(Point& ipoint)
{
	
}