
#include <QApplication>

#include <QDebug>
#include <QTextCodec>
#include <QTreeView>



#include "../xml/muistixmlmodel.h"
#include "../html/muistihtml.h"
#include "../proxymodel/muistihakuproxymodel.h"
#include <QtWebKitWidgets/QWebView>

#include <QSortFilterProxyModel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("Muisti");
    a.setOrganizationName("Muisti");

    MuistiXmlModel model;
    model.lataaTiedosto("/tmp/muisti.xml");
    model.haeKoristeet("/home/arto/Krypta/muisti/pic");

    MuistiHakuProxyModel proxy;
    proxy.setSourceModel(&model);
    proxy.hae("Juho");

    QSortFilterProxyModel sort;
    sort.setSourceModel(&proxy);
    sort.sort(2, Qt::DescendingOrder);

    MuistiHtml kirjoittaja;
    kirjoittaja.asetaModel( &sort);
    kirjoittaja.asetaMuistiKoristeModel(&model);
    kirjoittaja.asetaKorostettava("Juho");

    QWebView view;
    view.setHtml( kirjoittaja.html()  );
    view.show();

    model.tallennaTiedostoon("/tmp/ulos.xml");

    QTreeView puu;
    puu.setModel( &model);
    puu.show();


    return a.exec();
}
