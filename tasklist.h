#ifndef TASKLIST_H
#define TASKLIST_H

#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <QAbstractListModel>

class Task : public QObject
{
    /** this class models a task, which is a portion of a session */
    Q_OBJECT
    QString _title;
    QTime _taskLength;
    QTime _timeRemaining;

public:
    Task(QString title, QTime taskLength) : _title(title), _taskLength(taskLength), _timeRemaining() { };
    Task(QDomElement& root);
    QString title(void) { return _title; };
    QTime taskLength(void) { return _taskLength; }

};

class TaskList : QAbstractListModel
{
    /**	TaskList is our model class. It loads and saves tasks from an xml file.
		Format of the xml file :
		<session>
		    <task>
			<title>Task 1</title>
			<length>
			    <hours>3</hours>
			    <minutes>5</minutes>
			</length>
			<elasped>
			    <hours>3</hours>
			    <minutes>5</minutes>
			</elapsed>
		    </task>
		    <task>
			...
		</session>
 */

QList <Task *> _taskList;
public:    
    TaskList(QFile& f);
    ~TaskList();

    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    int rowCount (const QModelIndex & parent = QModelIndex() ) const;

};

#endif // TASKLIST_H
