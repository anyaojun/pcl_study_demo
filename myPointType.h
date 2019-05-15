#define PCL_NO_PRECOMPILE

#ifndef MYPOINTTYPE_H
#define MYPOINTTYPE_H

#include <pcl/point_types.h>

struct myPointXYZTI
{
	//PCL_ADD_POINT4D;
	union
	{
		double coordinate[3];
		struct
		{
			double x;
			double y;
			double z;
		};
	};
	double GPSTime;
	double instensity;
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
}EIGEN_ALIGN16;


POINT_CLOUD_REGISTER_POINT_STRUCT(myPointXYZTI,// ◊¢≤·µ„¿‡–Õ∫Í
	(double, x, x)
	(double, y, y)
	(double, z, z)
	(double, GPSTime, GPSTime)
	(double, instensity, instensity)
	)

#endif
