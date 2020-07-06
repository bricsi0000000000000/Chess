TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Field.cpp \
        GameManager.cpp \
        Grid.cpp \
        InputManager.cpp \
        Piece.cpp \
        PieceManager.cpp \
        Player.cpp \
        RuleManager.cpp \
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
