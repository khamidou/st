#include "summarylist.h"

SummaryList::SummaryList(QDir& d)
{
    _directory = d;
    _directory.setFilter(QDir::Files | QDir::NoSymLinks);
}

SummaryList::~SummaryList()
{

}

QVariant SummaryList::data ( const QModelIndex & index, int role) const
{
    if (role == Qt::DisplayRole) {
	/* Open the file and get its session name */
	QString filePath = _directory.absoluteFilePath(_directory.entryList().at(index.row()));
	QFile f(filePath);

	if (!f.open(QIODevice::ReadOnly)) {
	  // fail silently
	  return QVariant();
	}

	/* otherwise, open the file and get the session name */
	TaskList t(f);

	if(t.sessionName() != "")
	    return t.sessionName();
	else
	    return _directory.entryList().at(index.row());
    }

    return QVariant();
}

int SummaryList::rowCount (const QModelIndex & parent) const
{
    return _directory.entryList().size();
}

QString SummaryList::fileNameAt(const QModelIndex &index)
{
    return _directory.absoluteFilePath(_directory.entryList().at(index.row()));
}
