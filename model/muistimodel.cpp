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

MuistiModel::MuistiModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

QIcon MuistiModel::koriste(int tyyppi, const QString & /* avain */)
{
    switch (tyyppi) {
    case HenkiloNoodi:
        return QIcon(":/model/noodiTyyppiPic/naama.png");
    case TietoNoodi:
        return QIcon(":/model/noodiTyyppiPic/tieto.png");
    case PvmNoodi:
        return QIcon(":/model/noodiTyyppiPic/date.png");
    case MemoNoodi:
        return QIcon(":/model/noodiTyyppiPic/memo.png");
    case PuhelinNoodi:
        return QIcon(":/model/noodiTyyppiPic/puhelin.png");
    case SijaintiNoodi:
        return QIcon(":/model/noodiTyyppiPic/sijainti.png");
    default:
        return QIcon(":/model/noodiTyyppiPic/muisti.png");
    }
}
