
QT	+=	core gui widgets webkitwidgets

SOURCES	+= \	
    model/muistimodel.cpp \
    model/muistinodemodel.cpp \
    model/muistinoodi.cpp \
    xml/muistixmlmodel.cpp \
    html/muistihtml.cpp \
    testi/main.cpp \
    proxymodel/muistihakuproxymodel.cpp

HEADERS += \ 
    model/muistimodel.h \
    model/muistinodemodel.h \
    model/muistinoodi.h \
    xml/muistixmlmodel.h \
    html/muistihtml.h \
    proxymodel/muistihakuproxymodel.h

RESOURCES += \ 
    model/modelPic.qrc \
    html/html.qrc

FORMS +=

OTHER_FILES +=
