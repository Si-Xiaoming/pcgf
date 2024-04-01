/*
 * @Author: Shuming Si
 * @Date: 2024-03-31 19:27:42
 * @LastEditors: Shuming Si
 * @LastEditTime: 2024-03-31 23:19:10
 * @Description: 
 * Copyright (c) 2024 by zbssm123@gmail.com, All Rights Reserved. 
 */
#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>

#include <pdal/PointTable.hpp>
#include <pdal/PointView.hpp>
#include <pdal/Options.hpp>
#include <pdal/io/BufferReader.hpp>
#include <pdal/StageFactory.hpp>
#include <pdal/Stage.hpp>



#include <pdal/io/LasWriter.hpp>
#include <pdal/io/LasReader.hpp>
#include <pdal/io/LasHeader.hpp>


namespace pcgf{
	//定义全局的点云数据集
typedef struct {
	Eigen::MatrixXf points; //row：单个点
	Eigen::VectorXf intensities;
	std::vector<int> classifications;

	////0:不是噪声；1：是噪声
	//vector<int> flag;
	size_t kdtree_get_point_count() const {
		return classifications.size();
	}
	
	template <class BBOX>
	bool kdtree_get_bbox(BBOX& /* bb */) const { return false; }
	inline double kdtree_get_pt(const size_t idx, const size_t dim) const
	{
		if (dim == 0) return points(idx, 0);
		else if (dim == 1) return points(idx, 1);
		else return points(idx, 2);
	}

}PointCloud;

typedef struct {
	Eigen::Vector3d offset;
	Eigen::Vector3d scale;
	//size_t num_point;

}LasHeader_fresh;
class pdalLasOperator {
public:
	pdalLasOperator(const string filename) :lasFileName(filename) {};
	~pdalLasOperator() {};

	//LasHeader_fresh pc_read_header();
	PointCloud pc_read();
	void pc_save(const std::string& path, std::vector<int>clc, int NoiseLabel = 22);//   convert 0:pcl;   1:rf


protected:
	std::string lasFileName;
	
};
	

} // namespace pcgf