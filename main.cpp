#include "InverseNBodyProblemBH.cpp"
#include "NBodyProblemBHSolver.cpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Star S2("s2");
    Star S38("s38");
    Star S55("s55");
    Simulation simulation(&S2, &S38, &S55, HOUR);
    simulation.generalSolution();
    S2.saveHistoryToFile("s2_res.txt");
    S38.saveHistoryToFile("s38_res.txt");
    S55.saveHistoryToFile("s55_res.txt");
    simulation.printRes();

    return a.exec();
}
