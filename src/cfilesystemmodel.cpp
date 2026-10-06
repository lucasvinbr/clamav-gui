/***************************************************************************************
 * Filesystem model for directory tree used in the scan tab and profile wizard class.
****************************************************************************************/
#include "cfilesystemmodel.h"
#include <QDebug>

Qt::ItemFlags CFileSystemModel::flags(const QModelIndex& index) const
{
    return QFileSystemModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant CFileSystemModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::CheckStateRole) {
        return m_checkedIndexes.contains(index) ? Qt::Checked : Qt::Unchecked;
    }
    else {
        return QFileSystemModel::data(index, role);
    }
}

bool CFileSystemModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (role == Qt::CheckStateRole) {
        if (value == Qt::Checked) {
            m_checkedIndexes.insert(index);
        }
        else {
            m_checkedIndexes.remove(index);
        }
        emit dataChanged(index, index);
        return true;
    }
    return QFileSystemModel::setData(index, value, role);
}

void CFileSystemModel::setChecked(const QModelIndex& index, bool state)
{
    if (state == true) {
        m_checkedIndexes.insert(index);
    }
    else {
        m_checkedIndexes.remove(index);
    }
}

void CFileSystemModel::setChecked(QString pfad, bool state)
{
    QModelIndex index = this->index(pfad);

    if (state == true) {
        m_checkedIndexes.insert(index);
    }
    else {
        m_checkedIndexes.remove(index);
    }
}

void CFileSystemModel::unCheckAll()
{
    m_checkedIndexes.clear();
}
