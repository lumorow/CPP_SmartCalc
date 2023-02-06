#ifndef BACKCALC_H
#define BACKCALC_H
#include <QDebug>
#include <QStack>
#include <QtCore/QObject>
#include <cmath>
#include <iomanip>
#include <iostream>

namespace s21 {
class Back : public QObject {
  Q_OBJECT

public:
  Back();
  explicit Back(QString Data);
  Back(const Back &);
  Back(Back &&);
  ~Back();
  double getRes();
  void setInput(QString data);
  void setX(double newX);
  void polishConvert();
  double calculate();

  // for view
  int status;
  int countLeftBranch;
  int checkBr();
  int checkDot();
  void clearLabel();
  void changeOperation(char oper);
  QChar backCharLabel;
  QString on_pushButton_clicked(QString data);
  QString on_pushButton_dot_clicked();
  QString on_pushButton_clear_clicked();
  QString on_pushButton_CE_clicked();
  QString on_pushButton_eq_clicked(QString x);
  QString on_pushButton_sum_clicked();
  QString on_pushButton_sub_clicked();
  QString on_pushButton_mul_clicked();
  QString on_pushButton_div_clicked();
  QString on_pushButton_bl_clicked();
  QString on_pushButton_br_clicked();
  QString on_pushButton_deg_clicked();
  QString on_pushButton_sin_clicked();
  QString on_pushButton_cos_clicked();
  QString on_pushButton_tan_clicked();
  QString on_pushButton_asin_clicked();
  QString on_pushButton_sqrt_clicked();
  QString on_pushButton_atan_clicked();
  QString on_pushButton_acos_clicked();
  QString on_pushButton_ln_clicked();
  QString on_pushButton_log_clicked();
  QString on_pushButton_mod_clicked();
  QString on_pushButton_0_clicked();
  QString on_pushButton_1_clicked();
  QString on_pushButton_2_clicked();
  QString on_pushButton_3_clicked();
  QString on_pushButton_4_clicked();
  QString on_pushButton_5_clicked();
  QString on_pushButton_6_clicked();
  QString on_pushButton_7_clicked();
  QString on_pushButton_8_clicked();
  QString on_pushButton_9_clicked();
  QString on_pushButton_un_clicked();
  QString on_pushButton_e_clicked();
  void on_pushButton_GRAPH_clicked();

private:
  int countSymb;
  double result;
  double x;
  QString temp;
  QString input;
  void popMapOperation(QChar *operation);
  void popMapFunction(QString function);
  void popLeftBracket();
  void popEnd();
  double Execute(QString op, double first, double second);
  QList<QString> polishStack;
  QStack<QString> mathStack;
  QMap<QString, int> mapOperation{{"(", 0}, {"+", 1}, {"-", 1}, {"*", 2},
                                  {"/", 2}, {"^", 3}, {"~", 4}, {"e", 4}};
  QMap<QString, int> mapFunction{
      {"mod", 4},  {"cos", 4},  {"sin", 4},  {"tan", 4}, {"acos", 4},
      {"asin", 4}, {"atan", 4}, {"sqrt", 4}, {"ln", 4},  {"log", 4}};

  void viewList();
  void viewMathStack();
};
} // namespace s21
#endif //  BACKCALC_H
