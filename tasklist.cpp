#include "tasklist.h"

Task::Task(QDomElement &root)
{
    QDomElement titleElement = root.firstChildElement("title");
    _title = titleElement.text();

    QDomElement length = titleElement.nextSibling();
    QDomElement hours = length.firstChild("hours");    

    int hour = hours.text().toInt();

    QDomElement minutes = hours.nextSibling();

    int minute = minutes.text().toInt();

    _taskLength = QTime(hour, minute, 0);

    /* Fixme : implement remaining */
}

TaskList::TaskList()
{
}

QVariant TaskList::data ( const QModelIndex & index, int role) const
{
    /*
    if (!index.isValid())
        return QVariant();
    if (index.row() >= machineList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
    return machineList.at(index.row());

    return QVariant();
    */
    return QVariant();
}

int TaskList::rowCount (const QModelIndex & parent) const
{
    return 2;
}
