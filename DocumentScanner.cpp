//
// Created by George Ford on 8/27/21.
//

#include "DocumentScanner.h"

#include <utility>

using namespace std;
using namespace cv;
using namespace chrono_literals; // ms, ns, s

/************************ CONSTRUCTOR ***************************************/
DocumentScanner::DocumentScanner(string filename, string cornersWinName,
                                 string finalWinName,
                                 int bordersz) :
  fileName(std::move(filename)), cornersWinName(cornersWinName), 
  finalWinName(finalWinName), borderSize(bordersz),
  pointMover(CVPointMover())
{
  if (!loadImage())
    handleError(DSErrorCodes::FILE_LOADING_ERROR);
  else
  {
    pDirtyImg = make_shared<cv::Mat> (Mat(pOrigImg->clone()));
    GaussianBlur(*pDirtyImg, *pDirtyImg,
                 cv::Size(9,9), 4.0);
    pMask = make_shared<cv::Mat> (Mat(pOrigImg->size(), CV_8U,
                                      Scalar(0)));
    Point_<int> upperLeft(borderSize, borderSize);
    Point_<int> lowerRight(pOrigImg->cols - borderSize,
                           pOrigImg->rows - borderSize);
    rect = make_shared<cv::Rect> (Rect_<int>(upperLeft, lowerRight));
    int x = rect->x;
    int y = rect->y;
    // NOTE: Points go CW

    // SET ARGUMENTS TO CVPointMover
    namedWindow(cornersWinName);
    cv::setMouseCallback(cornersWinName, on_move<int>, &pointMover);
    pointMover.setPCleanMat(shared_ptr<cv::Mat>(pOrigImg));
    pointMover.setPDirtyMat(shared_ptr<cv::Mat>(pDirtyImg));
    pointMover.setWinName(cornersWinName);
    grabCutMode = cv::GC_INIT_WITH_RECT;
    aspectRatio = 8.5 / 11; // 0.773
  }
}

// LOAD IMAGE
/******************************************************************************/
bool DocumentScanner::loadImage()
{
  pOrigImg  = make_shared<cv::Mat>(Mat(cv::imread(fileName)));
  // SCALE DOWN IMAGE IF TOO LARGE
  if (pOrigImg->cols > 2000)
    cv::resize(*pOrigImg, *pOrigImg,
               cv::Size(pOrigImg->cols / 2, pOrigImg->rows / 2),
               0, 0);
  return (!pOrigImg->empty());
}

// ERROR HANDLER
/******************************************************************************/
void DocumentScanner::handleError(DSErrorCodes errorCode)
{
  switch (errorCode)
  {
  case DSErrorCodes::FILE_LOADING_ERROR:
    cerr << "Could not load file, " << fileName << endl;
    throw runtime_error("File loading error");
  case DSErrorCodes::GRABCUT_ERROR:
    throw runtime_error("cv::grabCut error");
  default:
    throw runtime_error("Unknown option");
  }
}

// RUN GRAB CUT
/******************************************************************************/
void DocumentScanner::runGrabCut(int numIterations)
{
  Mat bgdModel, fgdModel;
  pGrabCutImg = make_shared<cv::Mat>(pDirtyImg->clone());
  Mat threshImg;
  cvtColor(*pGrabCutImg, threshImg, COLOR_BGR2GRAY);
  threshold(*pGrabCutImg, threshImg, 165, 255,
            THRESH_BINARY);
  imshow("Thresh", threshImg);
  waitKey();
  destroyWindow("Thresh");
  try
  {
    grabCut(threshImg, *pMask, *rect, bgdModel,
    //grabCut(*pDirtyImg, *pMask, *rect, bgdModel,
            fgdModel, numIterations, grabCutMode);
    cout << endl << "Done with grabCut" << endl;
  }
  catch (const char* exp)
  {
    cerr << "Exception: " << exp << endl;
    handleError(DSErrorCodes::GRABCUT_ERROR);
  }

  // REPLACE BACKGROUND AND PROBABLY BACKGROUND WITH BLACK (i.e. 0)
  for(int i = 0; i < pMask->rows; ++i)
    for(int j = 0; j < pMask->cols; ++j)
      if (pMask->ptr<uchar>(i, j)[0] == 0 || pMask->ptr(i, j)[2] == 2)
        for(int chanNum = 0; chanNum < 3; ++chanNum)
          pGrabCutImg->ptr(i, j)[chanNum] = 0;
}

