#pragma once

#include "ParameterReader.h"

// PCL 库
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/common/time.h>
#include <pcl/point_cloud.h>
#include <boost/thread/thread.hpp>
#include <pcl/features/normal_3d.h>
#include <pcl/console/time.h>
#include <pcl/filters/voxel_grid.h>



//OpenCV 库
#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/core/eigen.hpp>


// C++ 标准库
#include <iostream>
#include <sstream>
#include <fstream>


// 命名空间
using namespace cv;
using namespace std;


// 定义点云类型
typedef pcl::PointXYZRGBA PointT;
typedef pcl::PointCloud<PointT> PointCloud;


// 帧结构
struct FRAME
{
    cv::Mat bgrImage, depthMap; //该帧对应的彩色图与深度图
    cv::Mat desp;       //特征描述子
    vector<cv::KeyPoint> key_point; //关键点
};


class captureImage_generatePointCloud
{
 public:
	FRAME frame_now, frame_pre;
	Mat depthMap_show;
    VideoCapture capture;


    /*********视频存储设置***********/

    VideoWriter writerdepth, writerrgb;

    /*******图像+点云 存储设置********/
    bool save_image;
    bool save_video;
    std::stringstream ss_index;
    std::string depthname;
    std::string rgbname;
    std::string pcdname;
    int index;

    // 使用智能指针，创建空点云。这种指针用完会自动释放。
    PointCloud::Ptr _cloud_now;
    PointCloud::Ptr _cloud_pre;


 public:
    captureImage_generatePointCloud();
    ~captureImage_generatePointCloud();

    void captureImage();
    void generatePointCloud();

};
