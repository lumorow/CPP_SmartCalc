#ifndef GRAPH_H
#define GRAPH_H

#include <math.h>

#include <QVector>
#include <QWidget>

#include "ui_graph.h"
#include "../controller_calc/controllerCalc.h"

namespace Ui {
class graph;
}

namespace s21 {
class graph : public QWidget {
  Q_OBJECT

 public:
  void slot(QString data, int leftX, int rightX);
  explicit graph(Controller *newController, QWidget *parent = nullptr);
  ~graph();

 private:
  Ui::graph *ui;
  int range;
  double res;
  Controller *CalcController;
};
}  // namespace s21
#endif  // GRAPH_H
