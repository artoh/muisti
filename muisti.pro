
QT	+=	core gui widgets webkitwidgets

SOURCES	+= \	
    model/muistimodel.cpp \
    model/muistinodemodel.cpp \
    model/noodi/muistinoodi.cpp \
    model/noodi/muistinoodintieto.cpp \
    model/noodi/merkkijonotieto.cpp \
    model/muistixmlmodel.cpp

HEADERS += \ 
    model/muistimodel.h \
    model/muistinodemodel.h \
    model/noodi/muistinoodi.h \
    model/noodi/muistinoodintieto.h \
    model/noodi/merkkijonotieto.h \
    model/muistixmlmodel.h

RESOURCES += \ 
    model/modelPic.qrc

FORMS +=

OTHER_FILES +=
