#include "NdiSourceInfoModel.h"

NdiSourceInfoModel::NdiSourceInfoModel(QObject *parent)
    : QAbstractListModel{parent}
{}

void NdiSourceInfoModel::hotUpdate(const QVariantList &data)
{
    // 增加
    for (size_t i = 0; i < data.size(); i++)
    {
        bool is_exist = false;
        for (size_t j = 0; j < m_modelData.size(); j++)
        {
            if (data[i].toMap().value("ip_address") == m_modelData[j].toMap().value("ip_address"))
            {
                is_exist = true;
                break;
            }
        }
        if (!is_exist)
        {
            pushBack(data[i].toMap());
        }
    }

    // 删除
    for (size_t i = 0; i < m_modelData.size(); i++)
    {
        bool is_exist = false;
        for (size_t j = 0; j < data.size(); j++)
        {
            if (m_modelData[i].toMap().value("ip_address") == data[j].toMap().value("ip_address"))
            {
                is_exist = true;
                break;
            }
        }
        if (!is_exist)
        {
            remove(m_modelData[i].toMap().value("ip_address").toString());
        }
    }


    // 更新
    for (size_t i = 0; i < m_modelData.size(); i++)
    {
        for (size_t j = 0; j < data.size(); j++)
        {
            if (m_modelData[i].toMap().value("ip_address") == data[j].toMap().value("ip_address"))
            {
                update(m_modelData[i].toMap().value("ip_address").toString(), data[j].toMap());
            }
        }
    }
    
}

void NdiSourceInfoModel::pushBack(const QVariantMap &value)
{
    beginInsertRows(QModelIndex(), m_modelData.size(), m_modelData.size());
    m_modelData.append(value);
    endInsertRows();
}

void NdiSourceInfoModel::remove(const QString &key)
{
    for (int i = 0; i < m_modelData.size(); i++)
    {
        if (m_modelData[i].toMap().value("ip_address") == key)
        {
            beginRemoveRows(QModelIndex(), i, i);
            m_modelData.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}

void NdiSourceInfoModel::update(const QString &key, const QVariantMap &value)
{
    for (int i = 0; i < m_modelData.size(); i++)
    {
        if (m_modelData[i].toMap().value("ip_address") == key)
        {
            m_modelData[i] = value;
            emit dataChanged(index(i), index(i));
            break;
        }
    }
}

QVariant NdiSourceInfoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    return m_modelData[index.row()].toMap().value(roleNames()[role]);
}

int NdiSourceInfoModel::rowCount(const QModelIndex &parent) const
{
    return m_modelData.size();
}

QHash<int, QByteArray> NdiSourceInfoModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IpAddressRole] = "ip_address";
    roles[NameRole] = "name";
    return roles;
}
