/**************************************************************************
Muisti Notes Manager

(c) Arto Hyvättinen 2013

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


**************************************************************************/


#include "muistimodel.h"

#include <QDir>
#include <QFileInfo>

MuistiModel::MuistiModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

QIcon MuistiModel::koriste(int tyyppi, const QString &avain ) const
{
    return QIcon( koristePolku(tyyppi, avain));
}

QString MuistiModel::koristePolku(int tyyppi, const QString &avain) const
{
    // Ensisijaisesti palautetaan avaimeen liittyvä koriste
    QString polku = avainKoristeet_.value(avain, QString());
    if( !polku.isEmpty() )
        return polku;


    // Toissijaisesti tyyppiin liittyvä (kiinteä resurssi)

    switch (tyyppi) {
    case HenkiloNoodi:
        return ":/model/noodiTyyppiPic/naama.png";
    case TietoNoodi:
        return ":/model/noodiTyyppiPic/tieto.png";
    case PvmNoodi:
        return ":/model/noodiTyyppiPic/date.png";
    case MemoNoodi:
        return ":/model/noodiTyyppiPic/memo.png";
    case PuhelinNoodi:
        return ":/model/noodiTyyppiPic/puhelin.png";
    case SijaintiNoodi:
        return ":/model/noodiTyyppiPic/sijainti.png";

    // Ja lopulta ohjelman kuvake
    default:
        return ":/model/noodiTyyppiPic/muisti.png";
    }

}

void MuistiModel::haeKoristeet(const QString &hakemistopolku)
{
    QDir hakemisto(hakemistopolku);
    QFileInfoList tiedostot = hakemisto.entryInfoList( QStringList() << "*.png" << "*.jpg" );
    foreach (QFileInfo tiedosto, tiedostot)
    {
        QString avain = tiedosto.baseName();
        QString polku = tiedosto.absoluteFilePath();

        avainKoristeet_.insert(avain, polku);
    }

}


QVariant MuistiModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
        case AvainSarake:
            return QVariant("Laji");
        case ArvoSarake :
            return QVariant("Otsikko");
        case PvmSarake:
            return QVariant("Pvm");
        case MuokattuSarake :
            return QVariant("Muokattu");
        default:
            break;
        }
    }
    return QVariant();
}

int MuistiModel::columnCount(const QModelIndex &parent) const
{
    if( parent.isValid())
        return 2;
    else
        return 4;   // Vain juuren alla on pvm-sarake
}
