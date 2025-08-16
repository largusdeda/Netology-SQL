cmake_minimum_required(VERSION 3.22.0)

project("orm_homework")

set(PostgreSQL_ADDITIONAL_VERSIONS "17.5")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

find_package(Wt REQUIRED)

add_library(lib SHARED 
    lib/db.h 
    lib/db.cpp 
    lib/book.h 
    lib/book.cpp 
    lib/publisher.h 
    lib/publisher.cpp 
    lib/sale.h 
    lib/sale.cpp 
    lib/shop.h 
    lib/shop.cpp 
    lib/stock.h 
    lib/stock.cpp 
)

target_link_libraries(lib PRIVATE
    Wt::Dbo
    Wt::DboPostgres
)
target_include_directories(lib PRIVATE
    ${Wt_INCLUDE_DIR}
)

include_directories(lib)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Wt::Dbo
    Wt::DboPostgres
    lib
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Wt_INCLUDE_DIR}
)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32)
endif()



