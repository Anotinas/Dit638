#pragma once
#include <string>
//#include "../control/cluon-complete.hpp"

namespace cv{

    int COLOR_BGR2HSV = 5;
    const int CAP_PROP_FRAME_WIDTH = 50;
    const int CAP_PROP_FRAME_HEIGHT = 51;
    const int RETR_CCOMP = 30;
    const int CHAIN_APPROX_SIMPLE = 31;

    class Scalar {
        private:

        public:
        Scalar(int low, int high, int thing);
    };

    class Mat {
        private:

        public:
        Mat();
        };

    class CascadeClassifier{
        char* filePath;
        private:

        public:        
        CascadeClassifier();

        void load (char* filePath);
    };

    class VideoCapture{
        private:

        public:
        VideoCapture(int limit);
        void read(Mat image);
        bool isOpened();
        void set(int value, int setting);
    };

    class Point{
        int x;
        int y;
        public:
        Point(int x, int y);
    };

    class Vec4i{
        int x_1;
        int y_1;
        int x_2;
        int y_2;
        public:
        Vec4i(int x_1, int y_1, int x_2, int y_2);
    };

    class Moments{

        public:
        moments(Mat image);

    };

    void imshow();
    void imshow(char* tipe ,Mat content);

    void cvtColor();
    void cvtColor(Mat first, Mat second, int third);

    bool waitKey(int time);

    void inRange(Mat hsv, Scalar low, Scalar high, Mat frame);

    //Add the last two here
    // void findContours(Mat image, std::vector* contours, std::vector* hierarchy, int retr1, int retr2);

}