include_guard()
message("All external Library.")

# STM32F10x_StdPeriph_Driver
include(${CMAKE_CURRENT_LIST_DIR}/ST_Lib/STM32F10x_StdPeriph_Driver.cmake)

# U8G2 LCD display lib
include(${CMAKE_CURRENT_LIST_DIR}/u8g2_Lib/u8g2.cmake)
