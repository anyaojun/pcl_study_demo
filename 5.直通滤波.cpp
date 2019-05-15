#include <pcl/io/pcd_io.h>  //�ļ��������
#include <pcl/point_types.h>  //��������ض���
#include <pcl/visualization/cloud_viewer.h>  //���ƿ��ӻ���ض���
#include <pcl/filters/passthrough.h>  //ֱͨ�˲����
#include <pcl/common/common.h>  

#include <iostream>
#include <vector>

using namespace std;

int main5()
{
	//1.��ȡ����
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	if (pcl::io::loadPCDFile<pcl::PointXYZ>("data\\demo.pcd", *cloud) == -1)
	{
		PCL_ERROR("Cloudn't read file!");
		return -1;
	}
	cout << "there are " << cloud->points.size()<<" points before filtering." << endl;

	//2.ȡ�õ������꼫ֵ
	pcl::PointXYZ minPt, maxPt;
	pcl::getMinMax3D(*cloud, minPt, maxPt);

	//3.ֱͨ�˲�
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filter(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PassThrough<pcl::PointXYZ> pass;     //�����˲�������
	pass.setInputCloud(cloud);                //���ô��˲��ĵ���
	pass.setFilterFieldName("z");             //������Z�᷽���Ͻ����˲�
	pass.setFilterLimits(0, maxPt.z - 12);    //�����˲���Χ(����ߵ�����12��ȥ��)
	pass.setFilterLimitsNegative(false);      //����
	pass.filter(*cloud_filter);               //�˲����洢

	//4.�˲��������
	pcl::io::savePCDFile<pcl::PointXYZ>("data\\demo_filter.pcd", *cloud_filter);
	cout << "there are " << cloud_filter->points.size() << " points after filtering." << endl;
	
	system("pause");
	return 0;
}