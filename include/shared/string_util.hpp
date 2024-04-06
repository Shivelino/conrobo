/*********************************************************************
 * @file    string_util.h    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.6
 * @version 
 * @par Copyright(c): Shivelino Authorized
 * @par todo:
 * @par history: 
 *********************************************************************/
#pragma once
#include <algorithm>
#include <string>

#include "base.h"

namespace conrobo {
/**
 * @brief   字符串转小写.
 * @details
 * @param[in] s 输入字符串
 * @return  小写字符串
 * @par todo:
 * @par history:
 */
ALWAYS_INLINE_FUNCTION std::string string_lower(const std::string& s) {
    std::string ret = s;
    std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
    return ret;
}

/**
 * @brief   字符串转大写.
 * @details
 * @param[in] s 输入字符串
 * @return  大写字符串
 * @par todo:
 * @par history:
 */
ALWAYS_INLINE_FUNCTION std::string string_upper(const std::string& s) {
    std::string ret = s;
    std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
    return ret;
}
}  // namespace conrobo
