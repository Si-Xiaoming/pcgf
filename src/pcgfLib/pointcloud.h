/*
 * @Author: Shuming Si
 * @Date: 2024-03-31 23:34:04
 * @LastEditors: Shuming Si
 * @LastEditTime: 2024-04-01 21:58:46
 * @Description: 
 * Copyright (c) 2024 by zbssm123@gmail.com, All Rights Reserved. 
 */
#include <pcgfLib\common.h>
namespace pcgf{
    class PointCloud {

    public:
        PointCloud();
        ~PointCloud();
        /**
         * @brief 从文件中加载点云数据
         *
         * @param path  las 文件路径
         * @return true
         * @return false
         */
        bool load_las(const std::string& path);
        /**
         * @brief 保存点云数据到文件
         *
         * @param path 保存路径
         * @return true
         * @return false
         */
        void save_las(const std::string& path);

        std::string get_path() { return path_; }
        std::string get_proj() { return proj_; }
        int num_points();

        const MatrixXf& get_points() const { return points_; }

    protected:
        bool load_las(const std::string& path);

    protected:
        //投影信息
        std::string proj_;
        //文件路径
        std::string path_;

        //原点偏移量
        Vector3d offset_;
        // 点云数据, 每一列是一个点，矩阵为 column major
        MatrixXf points_;



    };
using PointcloudPtr = std::shared_ptr<PointCloud>;
} // namespace pcgf