#include "controllerCalc.h"

using namespace s21;

Controller::Controller(Back *b) : back(b) {}

double Controller::CalcResultX(QString data, double x) {
  back->setInput(data);
  back->setX(x);
  back->polishConvert();
  return back->calculate();
}

QString Controller::on_pushButton_clicked(QString data) {
  return back->on_pushButton_clicked(data);
}

QString Controller::on_pushButton_clear_clicked() {
  return back->on_pushButton_clear_clicked();
}

QString Controller::on_pushButton_CE_clicked() {
  return back->on_pushButton_CE_clicked();
}

QString Controller::on_pushButton_eq_clicked(QString x) {
  return back->on_pushButton_eq_clicked(x);
}
