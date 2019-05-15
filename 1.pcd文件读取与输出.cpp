#include <iostream>
#include <fstream>
#include <pcl/io/pcd_io.h>  //文件输入输出
#include <pcl/point_types.h>  //点类型相关定义
#include <pcl/visualization/cloud_viewer.h>  //点类型相关定义

using namespace std;

int main1()
{

	//1.loadPCDFile读取点云
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud1(new pcl::PointCloud<pcl::PointXYZ>);
	if (pcl::io::loadPCDFile<pcl::PointXYZ>("车载道路2.pcd", *cloud1) == -1)
	{
		PCL_ERROR("Cloudn't read file!");
		return -1;
	}
	cout << "1.loadPCDFile方式使用指针读取点个数: " << cloud1->points.size() << endl;

	//2.读取点云
	pcl::PointCloud<pcl::PointXYZ> cloud;
	if (pcl::io::loadPCDFile<pcl::PointXYZ>("车载道路2.pcd", cloud) == -1)
	{
		PCL_ERROR("Cloudn't read file!");
		return -1;
	}
	cout << "2.loadPCDFile方式使用对象读取点个数: " << cloud.points.size() << endl;

	//3.PCDReader读取点云
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PCDReader reader;
	reader.read<pcl::PointXYZ>("车载道路2.pcd", *cloud2);
	cout << "3.PCDReader方式读取点个数: " << cloud2->points.size() << endl;

	//4.savePCDFile方式点云输出
	//pcl::io::savePCDFile<pcl::PointXYZ>("车载道路2_.pcd", cloud); //默认二进制方式保存
	pcl::io::savePCDFileASCII<pcl::PointXYZ>("车载道路2_ASCII.pcd", cloud); //ASCII方式保存
	//pcl::io::savePCDFileBinary<pcl::PointXYZ>("车载道路2_Binary.pcd", cloud); //二进制方式保存

	//5.PCDWriter方式点云输出
	pcl::PCDWriter writer;
	//writer.write<pcl::PointXYZ>("1车载道路2_.pcd", cloud); //默认二进制方式保存
	writer.writeASCII<pcl::PointXYZ>("1车载道路2_ASCII.pcd", cloud); //ASCII方式保存
	//writer.writeBinary<pcl::PointXYZ>("1车载道路2_Binary.pcd", cloud); //二进制方式保存

	//5.显示点云
	pcl::visualization::CloudViewer viewer("cloud viewer");
	viewer.showCloud(cloud1);

	system("pause");
	return 0;
}