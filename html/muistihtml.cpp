#include "muistihtml.h"
#include "../model/muistimodel.h"

#include <QDate>

MuistiHtml::MuistiHtml(QObject *parent) :
    QObject(parent), tyylisivu_("qrc:/html/muistihtml.css"), model_(0), koristeModel_(0), valinnat_(0)
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

    // Asetetaan korostetun tyylin replace.
    korostettu_ = "<span style=\"background-color: yellow\">" + korostettava_ + "</span>";

    html_.clear();

    html_ = "<html><head>";

    if( !tyylisivu_.isEmpty())
    {
        html_ += "<link rel=stylesheet type=text/css href=\"" + tyylisivu_ + "\">";
    }
    html_ += "</head><body>";

    html_ += "<script src=\"qrc:/html/muistihtml.js\"></script>";

    for( int i = 0; i < model_->rowCount(QModelIndex()); i++)
        kirjoitaMuisto(i);

    html_ += "</body></html>";

    return html_;

}

void MuistiHtml::valitse(int valinta)
{
    valinnat_ |= valinta;
}

void MuistiHtml::kirjoitaMuisto(int rivi)
{
    QModelIndex indeksi = model_->index(rivi, 0, QModelIndex());

    html_.append("<table width=100%><tr><th class=pvm>");
    html_.append( indeksi.data(MuistiModel::AvainRooli).toString() );
    html_.append("<br/>");
    html_.append( indeksi.data(MuistiModel::PvmRooli).toDate().toString("dd.MM.yyyy") );

    html_ += "</th><th>";

    html_.append( indeksi.data(MuistiModel::NaytettavaArvoRooli).toString());
    html_.append("<a href=\"muisti:/");
    html_.append( indeksi.data(MuistiModel::IdRooli).toString());


    // Piirrettävä kuvake pyritään hakemaan MuistiModelin kuvakkeenhaku-
    // toiminnolla

    QString kuvakepolku;
    if( koristeModel_)
        kuvakepolku = koristeModel_->koristePolku(MuistiModel::MuistoNoodi,
                                                    indeksi.data(MuistiModel::AvainRooli).toString());
    else
        kuvakepolku = ":/html/muisti.png";

    if( kuvakepolku.startsWith(":/"))
        kuvakepolku = "qrc" + kuvakepolku;
    else
        kuvakepolku = "file:" + kuvakepolku;

    html_.append("\"><img class=\"muistokuva\" src=\"" + kuvakepolku + "\"></a></tr>");

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
    if( indeksi.data(MuistiModel::NaytettavaArvoRooli).toString().isEmpty() )
       return;     // Ei tyhjiä kenttiä!


    int tyyppi = indeksi.data(MuistiModel::TyyppiRooli).toInt();
    QString id = indeksi.data(MuistiModel::IdRooli).toString();
    QString avain = indeksi.data(MuistiModel::AvainRooli).toString();
    QString tietoteksti = indeksi.data(MuistiModel::NaytettavaArvoRooli).toString();

    html_ += "<tr><td>";

    for(int i=0; i<sisennys; i++)
        html_ += "&nbsp;&nbsp;&nbsp;";

    // Mahdollinen tyypin kuvake
    if( valinnat() & HtmlTyyppiKuvakkeet && koristeModel_ )
    {
        QString koristepolku  = koristeModel_->koristePolku(tyyppi, avain);
        if( koristepolku.startsWith(":/"))
            koristepolku = "qrc" + koristepolku;
        else
            koristepolku = "file:" + koristepolku;
        html_ += "<img class=\"koriste\" src=\"" + koristepolku + "\"/>";
    }

    html_ += avain + "</td>";


    // Datasarakkeen otsikko
    html_ += "<td id=\"data" + id + "\"";

    // Sijainnin javascript-linkki
    if( tyyppi == MuistiModel::SijaintiNoodi)
        html_ += " onclick=\"kartta(\'data"+ id +"\',\'" + indeksi.data(MuistiModel::NaytettavaArvoRooli).toString()
                +"\')\"";

    html_ += " >";

    // Datasarakkeen tieto
    if( !korostettava_.isEmpty())
    {
         tietoteksti.replace( korostettava_, korostettu_);
    }
    html_ += tietoteksti;





    html_ += "</td></tr>";

    for( int rivi = 0; rivi < model_->rowCount(indeksi); rivi++)
    {
        QModelIndex tietoIndeksi = indeksi.child(rivi,0);
        if( tietoIndeksi.isValid())
            kirjoitaTieto(tietoIndeksi, sisennys+1);
    }
}
