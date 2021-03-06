#include "tasklist.h"

Task::Task(QDomElement &root)
{
    QDomElement titleElement = root.firstChildElement("title");
    if (titleElement.isNull())
	QMessageBox(QMessageBox::Critical, "Error !", "Error : the xml input file is malformed");
    /* FIXME : add it to the rest */

    _title = titleElement.text();

    QDomElement length = titleElement.nextSiblingElement("length");
    QDomElement hours = length.firstChildElement("hours");

    int hour = hours.text().toInt();

    QDomElement minutes = hours.nextSiblingElement("minutes");
    int minute = minutes.text().toInt();

    _taskLength = QTime(hour, minute, 0);

    QDomElement remaining = length.nextSiblingElement("remaining");
    hours = remaining.firstChildElement("hours");
    hour = hours.text().toInt();
    minutes = hours.nextSiblingElement("minutes");
    minute = minutes.text().toInt();
    _timeRemaining = QTime(hour, minute, 0);

}

TaskList::TaskList(QString listName)
{
	QDomDocument doc;
	QDomElement root = doc.createElement("todolist");
	doc.appendChild(root);
	root.setAttribute("name", listName);

	QFile file("./tests/" + listName + ".xml");	
	if(!file.open(QIODevice::WriteOnly | QFile::Truncate)) {
	    QMessageBox::critical(0,	tr("Unable to create Todo List"),
							tr("An error happened while creating the list file : ") + file.errorString());
	    return;
	}

	QTextStream stream(&file);
	doc.save(stream, 4);
	stream.flush();
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

    _todoListName = doc.firstChildElement("todolist").attribute("name");
    QDomElement child = doc.firstChildElement("todolist").firstChildElement("task");

    if (doc.firstChildElement("todolist").isNull()) {
	QMessageBox::critical(0, "Critical error !", "The Document doesn't have a root tag");
	return;
    }

    while(!child.isNull()) {
	Task *t = new Task(child);
	_taskList.append(t);
	child = child.nextSiblingElement("task");
    }

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

int TaskList::columnCount( const QModelIndex & parent = QModelIndex() ) const
{
    return 1;
}
