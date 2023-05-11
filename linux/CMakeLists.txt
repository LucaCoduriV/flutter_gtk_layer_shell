cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME "multi_gtk_window")
project(${PROJECT_NAME} LANGUAGES CXX)

# This value is used when generating builds using this plugin, so it must
# not be changed
set(PLUGIN_NAME "multi_gtk_window_plugin")

add_library(${PLUGIN_NAME} SHARED
  "desktop_multi_window_plugin.cc"
  "multi_window_manager.cc"
  "flutter_window.cc"
  "base_flutter_window.cc"
  "window_channel.cc"
  "flutter_layer_shell.cc"
)
apply_standard_settings(${PLUGIN_NAME})
set_target_properties(${PLUGIN_NAME} PROPERTIES
  CXX_VISIBILITY_PRESET hidden)

pkg_check_modules(GLS REQUIRED IMPORTED_TARGET gtk-layer-shell-0)

target_compile_definitions(${PLUGIN_NAME} PRIVATE FLUTTER_PLUGIN_IMPL)
target_include_directories(${PLUGIN_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PLUGIN_NAME} PRIVATE flutter)
target_link_libraries(${PLUGIN_NAME} PRIVATE PkgConfig::GTK)
target_link_libraries(${PLUGIN_NAME} PRIVATE PkgConfig::GLS)

# List of absolute paths to libraries that should be bundled with the plugin
set(multi_gtk_window_libraries
  ""
  PARENT_SCOPE
)
