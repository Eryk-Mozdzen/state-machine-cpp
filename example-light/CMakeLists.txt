cmake_minimum_required(VERSION 3.16)

project(example-light)

add_executable(${PROJECT_NAME}
	"example-light.cpp"
)

include_directories(PUBLIC
    "../sm"
)
