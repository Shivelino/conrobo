/*********************************************************************
 * @file    video.hpp    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.7
 * @version 
 * @par Copyright(c): Conrobo Team
 * @par todo:
 * @par history: 
 *********************************************************************/
#pragma once
#include <string>

#include <opencv2/core.hpp>  // opencv
#include <opencv2/opencv.hpp>

#include "base.h"

namespace conrobo {

namespace video::details {

class VideoHandler {
public:
    struct Config {
        std::string path;
    };

private:
    Config _config;
    cv::VideoCapture _cap;

public:
    ALWAYS_INLINE_FUNCTION VideoHandler(Config config) {
        _config = config;
        _cap = cv::VideoCapture(_config.path);
    }

    ALWAYS_INLINE_FUNCTION ~VideoHandler() = default;

public:
    ALWAYS_INLINE_FUNCTION std::string cam_type_info_impl() { return std::string("VideoHandler"); }

    ALWAYS_INLINE_FUNCTION void display_impl() {
        cv::Mat frame;
        while (true) {
            _cap >> frame;
            if (!frame.empty()) {
                cv::imshow("cam live", frame);
                int key = cv::waitKey(1);
                if (key == (int)'q')
                    break;
            } else
                break;
        }
    }

    ALWAYS_INLINE_FUNCTION void frame_impl(cv::Mat& frame) { _cap >> frame; }
};

}  // namespace video::details
}  // namespace conrobo
