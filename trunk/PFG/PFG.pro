# building an application
TEMPLATE = app

# build a debug version so we can debug ;)
# using the qt flag so that we can leave out the gui libs
CONFIG = console qt debug

# we do not need the gui here
QT -= gui

# our application name
TARGET = PFG
DEPENDPATH += .
INCLUDEPATH += .

# header files
HEADERS += create_module_vector.h \
           definitions.h \
           get_all_files.h \
           get_all_includes.h \
           get_modules.h \
           write_pro_file.h

# source files
SOURCES += create_module_vector.cpp \
           definitions.cpp \
           get_all_files.cpp \
           get_all_includes.cpp \
           get_modules.cpp \
           main.cpp \
           write_pro_file.cpp
