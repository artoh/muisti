#include "muistihakuproxymodel.h"

// Rooleja varten
#include "../model/muistimodel.h"

#include <QDebug>

MuistiHakuProxyModel::MuistiHakuProxyModel(QObject *parent) :
    QAbstractProxyModel(parent)
{
}

QModelIndex MuistiHakuProxyModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    if( !sourceIndex.isValid())
        return QModelIndex();

    // Jos ollaan juuren alla, pitää etsiä listasta
    if( !sourceIndex.parent().isValid() )
    {
        int rivi = haettu_.indexOf( sourceIndex.row());
        return index(rivi, sourceIndex.column(), QModelIndex());
    }
    // Muuten mennään vanhempien avulla

    QModelIndex vanhempi = mapFromSource(sourceIndex.parent());
    return index(sourceIndex.row(), sourceIndex.column(), vanhempi);
}

QModelIndex MuistiHakuProxyModel::mapToSource(const QModelIndex &proxyIndex) const
{
    if( !proxyIndex.isValid())
        return QModelIndex();

    // Juuren alla pitää tehdä mappaus
    if( !proxyIndex.parent().isValid())
    {
        int rivi = haettu_.value(proxyIndex.row(), -1);
        return sourceModel()->index(rivi, proxyIndex.column(), QModelIndex());
    }

    QModelIndex vanhempi = mapToSource(proxyIndex.parent());
    return sourceModel()->index(proxyIndex.row(), proxyIndex.column(), vanhempi);

}

QModelIndex MuistiHakuProxyModel::index(int row, int column, const QModelIndex &parent) const
{

    if( !parent.isValid())
    {
        int rivi = haettu_.value(row);
        QModelIndex sorsaindeksi = sourceModel()->index(rivi, column, QModelIndex());
        return createIndex(row,column, sorsaindeksi.internalPointer() );
    }


    // Sorsauudistus
    //
    QModelIndex sorsalapsi = sourceModel()->index(row, column, parent);
    if( sorsalapsi.isValid() )
        return createIndex(row, column, sorsalapsi.internalPointer() );

    return QModelIndex();

}


QModelIndex MuistiHakuProxyModel::parent(const QModelIndex &child) const
{
    if( !child.isValid())
        return QModelIndex();

    QModelIndex sorsaisa = sourceModel()->parent(child);

    if( sorsaisa.parent().isValid())
        return createIndex(sorsaisa.row(), sorsaisa.column(), sorsaisa.internalPointer());

    // Pitää "mapata" iskä
    int rivi = haettu_.indexOf( sorsaisa.row() );
    return createIndex(rivi, sorsaisa.column(), sorsaisa.internalPointer());
}


void MuistiHakuProxyModel::hae(const QString &haettava, int tyyppi)
{
    haettu_.clear();

    beginResetModel();

    if( !haettava.isEmpty())
    {
        for( int i = 0; i < sourceModel()->rowCount() ; i++ )
        {
            QModelIndex indeksi = sourceModel()->index(i, 0, QModelIndex());
            if( loytyyko(indeksi, haettava, tyyppi ))
                haettu_.append(i);
            // haettu_ -listaan tulee ne rivinumerot, jotka ovat
            // näkyvissä
        }
    }
    else if( haettava.isNull())
    {
        // Jos haettavana Null, näytetään kaikki
        for( int i = 0; i < sourceModel()->rowCount(); i++)
            haettu_.append(i);
    }
    endResetModel();

}

bool MuistiHakuProxyModel::loytyyko(const QModelIndex &index, const QString &haettava, int tyyppi)
{

    // Haku voidaan rajata vain tiettyyn tyyppiin, kuten tehdään
    // automaattisessa haussa - tämän pitäisi nopeuttaa melkoisesti ;)

    if( !tyyppi || index.data(MuistiModel::TyyppiRooli ).toInt() == tyyppi )
    {
        if( index.data(MuistiModel::NaytettavaArvoRooli).toString().contains( haettava, Qt::CaseInsensitive))
            return true;
    }

    // Sitten haetaan myös lapsista

    QModelIndex hakuindeksi = sourceModel()->index(index.row(), 0, index.parent() );

    for( int i = 0; i < sourceModel()->rowCount(hakuindeksi); i++ )
    {
        if( loytyyko( sourceModel()->index(i,0,index)  ,haettava, tyyppi) )
            return true;
    }
    return false;
}


int MuistiHakuProxyModel::rowCount(const QModelIndex &parent) const
{
    if( !parent.isValid())
        return haettu_.count();

    return sourceModel()->rowCount( mapToSource(parent) );
}

int MuistiHakuProxyModel::columnCount(const QModelIndex &parent) const
{
    return sourceModel()->columnCount( mapToSource(parent));
}

