#include "muistihtml.h"
#include "../model/muistimodel.h"

MuistiHtml::MuistiHtml(QObject *parent) :
    QObject(parent), model_(0), koristeModel_(0)
{
}

void MuistiHtml::asetaTyylisivu(const QString &tyylisivu)
{
    tyylisivu_ = tyylisivu;
}

void MuistiHtml::asetaModel(QAbstractItemModel *model)
{
    model_ = model;

    // Jos on muistimodel, asetetaan koristeet samalla
    if( MuistiModel* mmodel = dynamic_cast<MuistiModel*>(model ))
        koristeModel_ = mmodel;

}

void MuistiHtml::asetaMuistiKoristeModel(MuistiModel *mmodel)
{
    koristeModel_ = mmodel;
}

void MuistiHtml::asetaKorostettava(const QString &korostettava)
{
    korostettava_ = korostettava;
}

QString MuistiHtml::html()
{
    if( !model_)
        return tr("Mallia ei asetettu");

    html_.clear();

    html_ = "<html><head>";

    if( !tyylisivu_.isEmpty())
    {
        html_ += "<link rel=stylesheet type=text/css href=\"" + tyylisivu_ + "\">";
    }
    html_ += "</head><body>";

    for( int i = 0; i < model_->rowCount(QModelIndex()); i++)
        kirjoitaMuisto(i);

    html_ += "</body></html>";

    if( !korostettava_.isEmpty())
    {
        QString korostettu = "<span style=\"background-color: yellow\">" + korostettava_ + "</span>";
        html_.replace(korostettava_, korostettu);
    }

    return html_;

}

void MuistiHtml::kirjoitaMuisto(int rivi)
{
    QModelIndex indeksi = model_->index(rivi, 0, QModelIndex());
    html_.append("<table width=100%><tr><th class=pvm width=33%>");
    html_.append( indeksi.data().toString() );
    html_.append("<br/>");

    html_.append( model_->data( model_->index(rivi, MuistiModel::PvmSarake , QModelIndex()) , Qt::DisplayRole ).toString());

    html_.append( "</th><th>");
    html_.append( indeksi.data(MuistiModel::ArvoRooli).toString());
    html_.append("</th><th width=34><a href=\"muisti:/");
    html_.append( model_->data( model_->index(rivi, 1, QModelIndex()),MuistiModel::IdRooli ).toString()  );


    // Piirrettävä kuvake pyritään hakemaan MuistiModelin kuvakkeenhaku-
    // toiminnolla

    QString kuvakepolku;
    if( koristeModel_)
        kuvakepolku = koristeModel_->koristePolku(MuistiModel::MuistoNoodi,
                                                    indeksi.data(MuistiModel::AvainRooli).toString());
    else
        kuvakepolku = ":/muisti32.png";

    if( kuvakepolku.startsWith(":/"))
        kuvakepolku = "qrc" + kuvakepolku;

    html_.append("\"><img width=32 height=32 src=\"" + kuvakepolku + "\"></a></td></tr>");

    for( int rivi = 0; rivi < model_->rowCount(indeksi); rivi++)
    {
        QModelIndex tietoIndeksi = model_->index(rivi,0,indeksi);
        if( tietoIndeksi.isValid())
            kirjoitaTieto(tietoIndeksi);
    }
    html_.append("</table><p>");

}

void MuistiHtml::kirjoitaTieto(const QModelIndex &indeksi, int sisennys)
{
    QModelIndex arvoIndeksi = model_->index( indeksi.row(), 1, indeksi.parent() );
    if( arvoIndeksi.data(Qt::DisplayRole).toString().isEmpty() )
        return;     // Ei tyhjiä kenttiä!

    html_.append("<tr><td>");
    for(int i=0; i<sisennys; i++)
        html_.append("&nbsp;&nbsp;&nbsp;");
    html_.append( indeksi.data(Qt::DisplayRole).toString());
    html_.append("</td><td colspan=2>");
    html_.append(arvoIndeksi.data().toString());

    html_.append("</td></tr>");

    for( int rivi = 0; rivi < model_->rowCount(indeksi); rivi++)
    {
        QModelIndex tietoIndeksi = indeksi.child(rivi,0);
        if( tietoIndeksi.isValid())
            kirjoitaTieto(tietoIndeksi, sisennys+1);
    }
}