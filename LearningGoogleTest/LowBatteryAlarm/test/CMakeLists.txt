cmake_minimum_required(VERSION 3.22)

set(This LowBatteryAlarmTests)

set(Sources
    LowBatteryAlarmTests.cpp
    m_led_mock.cpp
    m_adc_mock.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    gmock_main
    LowBatteryAlarm
)

add_test(
    NAME ${This}
    COMMAND ${This}
)