/*
 * @Author: Shuming Si
 * @Date: 2024-04-02 01:22:55
 * @LastEditors: Shuming Si
 * @LastEditTime: 2024-04-02 01:23:30
 * @Description: 
 * Copyright (c) 2024 by zbssm123@gmail.com, All Rights Reserved. 
 */
#pragma once
#include<pcgfLib\common.h>
#include<nanoflann.hpp>
namespace nanoflann {
	template <class MatrixType, int DIM = -1, class Distance = nanoflann::metric_L2> struct KDTreeAdapteor {
		using self_t = KDTreeAdapteor<MatrixType, DIM, Distance>;
		using num_t = typename MatrixType::Scalar;
		using IndexType = typename Distance::template traits<num_t, self_t>::distance_t;
		using metric_t = typename Distance::template traits<num_t, self_t>::distance_t;
		using index_t = KDTreeSingleIndexAdaptor<metric_t, self_t, DIM, IndexType>;
		index_t* index;

		KDTreeAdaptor(const int dimensionality, const MatrixType &mat, const int leaf_max_size = 10)
};

}