#include "tasklist.h"

Task::Task(QDomElement &root)
{
    QDomElement titleElement = root.firstChildElement("title");
    if (titleElement.isNull())
	QMessageBox(QMessageBox::Critical, "Error !", "Error : the xml input file is malformed");
    /* FIXME : add it to the rest */

    _title = titleElement.text();

    QDomElement length = titleElement.nextSiblingElement();
    QDomElement hours = length.firstChildElement("hours");

    int hour = hours.text().toInt();

    QDomElement minutes = hours.nextSiblingElement();
    int minute = minutes.text().toInt();

    _taskLength = QTime(hour, minute, 0);

    QDomElement remaining = length.nextSiblingElement();
    hours = remaining.firstChildElement("hours");
    hour = hours.text().toInt();
    minutes = hours.nextSiblingElement();
    minute = minutes.text().toInt();
    _timeRemaining = QTime(hour, minute, 0);

    qDebug() << minute << " " << hour;
}

TaskList::TaskList(QFile &f)
{
    QDomDocument doc;

    QString s;
    int errorLine;

    if(!doc.setContent(/*(QIODevice *)*/ &f, &s, &errorLine)) {
	f.close();
	QString errorMsg = QString("Error while parsing the XML file %1!").arg(f.fileName());
	QString t = s + "error at line %1";
	QString errorText = t.arg(errorLine);

	QMessageBox::critical(0, errorMsg, errorText);
	return;
    }

    QDomElement child = doc.firstChildElement("session").firstChildElement();

    if (child.isNull()) {
	QMessageBox::critical(0, "Critical error !", "The Document doesn't have a root tag");
	return;
    }

    do {
	Task *t = new Task(child);
	qDebug() << child.tagName();
	_taskList.append(t);
	child = child.nextSiblingElement();
    } while(!child.isNull());

}

TaskList::~TaskList()
{
    QList<Task* >::iterator i;
    for (i = _taskList.begin(); i != _taskList.end(); ++i)
	delete(*i);
}

QVariant TaskList::data ( const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= _taskList.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
	    Task *t = _taskList.at(index.row());
	    return t->title();
    }

    return QVariant();
}

int TaskList::rowCount (const QModelIndex & parent) const
{
    return _taskList.length();
}
