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
#include "capture.hpp"
#include "handler/video-impl.hpp"

namespace conrobo {

using Video = Cam<video::details::VideoHandler>;

}  // namespace conrobo
