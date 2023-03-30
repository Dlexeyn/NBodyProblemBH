#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <Q3DScatter>
#include <QtDataVisualization>

using namespace QtDataVisualization;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void printGraph(QScatterDataArray &array);

private:
    Ui::MainWindow *ui;
    Q3DScatter *scatter;
};
#endif // MAINWINDOW_HPP
