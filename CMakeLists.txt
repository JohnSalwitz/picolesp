cmake_minimum_required(VERSION 3.20)
project(picolesp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(archive)

add_executable(picolesp
        archive/ESPRelaySlave.ino
        archive/networking.cpp
        archive/networking.h
        archive/picol.h
        archive/picol_glue.cpp
        cloud_mqqt.cpp
        cloud_mqqt.h
        debug2.cpp
        debug2.h
        esp_relay.cpp
        esp_relay.h
        led_status.cpp
        led_status.h
        logger.cpp
        logger.h
        picol.h
        picol_glue.cpp
        picol_glue.h
        picolesp.ino
        settings.h
        static_storage.cpp
        static_storage.h
        subscriptions.cpp
        subscriptions.h
        version.h credentials.h clock_timer.cpp clock_timer.h event.cpp event.h)
