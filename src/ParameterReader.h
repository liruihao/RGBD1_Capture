/*****************************************
 * ParameterReader.h 参数管理类
 * 程序中将有一个该类的全局变量，从parameter.yaml中
 * 读取各个参数的值，供其他类使用，方便调试
 ****************************************/

#pragma once
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

//the following are UBUNTU/LINUX ONLY terminal color
#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */
#define YELLOW "\033[33m" /* Yellow */
#define BLUE "\033[34m" /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m" /* Cyan */
#define WHITE "\033[37m" /* White */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define BOLDRED "\033[1m\033[31m" /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m" /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m" /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m" /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m" /* Bold White */


class ParameterReader
{
public:
    ParameterReader( );
    virtual ~ParameterReader( );

public:
    stringstream ss;

    // 相机内参模型
   	double _camera_factor ;
   	double _camera_cx ;    //320
   	double _camera_cy ;    //240
   	double _camera_fx ;    //525
   	double _camera_fy ;    //525


    // main 函数
    double _max_pos_change;

    // captureImage_generatePointCloud 参数
    bool _save_image;
    bool _save_video;
    bool _save_pointcloud;

    // point_vo 参数
    string _feature_name;
    double _good_match_threshold;
    int _min_goodmatch_num;
    double _pnp_reprojectionError;
    double _pnp_iterationsCount;

    // extract_model 参数
    double _plane_dis_thread;
    double _sphere_dis_thread;
    double _plane_percent_left;
    double _max_plane_number;

    // map_generation 参数
    double _grid_leaf;




    
};

extern	ParameterReader* Para_Reader;  // 声明全局类（.h 文件中也需要初始化）
