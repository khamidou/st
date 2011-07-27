#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    sessionView = new QListView(this);
    QFile fd(tr("tests/first.xml"));
    if(!fd.open(QIODevice::ReadOnly))
	return;

    tasks = new TaskList(fd);
    sessionView->setModel((QAbstractItemModel *) tasks);
    setCentralWidget(sessionView);

}

MainWindow::~MainWindow()
{

}
