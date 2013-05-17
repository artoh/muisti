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
#include "muistinoodi.h"


MuistiNodeModel::MuistiNodeModel(QObject *parent) :
    MuistiModel(parent)
{
    // Alussa on aina tyhjä juuri
    juuriNoodi_ = new MuistiNoodi(0);
    juuriNoodi_->asetaTyyppi(JuuriNoodi);
}

MuistiNodeModel::~MuistiNodeModel()
{
    if( juuriNoodi())
        delete juuriNoodi_;
}

QModelIndex MuistiNodeModel::index(int row, int column, const QModelIndex &parent) const
{
    if( !juuriNoodi() || row < 0 || column < 0 )
        return QModelIndex;

    MuistiNoodi *vanhempi = noodiIndeksista(parent);
    if( !vanhempi)
        return QModelIndex();   // Juuri-indeksi

    MuistiNoodi *lapsi = vanhempi->lapset().value(row);

    if( !lapsi )
        return QModelIndex();

    return createIndex(row,column,lapsi);
}

QModelIndex MuistiNodeModel::parent(const QModelIndex &child) const
{
    MuistiNoodi *noodi = noodiIndeksista(child);
    if( !noodi )
        return QModelIndex();

    MuistiNoodi *vanhempiNoodi = noodi->vanhempi();
    if( !vanhempiNoodi )
        return QModelIndex();

    MuistiNoodi *isoVanhempiNoodi = vanhempiNoodi->vanhempi();
    if( !isoVanhempiNoodi)
        return QModelIndex();

    int rivi = isoVanhempiNoodi->lapset().indexOf(vanhempiNoodi);
    return createIndex( rivi, 0, vanhempiNoodi);
}

int MuistiNodeModel::rowCount(const QModelIndex &parent) const
{
    if( parent.column() > 0)
        return 0;   // Saa kysyä vain ensimmäiseltä sarakkeelta
    MuistiNoodi *vanhempi = noodiIndeksista(parent);
    if( !vanhempi )
        return 0;
    return vanhempi->lapsiLuku();
}

int MuistiNodeModel::columnCount(const QModelIndex &parent) const
{
    if( parent.isValid())
        return 2;
    else
        return 3;   // Vain juuren alla on pvm-sarake
}

bool MuistiNodeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if( !juuriNoodi())
        return false;

    // Vanhemman noodi
    MuistiNoodi *item = parent.isValid() ? noodiIndeksista(index) : juuriNoodi();

    beginInsertRows(parent, row, row + count - 1);
    for( int i = 0; i < count ; i++)
    {
        // Luodaan uusi noodi ja lisätään se
        MuistiNoodi *uusiNoodi = new MuistiNoodi();
        item->lisaaLapsi(uusiNoodi, row + i);
    }
    endInsertRows();

    return true;

}

bool MuistiNodeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    MuistiNoodi *noodi = noodiIndeksista(parent);
    beginRemoveRows(parent, row, row + count - 1);

    for( int i = 0 ; i < count; i ++ )
        delete noodi->otaLapsi(row);

    endRemoveRows();
    return true;
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

bool MuistiNodeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    MuistiNoodi *noodi = noodiIndeksista(index);

    if( !noodi )
        return false;
    if( ( role == Qt::EditRole && index.column() == AvainSarake )
            || role == AvainRooli )
        noodi->asetaAvain(value.toString());
    else if( ( role == Qt::EditRole && index.column() == ArvoSarake )
             || role == ArvoRooli )
        noodi->asetaTieto(value);
    else if( role == TyyppiRooli )
        noodi->asetaTyyppi(value.toString());
    else
        return false;

    emit dataChanged(index,index);
    return true;

}

Qt::ItemFlags MuistiNodeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags= QAbstractItemModel::flags(index);

    MuistiNoodi* noodi = noodiIndeksista(index);

    // Avainsaraketta voi muokata muistossa sekä tietokentillä
    // Arvosaraketta voi muokata tietokentillä
    if( (noodi->tyyppi() > JuuriNoodi  && index.column() == AvainSarake ) ||
            (noodi->tyyppi() > MuistoNoodi && index.column() == ArvoSarake))
        flags |= Qt::ItemIsEditable;

    return flags;

}

QVariant MuistiNodeModel::headerData(int section, Qt::Orientation orientation, int role) const
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
        default:
            break;
        }
    }
    return QVariant();
}

void MuistiNodeModel::asetaJuuriNoodi(MuistiNoodi *noodi)
{
    beginResetModel();
    if( juuriNoodi_)
        delete juuriNoodi_;
    juuriNoodi_ = noodi;
    endResetModel();
}

MuistiNoodi *MuistiNodeModel::noodiIndeksista(const QModelIndex &index)
{
    if( index.isValid())
        return static_cast<MuistiNoodi*>(index.internalPointer());
    else
        return juuriNoodi();
}
