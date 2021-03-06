#include "captureImage_generatePointCloud.h"



captureImage_generatePointCloud::captureImage_generatePointCloud():
		_cloud_now(new PointCloud),
		_cloud_pre(new PointCloud),
		index (0),
		save_image( Para_Reader->_save_image),
		save_video( Para_Reader->_save_video)
{

}


captureImage_generatePointCloud::~captureImage_generatePointCloud()
{

}


void captureImage_generatePointCloud::captureImage()
{
    index++;
    // 深度图存储编号
    ss_index << "../data/depth/"<<index<<".png";
    ss_index>>depthname;
    ss_index.clear();

    // rgb存储编号
    ss_index << "../data/rgb/"<<index<<".png";
    ss_index>>rgbname;
    ss_index.clear();

    // 抓取图像失败
    if( !capture.grab() )
        cout << "Can not grab images." << endl;
    // 抓取图像成功
    else
    {
//    	Mat depth_tmp;
//    	Mat rgb_tmp;
        if( capture.retrieve( frame_now.depthMap, CV_CAP_OPENNI_DEPTH_MAP ) )
        {
//        	pyrDown (depth_tmp, frame_now.depthMap, Size(depth_tmp.cols/2, depth_tmp.rows/2)) ;
            const float scaleFactor = 0.05f;

        //    frame_now.depthMap.convertTo( depthMap_show, CV_8UC1, scaleFactor );  // 深度图像--depthMap(CV_16UC1) 转变为 show（CV_8UC1）
       //     imshow( "depth map", depthMap_show );
            if (save_image )
            {
                // 保存深度图像
                imwrite(depthname, frame_now.depthMap);
            }
            if (save_video)
            {
                // 保存为视频--格式解码有问题
               writerdepth << depthMap_show;
            }

        }
        if( capture.retrieve( frame_now.bgrImage, CV_CAP_OPENNI_BGR_IMAGE ) )   //RGB图像--CV_8UC3 格式
        {
//        	pyrUp (rgb_tmp, frame_now.bgrImage, Size(rgb_tmp.cols*2, rgb_tmp.rows*2)) ;
          //  imshow( "rgb image", frame_now.bgrImage );
            if (save_image )
            {
                // 保存rgb图像
                imwrite(rgbname, frame_now.bgrImage);
            }
            if (save_video)
            {
                // 保存为视频
                writerrgb << frame_now.bgrImage;
            }
        }

        /****  保存点云  ****/
        /*
    	// 清除数据并退出
    	_cloud_now->points.clear();
    	_cloud_now->height = 480;
    	_cloud_now->width = 640;
    	_cloud_now->is_dense = false;
    	_cloud_now->points.resize(_cloud_now->width*_cloud_now->height);
    	// 坏点
    	const float bad_point = std::numeric_limits<float>::quiet_NaN();

    	std::cout<< "   "<< frame_now.depthMap.rows <<"  "<< frame_now.depthMap.cols<< std::endl;

    	for (int i = 0; i < frame_now.depthMap.rows; i++)
    		for (int j = 0; j<frame_now.depthMap.cols; j++)
    		{
    			PointT *point= &_cloud_now->points[i*_cloud_now->width+j];
    			// 获取深度图中(i,j)处的深度值
    			ushort d = frame_now.depthMap.ptr<ushort>(i)[j];

    			// 如果此处深度值为零，略过此点
    			if ( d <=300 || d>3600 || i<30 || i>450 || j<40 ||j>600)
    			{
    				point->x = point->y = point->z = bad_point;
    				point->rgba =0;
    				continue;
    			}


    			// 计算此点的三维空间
    			point->z = (double)d / Para_Reader->_camera_factor;           //  可以直接对Z轴滤波！！！！！！
    			point->x = (j-Para_Reader->_camera_cx) * point->z /Para_Reader->_camera_fx;
    			point->y = (i-Para_Reader->_camera_cy) * point->z /Para_Reader->_camera_fy;

    			// 获取此点的RGB
    			point->b = frame_now.bgrImage.ptr<uchar>(i)[j*3];
    			point->g = frame_now.bgrImage.ptr<uchar>(i)[j*3+1];
    			point->r = frame_now.bgrImage.ptr<uchar>(i)[j*3+2];

    	//		_cloud_now->at(j+1,i+1) =point;
    	//		_cloud_now->points[i*_cloud_now->width+j] = &point;
    			// 将点加入到点云中(此时点云is not organized)
    			//_cloud_now->push_back(point);
    		}
    	std::cout<< "   "<< _cloud_now->size()<<"   "<< _cloud_now->width<< std::endl;
    	// 点云格式设置
    	//_cloud_now->height = 1;
    	//_cloud_now->width = _cloud_now->size();

    	pcl::console::TicToc time;
    	time.tic();

    	// Voxel grid 滤波----unorganized
    	PointCloud::Ptr cloud_tmp(new PointCloud);
    	static pcl::VoxelGrid<PointT> voxel;
    	voxel.setLeafSize( Para_Reader->_grid_leaf, Para_Reader->_grid_leaf, Para_Reader->_grid_leaf );
    	voxel.setInputCloud( _cloud_now );
    	voxel.filter( *cloud_tmp );
    	pcl::copyPointCloud(*cloud_tmp, *_cloud_now);

    	cout << "\nOrigin PointCloud voxel grid filter: " << time.toc () << " ms\n" << endl;
    	std::cout<< "   "<< _cloud_now->size()<<"   "<< _cloud_now->width<< std::endl;

    	// 点云保存
        ss_index << "../data/pointcloud/pointcloud"<<index<<".pcd";
        ss_index>>pcdname;
        ss_index.clear();
        if (Para_Reader->_save_pointcloud)
        {
        	pcl::io::savePCDFile(pcdname, *_cloud_now);     // 存储点云影响速度，30Hz降至2.7Hz
        	cout<<"Point cloud saved."<<endl;
        }
    */


    }
}


