#ifndef VIEWCALC_H
#define VIEWCALC_H

#include <QMainWindow>

#include "graph/graph.h"
#include "ui_viewCalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ViewCalc;
}
QT_END_NAMESPACE

namespace s21 {
class ViewCalc : public QMainWindow {
  Q_OBJECT

public:
  ViewCalc(Controller *newController, graph *newGraph,
           QWidget *parent = nullptr);
  ~ViewCalc();

private:
  Ui::viewCalc *ui;
  Controller *CalcController;
  graph *CalcGraph;

private slots:
  void on_pushButton_dot_clicked();
  void on_pushButton_clear_clicked();
  void on_pushButton_CE_clicked();
  void on_pushButton_eq_clicked();
  void on_pushButton_sum_clicked();
  void on_pushButton_sub_clicked();
  void on_pushButton_mul_clicked();
  void on_pushButton_div_clicked();
  void on_pushButton_bl_clicked();
  void on_pushButton_br_clicked();
  void on_pushButton_deg_clicked();
  void on_pushButton_sin_clicked();
  void on_pushButton_cos_clicked();
  void on_pushButton_tan_clicked();
  void on_pushButton_asin_clicked();
  void on_pushButton_sqrt_clicked();
  void on_pushButton_atan_clicked();
  void on_pushButton_acos_clicked();
  void on_pushButton_ln_clicked();
  void on_pushButton_log_clicked();
  void on_pushButton_mod_clicked();
  void on_pushButton_0_clicked();
  void on_pushButton_1_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();
  void on_pushButton_8_clicked();
  void on_pushButton_9_clicked();
  void on_pushButton_un_clicked();
  void on_pushButton_e_clicked();
  void on_pushButton_GRAPH_clicked();
};
} // namespace s21
#endif // VIEWCALC_H
