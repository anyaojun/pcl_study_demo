#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>


struct PointXYZ
{
	double x, y, z;
};

/*
  Author:chd_ayj
  Date:2018-6-8
  Description: read .PCD file
*/

//��ȡpcd�����ļ�
void readPCDfile(const std::string finname, std::vector<PointXYZ>& points, const std::string foutname)
{
	std::ifstream fin(finname);
	if (fin.bad()){
		std::cout << "���ļ�ʧ�ܣ�" << std::endl;
		return;
	}

	char s[11][1024]; //�洢Header
	int Points_Num; //������
	std::string data_columns_type; //����: X Y Z
	std::string data_type; //������洢��ʽ(ascii����binary)

	std::vector<PointXYZ> cloud;
	//������ȡHeader����   
	std::cout << "start to read file header....." << std::endl;
	std::cout << "file header: " << std::endl;
	for (int i = 0; i < 11; ++i){
		fin.getline(s[i], 1024);
		//std::cout << "��" << i + 1 << "�У�" << s[i] << std::endl;
		std::cout << s[i] << std::endl;

		//FIELDS x y z rgb
		if (i == 2){
			std::string s2 = s[2];
			size_t pos = s2.find("FIELDS");
			size_t size = s2.size();
			data_columns_type = s2.substr(pos + 7, size);
			//std::cout << "data_columns_type:" << data_columns_type << std::endl;
		}

		//POINTS xxx
		if (i == 9){
			std::string s9 = s[9], Points_Str;
			size_t pos = s9.find("POINTS");
			size_t size = s9.size();
			Points_Str = s9.substr(pos + 7, size);
			Points_Num = atoi(Points_Str.c_str());
			//std::cout << "Points:" << std::Points_Num << endl;
		}

		//DATA ascii����binary
		if (i == 10){
			std::string s10 = s[10], DATA_SIZE;
			size_t pos = s10.find("DATA");
			size_t size = s10.size();
			data_type = s10.substr(pos + 5, size);
			//std::cout << "data_type:" << data_type << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "start to read point ....." << std::endl;
	PointXYZ p;
	if ((data_columns_type == "x y z") && (data_type == "ascii")){
		//��ȡ�������¼
		while (!fin.eof()){
			fin >> p.x >> p.y >> p.z;
			if (fin.peek() == EOF){
				break;
			}
			cloud.push_back(p);
		}
	}else{
		std::cout << "data_type = binary, read failed!" << std::endl;
    }
    ////////////////////////////////////////////////////////////
	//���������txt�ı�
	std::cout << "start to write point to txt....." << std::endl;
	std::ofstream out(foutname);
	for (size_t i = 0; i < points.size(); ++i)
	{
		out << std::setiosflags(std::ios::fixed) << std::setprecision(7)
			<< points.at(i).x << " "
			<< points.at(i).y << " "
			<< points.at(i).z << std::endl;
	}
	std::cout << "write point to txt finished!" << std::endl;
}


int main0()
{
	std::string finname = "ascii_pcd.pcd";
	std::string foutame = "ascii_pcd.txt";
	std::vector<PointXYZ> points;
	readPCDfile(finname, points, foutame);

	system("pause");
	return 0;
}

