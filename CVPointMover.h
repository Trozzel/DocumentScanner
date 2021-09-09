//
// Created by George Ford on 8/29/21.
//

#ifndef DOCUMENTSCANNER_CVPOINTMOVER_H
#define DOCUMENTSCANNER_CVPOINTMOVER_H

#include <utility>
#include <vector>
#include <list>
#include <cmath>
#include <string>

#define sptr std::shared_ptr

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define BLUE          cv::Scalar(255,   0,   0)
#define GREEN         cv::Scalar(0,   255,   0)
#define RED           cv::Scalar(0,   0,   255)

typedef enum pointLoc {
  UPPER_LEFT, UPPER_RIGHT, LOWER_RIGHT, LOWER_LEFT
} PointLoc;
std::string pointLocToString(PointLoc pl);

enum class LButtonEventStatus {
  Released,
  Pressed
};

// HINGES: the two(2) Points connected to each Point and the non-connected Point
const PointLoc HINGES[4][3] {
    {LOWER_RIGHT, UPPER_RIGHT, LOWER_RIGHT}, // For UPPER_LEFT
    {UPPER_LEFT,  LOWER_RIGHT, LOWER_LEFT}, // For UPPER_RIGHT
    {UPPER_RIGHT, LOWER_RIGHT, UPPER_LEFT}, // For LOWER_RIGHT
    {UPPER_LEFT,  LOWER_RIGHT, UPPER_RIGHT}  // For LOWER_LEFT
};


void on_move(int event, int x, int y, int flags, void* data);

template <typename T>
class CVPointMover_
{
private:
  sptr<std::vector<cv::Point_<T>>>  pPoints; // starts from upper left and rotates CW
  sptr<cv::Mat> pCleanMat;
  sptr<cv::Mat> pDirtyMat;
  std::string winName;
  int pointRadius = 20; // circle of 20 pixels
  LButtonEventStatus btnStatus = LButtonEventStatus::Released;

  /************************** PRIVATE METHODS *********************************/
  // GET DISTANCES BETWEEN MOUSE-CLICK AND EVERY OTHER POINT
  PointLoc getClosestPoint(int x, int y, float& minDist)
  {
    // RETURNS A VALUE FROM PointLoc enum BY DETERMINING CLOSEST POINT
    // Also 'returns' dist as the minimum distance
    std::vector<float> distances(4);
    distances[UPPER_LEFT]  = sqrt(std::pow(x-pPoints->at(UPPER_LEFT).x,2) +
                                  std::pow(y-pPoints->at(UPPER_LEFT).y,2));
    distances[UPPER_RIGHT] = sqrt(std::pow(x-pPoints->at(UPPER_RIGHT).x,2) +
                                  std::pow(y-pPoints->at(UPPER_RIGHT).y,2));
    distances[LOWER_RIGHT] = sqrt(std::pow(x-pPoints->at(LOWER_RIGHT).x,2) +
                                  std::pow(y-pPoints->at(LOWER_RIGHT).y,2));
    distances[LOWER_LEFT]  = sqrt(std::pow(x-pPoints->at(LOWER_LEFT).x,2) +
                                  std::pow(y-pPoints->at(LOWER_LEFT).y,2));

    // ACQUIRE WHICH POINT IS CLOSEST TO MOUSE CLICK
    ptrdiff_t closestPtIdx = std::min_element(distances.cbegin(),
                                      distances.cend()) - distances.cbegin();
    //minDist = *(std::min(distances.cbegin(), distances.cend()));
    minDist = distances[closestPtIdx];
    return static_cast<PointLoc>(closestPtIdx);
  }

public:
  /**************************** CONSTRUCTORS **********************************/
  CVPointMover_() = default;
  CVPointMover_(sptr<std::vector<cv::Point_<T> > > points,
                sptr<cv::Mat> cleanMat,
                sptr<cv::Mat> dirtyMat,
                std::string name = "Window") : winName(std::move(name))
  {
    pPoints   = points;
    pCleanMat = cleanMat;
    pDirtyMat = dirtyMat;
    drawLines();
  }
  CVPointMover_(std::vector<cv::Point_<T> >*  points,
                   cv::Mat* cleanMat,
                   cv::Mat* dirtyMat,
                   std::string name = "Window") : winName(std::move(name))
  {
    pPoints   = sptr<std::vector<cv::Point_<T>>>(points);
    pCleanMat = sptr<cv::Mat>(cleanMat);
    pDirtyMat = sptr<cv::Mat>(dirtyMat);
    drawLines();
  }
  ~CVPointMover_() = default;
  CVPointMover_(const CVPointMover_<T>& src)
  {
    pPoints   = src.pPoints;
    pCleanMat = src.pCleanMat;
    pDirtyMat = src.pDirtyMat;
    winName   = src.winName;
    drawLines();
  }
  CVPointMover_& operator=(const CVPointMover_<T>& src)
  {
    if (!src.pPoints->empty())
      pPoints = src.pPoints;
    if (!src.pCleanMat->empty())
      pCleanMat = src.pCleanMat;
    if (!src.pDirtyMat->empty())
      pDirtyMat = src.pDirtyMat;
    if(!src.winName.empty())
      winName = src.winName;
    drawLines();
    return *this;
  }

