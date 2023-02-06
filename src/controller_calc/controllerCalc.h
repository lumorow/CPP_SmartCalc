#ifndef CONTROLLERCALC_H
#define CONTROLLERCALC_H

#include "../back_calc/back_calc.h"

namespace s21 {
class Controller {
public:
  explicit Controller(Back *b);
  double CalcResultX(QString data, double x);
  QString on_pushButton_clicked(QString data);
  QString on_pushButton_clear_clicked();
  QString on_pushButton_CE_clicked();
  void on_pushButton_GRAPH_clicked();
  QString on_pushButton_eq_clicked(QString x);

private:
  Back *back;
};
} // namespace s21
#endif //  CONTROLLERCALC_H
