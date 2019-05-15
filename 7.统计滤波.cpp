#include <pcl/io/pcd_io.h>  //�ļ��������
#include <pcl/point_types.h>  //��������ض���
#include <pcl/visualization/cloud_viewer.h>  //���ƿ��ӻ���ض���
#include <pcl/filters/statistical_outlier_removal.h>  //�˲����
#include <pcl/filters/radius_outlier_removal.h>  //�˲����

#include <pcl/common/common.h>  

#include <iostream>
#include <vector>

#include "myPointType.h"

using namespace std;

int main()
{
	//1.��ȡ����
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);
	pcl::PCDReader r;
	r.read<pcl::PointXYZI>("data\\data1-Ԥ����.pcd", *cloud);
	cout << "there are " << cloud->points.size() << " points before filtering." << endl;

	//2.ͳ���˲�
	pcl::PointCloud<pcl::PointXYZI>::Ptr cloud_filter(new pcl::PointCloud<pcl::PointXYZI>);
	/*pcl::StatisticalOutlierRemoval<pcl::PointXYZI> sor;
	sor.setInputCloud(cloud);
	sor.setMeanK(10);
	sor.setStddevMulThresh(2.0);
	sor.setNegative(false);
	sor.filter(*cloud_filter);*/

	pcl::RadiusOutlierRemoval<pcl::PointXYZI>  outrem;
	outrem.setInputCloud(cloud);
	outrem.setRadiusSearch(0.45);//������0.05�뾶�ķ�Χ�����ڽ���
	outrem.setMinNeighborsInRadius(5);//���ò�ѯ����ڽ��㼯��С��5��ɾ��
	outrem.filter(*cloud_filter);
	
	//3.�˲��������
	pcl::PCDWriter w;
	w.writeASCII<pcl::PointXYZI>("data\\data1-Ԥ����_filter.pcd", *cloud_filter);
	cout << "there are " << cloud_filter->points.size() << " points after filtering." << endl;

	system("pause");
	return 0;
}