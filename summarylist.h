#ifndef SummaryList_H
#define SummaryList_H

#include <QtCore>
#include "tasklist.h"

class SummaryList : QAbstractListModel
{
    /**	This class represents the list of training sessions the user has created.
 */

    QDir    _directory;
    
public:
    SummaryList(QDir& d);
    ~SummaryList();

    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    int rowCount (const QModelIndex & parent = QModelIndex() ) const;
    QString fileNameAt(const QModelIndex &index);
};

#endif // SummaryList_H