  /***************************** SETTERS **************************************/
  void setPPoints(const std::shared_ptr<std::vector<cv::Point_<T>>>& pPoints)
  {
    CVPointMover_::pPoints = pPoints;
  }
  void setPCleanMat(const std::shared_ptr<cv::Mat>& pCleanMat)
  {
    CVPointMover_::pCleanMat = pCleanMat;
  }
  void setPDirtyMat(const std::shared_ptr<cv::Mat>& pDirtyMat)
  {
    CVPointMover_::pDirtyMat = pDirtyMat;
  }
  void setWinName(const std::string& winName)
  {
    CVPointMover_::winName = winName;
  }
  std::string getWinName() const
  {
    return winName;
  }
  /**************************** PUBLIC METHODS ********************************/
  // DRAW LINES TO FORM RECTANGLE
  void drawLines(const std::list<std::string>& messages =
                        {"Press any 'q' to Extract","Drag circles to correct"})
  {
    *pDirtyMat = pCleanMat->clone();
    // PLOT LINES AND CIRCLES
    for (int i=0; i<4; ++i)
    {
      cv::line(*pDirtyMat, pPoints->at(i),
               pPoints->at((i+1)%4), BLUE, 3);
      cv::circle(*pDirtyMat, pPoints->at(i),
                 pointRadius, BLUE,-1);
      int fontScale = 2;
      int thickness = 3;
      int pxl = 100;
      int y_plus = 0;
      for(auto& message : messages)
      {
        putText(*pDirtyMat, message, cv::Point(pxl,pxl+y_plus),
                cv::FONT_HERSHEY_SIMPLEX,1.3, GREEN, 3);
        y_plus+=60;
      }
      cv::putText(*pDirtyMat, std::to_string(i), pPoints->at(i),
                  cv::FONT_HERSHEY_SIMPLEX, fontScale, GREEN, thickness);
      imshow(winName, *pDirtyMat);
    }
  }

  // MOUSE EVENT WRAPPER
  void mouseEventHandler(int event, int x, int y, int flags, void* data)
  {
    static sptr<cv::Point_<T> > pActivePoint;
    static PointLoc pointLoc;
    static float minDist{};

    switch (event)
    {
    case cv::EVENT_LBUTTONDOWN:
      // getClosestPoint returns the closest Point and the distance between the
      // clicked point and the nearest Point
      // Also check if within the bounds of radius
      pointLoc = getClosestPoint(x,y, minDist);
      if (minDist <= pointRadius * 5)
      {
        btnStatus = LButtonEventStatus::Pressed;
        pActivePoint = std::make_shared<cv::Point_<T>>(pPoints->at(pointLoc));
      }
      break;
    case cv::EVENT_LBUTTONUP:
      btnStatus = LButtonEventStatus::Released;
      pActivePoint = nullptr;
      break;
    case cv::EVENT_MOUSEMOVE:
      if (btnStatus == LButtonEventStatus::Pressed)
      {
        cv::Mat tempMat = pCleanMat->clone();
        pActivePoint->x = x;
        pActivePoint->y = y;
        pPoints->at(pointLoc).x = x;
        pPoints->at(pointLoc).y = y;
        drawLines();
      }
    default:
      break;
    }
  }

  // STATIC METHOD FOR MOUSE EVENT
  /****************************************************************************/
  //static void on_move(int event, int x, int y, int flags, void* data)
  //{
  //  auto* cvpm = (CVPointMover_<T>*)data;
  //  cvpm->mouseEventHandler(event,x,y,flags, nullptr);
  //}
};

/******************************************************************************/
template<typename T>
void on_move(int event, int x, int y, int flags, void* data)
{
  auto* cvpm = static_cast<CVPointMover_<T>*>(data);
  cvpm->mouseEventHandler(event,x,y,flags, nullptr);
}


using CVPointMover = CVPointMover_<int>;

#endif //DOCUMENTSCANNER_CVPOINTMOVER_H
