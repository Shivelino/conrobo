/*********************************************************************
 * @file    veri_video.cpp    
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

#include "shared/filesystem.h"

#include "sensor/video/video.hpp"

int main() {
    using namespace conrobo;
    Video cam(Video::Config(path_join(PROJ_DATA_DIR, "video.mp4")));
    //cam.display();

    cv::Mat frame;
    cam.frame(frame);
    cv::imshow("cam live", frame);
    int key = cv::waitKey(0);

    return 0;
}
