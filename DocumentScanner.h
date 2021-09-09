//
// Created by George Ford on 8/27/21.
//

#ifndef DOCUMENTSCANNER_DOCUMENTSCANNER_H
#define DOCUMENTSCANNER_DOCUMENTSCANNER_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <map>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <MacTypes.h>
#include "DSUtilities.h"
#include "CVPointMover.h"

#ifndef RED
#define RED				  Scalar(0,  0,  255)
#endif
#ifdef PINK
#define PINK			  Scalar(230,130,255)
#endif
#ifndef BLUE
#define BLUE			  Scalar(255,0,  0  )
#endif
#ifndef LIGHTBLUE
#define LIGHTBLUE	  Scalar(255,255,160)
#endif
#ifndef GREEN
#define GREEN			  Scalar(0,  255,  0)
#endif

#define sptr std::shared_ptr

enum class DSErrorCodes
{
  FILE_LOADING_ERROR,
  GRABCUT_ERROR
};

enum class DocOrientation {
  NOT_SET, TO_LEFT, TO_RIGHT, UPRIGHT
};

enum class CornerPoints{
  UPPER_LEFT, UPPER_RIGHT, LOWER_LEFT, LOWER_RIGHT
};


class DocumentScanner
{
private:
  std::string fileName;
  std::string cornersWinName;
  std::string finalWinName;
  float aspectRatio; // 8.5 / 11 is default
  sptr<cv::Mat> pMask;
  sptr<cv::Mat> pOrigImg;
  sptr<cv::Mat> pDirtyImg;
  sptr<cv::Mat> pGrabCutImg;
  CVPointMover_<int> pointMover;
  int grabCutMode;
  int borderSize;
  DocOrientation orientation = DocOrientation::NOT_SET;
  sptr<cv::Rect> rect;
  std::map<CornerPoints, cv::Point> cornerPoints;
  std::vector<cv::Point> origPaperContour;

  /******************************* PRIVATE METHODS ****************************/
  bool loadImage();
  void handleError(DSErrorCodes errorCode);
  void runGrabCut(int numIterations=2);
  [[maybe_unused]] void drawGrabCutRect();
  void runFindContours();
  void findCorners();
  void performFindHomography();

public:

  /****************************** CONSTRUCTORS ********************************/
  explicit DocumentScanner(std::string filename, 
                           std::string cornersWinName = "Detection",
                           std::string finalWinName = "Extracted Document",
                           int bordersz = 2);
  virtual ~DocumentScanner() = default;

  /**************************** SETTERS & GETTERS *****************************/
  void setAspectRatio(float ratio);

  void setCornerPoint(CornerPoints cp, cv::Point& point);

  /*************************** PUBLIC METHODS *********************************/
  void drawLines();
  void run();

  /**************************** STATIC METHODS ********************************/
  static std::string orientationToString(DocOrientation o);
};


#endif //DOCUMENTSCANNER_DOCUMENTSCANNER_H
