#include "Window_sph_graph.hpp"
#include "ui_mainwindow_sph_graph.h"

Window_Sph_Graph::Window_Sph_Graph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Sph_Graph)
{
    ui->setupUi(this);
//    scatter = new Q3DScatter();
//    scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
//    scatter->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);
//    QWidget *container = QWidget::createWindowContainer(scatter);

    chartView = new QChartView(this);


    ui->horizontalLayout->addWidget(chartView);
}

Window_Sph_Graph::~Window_Sph_Graph()
{
    delete ui;
}

void Window_Sph_Graph::printGraph(QLineSeries *firstStar,
                                  QLineSeries *secondStar,
                                  QLineSeries *thirdStar,
                                  double &min_x, double &min_y,
                                  double &max_x, double &max_y)
{
//    std::vector<QColor> colors = { Qt::green, Qt::blue, Qt::red };
//    for(std::size_t i = 0; i < data.size(); i++)
//    {
//        QScatter3DSeries *current_series = new QScatter3DSeries;
//        current_series->dataProxy()->addItems(data[i]);
//        current_series->setBaseColor(colors[i]);
//        scatter->addSeries(current_series);
//    }
//    scatter->show();

    QChart *chart = new QChart();
    chart->addSeries(firstStar);
    chart->addSeries(secondStar);
    chart->addSeries(thirdStar);
    chart->legend()->hide();
    chart->setTitle("Graphic");
    //chart->setPlotArea()

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Decl, рад");
    axisX->setLabelFormat("%.20f");
    axisX->setTickCount(10);
    axisX->setRange(min_x, max_x);
    chart->addAxis(axisX, Qt::AlignBottom);
    firstStar->attachAxis(axisX);
    secondStar->attachAxis(axisX);
    thirdStar->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("R.A., рад");
    axisY->setLabelFormat("%.20f");
    axisY->setTickCount(10);
    axisY->setRange(min_y, max_y);
    chart->addAxis(axisY, Qt::AlignLeft);
    firstStar->attachAxis(axisY);
    secondStar->attachAxis(axisY);
    thirdStar->attachAxis(axisY);

    // Устанавливаем график в представление
    chartView->setChart(chart);
    this->show();
}
