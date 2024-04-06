/*********************************************************************
 * @file    cam.hpp    
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
#include "handler/usbcam-impl.hpp"

namespace conrobo {

using CamUSB = Cam<video::details::UsbCamHandler>;

}  // namespace conrobo
