#include "viewCalc.h"

using namespace s21;

ViewCalc::ViewCalc(Controller *newController, graph *newGraph, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::viewCalc), CalcController(newController),
      CalcGraph(newGraph) {
  ui->setupUi(this);
}

ViewCalc::~ViewCalc() { delete ui; }

void ViewCalc::on_pushButton_CE_clicked() {
  ui->label->setText(CalcController->on_pushButton_CE_clicked());
}

void ViewCalc::on_pushButton_dot_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("."));
}

void ViewCalc::on_pushButton_e_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("e"));
}

void ViewCalc::on_pushButton_clear_clicked() {
  ui->label->setText(CalcController->on_pushButton_clear_clicked());
}

void ViewCalc::on_pushButton_eq_clicked() {
  ui->label->setText(CalcController->on_pushButton_eq_clicked(ui->X->text()));
}

void ViewCalc::on_pushButton_sum_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("+"));
}

void ViewCalc::on_pushButton_sub_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("-"));
}

void ViewCalc::on_pushButton_mul_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("*"));
}

void ViewCalc::on_pushButton_div_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("/"));
}

void ViewCalc::on_pushButton_bl_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("("));
}

void ViewCalc::on_pushButton_br_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked(")"));
}

void ViewCalc::on_pushButton_deg_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("^"));
}

void ViewCalc::on_pushButton_sin_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("sin"));
}

void ViewCalc::on_pushButton_cos_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("cos"));
}

void ViewCalc::on_pushButton_tan_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("tan"));
}

void ViewCalc::on_pushButton_asin_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("asin"));
}

void ViewCalc::on_pushButton_sqrt_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("sqrt"));
}

void ViewCalc::on_pushButton_atan_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("atan"));
}

void ViewCalc::on_pushButton_acos_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("acos"));
}

void ViewCalc::on_pushButton_ln_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("ln"));
}

void ViewCalc::on_pushButton_log_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("log"));
}

void ViewCalc::on_pushButton_mod_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("mod"));
}

void ViewCalc::on_pushButton_0_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("0"));
}

void ViewCalc::on_pushButton_1_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("1"));
}

void ViewCalc::on_pushButton_2_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("2"));
}

void ViewCalc::on_pushButton_3_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("3"));
}

void ViewCalc::on_pushButton_4_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("4"));
}

void ViewCalc::on_pushButton_5_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("5"));
}

void ViewCalc::on_pushButton_6_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("6"));
}

void ViewCalc::on_pushButton_7_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("7"));
}

void ViewCalc::on_pushButton_8_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("8"));
}

void ViewCalc::on_pushButton_9_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("9"));
}

void ViewCalc::on_pushButton_un_clicked() {
  ui->label->setText(CalcController->on_pushButton_clicked("x"));
}

void ViewCalc::on_pushButton_GRAPH_clicked() {
  CalcGraph->slot(ui->label->text(), ui->Left_X->text().toInt(),
                  ui->Right_X->text().toInt());
  CalcGraph->show();
}
