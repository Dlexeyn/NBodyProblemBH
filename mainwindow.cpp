#include "mainwindow.hpp"
#include "ui_mainwindow.h"



using namespace QtDataVisualization;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scatter = new Q3DScatter();
    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
    QWidget *container = QWidget::createWindowContainer(scatter);

    ui->horizontalLayout->addWidget(container, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::printGraph(QScatterDataArray &array)
{

    QScatter3DSeries *series = new QScatter3DSeries;

    series->dataProxy()->addItems(array);
    scatter->addSeries(series);
    scatter->show();

    this->show();

}

