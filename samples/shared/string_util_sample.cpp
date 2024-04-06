/*********************************************************************
 * @file    string_util_sample.cpp    
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

#include "shared/string_util.h"

int main(int argc, char** argv) {
    // 转大写
    std::cout << string_upper("HelloWorld2023!") << std::endl;
    // 转小写
    std::cout << string_lower("HelloWorld2023!") << std::endl;
    return 0;
}
