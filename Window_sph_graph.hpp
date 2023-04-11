#ifndef MAINWINDOW_SPH_GRAPH_HPP
#define MAINWINDOW_SPH_GRAPH_HPP

#include <QMainWindow>
#include <Q3DScatter>
#include <QtDataVisualization>
#include "qcustomplot.h"

using namespace QtDataVisualization;

namespace Ui {
class MainWindow_Sph_Graph;
}

class Window_Sph_Graph : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_Sph_Graph(QWidget *parent = nullptr);
    ~Window_Sph_Graph();
    void printGraph(std::vector<QScatterDataArray> &data);

private:
    Ui::MainWindow_Sph_Graph *ui;
    Q3DScatter *scatter;
    QCustomPlot *graph;
};

#endif // MAINWINDOW_SPH_GRAPH_HPP
