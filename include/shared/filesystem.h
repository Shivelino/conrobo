/*********************************************************************
 * @file    filesystem.h    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.3.25
 * @version 
 * @par Copyright(c): Shivelino Authorized
 * @par todo:
 * @par history: 
 *********************************************************************/
#pragma once
#include <filesystem>
#include <string>

namespace conrobo {

/**
 * @brief   .
 * @details  
 * @return   
 * @par todo:
 * @par history: 
 */
template <typename _Ty>
inline std::string path_join(_Ty first) {
    return std::string(first);
}

/**
 * @brief   .
 * @details  
 * @param[in] first
 * @param[in] ...args
 * @return   
 * @par todo:
 * @par history: 
 */
template <typename _Ty, typename... Args>
inline std::string path_join(_Ty first, Args... args) {
    std::filesystem::path ret = std::filesystem::path(first) / path_join(args...);
    return ret.string();
}

/**
 * @brief   .
 * @details  
 * @param[in] folder_path
 * @return   
 * @par todo:
 * @par history: 
 */
inline void mkdir(const std::string& folder_path) {
    if (!std::filesystem::exists(folder_path)) {
        std::filesystem::create_directory(folder_path);
    }
}

}  // namespace conrobo