[[maybe_unused]] void DocumentScanner::drawGrabCutRect()
{
  // draw grab rect
  Point_<int> point1(rect->x, rect->y);
  Point_<int> point2(rect->x + rect->width, rect->y + rect->height);
  cv::rectangle(*pDirtyImg, point1, point2, LIGHTBLUE);
  Mat combined;
  cv::hconcat(*pOrigImg, *pDirtyImg, combined);
  cv::imshow("Output", combined);
  waitKey();
}

void DocumentScanner::runFindContours()
{
  Mat imgGray;
  cvtColor(*pGrabCutImg, imgGray, COLOR_BGR2GRAY);
  vector<vector<cv::Point> > contours;
  vector<Vec4i> hierarchy;
  findContours(imgGray, contours, hierarchy,
               RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

  // Find contour with greatest area
  double area = -1.0;
  double tempArea = -1;
  int idx = 0;
  for(int i = 0; i < contours.size(); ++i)
  {
    if((tempArea = contourArea(contours[i])) > area)
    {
      area = tempArea;
      idx = i;
    }
  }

  // ASSUME THE PAPER IS THE LARGEST CONTOUR
  origPaperContour = std::move(contours[idx]); // transfer value to origPaperContour address
}

void DocumentScanner::findCorners()
{
  // TO ME, THIS SEEMS REDUNDANT.
  vector<cv::Point> approxRect;
  approxPolyDP(origPaperContour, approxRect, 1,
               true);
  cv::Rect paperRect = boundingRect(approxRect);

  // FIND EXTREME POINTS
  int minX = INT_MAX, maxX = 0;
  int minY = INT_MAX, maxY = 0;
  int minXIdx = -1, maxXIdx = -1;
  int minYIdx = -1, maxYIdx = -1;
  for(int i = 0; i < approxRect.size(); ++i)
  {
    if (approxRect[i].x > maxX)
    {
      maxX = approxRect[i].x;
      maxXIdx = i;
    }
    if (approxRect[i].x < minX)
    {
      minX = approxRect[i].x;
      minXIdx = i;
    }
    if (approxRect[i].y > maxY)
    {
      maxY = approxRect[i].y;
      maxYIdx = i;
    }
    if (approxRect[i].y < minY)
    {
      minY = approxRect[i].y;
      minYIdx = i;
    }
  }

  // Determine if rotated to left or to right
  if (approxRect[minXIdx].y < approxRect[maxXIdx].y)
  {
    orientation = DocOrientation::TO_LEFT;
    setCornerPoint(CornerPoints::UPPER_LEFT,  approxRect[minXIdx]);
    setCornerPoint(CornerPoints::UPPER_RIGHT, approxRect[minYIdx]);
    setCornerPoint(CornerPoints::LOWER_LEFT,  approxRect[maxYIdx]);
    setCornerPoint(CornerPoints::LOWER_RIGHT, approxRect[maxXIdx]);
  }
  else if (approxRect[minXIdx].y == approxRect[maxXIdx].y)
  {
    orientation = DocOrientation::UPRIGHT;
  }
  else
  {
    orientation = DocOrientation::TO_RIGHT;
    setCornerPoint(CornerPoints::UPPER_LEFT,  approxRect[minYIdx]);
    setCornerPoint(CornerPoints::UPPER_RIGHT, approxRect[maxXIdx]);
    setCornerPoint(CornerPoints::LOWER_LEFT,  approxRect[minXIdx]);
    setCornerPoint(CornerPoints::LOWER_RIGHT, approxRect[maxYIdx]);
  }
  cout << "Orientation of document: " << orientationToString(orientation)
       << endl;
}

/***************************** GETTERS & SETTERS ******************************/
void DocumentScanner::setAspectRatio(float ratio)
{
  aspectRatio = ratio;
}

void DocumentScanner::setCornerPoint(const CornerPoints cp, cv::Point& point)
{
  cornerPoints[cp] = std::move(point);
}

// DRAW LINES
/******************************************************************************/
void DocumentScanner::drawLines()
{
  if (orientation == DocOrientation::NOT_SET)
  {
    cout << "You must first find contours and corners" << endl;
    return;
  }
  auto points = make_shared<vector<cv::Point>>(vector<cv::Point>({
    cornerPoints[CornerPoints::UPPER_LEFT],
    cornerPoints[CornerPoints::UPPER_RIGHT],
    cornerPoints[CornerPoints::LOWER_RIGHT],
    cornerPoints[CornerPoints::LOWER_LEFT]}
  ));
  pointMover.setPPoints(shared_ptr<vector<cv::Point>>(points));
  pointMover.drawLines();
  // TODO: Place text for instructions here
  char c;
  while (true)
  {
    c = static_cast<char>(waitKey());
    if (c == 'q')
      break;
  }
  // MUST REASSIGN BACK TO cornerPoints map (Yes, should have just used vector)
  cornerPoints[CornerPoints::UPPER_LEFT]  = points->at(0);
  cornerPoints[CornerPoints::UPPER_RIGHT] = points->at(1);
  cornerPoints[CornerPoints::LOWER_RIGHT] = points->at(2);
  cornerPoints[CornerPoints::LOWER_LEFT]  = points->at(3);
}

// PERFORM FIND HOMOGRAPHY
/******************************************************************************/
void DocumentScanner::performFindHomography()
{
  // TRANSFER CORNER POINTS TO AN ARRAY
  vector<Point2f> srcPoints = {
    cornerPoints[CornerPoints::UPPER_LEFT],
    cornerPoints[CornerPoints::UPPER_RIGHT],
    cornerPoints[CornerPoints::LOWER_RIGHT],
    cornerPoints[CornerPoints::LOWER_LEFT]
  };

  // FIND DIMENSIONS FOR NEW MAT
  int w1 = cornerPoints[CornerPoints::UPPER_LEFT].x -
           cornerPoints[CornerPoints::UPPER_RIGHT].x;
  int h1 = cornerPoints[CornerPoints::UPPER_LEFT].y -
           cornerPoints[CornerPoints::UPPER_RIGHT].y;
  int dirtyImgW = static_cast<int>(sqrt(w1*w1 + h1*h1));
  int w2 = cornerPoints[CornerPoints::UPPER_LEFT].x -
           cornerPoints[CornerPoints::LOWER_LEFT].x;
  int h2 = cornerPoints[CornerPoints::UPPER_LEFT].y -
           cornerPoints[CornerPoints::LOWER_LEFT].y;
  int dirtyImgH = static_cast<int>(sqrt(w2*w2 + h2*h2));
  // TODO: Fix aspect ratio
  //  dirtyImgW /= aspectRatio;

  // GET DESTINATION POINTS
  vector<Point2f> dstPoints = {
    cv::Point(0,           0),
    cv::Point(dirtyImgW-1, 0),
    cv::Point(dirtyImgW-1, dirtyImgH-1),
    cv::Point(0,           dirtyImgH-1)
  };
  Mat h = findHomography(srcPoints, dstPoints, RANSAC);
  cv::Size finalSz(dirtyImgW, dirtyImgH);
  Mat finalImg(finalSz, CV_8U, Scalar(0));
  warpPerspective(*pOrigImg, finalImg, h, finalSz);
  imshow(finalWinName, finalImg);
  waitKey();
}

// RUN - MACRO
/******************************************************************************/
void DocumentScanner::run()
{
  // SPAWN THREAD FOR WAITING COMMAND LINE OUTPUT
  bool stopThread = false;
  string message = "Separating foreground from background";
  thread spinThread(spinWaiting, 300, std::ref(stopThread),
                    std::ref(message));
  // 1. GRABCUT
  this->runGrabCut(2);
  stopThread = true;
  message    = "Finished performing grabCut";
  spinThread.join();

  // 2. FIND CONTOURS
  this->runFindContours();

  // 3. FIND CORNERS
  this->findCorners();

  // 4. DRAW LINES
  this->drawLines();

  // 5. PERFORM findHomography
  this->performFindHomography();
}

// STATIC
string DocumentScanner::orientationToString(DocOrientation o)
{
  std::string docOrient;
  switch (o)
  {
  case DocOrientation::UPRIGHT:
    docOrient = "Upright";
    break;
  case DocOrientation::TO_LEFT:
    docOrient = "To left";
    break;
  case DocOrientation::TO_RIGHT:
    docOrient = "To right";
    break;
  default:
    docOrient = "Not a valid orientation";
    break;
  }
  return docOrient;
}









