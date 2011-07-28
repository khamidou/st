#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    summaryView = new QListView();
    taskView = new QListView();


    /* FIXME: use setPlaceholderText when I'll have QT 4.7 */
    QHBoxLayout *newListHBox = new QHBoxLayout();
    newListField = new QLineEdit();
    newListButton = new QPushButton("Create a new list");
    newListHBox->addWidget(newListField);
    newListHBox->addWidget(newListButton);

    QFrame *frame = new QFrame();

    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->addWidget(summaryView, 0, 0);
    gridLayout->addWidget(taskView, 0, 1);
    gridLayout->addLayout(newListHBox, 1, 0);


    QFile fd(tr("tests/first.xml"));    
    if(!fd.open(QIODevice::ReadOnly))
	return;

    QDir d(tr("./tests"));

    tasks = new TaskList(fd);
    sList = new SummaryList(d);

    summaryView->setModel((QAbstractItemModel *) sList);
    taskView->setModel((QAbstractItemModel *) tasks);

    connect(summaryView, SIGNAL(clicked(QModelIndex)), this, SLOT(changeTaskList(QModelIndex)));

    frame->setLayout(gridLayout);
    setCentralWidget(frame);
    setWindowTitle(tr("A Faire"));
    resize(640, 350);
}

MainWindow::~MainWindow()
{

}

void MainWindow::changeTaskList(const QModelIndex &index)
{
    QString filename = ((SummaryList*) summaryView->model())->fileNameAt(index);

    QFile fd(filename);
    if(!fd.open(QIODevice::ReadOnly))
	return;

    TaskList *oldModel = (TaskList *) taskView->model();
    TaskList *newModel = new TaskList(fd);
    taskView->setModel((QAbstractItemModel *) newModel);
    delete oldModel;

}
