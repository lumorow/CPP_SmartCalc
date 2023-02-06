#include "../view_calc/viewCalc.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    s21::Back back;
    s21::Controller controller(&back);
    s21::graph graph(&controller);
    s21::ViewCalc view(&controller, &graph);
    view.show();
    return a.exec();
}
