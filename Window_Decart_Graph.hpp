#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <Q3DScatter>
#include <QtDataVisualization>

using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Window_Decart_Graph : public QMainWindow
{
    Q_OBJECT

public:
    Window_Decart_Graph(QWidget *parent = nullptr);
    ~Window_Decart_Graph();

    void printGraph(std::vector<QScatterDataArray> &data);

private:
    Ui::MainWindow *ui;
    Q3DScatter *scatter;
};
#endif // MAINWINDOW_HPP