void captureImage_generatePointCloud::generatePointCloud()
{
	// 清除数据并退出
	_cloud_now->points.clear();
	_cloud_now->height = 480;
	_cloud_now->width = 640;
	_cloud_now->is_dense = false;
	_cloud_now->points.resize(_cloud_now->width*_cloud_now->height);
	// 坏点
	const float bad_point = std::numeric_limits<float>::quiet_NaN();

	std::cout<< "   "<< frame_now.depthMap.rows <<"  "<< frame_now.depthMap.cols<< std::endl;

	for (int i = 0; i < frame_now.depthMap.rows; i++)
		for (int j = 0; j<frame_now.depthMap.cols; j++)
		{
			PointT *point= &_cloud_now->points[i*_cloud_now->width+j];
			// 获取深度图中(i,j)处的深度值
			ushort d = frame_now.depthMap.ptr<ushort>(i)[j];

			// 如果此处深度值为零，略过此点
			if ( d <=300 || d>3600 || i<30 || i>450 || j<40 ||j>600 )
			{
				point->x = point->y = point->z = bad_point;
				point->rgba =0;
				continue;
			}


			// 计算此点的三维空间
			point->z = (double)d / Para_Reader->_camera_factor;           //  可以直接对Z轴滤波！！！！！！
			point->x = (j-Para_Reader->_camera_cx) * point->z /Para_Reader->_camera_fx;
			point->y = (i-Para_Reader->_camera_cy) * point->z /Para_Reader->_camera_fy;

			// 获取此点的RGB
			point->b = frame_now.bgrImage.ptr<uchar>(i)[j*3];
			point->g = frame_now.bgrImage.ptr<uchar>(i)[j*3+1];
			point->r = frame_now.bgrImage.ptr<uchar>(i)[j*3+2];

	//		_cloud_now->at(j+1,i+1) =point;
	//		_cloud_now->points[i*_cloud_now->width+j] = &point;
			// 将点加入到点云中(此时点云is not organized)
			//_cloud_now->push_back(point);
		}
	std::cout<< "   "<< _cloud_now->size()<<"   "<< _cloud_now->width<< std::endl;
	// 点云格式设置
	//_cloud_now->height = 1;
	//_cloud_now->width = _cloud_now->size();

	pcl::console::TicToc time;
	time.tic();
/*
	// Voxel grid 滤波----unorganized
	PointCloud::Ptr cloud_tmp(new PointCloud);
	static pcl::VoxelGrid<PointT> voxel;
	voxel.setLeafSize( Para_Reader->_grid_leaf, Para_Reader->_grid_leaf, Para_Reader->_grid_leaf );
	voxel.setInputCloud( _cloud_now );
	voxel.filter( *cloud_tmp );
	pcl::copyPointCloud(*cloud_tmp, *_cloud_now);

	cout << "\nOrigin PointCloud voxel grid filter: " << time.toc () << " ms\n" << endl;
	std::cout<< "   "<< _cloud_now->size()<<"   "<< _cloud_now->width<< std::endl;
*/
	// 点云保存
    ss_index << "../data/pointcloud/pointcloud"<<index<<".pcd";
    ss_index>>pcdname;
    ss_index.clear();
    if (Para_Reader->_save_pointcloud)
    {
    	pcl::io::savePCDFile(pcdname, *_cloud_now);     // 存储点云影响速度，30Hz降至2.7Hz
    	cout<<"Point cloud saved."<<endl;
    }

}


























