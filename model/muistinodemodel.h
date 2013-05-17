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


#ifndef MUISTINODEMODEL_H
#define MUISTINODEMODEL_H

#include "muistimodel.h"

class MuistiNoodi;

/**
 * @brief MuistiNoodi -tietorakenteeseen tukeutuva MuistiModel
 */
class MuistiNodeModel : public MuistiModel
{
    Q_OBJECT
public:
    explicit MuistiNodeModel(QObject *parent = 0);
    ~MuistiNodeModel();
    
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);


    /**
     * @brief data Palauttaa modelin tietoa
     * @param index Indeksi
     * @param role Rooli: Qt::DisplayRole, Qt::EditRole sarakkeen mukaisesti
     * @return
     */
    QVariant data(const QModelIndex &index, int role) const;

    /**
     * @brief Muuttaa modelin tietoa
     * @param index Indeksi
     * @param value Muutettava arvo
     * @param role Rooli: Qt::EditRole muuttaa sarakkeen mukaan arvoa tai avainta,
     *  AvainRooli, ArvoRooli tai TyyppiRooli
     * @return tosi, jos onnistui
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:
    
public slots:

protected:
    MuistiNoodi* juuriNoodi() const { return juuriNoodi_; }
    void asetaJuuriNoodi(MuistiNoodi* noodi);

    MuistiNoodi* noodiIndeksista(const QModelIndex &index);

private:
    MuistiNoodi *juuriNoodi_;
    
};

#endif // MUISTINODEMODEL_H
