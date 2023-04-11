#include "Window_sph_graph.hpp"
#include "ui_mainwindow_sph_graph.h"

Window_Sph_Graph::Window_Sph_Graph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Sph_Graph)
{
    ui->setupUi(this);
    scatter = new Q3DScatter();
    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
    scatter->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    QWidget *container = QWidget::createWindowContainer(scatter);

    ui->horizontalLayout->addWidget(container, 1);
}

Window_Sph_Graph::~Window_Sph_Graph()
{
    delete ui;
}

void Window_Sph_Graph::printGraph(std::vector<QScatterDataArray> &data)
{
    std::vector<QColor> colors = { Qt::green, Qt::blue, Qt::red };
    for(std::size_t i = 0; i < data.size(); i++)
    {
        QScatter3DSeries *current_series = new QScatter3DSeries;
        current_series->dataProxy()->addItems(data[i]);
        current_series->setBaseColor(colors[i]);
        scatter->addSeries(current_series);
    }
    scatter->show();

    this->show();
}
