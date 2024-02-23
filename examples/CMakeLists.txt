cmake_minimum_required(VERSION 3.16)

project(light)

add_executable(${PROJECT_NAME}
	"light.cpp"
)

include_directories(PUBLIC
    "../include"
)
