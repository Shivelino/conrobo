/*********************************************************************
 * @file    cam.hpp    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.6
 * @version 
 * @par Copyright(c): Conrobo Team
 * @par todo:
 * @par history: 
 *********************************************************************/
#pragma once
#include <concepts>
#include <string>
#include <type_traits>

#include "base.h"

namespace conrobo {

template <typename _Ty>
concept CamHandler = requires(_Ty obj) {
    typename _Ty::Config;
    { obj.cam_type_info_impl() } -> std::same_as<std::string>;
    { obj.display_impl() } -> std::same_as<void>;
    // frame_impl implemented by custom FrameTypes(by overload), so do not use frame_impl to check concept
};

template <CamHandler _Ty>
class Cam {
public:
    using Config = _Ty::Config;

private:
    _Ty* _handler = nullptr;

public:
    ALWAYS_INLINE_FUNCTION Cam() = default;
    ALWAYS_INLINE_FUNCTION Cam(const Cam&) = default;
    ALWAYS_INLINE_FUNCTION Cam(Cam&&) = default;
    ALWAYS_INLINE_FUNCTION Cam& operator=(const Cam&) = default;
    ALWAYS_INLINE_FUNCTION Cam& operator=(Cam&&) = default;

    ALWAYS_INLINE_FUNCTION Cam(Config config) { _handler = new _Ty(config); }

    ALWAYS_INLINE_FUNCTION ~Cam() {
        if (_handler != nullptr)
            delete _handler;
        _handler = nullptr;
    }

public:
    /**
     * @brief   .
     * @details cam into of CamHandler type, to identify if a type is CamHandler type.
     * @return   
     * @par todo:
     * @par history: 
     */
    ALWAYS_INLINE_FUNCTION std::string cam_type_info() { _handler->cam_type_info_impl(); }

public:
    ALWAYS_INLINE_FUNCTION void display() { _handler->display_impl(); }

    template <typename _Fty>
    ALWAYS_INLINE_FUNCTION void frame(_Fty& frame) {
        _handler->frame_impl(frame);
    }
};

}  // namespace conrobo
