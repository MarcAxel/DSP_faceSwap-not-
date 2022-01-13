#include "faceSwap.h"


void FaceSwap::loadFiles(cv::String faceCascadeFilename,
                       cv::String eyeCascadeFilename,
                             cv::String smileCascadeFilename)
{
    // TODO: Add in a try catch statement here
    if( !faceCascade.load( faceCascadeFilename ) )
    {
        std::cout << "Error Loading" << faceCascadeFilename << std::endl;
    }

    if( !eyeCascade.load( eyeCascadeFilename ) )
    {
        std::cout << "Error Loading" << eyeCascadeFilename << std::endl;
    }
    if( !smileCascade.load( smileCascadeFilename ) )
    {
        std::cout << "Error Loading" << smileCascadeFilename << std::endl;
    }
}
FaceSwap::~FaceSwap()
{

}
void FaceSwap::buff(const QImage &frame){
    if (cameraIndex>0)cap.open(cameraIndex);
    else cap.open(0); //default

        if( !cap.isOpened() ) return;
        cap >> capture;

        Mat grey_image;
        Mat grey_capt;
        vector<Rect> faces;
        cvtColor(capture, grey_capt, COLOR_BGR2GRAY);
        equalizeHist(grey_capt, grey_capt);
        faceCascade.detectMultiScale(grey_image, faces, 1.1, 2,  0|CASCADE_SCALE_IMAGE,
                                     cv::Size(capture.cols/4, capture.rows/4));

        medianBlur(capture, smooth, 5);
        for( int i = 0; i < 10; i++)
            medianBlur(smooth, smooth, 5);
        Canny(smooth, edge, 50, 100, 3);
        std::vector<Vec4i> lines;
        HoughLinesP(edge, lines, 1, CV_PI/180, 100, 50, 10 );
        capture.copyTo( hline );
        for( size_t i = 0; i < lines.size(); i++ ){
            Vec4i l = lines[i];
            line( hline, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
        }

//     Point2f srcTri[3];
//     srcTri[0] = Point2f( 0.f, 0.f );
//     srcTri[1] = Point2f( frame.cols - 1.f, 0.f );
//     srcTri[2] = Point2f( 0.f, frame.rows - 1.f );
//     Point2f dstTri[3];
//     dstTri[0] = Point2f( 0.f, frame.rows*0.33f );
//     dstTri[1] = Point2f( frame.cols*0.85f, frame.rows*0.25f );
//     dstTri[2] = Point2f( frame.cols*0.15f, frame.rows*0.7f );
//    if(faces.size()!=temfaces.size()) faces.resize(temfaces.size());

//    cv::Mat imgWrap = frame.clone();
//    std::vector<cv::Point2f> point1;
//    std::vector<cv::Point2f> point2;

    //-- Draw rectangles around faces
//    for( size_t i = 0; i < faces.size(); i++){
       // cv::rectangle(frame, faces[i], cv::Scalar( 255, 0, 255 ));

//        Point2f center( faces[i].x + faces[i].width*0.5,
//                  faces[i].y + faces[i].height*0.5);
//        point1[i] = center;

 //        cv::Mat faceROI = grey_image( faces[i] );
//        std::vector<cv::Rect> eyes;

//        //-- In each face, detect eyes
//        eyeCascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0|CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

//        for( size_t j = 0; j < eyes.size(); j++)
//        {
//            cv::Point center( faces[i].x + eyes[j].x + eyes[j].width*0.5,
//                      faces[i].y + eyes[j].y + eyes[j].height*0.5 );
//            int radius = cvRound( (eyes[j].width + eyes[j].height) *0.25);
//            circle( frame, center, radius, cv::Scalar( 200, 80, 0 ), 2, 4, 0);
//       }
//    }
//    for( size_t i = 0; i < temfaces.size(); i++){
//        Point2f center( temfaces[i].x + temfaces[i].width*0.5,
//                  temfaces[i].y + temfaces[i].height*0.5);
//        point2[i] = center;}

//    vector<Point2f> bound1;
//    vector<Point2f> bound2;
//    vector<int> index;
//    convexHull(Mat(point1), index, false, false);
//    for(size_t i = 0; i<index.size();i++){
//    bound1.push_back(point1[index[i]]);
//    bound2.push_back(point2[index[i]]);}

//    Rect rect(0,0, imgWrap.cols, imgWrap.rows);
//    vector<vector<int>> triangles;
//    cv::Mat wrap_mat = getAffineTransform(srcTri, dstTri);
//    cv::Mat wrap_des = cv::Mat::zeros(frame.rows, frame.cols, frame.type());
//    warpAffine(frame, wrap_des, wrap_mat, wrap_des.size());
//    vector<Point> hull;
 //   for(size_t i = 0; i < bound1.size(); i++)
 //   {
 //       Point pt((int)bound1[i].x,(int)bound1[i].y);
 //       hull.push_back(pt);
 //   }
 //   Mat mask = Mat::zeros(frame.rows, frame.cols, frame.depth());
 //   fillConvexPoly(mask,&hull[0],(int)hull.size(), Scalar(255,255,255));
 //   Rect r = boundingRect(bound1);
 //   Point centers = (r.tl() + r.br()) / 2;
 //   Mat output;
 //   wrap_des.convertTo(wrap_des, CV_8UC3);
//    cv::seamlessClone(wrap_des,tem_frame_,mask, centers, output, NORMAL_CLONE);

     /*std::vector<cv::Rect> smile;
     smileCascade.detectMultiScale(grey_image,smile, 1.1, 2, 0|CASCADE_SCALE_IMAGE, cv::Size(30, 30));
     for( size_t k = 0; k < smile.size(); k++)
     {
         cv::rectangle(frame, smile[k], cv::Scalar( 0, 150, 150 ),2,4,0);
     }*/

    QImage image = MatToQImage(hline);
    emit image_signal(image);
}
void FaceSwap::cameraIndexload(int index){
    cameraIndex = index;
}
void FaceSwap::running(const QImage &frame){
    frame_oper = frame;
    buff(frame);
}
