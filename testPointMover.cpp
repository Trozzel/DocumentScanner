//
// Created by George Ford on 8/30/21.
//
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

#include "CVPointMover.h"
#include "DSUtilities.h"

using namespace std;
using namespace cv;
namespace fs = __fs::filesystem;

static void on_mouse(int event, int x, int y, int flags, void* data);

int main()
{
  // NOTE: CTOR WILL HANDLE POINTER DELETION
  auto* cleanImg = new Mat(imread("../images/document1.jpg"));
  auto* dirtyImg = new Mat(cleanImg->clone());
  auto* points  =  new vector<cv::Point> ({
    cv::Point(100,100), cv::Point(1000,100),
    cv::Point(1000, 1000), cv::Point(100, 1000)
  });
  string winName = "Window";
  namedWindow(winName);
  //CVPointMover cvpm(points, cleanMat, dirtyMat,
  //                  winName);

  CVPointMover cvpm2(points, cleanImg, dirtyImg, "Window");

  imshow("Window", *dirtyImg);
  setMouseCallback("Window", on_mouse, &cvpm2);
  waitKey();
}
/******************************************************************************/
void on_mouse(int event, int x, int y, int flags, void* data)
{
  auto* cvpm = (CVPointMover*)data;
  cvpm->mouseEventHandler(event,x,y,flags, nullptr);
}
