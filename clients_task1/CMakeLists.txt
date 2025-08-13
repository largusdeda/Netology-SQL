cmake_minimum_required(VERSION 3.22.0)

project("clients_task_1")

set(PostgreSQL_ADDITIONAL_VERSIONS "17.5")
#set(PostgreSQL_ROOT "C:/Program Files/PostgreSQL/17")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_subdirectory(C:/libpqxx/libpqxx libpqxx-build)

add_executable(${PROJECT_NAME} main.cpp sql_class.h sql_class.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} pqxx)




