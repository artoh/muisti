
#include <QApplication>

#include <QDebug>
#include <QTextCodec>
#include <QTreeView>


#include "../xml/muistixmlmodel.h"
#include "../html/muistihtml.h"
#include <QtWebKitWidgets/QWebView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Muisti");
    a.setOrganizationName("Muisti");

    MuistiXmlModel model;
    model.lataaTiedosto("/tmp/muisti.xml");

    MuistiHtml kirjoittaja;
    kirjoittaja.asetaModel( &model);

    QWebView view;
    view.setHtml( kirjoittaja.html()  );
    view.show();

    model.tallennaTiedostoon("/tmp/ulos.xml");

    QTreeView puu;
    puu.setModel( &model);
    puu.show();


    return a.exec();
}
