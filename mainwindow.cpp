#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    sessionView = new QListView();
    taskView = new QListView();
    QFrame *frame = new QFrame();

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(sessionView, 0, 0);
    gridLayout->addWidget(taskView, 0, 1);


    QFile fd(tr("tests/first.xml"));    
    if(!fd.open(QIODevice::ReadOnly))
	return;

    QDir d(tr("./tests"));

    tasks = new TaskList(fd);
    sList = new SessionList(d);

    sessionView->setModel((QAbstractItemModel *) sList);
    taskView->setModel((QAbstractItemModel *) tasks);

    connect(sessionView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeTaskList(QModelIndex)));

    frame->setLayout(gridLayout);
    setCentralWidget(frame);
    setWindowTitle(tr("Session Tracker"));
    resize(440, 350);
}

MainWindow::~MainWindow()
{

}

void MainWindow::changeTaskList(const QModelIndex &index)
{
    QString filename = ((SessionList*) sessionView->model())->fileNameAt(index);

    QFile fd(filename);
    if(!fd.open(QIODevice::ReadOnly))
	return;

    TaskList *oldModel = (TaskList *) taskView->model();
    TaskList *newModel = new TaskList(fd);
    taskView->setModel((QAbstractItemModel *) newModel);
    delete oldModel;

}
