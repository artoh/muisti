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


#ifndef MUISTIMODEL_H
#define MUISTIMODEL_H

#include <QAbstractItemModel>
#include <QIcon>
#include <QMap>


/**
 * @brief Muistin tietoja säilyttävä model, kantaluokka
 * @author Arto Hyvättinen
 */

class MuistiModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum { TyyppiRooli = Qt::UserRole /** Noodin tyyppi */,
           IdRooli = Qt::UserRole + 1,
           AvainRooli = Qt::UserRole + 2,
           ArvoRooli = Qt::UserRole + 3,
           NaytettavaArvoRooli = Qt::UserRole + 4
         };

    enum { AvainSarake = 0, ArvoSarake = 1, PvmSarake = 2 } ;

    enum MuistiNoodiTyyppi { NullNoodi = 0, JuuriNoodi = 1,
                            MuistoNoodi = 2,
                            HenkiloNoodi = 10,
                            TietoNoodi = 21, PvmNoodi = 22,
                            SijaintiNoodi = 23, PuhelinNoodi = 24,
                            MemoNoodi = 30
                          };


    explicit MuistiModel(QObject *parent = 0);

    /**
     * @brief Ikoni (decoration), joka liittyy kyseiseen tyyppiin (Qt::DecorationRole)
     *
     *
     * @param tyyppi Noodin tyyppi
     * @param avain Noodin avainkentän arvo
     * @return Tyyppiin liittyvä ikoni
     */
    virtual QIcon koriste(int tyyppi, const QString &avain = QString()) const;

    /**
     * @brief Polku, josta löytyy koriste (kuvaketiedosto)
     * Ensisijaisesti haetaan avaimella, toissijaisesti tyypillä
     * @param tyyppi Noodin tyyppi
     * @param avain Avainkenttä
     * @return polku kuvaketiedostoon
     */
    virtual QString koristePolku(int tyyppi, const QString &avain = QString()) const;

    /**
     * @brief Hakee koristeita polusta
     *
     * Koristeet ovat png/jpg-tiedostoja, joiden tiedostonnimenä haluttu avainkenttä-
     * Ellei avaimelle ole koristetta, käytetään tyypin mukaista koristetta
     *
     * @see koriste
     * @see koristePolku
     *
     * @param hakemistopolku
     */
    virtual void haeKoristeet(const QString &hakemistopolku) ;
    
signals:
    
public slots:

private:
    /**
     * @brief Koristeiden tiedostopolut halutuille avaimille
     */
    QMap<QString,QString> avainKoristeet_;
    
};

#endif // MUISTIMODEL_H
