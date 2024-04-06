/*********************************************************************
 * @file    veri_usbcam.cpp    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.6
 * @version 
 * @par Copyright(c): Conrobo Team
 * @par todo:
 * @par history: 
 *********************************************************************/
#include <iostream>

#include "sensor/video/cam.hpp"

int main() {
    using namespace conrobo;
    CamUSB cam(CamUSB::Config(0));
    //cam.display();

    cv::Mat frame;
    cv::imshow("cam live", frame);
    int key = cv::waitKey(0);

    return 0;
}
