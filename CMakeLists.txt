cmake_minimum_required(VERSION 3.10)
project(dune1.5 C)

# 헤더 파일 경로 설정
include_directories(${PROJECT_SOURCE_DIR}/include)

# 소스 파일 지정
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})
