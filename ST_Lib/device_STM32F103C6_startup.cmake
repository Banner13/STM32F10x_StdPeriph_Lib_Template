include_guard()
message("device_STM32F103C6_startup component is included.")

file(GLOB ST_LIB_SRC_FILE 
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/STM32F10x_StdPeriph_Driver/src/*.c
)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/gcc_ride7/startup_stm32f10x_ld.s
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
    ${CMAKE_CURRENT_LIST_DIR}/stm32f10x_it.c
    ${ST_LIB_SRC_FILE}
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/CMSIS/CM3/CoreSupport
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/
    ${CMAKE_CURRENT_LIST_DIR}/Libraries/STM32F10x_StdPeriph_Driver/inc
    ${CMAKE_CURRENT_LIST_DIR}/
)

include(device_STM32F103C6_startup)

