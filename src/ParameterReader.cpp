#include <fstream>

#include "ParameterReader.h"
#include "yaml-cpp/yaml.h"

ParameterReader* Para_Reader = new ParameterReader ;  // 全局类初始化（.cpp 文件中也需要声明）

ParameterReader::ParameterReader(  )
{
    cout<<BOLDRED<<"Init class:parameterReader"<< RESET<< endl;

    const string para_file = "../parameter.yaml";
    ifstream fin(para_file.c_str());

    YAML::Parser parser(fin);
    YAML::Node config;
    try {
        parser.GetNextDocument(config);
    } catch (YAML::ParserException& e)
    {
    	cerr << e.what() << endl;
        return ;
    }

    // main函数
    config[ "max_pos_change" ] >> _max_pos_change;

    // captureImage_generatePointCloud 参数
    config[ "save_image" ] >> _save_image;
    config[ "save_video" ] >> _save_video;
    config[ "save_pointcloud" ] >> _save_pointcloud;

    // point_vo 类
    config[ "feature_name" ] >> _feature_name;
    config[ "good_match_threshold" ] >> _good_match_threshold;
    config[ "min_goodmatch_num" ] >> _min_goodmatch_num;
    config[ "pnp_reprojectionError" ] >> _pnp_reprojectionError;
    config[ "pnp_iterationsCount" ] >> _pnp_iterationsCount;

    // extract_model 参数
    config[ "plane_dis_thread" ] >> _plane_dis_thread;
    config[ "sphere_dis_thread" ] >> _sphere_dis_thread;
    config[ "plane_percent_left" ] >> _plane_percent_left;
    config[ "max_plane_number" ] >> _max_plane_number;

    // map_generation 类
    config[ "grid_leaf" ] >> _grid_leaf;


    config[ "camera_fx" ] >> _camera_fx;
    config[ "camera_fy" ] >> _camera_fy;
    config[ "camera_cx" ] >> _camera_cx;
    config[ "camera_cy" ] >> _camera_cy;
    config[ "camera_factor" ] >> _camera_factor;



    cout <<BOLDRED<<"The parameter.yaml is read successfully!"<<RESET<< endl;
}

ParameterReader::~ParameterReader()
{

}

