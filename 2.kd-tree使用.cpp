#include <pcl/kdtree/kdtree_flann.h>  //kdtree��������
#include <pcl/io/pcd_io.h>  //�ļ��������
#include <pcl/point_types.h>  //��������ض���
#include <pcl/visualization/cloud_viewer.h>  //���ƿ��ӻ���ض���

#include <iostream>
#include <vector>

int main2()
{
	//1.��ȡ����
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	if (pcl::io::loadPCDFile<pcl::PointXYZRGB>("rabbit.pcd", *cloud) == -1)
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

	//3.����kd-tree
	pcl::KdTreeFLANN<pcl::PointXYZRGB> kdtree;  //����kdtree����
	kdtree.setInputCloud(cloud); //������Ҫ����kdtree�ĵ���ָ��

	//4.K��������
	pcl::PointXYZRGB searchPoint = cloud->points[1000]; //���ò��ҵ�
	int K = 900;  //������Ҫ���ҵĽ��ڵ����
	std::vector<int> pointIdxNKNSearch(K);  //����ÿ�����ڵ������
	std::vector<float> pointNKNSquaredDistance(K); //����ÿ�����ڵ�����ҵ�֮���ŷʽ����ƽ��

	std::cout << "K nearest neighbor search at (" << searchPoint.x
		<< " " << searchPoint.y
		<< " " << searchPoint.z
		<< ") with K=" << K << std::endl;

	if (kdtree.nearestKSearch(searchPoint, K, pointIdxNKNSearch, pointNKNSquaredDistance) > 0)
	{
		for (size_t i = 0; i < pointIdxNKNSearch.size(); ++i){
			cloud->points[pointIdxNKNSearch[i]].r = 0;
			cloud->points[pointIdxNKNSearch[i]].g = 255;
			cloud->points[pointIdxNKNSearch[i]].b = 0;
		}		
	}
	std::cout << "K = 900���ڵ������" << pointIdxNKNSearch.size() << endl;

	//4.radius�뾶����
	pcl::PointXYZRGB searchPoint1 = cloud->points[3500];  //���ò��ҵ�
	std::vector<int> pointIdxRadiusSearch;  //����ÿ�����ڵ������
	std::vector<float> pointRadiusSquaredDistance;  //����ÿ�����ڵ�����ҵ�֮���ŷʽ����ƽ��
	float radius = 0.03;  //���ò��Ұ뾶��Χ

	std::cout << "Neighbors within radius search at (" << searchPoint.x
		<< " " << searchPoint.y
		<< " " << searchPoint.z
		<< ") with radius=" << radius << std::endl;


	if (kdtree.radiusSearch(searchPoint1, radius, pointIdxRadiusSearch, pointRadiusSquaredDistance) > 0)
	{
		for (size_t i = 0; i < pointIdxRadiusSearch.size(); ++i){
			cloud->points[pointIdxRadiusSearch[i]].r = 255;
			cloud->points[pointIdxRadiusSearch[i]].g = 0;
			cloud->points[pointIdxRadiusSearch[i]].b = 0;
		}
	}
	std::cout << "�뾶0.03���ڵ������ " << pointIdxRadiusSearch.size() << endl;
	pcl::io::savePCDFileASCII<pcl::PointXYZRGB>("rabbit21.pcd", *cloud); //ASCII��ʽ����

	//5.��ʾ����
	pcl::visualization::CloudViewer viewer("cloud viewer");
	viewer.showCloud(cloud);

	system("pause");
	return 0;
}