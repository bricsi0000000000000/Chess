TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Grid.cpp \
        Piece.cpp \
        Player.cpp \
        main.cpp

HEADERS += \
 Color.h \
 Field.h \
 GameManager.h \
 Grid.h \
 InputManager.h \
 Piece.h \
 PieceManager.h \
 PieceType.h \
 Player.h \
 Position.h \
 RuleManager.h
