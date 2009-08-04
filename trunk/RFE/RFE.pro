TEMPLATE = vcapp
TARGET = RFE
DEPENDPATH += . RFE_ImagePreview RFE_MainWindow RFE_StandardItem RFE_Widget
INCLUDEPATH += . RFE_ImagePreview RFE_MainWindow RFE_StandardItem RFE_Widget
RESOURCES = icons.qrc
HEADERS = RFE_ImagePreview/RFE_ImagePreview.h \
          RFE_MainWindow/RFE_MainWindow.h \
          RFE_StandardItem/RFE_StandardItem.h \
          RFE_Widget/RFE_Widget.h
SOURCES = main.cpp \
          RFE_ImagePreview/RFE_ImagePreview.cpp \
          RFE_MainWindow/RFE_MainWindow.cpp \
          RFE_StandardItem/RFE_StandardItem.cpp \
          RFE_Widget/RFE_Widget.cpp
TRANSLATIONS = translations/RFE_de.ts
