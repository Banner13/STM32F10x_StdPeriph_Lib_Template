include_guard()
message("u8g2 component is included. github: https://github.com/olikraus/u8g2")

file(GLOB ST_LIB_SRC_FILE 
    ${CMAKE_CURRENT_LIST_DIR}/csrc/*.c
)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ST_LIB_SRC_FILE}
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/csrc
)

