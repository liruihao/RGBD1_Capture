#include "ParameterReader.h"

#include "captureImage_generatePointCloud.h"

#include <pcl/visualization/cloud_viewer.h>

// Eigen !
#include <Eigen/Core>
#include <Eigen/Geometry>


using namespace cv;
using namespace std;


int main( int argc, char* argv[] )
{
	// 创建类对象
	captureImage_generatePointCloud Image_PointCloud;


	//打开视频设备
    cout << "Device opening ..." << endl;
    Image_PointCloud.capture.open( CV_CAP_OPENNI );
    cout << "done." << endl;
    if( !Image_PointCloud.capture.isOpened() )
        cout << "Can not open a capture object." << endl;
    // 相机模式设置30Hz
    Image_PointCloud.capture.set( CV_CAP_OPENNI_IMAGE_GENERATOR_OUTPUT_MODE, CV_CAP_OPENNI_VGA_30HZ );
    Image_PointCloud.capture.set( CV_CAP_PROP_OPENNI_REGISTRATION, 1);

    cout << "\nDepth generator output mode:" << endl <<
            "FRAME_WIDTH      :" << Image_PointCloud.capture.get(CV_CAP_PROP_FRAME_WIDTH)<< endl <<
			"FRAME_HEIGHT      :" << Image_PointCloud.capture.get(CV_CAP_PROP_FRAME_HEIGHT)<< endl <<
			"FPS              " << Image_PointCloud.capture.get( CV_CAP_PROP_FPS ) << endl <<
			"BASELINE      " << Image_PointCloud.capture.get( CV_CAP_PROP_OPENNI_BASELINE ) << endl <<
			"FOCAL_LENGTH  " << Image_PointCloud.capture.get( CV_CAP_PROP_OPENNI_FOCAL_LENGTH ) << endl <<
			"FRAME_MAX_DEPTH  " << Image_PointCloud.capture.get( CV_CAP_PROP_OPENNI_FRAME_MAX_DEPTH ) << " mm" << endl <<
			"REGISTRATION?  :"<< Image_PointCloud.capture.get(CV_CAP_PROP_OPENNI_REGISTRATION) <<endl;

/******如果需要存储视频*******/
    if (Para_Reader->_save_video)
    {
        double rate=Image_PointCloud.capture.get(CV_CAP_PROP_FPS);
        Size videoSize(Image_PointCloud.capture.get(CV_CAP_PROP_FRAME_WIDTH),
        		Image_PointCloud.capture.get(CV_CAP_PROP_FRAME_HEIGHT));
        Image_PointCloud.writerdepth.open("../data/depth.avi",CV_FOURCC('P','I','M','1'),rate,videoSize);
        Image_PointCloud.writerrgb.open("../data/rgb.avi",CV_FOURCC('P','I','M','1'),rate,videoSize);
    }



    while (1)
	{
    	// 抓取视频和点云
		Image_PointCloud.captureImage();
//		Image_PointCloud.generatePointCloud();



		// 计算显示频率（存储点云影响速度---30Hz降至2.7Hz）
    	static unsigned count = 0;              // static变量只有一次初始化
        static double last = pcl::getTime ();   // static变量只有一次初始化
        if (++count == 30)
        {
          double now = pcl::getTime ();
          cout << " mm. Average framerate: " << double(count)/double(now - last) << " Hz" << endl;
          count = 0;
          last = now;
        }

        // 如果ESC键，则break
        if( waitKey( 2 ) >= 0 )  // delay，ms级别
            break;
	}

    return 0;
}
