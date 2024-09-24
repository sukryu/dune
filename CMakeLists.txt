cmake_minimum_required(VERSION 3.10)
project(dune15 LANGUAGES C CXX)

# 헤더 파일 경로 설정
include_directories(${PROJECT_SOURCE_DIR}/include)

# 실행 파일 생성
add_executable(
    ${PROJECT_NAME} 
    "src/display.c"
    "src/engine.c"
    "src/io.c"
    "src/utils.c"

    "include/common.h"
    "include/constants.h"
    "include/display.h"
    "include/game_state.h"
    "include/io.h"
    "include/utils.h"
)