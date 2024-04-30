find_package(SQLite3)

add_library(user-mgmt-lib mgmt.cpp)
target_include_directories(user-mgmt-lib PUBLIC include)
target_include_directories(user-mgmt-lib PUBLIC /usr/include)
link_directories(/usr/lib/x86_64-linux-gnu)
target_link_libraries(user-mgmt-lib PUBLIC sqlite3)

add_executable(user-mgmt cli.cpp)
target_link_libraries(user-mgmt user-mgmt-lib)

