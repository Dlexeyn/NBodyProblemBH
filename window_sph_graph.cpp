#include "window_sph_graph.hpp"
#include "ui_window_sph_graph.h"

Window_Sph_Graph::Window_Sph_Graph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_Sph_Graph)
{
    ui->setupUi(this);
    chartView = new QChartView(this);
    ui->horizontalLayout->addWidget(chartView);
}

Window_Sph_Graph::~Window_Sph_Graph()
{
    delete ui;
}

void Window_Sph_Graph::printGraph(QLineSeries *firstStar, QLineSeries *secondStar, QLineSeries *thirdStar, double &min_x, double &min_y, double &max_x, double &max_y)
{
    std::vector<QColor> colors = { Qt::green, Qt::blue, Qt::red };
    firstStar->setColor(colors[0]);     // S2
    secondStar->setColor(colors[1]);    // S38
    thirdStar->setColor(colors[2]);     // S55

    QChart *chart = new QChart();
    chart->addSeries(firstStar);
    chart->addSeries(secondStar);
    chart->addSeries(thirdStar);
    chart->legend()->hide();
    chart->setTitle("Graphic");

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Decl, arcsec");
    axisX->setLabelFormat("%.3f");
    axisX->setTickCount(10);
    axisX->setRange(min_x, max_x);
    chart->addAxis(axisX, Qt::AlignBottom);
    firstStar->attachAxis(axisX);
    secondStar->attachAxis(axisX);
    thirdStar->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("R.A., arcsec");
    axisY->setLabelFormat("%.3f");
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
