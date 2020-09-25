include_directories(..)

add_executable(CardDriver CardDriver.cpp)
target_link_libraries(CardDriver Risk)

add_executable(DiceFacilityDriver DiceFacilityDriver.cpp)
target_link_libraries(DiceFacilityDriver Risk)

add_executable(MapDriver MapDriver.cpp)
target_link_libraries(MapDriver Risk)

add_executable(PlayerDriver PlayerDriver.cpp)
target_link_libraries(PlayerDriver Risk)

add_executable(PlayerStrategyDriver PlayerStrategyDriver.cpp)
target_link_libraries(PlayerStrategyDriver Risk)

add_executable(PhaseObserverDriver PhaseObserverDriver.cpp)
target_link_libraries(PhaseObserverDriver Risk)

add_executable(GameStatisticsObserverDriver GameStatisticsObserverDriver.cpp)
target_link_libraries(GameStatisticsObserverDriver Risk)