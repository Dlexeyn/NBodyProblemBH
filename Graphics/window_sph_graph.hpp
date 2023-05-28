#ifndef WINDOW_SPH_GRAPH_HPP
#define WINDOW_SPH_GRAPH_HPP

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QLogValueAxis>
#include <QMainWindow>
#include <QValueAxis>

using namespace QtCharts;

namespace Ui {
class Window_Sph_Graph;
}

class Window_Sph_Graph : public QMainWindow {
    Q_OBJECT

public:
    explicit Window_Sph_Graph(QWidget* parent = nullptr);
    ~Window_Sph_Graph();

    void printGraph(QLineSeries* firstStar, QLineSeries* secondStar, QLineSeries* thirdStar,
        long double& min_x, long double& min_y,
        long double& max_x, long double& max_y);

private:
    Ui::Window_Sph_Graph* ui;
    QChartView* chartView;
};

#endif // WINDOW_SPH_GRAPH_HPP
