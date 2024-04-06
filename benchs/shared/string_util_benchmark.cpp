/*********************************************************************
 * @file    string_util_benchmark.cpp    
 * @brief   
 * @details  
 * @author  Shivelino
 * @date    2024.4.6
 * @version 
 * @par Copyright(c): Conrobo Team
 * @par todo:
 * @par history: 
 *********************************************************************/
#include <benchmark/benchmark.h>

#include "shared/string_util.hpp"

using namespace conrobo;

class StringUtilFixture : public benchmark::Fixture {
public:
    void SetUp(benchmark::State& state) override {}

    void TearDown(benchmark::State& state) override {}
};

BENCHMARK_DEFINE_F(StringUtilFixture, Lower)(benchmark::State& state) {
    std::string data = "7898y&(FY&(HEWYhhgnA89f2F38sdg0h3Y&J*(Y&*(93y893y";
    for (auto _ : state) {
        std::string res = string_lower(data);
    }
}

BENCHMARK_REGISTER_F(StringUtilFixture, Lower)->Unit(benchmark::kMillisecond);

BENCHMARK_DEFINE_F(StringUtilFixture, Upper)(benchmark::State& state) {
    std::string data = "7898y&(FY&(HEWYhhgnA89f2F38sdg0h3Y&J*(Y&*(93y893y";
    for (auto _ : state) {
        std::string res = string_upper(data);
    }
}

BENCHMARK_REGISTER_F(StringUtilFixture, Upper)->Unit(benchmark::kMillisecond);
