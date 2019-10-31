#include <iostream>
#include "Pixel.hpp"
#include "opencv2/opencv.hpp"

int main()
{
    cv::VideoCapture video("../Videos/00005.mp4");
    
    if(video.isOpened()) std::cout << "TOP" << "\n";
    else std::cout << "Fail..." << "\n";

    video.release();
    return 0;
}
