#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include "summarylist.h"
#include "tasklist.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changeTaskList(const QModelIndex & index);

private:
    QListView *summaryView;
    QListView *taskView;
    QLineEdit *newListField;
    QPushButton *newListButton;

    SummaryList *sList;
    TaskList *tasks;
};

#endif // MAINWINDOW_H
