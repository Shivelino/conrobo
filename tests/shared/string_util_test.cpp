/*********************************************************************
 * @file    string_util_test.cpp    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.6
 * @version 
 * @par Copyright(c): Conrobo Team
 * @par todo:
 * @par history: 
 *********************************************************************/
#include "shared/string_util.h"

#include <fstream>
#include <iostream>

#include "gtest/gtest.h"

// =============================================================================================
// #define DEBUG_LOG
// =============================================================================================

class StringUtilTest : public ::testing::Test {
protected:
    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(StringUtilTest, LowerAndUpper) {
    std::string test_file_path = std::string(PROJ_DATA_DIR) + "/test/shared/string_util_case.txt";
    std::ifstream test_file_stream(test_file_path.c_str());
    std::streambuf* originalCinBuffer = std::cin.rdbuf();  // 保存原始的 std::cin 缓冲区
    std::cin.rdbuf(test_file_stream.rdbuf());              // 将 std::cin 重定向到文件流

    std::string str1, str2, str3;
    while (std::cin >> str1 >> str2 >> str3) {
#ifdef DEBUG_LOG
        std::cout << str1 << '\t' << str2 << '\t' << str3 << std::endl;
#endif
        EXPECT_EQ(string_lower(str1), str2);
        EXPECT_EQ(string_upper(str1), str3);
    }

    std::cin.rdbuf(originalCinBuffer);  // 恢复原始的 std::cin 缓冲区
    test_file_stream.close();           // 关闭文件
}
