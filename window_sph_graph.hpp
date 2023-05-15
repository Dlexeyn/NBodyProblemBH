#ifndef WINDOW_SPH_GRAPH_HPP
#define WINDOW_SPH_GRAPH_HPP

#include <QMainWindow>
#include <QLogValueAxis>
#include <QLineSeries>
#include <QValueAxis>
#include <QChart>
#include <QChartView>

using namespace QtCharts;

namespace Ui {
class Window_Sph_Graph;
}

class Window_Sph_Graph : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_Sph_Graph(QWidget *parent = nullptr);
    ~Window_Sph_Graph();

    void printGraph(QLineSeries *firstStar, QLineSeries *secondStar, QLineSeries *thirdStar,
                    double &min_x, double &min_y,
                    double &max_x, double &max_y);


private:
    Ui::Window_Sph_Graph *ui;
    QChartView *chartView;
};

#endif // WINDOW_SPH_GRAPH_HPP
