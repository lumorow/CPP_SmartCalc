#include "graph.h"

using namespace s21;

graph::graph(Controller *newController, QWidget *parent) : QWidget(parent),
    ui(new Ui::graph), CalcController(newController) {
  range = 0;
  res = 0;
  ui->setupUi(this);
}

graph::~graph() { delete ui; }

void graph::slot(QString data, int leftX, int rightX) {
  ui->widget->clearGraphs();
  QVector<double> x, y;
  for (double i = leftX; i < rightX; i += 0.01) {
    res = CalcController->CalcResultX(data, i);
    if (!isnan(res)) {
      x.append(i);
      y.append(res);
    }
  }
  ui->widget->replot();
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->xAxis->setRange(-20, 20);
  ui->widget->yAxis->setRange(-10, 10);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
}
