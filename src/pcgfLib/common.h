/*
 * @Author: Shuming Si
 * @Date: 2024-03-31 23:36:04
 * @LastEditors: Shuming Si
 * @LastEditTime: 2024-03-31 23:36:18
 * @Description: 
 * Copyright (c) 2024 by zbssm123@gmail.com, All Rights Reserved. 
 */
#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>


namespace pcgf{
using namespace Eigen;
typedef Eigen::Matrix<double, 3, 4> Matrix34d;
typedef Eigen::Matrix<double, 2, 3> Matrix23d;
typedef Eigen::AlignedBox3d BoundingBox3d;
typedef Eigen::AlignedBox3f BoundingBox3f;

typedef Eigen::Hyperplane<double, 3> Plane3d;
typedef Eigen::Hyperplane<double, 2> Line2d;
typedef Eigen::Transform<double, 3, Eigen::Affine, Eigen::ColMajor> Transform3d;



}