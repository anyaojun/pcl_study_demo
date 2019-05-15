#include <pcl/io/pcd_io.h>  //�ļ��������
#include <pcl/octree/octree_search.h>  //octree��ض���
#include <pcl/visualization/cloud_viewer.h>  //vtk���ӻ���ض���
#include <pcl/point_types.h>  //��������ض���

#include <iostream>
#include <vector>

int main3()
{
	//1.��ȡ����
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	if (pcl::io::loadPCDFile<pcl::PointXYZRGB>("demo.pcd", *cloud) == -1)
	{
		PCL_ERROR("Cloudn't read file!");
		return -1;
	}

	//2.ԭʼ������ɫ
	for (size_t i = 0; i < cloud->points.size(); ++i){
		cloud->points[i].r = 255;
		cloud->points[i].g = 255;
		cloud->points[i].b = 255;
	}

	//3.����Octreeʵ������
	float resolution = 0.03f;  //����octree���طֱ���
	pcl::octree::OctreePointCloudSearch<pcl::PointXYZRGB> octree(resolution); //����octree����
	octree.setInputCloud(cloud); //������Ҫ����kdtree�ĵ���ָ��
	octree.addPointsFromInputCloud();  //����Octree

	//3.1.�����ڽ�������
	pcl::PointXYZRGB searchPoint1 = cloud->points[1250]; //���ò��ҵ�
	std::vector<int> pointIdxVec;  //�������ؽ��������Ľ������
	if (octree.voxelSearch(searchPoint1, pointIdxVec))
	{
		std::cout << "Neighbors within voxel search at (" << searchPoint1.x
			<< " " << searchPoint1.y
			<< " " << searchPoint1.z << ")"
			<< std::endl;

		//�����ҵ��Ľ��ڵ�������ɫ
		for (size_t i = 0; i < pointIdxVec.size(); ++i){
			cloud->points[pointIdxVec[i]].r = 255;
			cloud->points[pointIdxVec[i]].g = 0;
			cloud->points[pointIdxVec[i]].b = 0;
		}		
	}

	//3.2.K��������
	pcl::PointXYZRGB searchPoint2 = cloud->points[3000]; //���ò��ҵ�
	int K = 200;
	std::vector<int> pointIdxNKNSearch; //����K���ڵ���������
	std::vector<float> pointNKNSquaredDistance;  //����ÿ�����ڵ�����ҵ�֮���ŷʽ����ƽ��

	std::cout << "K nearest neighbor search at (" << searchPoint2.x
		<< " " << searchPoint2.y
		<< " " << searchPoint2.z
		<< ") with K=" << K << std::endl;

	if (octree.nearestKSearch(searchPoint2, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
	{   //�����ҵ��Ľ��ڵ�������ɫ
		for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i){
			cloud->points[pointIdxNKNSearch[i]].r = 0;
			cloud->points[pointIdxNKNSearch[i]].g = 255;
			cloud->points[pointIdxNKNSearch[i]].b = 0;
		}	
	}
	std::cout << "K = 200���ڵ������" << pointIdxNKNSearch.size() << endl;

	//3.3.�뾶�ڽ�������
	pcl::PointXYZRGB searchPoint3 = cloud->points[6500]; //���ò��ҵ�
	std::vector<int> pointIdxRadiusSearch;  //����ÿ�����ڵ������
	std::vector<float> pointRadiusSquaredDistance;  //����ÿ�����ڵ�����ҵ�֮���ŷʽ����ƽ��
	float radius = 0.02; //���ò��Ұ뾶��Χ

	std::cout << "Neighbors within radius search at (" << searchPoint3.x
		<< " " << searchPoint3.y
		<< " " << searchPoint3.z
		<< ") with radius=" << radius << std::endl;


	if (octree.radiusSearch(searchPoint3, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
	{    //�����ҵ��Ľ��ڵ�������ɫ
		for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i){
			cloud->points[pointIdxRadiusSearch[i]].r = 0;
			cloud->points[pointIdxRadiusSearch[i]].g = 0;
			cloud->points[pointIdxRadiusSearch[i]].b = 255;
		}		
	}
	std::cout << "�뾶0.02���ڵ������ " << pointIdxRadiusSearch.size() << endl;


	//4.��ʾ����
	pcl::visualization::CloudViewer viewer("cloud viewer");
	viewer.showCloud(cloud);

	system("pause");
	return 0;
}