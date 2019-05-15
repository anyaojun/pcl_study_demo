#include <pcl/io/pcd_io.h>  //�ļ��������
#include <pcl/point_types.h>  //��������ض���
#include <pcl/visualization/cloud_viewer.h>  //���ƿ��ӻ���ض���
#include <pcl/filters/voxel_grid.h>  //�����˲����
#include <pcl/common/common.h>  

#include <iostream>
#include <vector>

using namespace std;

int main6()
{
	//1.��ȡ����
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	if (pcl::io::loadPCDFile<pcl::PointXYZ>("data\\demo.pcd", *cloud) == -1)
	{
		PCL_ERROR("Cloudn't read file!");
		return -1;
	}
	cout << "there are " << cloud->points.size() << " points before filtering." << endl;


	//2����դ���˲�
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filter(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::VoxelGrid<pcl::PointXYZ> sor;
	sor.setInputCloud(cloud);
	sor.setLeafSize(0.3f, 0.3f, 0.3f);//���ش�С����Ϊ30*30*30cm
	sor.filter(*cloud_filter);
	

	//3.�˲��������
	pcl::io::savePCDFile<pcl::PointXYZ>("data\\demo_filter.pcd", *cloud_filter);
	cout << "there are " << cloud_filter->points.size() << " points after filtering." << endl;

	system("pause");
	return 0;
}