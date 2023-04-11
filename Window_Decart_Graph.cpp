#include "Window_Decart_Graph.hpp"
#include "ui_mainwindow.h"



using namespace QtDataVisualization;

Window_Decart_Graph::Window_Decart_Graph(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scatter = new Q3DScatter();
    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
    scatter->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
    QWidget *container = QWidget::createWindowContainer(scatter);

    ui->horizontalLayout->addWidget(container, 1);
}

Window_Decart_Graph::~Window_Decart_Graph()
{
    delete ui;
}

/**
 * @brief MainWindow::printGraph - функция, которая получает в аргумент
 * вектор прокси-серверов данных каждой звезды и рисует график по содержимому
 * каждой сервера
 * @param data - вектор прокси-серверов данных для 3D-точечного графика
 */
void Window_Decart_Graph::printGraph(std::vector<QScatterDataArray> &data)
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

