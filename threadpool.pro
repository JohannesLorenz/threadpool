######################################################################
# Automatically generated by qmake (2.01a) Do. Apr 16 07:52:33 2015
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . \
	src/lib \
	src/test
INCLUDEPATH += . \
	src/include

# Input
HEADERS += src/include/threadpool.h \
	src/include/thread.h
SOURCES += src/lib/threadpool.cpp \
	src/lib/thread.cpp \
    src/test/test.cpp \
    src/test/test2.cpp

OTHER_FILES += src/lib/CMakeLists.txt \
	src/test/CMakeLists.txt \
	src/CMakeLists.txt \
	src/threadpool.pc.in \
	CMakeLists.txt
