#ifndef MUISTIHAKUPROXYMODEL_H
#define MUISTIHAKUPROXYMODEL_H

#include <QAbstractProxyModel>
#include <QList>


/**
 * @brief Proxy muistiinpanojen hakemiseen
 *
 * Näyttää ne muistiinpanot, joista haettava teksti löytyy
 * jostakin arvokentästä.
 */
class MuistiHakuProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit MuistiHakuProxyModel(QObject *parent = 0);
    
    QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    /**
     * @brief Suodattaa modelia haun mukaan
     * @param haettava Etsittävä teksti, QString() näyttää kaikki, tyhjä merkkijono ei mitään.
     * @param tyyppi Etsittävä tyyppi
     */
    void hae(const QString& haettava, int tyyppi = 0);

signals:
    
public slots:

protected:
    bool loytyyko(const QModelIndex &index, const QString& haettava, int tyyppi);

    QList<int> haettu_;

    
};

#endif // MUISTIHAKUPROXYMODEL_H
