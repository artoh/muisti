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

#include "muistinodemodel.h"
#include "noodi/muistinoodi.h"


MuistiNodeModel::MuistiNodeModel(QObject *parent) :
    MuistiModel(parent), juuriNoodi_(0)
{
}

MuistiNodeModel::~MuistiNodeModel()
{
    if( juuriNoodi())
        delete juuriNoodi_;
}

QVariant MuistiNodeModel::data(const QModelIndex &index, int role) const
{
    MuistiNoodi *noodi = noodiIndeksista(index);
    if( !noodi )
        return QVariant();

    // Decoration: ikoni, vain ensimmäiseen sarakkeeseen
    if( index.column() == 0 && role == Qt::DecorationRole )
        return koriste(noodi->tyyppi(), noodi->avain());
    // Avain
    else if( (index.column() == AvainSarake && (role == Qt::DisplayRole || role == Qt::EditRole)  )
             || role == AvainRooli )
        return noodi->avain();
    // Näytettävä arvo
    else if( (index.column() == ArvoSarake && role == Qt::DisplayRole )
             || role == NaytettavaArvoRooli )
        return noodi->naytettavaTieto();
    // Muokattava arvo
    else if( (index.column() == ArvoSarake && role == Qt::EditRole )
             || role == ArvoRooli )
        return noodi->naytettavaTieto();
    // Päiväyssarake

    return QVariant();
}

void MuistiNodeModel::asetaJuuriNoodi(MuistiNoodi *noodi)
{
    if( juuriNoodi_)
        delete juuriNoodi_;
    juuriNoodi_ = noodi;
}

MuistiNoodi *MuistiNodeModel::noodiIndeksista(const QModelIndex &index)
{
    if( index.isValid())
        return static_cast<MuistiNoodi*>(index.internalPointer());
    else
        return juuriNoodi();
}
