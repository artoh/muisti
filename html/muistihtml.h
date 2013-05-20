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


#ifndef MUISTIHTML_H
#define MUISTIHTML_H

#include <QObject>

#include <QAbstractItemModel>
#include "../model/muistimodel.h"

/**
 * @brief Kirjoittaa Muistin modelista html:ää
 */
class MuistiHtml : public QObject
{
    Q_OBJECT
public:

    enum HtmlValinnat {
        HtmlTyyppiKuvakkeet = 1 /** Näyttää avaimen edessä tyypin kuvakkeen */,
        JSKarttaLinkki = 2 /** Lisää sijaintikenttiin karttalinkit */
    };

    explicit MuistiHtml(QObject *parent = 0);
    
    void asetaTyylisivu(const QString& tyylisivu );
    void asetaModel(QAbstractItemModel *model);
    /**
     * @brief Asettaa koristeiden hakuun käytettävän MuistiModelin
     *
     * Koska modelina voidaan käyttää myös proxymodelia, pitää niissä
     * tapauksissa asettaa erikseen MuistiModel, jota käytetään
     * koristeiden hakuun.
     *
     * @param mmodel
     */
    void asetaMuistiKoristeModel(MuistiModel* mmodel);
    void asetaKorostettava(const QString &korostettava = QString());

    /**
     * @brief Palauttaa modelin tiedot html:nä
     * @return
     */
    QString html();

    /**
     * @brief Ottaa käyttöön valinnan (option)
     * @param valinta HtmlValinnat -vaihtoehto, joka valitaan
     */
    void valitse(int valinta);
    int valinnat() const { return valinnat_; }

signals:
    
public slots:

private:
    QString tyylisivu_;
    QAbstractItemModel *model_;
    MuistiModel *koristeModel_;
    QString korostettava_;
    QString korostettu_;

    QString html_;
    int valinnat_;

    void kirjoitaMuisto(int rivi);
    void kirjoitaTieto(const QModelIndex &indeksi, int sisennys=0);
};

#endif // MUISTIHTML_H

