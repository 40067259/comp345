set(SOURCES
        Card.cpp
        Territory.cpp
        Deck.cpp
        DiceFacility.cpp
        Die.cpp
		Game.cpp
        Hand.cpp
        Map.cpp
        MapLoader.cpp
		Observer.cpp
        Player.cpp
		Subject.cpp
		UserInterface.cpp
        Strategy.cpp
        HumanPlayer.cpp
        AggressivePlayer.cpp
        BenevolentPlayer.cpp)
set(HEADERS
        Card.h
        Territory.h
        Deck.h
        DiceFacility.h
        Die.h
		Game.h
        Hand.h
        Map.h
        MapLoader.h
		Observer.h
        Player.h
		Subject.h
		UserInterface.h
        Strategy.h
        HumanPlayer.h
        AggressivePlayer.h
        BenevolentPlayer.h)

add_library(Risk STATIC ${SOURCES} ${HEADERS})
add_executable(RiskGame RiskGame.cpp)
target_link_libraries(RiskGame Risk)