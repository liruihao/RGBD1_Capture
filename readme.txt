###########################################
RGBD1_capture
Author: Ruihao Li

Last update date: 29/10/2015

Tools: Xmotion

###########################################

lib installed first：
	OpenCV2.4.9，
	PCL1.8，
	EIGEN3，
	YAML(old version)


功能：
	利用openni驱动，获取图像和深度图的原始数据，并生成点云。其中depth image 和rgb image 已经registrated

function:
	using openni driver, capture the registrated rgb image and depth image, then generate pointcloud.
	
	
Here I use eclipse as IDE, so I will compile cmake file as below:
	
	cd ../build	
	cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../src 
	make
	
	
	
	Enjoy!
