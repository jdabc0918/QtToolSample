#pragma once

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

//	Standard
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <math.h>

//	OpenCV
#include <opencv2/opencv.hpp>
#ifdef _DEBUG
#pragma comment(lib,"opencv_world310d.lib")		// opencv_world
#else
#pragma comment(lib,"opencv_world310.lib")			// opencv_world
#endif

//	Boost
#include <boost\filesystem.hpp>
#include <boost\format.hpp>
namespace fs = boost::filesystem;

//	Qt
#include <QDebug>
#include <QMessageBox>

//	<3ŽŸŒ³À•W, ƒRƒƒ“ƒg>Œ^
typedef std::pair<cv::Point3f, std::string> PointWithComment;