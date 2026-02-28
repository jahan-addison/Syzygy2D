cmake_minimum_required(VERSION 3.16)

# ESP-IDF project — target must be set before including the toolchain.
# Set via: idf.py set-target esp32s3  (or sdkconfig.defaults: CONFIG_IDF_TARGET)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(syzygy2d VERSION 0.1.0)
