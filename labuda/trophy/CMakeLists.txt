add_executable(trophy main.cpp check_point.h visitors.h)
add_executable(trophy_wx main_wx.cpp check_point.h visitors.h visitor_wx.h)

find_package(wxWidgets 3.0.5 REQUIRED)
include(${wxWidgets_USE_FILE})

target_link_libraries(trophy_wx ${wxWidgets_LIBRARIES} ${OPENGL_LIBRARIES})
