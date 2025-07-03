#ifndef NDISOURCEINFOMODEL_H
#define NDISOURCEINFOMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <deque>

class NdiSourceInfoModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum NdiSourceInfoRole
    {
        IpAddressRole = Qt::UserRole + 1,
        NameRole
    };
    explicit NdiSourceInfoModel(QObject *parent = nullptr);
    Q_INVOKABLE QVariantMap getValue(const int &index);

public:
    void hotUpdate(const QVariantList &data);
    void pushBack(const QVariantMap &value);
    void remove(const QString &key);
    void update(const QString &key, const QVariantMap &value);

protected:
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVariantList m_modelData;
};

#endif // NDISOURCEINFOMODEL_H
