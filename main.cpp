#include "NBodyProblemBHSolver.cpp"
#include "InverseNBodyProblemBH.cpp"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Star S2("s2.txt");
    Star S38("s38.txt");
    Star S55("s55.txt");
    Simulation simulation(&S2, &S38, &S55, HOUR);
    simulation.runSimulation(HOUR * DAY * YEAR * 20);
    S2.saveHistoryToFile("s2_res.txt");
    S38.saveHistoryToFile("s38_res.txt");
    S55.saveHistoryToFile("s55_res.txt");
    simulation.printRes();

    return a.exec();
}
