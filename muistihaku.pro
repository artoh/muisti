
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
    html/html.qrc \
    mobiili/mobiili.qrc

FORMS +=

OTHER_FILES += \
    html/muistihtml.js \
    html/muistihtml.css \
    mobiili/muistihtml.css

maemo5 {
    target.path = /opt/muistihaku/bin
    INSTALLS += target
}

maemo5 {
    desktopfile.files = muistihaku.desktop
    desktopfile.path = /usr/share/applications/hildon
    INSTALLS += desktopfile
}

maemo5 {
    icon.files = muistihaku.png
    icon.path = /usr/share/icons/hicolor/64x64/apps
    INSTALLS += icon
}
