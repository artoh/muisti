
QT	+=	core gui widgets webkit

SOURCES	+= \	
    model/muistimodel.cpp \
    model/muistinodemodel.cpp \
    model/muistinoodi.cpp \
    xml/muistixmlmodel.cpp \
    html/muistihtml.cpp \
    proxymodel/muistihakuproxymodel.cpp \
    mobiili/muistihakuikkuna.cpp \
    mobiili/main.cpp

HEADERS += \ 
    model/muistimodel.h \
    model/muistinodemodel.h \
    model/muistinoodi.h \
    xml/muistixmlmodel.h \
    html/muistihtml.h \
    proxymodel/muistihakuproxymodel.h \
    mobiili/muistihakuikkuna.h

RESOURCES += \ 
    model/modelPic.qrc \
    html/html.qrc

FORMS +=

OTHER_FILES +=
