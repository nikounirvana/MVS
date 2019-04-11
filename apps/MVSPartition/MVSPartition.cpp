
#include "../../libs/MVS/Common.h"
#include "../../libs/MVS/Scene.h"
#include <boost/program_options.hpp>
#include "QuadTree.h"

using namespace MVS;


// D E F I N E S ///////////////////////////////////////////////////

#define APPNAME _T("MVSPartitions")
#define MVS_EXT _T(".mvs")

// S T R U C T S ///////////////////////////////////////////////////

int main(int argc, LPCTSTR* argv)
{
	std::cout << "hello openmvs" << std::endl;
	// load MVS Scene
	Scene scene(4);
	String strInputFileName = "/home/bang/openMVS/build_debug/bin/scene_dense.mvs";
	if (!scene.Load(MAKE_PATH_SAFE(strInputFileName)))
	{
		std::cout << "load scene failed" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "the size of PointCloud is: "<< scene.pointcloud.GetSize() << std::endl;
	std::cout << scene.pointcloud.pointViews.GetSize() << std::endl;
	std::cout << scene.pointcloud.points.GetSize() << std::endl;
	std::cout << scene.pointcloud.pointWeights.GetSize() << std::endl;
	std::cout << scene.pointcloud.normals.GetSize() << std::endl;
	std::cout << scene.pointcloud.colors.GetSize() << std::endl;
	std::cout << "the size of Image is: "<< scene.images.GetSize() << std::endl;

	// retrive projection plane
	AABB3f bounds(true);
	if (!scene.pointcloud.IsEmpty()) {
		bounds = scene.pointcloud.GetAABB();
		std::cout << bounds.GetSize() << std::endl;
	}

	auto center = bounds.GetCenter();
	std::cout << center(0) << std::endl;
	std::cout << center(1) << std::endl;
	std::cout << center(2) << std::endl;

	AABB3f tmp[2];
	unsigned size = bounds.SplitBy(center(0), 0, tmp);

	AABB3f quad[4];
	if(size != 0)
	{
		tmp[0].SplitBy(center(1), 1, quad);
		tmp[1].SplitBy(center(1), 1, &quad[2]);
	}
	
	/*
	for(size_t i = 0; i<4; i++)
	{
		AABB3f aabb = quad[i];
		std::cout << aabb.GetSize() << std::endl;
		std::cout << aabb.GetCenter() << std::endl;
		std::cout << std::endl;
	}
	*/
	// init Quadtree
	MVS::Scene sc[4];
	for(size_t i = 0; i<4; i++)
	{
		sc[i].platforms = scene.platforms;
		sc[i].images = scene.images;
	}

	// partition the point cloud
	MVS::PointCloud& pointcloud = scene.pointcloud;
	FOREACH(idx, pointcloud.points) {
		const MVS::PointCloud::Point& point = pointcloud.points[idx];
		for(int i=0; i<4; i++)
		{
			if(quad[i].Intersects(point))
			{
				MVS::PointCloud::Point& rpoint = sc[i].pointcloud.points.AddEmpty();
				rpoint = point;
				MVS::PointCloud::ViewArr& views = sc[i].pointcloud.pointViews.AddEmpty();
				for (const auto& view: pointcloud.pointViews[idx])
					views.InsertSort(view);
				MVS::PointCloud::WeightArr& PointWeight = sc[i].pointcloud.pointWeights.AddEmpty();
				for(auto& weight: pointcloud.pointWeights[idx])
					PointWeight.InsertSort(weight);

				MVS::PointCloud::Color& col = sc[i].pointcloud.colors.AddEmpty();
				col = pointcloud.colors[idx];
			}
		}
	}

	// save the scene 

	for(int i=0; i<4; i++)
	{
		String strOutputFileName = "out";
		String strOutputFileNamemvs = strOutputFileName+std::to_string(i)+MVS_EXT ;
		sc[i].Save(MAKE_PATH_SAFE(strOutputFileNamemvs));
		String ply = strOutputFileName+std::to_string(i)+_T(".ply");
		sc[i].pointcloud.Save(MAKE_PATH_SAFE(ply));
	}

	return 0;
}
/*----------------------------------------------------------------*/
