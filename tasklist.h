#ifndef TASKLIST_H
#define TASKLIST_H

#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <QAbstractListModel>

class Task //: public QObject
{
    /** this class models a task, which is a portion of a session */
//    Q_OBJECT
    QString _title;
    QTime _taskLength;
    QTime _timeRemaining;

public:
    Task() : _title("Unnamed task"), _taskLength(), _timeRemaining() { };
    Task(QString title, QTime taskLength) : _title(title), _taskLength(taskLength), _timeRemaining() { };
    Task(QDomElement& root);
    QString title(void) { return _title; };
    QTime taskLength(void) { return _taskLength; }

};
Q_DECLARE_METATYPE(Task)

class TaskList : QAbstractItemModel
{

    /**	TaskList is our model class. It loads and saves tasks from an xml file.
		Format of the xml file :
		<todolist name="Work #1">
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
		</todolist>
 */

QList <Task *> _taskList;
QString _todoListName;

public:    
    TaskList(QFile& f);
    TaskList(QString listName);
    ~TaskList();

    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
    int rowCount (const QModelIndex & parent = QModelIndex() ) const;
    int columnCount( const QModelIndex & parent = QModelIndex() ) const;
    QModelIndex parent ( const QModelIndex & index ) const { return QModelIndex(); };
    /* accessors */
    QString todoListName() { return _todoListName; };
};
#endif // TASKLIST_H
