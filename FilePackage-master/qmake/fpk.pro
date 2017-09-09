SOURCES += ../fpk/*.cpp \
			../fpk/Utility/*.cpp \
			../test/*.cpp \
			../main.cpp \

HEADERS += ../fpk/*.h \
			../fpk/Utility/*.h \
			../test/*.h

CONFIG  = console warn_off debug
QMAKE_CXXFLAGS += -std=c++11
DESTDIR = ./bin
