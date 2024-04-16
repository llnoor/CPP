#ifndef SMART_CALC_2_SRC_VIEW_CALC_H_
#define SMART_CALC_2_SRC_VIEW_CALC_H_

#include <QWidget>

#include "credit.h"
#include "graph.h"

#define MAX_BUTTON 40

class QPushButton;
class QLineEdit;
class QLabel;
class QComboBox;

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

#include "../controller/controller.h"
#include "../model/model_calculator.h"

class Calc : public QWidget {
  Q_OBJECT

 public:
  Calc(QWidget *parent, ::Controller *controller);
  ~Calc();

  ::Controller *controller_;

 private slots:
  void handleButton();
  void openCalc();
  void openGraph();
  void openCredit();
  void openDeposit();

 private:
  Graph *g;
  Credit *c;
  QLabel *label1;
  QLineEdit *mainLineEdit;
  QLineEdit *xLineEdit;
  QPushButton *pushButtonCalc[4];
  QPushButton *digitPushButton[MAX_BUTTON];
  QString someString;
  QComboBox *comboBox;
  QGroupBox *groupBox();
  bool is_result = 1;
};
#endif  // SMART_CALC_2_SRC_VIEW_CALC_H_
