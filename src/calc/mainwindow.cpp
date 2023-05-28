#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_clicked() {
  QString expr = ui->lineEdit->text();
  double x = ui->doubleSpinBox->value();
  double res = logic(expr.toStdString().c_str(), x);
  ui->lineEdit->setText(QString::number(res));
}

void MainWindow::on_pushButton_2_clicked() {
  QString str = ui->lineEdit->text();
  str.resize(str.size() - 1);
  ui->lineEdit->setText(str);
}

void MainWindow::on_pushButton_3_clicked() { ui->lineEdit->setText("\0"); }

void MainWindow::on_pushButton_4_clicked() {
  double a = -10;
  double b = 10;
  double h = 0.001;
  int numer_of_points = (b - a) / h + 2;
  QVector<double> x(numer_of_points), y(numer_of_points);
  int i = 0;

  //Пробегаем по всем точкам
  for (double X = a; X <= b; X += h) {
    x[i] = X;
    y[i] = logic(ui->lineEdit->text().toStdString().c_str(), X);
    i++;
  }
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->graph(0)->setData(x, y);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  ui->widget->xAxis->setRange(a, b);  //Для оси Ox
  ui->widget->yAxis->setRange(a, b);  //Для оси Oy
  ui->widget->replot();
}
