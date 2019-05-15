#include <pcl/io/pcd_io.h>  //文件输入输出
#include <pcl/point_types.h>  //点类型相关定义
#include <pcl/visualization/cloud_viewer.h>  //点云可视化相关定义
#include <pcl/filters/statistical_outlier_removal.h>  //滤波相关
#include <pcl/filters/radius_outlier_removal.h>  //滤波相关

#include <pcl/common/common.h>  

#include <iostream>
#include <vector>

#include "myPointType.h"

using namespace std;

int main()
{
	//1.读取点云
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::PCDReader r;
	r.read<pcl::PointXYZI>("data\\data1-预处理.pcd", *cloud);
	cout << "there are " << cloud->points.size() << " points before filtering." << endl;

	//2.统计滤波
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_filter(new pcl::PointCloud<pcl::PointXYZI>);
	/*pcl::StatisticalOutlierRemoval<pcl::PointXYZI> sor;
	sor.setInputCloud(cloud);
	sor.setMeanK(10);
	sor.setStddevMulThresh(2.0);
	sor.setNegative(false);
	sor.filter(*cloud_filter);*/

	pcl::RadiusOutlierRemoval<pcl::PointXYZI>  outrem;
	outrem.setInputCloud(cloud);
	outrem.setRadiusSearch(0.45);//设置在0.05半径的范围内找邻近点
	outrem.setMinNeighborsInRadius(5);//设置查询点的邻近点集数小于5的删除
	outrem.filter(*cloud_filter);
	
	//3.滤波结果保存
	pcl::PCDWriter w;
	w.writeASCII<pcl::PointXYZI>("data\\data1-预处理_filter.pcd", *cloud_filter);
	cout << "there are " << cloud_filter->points.size() << " points after filtering." << endl;

	system("pause");
	return 0;
}