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


#ifndef MUISTINOODINTIETO_H
#define MUISTINOODINTIETO_H

#include <QVariant>

/**
 * @brief Muistinoodin tietojen kantaluokka
 */
class MuistiNoodinTieto
{
public:
    MuistiNoodinTieto();
    virtual ~MuistiNoodinTieto();

    /**
     * @brief Tieto varsinaisessa tallennusmuodossaan (Qt::EditRole)
     * @return
     */
    virtual QVariant tieto() const = 0;

    /**
     * @brief Tieto näytettävässä merkkijonomuodossa (Qt::DisplayRole)
     * @return
     */
    virtual QString naytettavaTieto() const ;


    virtual bool asetaTieto(const QVariant &tieto) = 0;
    virtual bool asetaTieto(const QString &tieto);

    virtual bool onkoTyhja();
};

#endif // MUISTINOODINTIETO_H
