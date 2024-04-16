#ifndef SMART_CALC_2_SRC_VIEW_CREDIT_H_
#define SMART_CALC_2_SRC_VIEW_CREDIT_H_

#include <QWidget>

class QPushButton;
class QLineEdit;
class QLabel;
class QComboBox;
class QTextEdit;

QT_BEGIN_NAMESPACE
class QGroupBox;
QT_END_NAMESPACE

#include "../controller/controller.h"
#include "../model/model_creditcalc.h"

class Credit : public QWidget {
  Q_OBJECT

 public:
  Credit(QWidget *parent, ::Controller *controller);
  ~Credit();

  ::Controller *controller_;

 Q_SIGNALS:
  void openCalc();
  void openGraph();
  void closeAll();

 private slots:
  void handleButton();

 private:
  QLabel *label1;
  QLineEdit *mainLineEdit;
  QLineEdit *xLineEdit;
  QPushButton *pushButtonCalc[4];
  QString someString;
  QComboBox *comboBox;
  QGroupBox *groupBox();

  QLabel *loanAmountQLabel;
  QLabel *periodQLabel;
  QLabel *interestRateQLabel;
  QLabel *typeQLabel;
  QLabel *monthlyPaymentQLabel;
  QLabel *overPaymentQLabel;
  QLabel *totalPaymentQLabel;

  QLineEdit *loanAmountQLineEdit;
  QLineEdit *periodQLineEdit;
  QLineEdit *interestRateQLineEdit;
  QComboBox *typeQComboBox;
  QLineEdit *monthlyPaymentQLineEdit;
  QLineEdit *overPaymentQLineEdit;
  QLineEdit *totalPaymentQLineEdit;

  QTextEdit *editQTextEdit;

  QPushButton *creditQPushButton;

  bool is_result = 1;
};
#endif  // SMART_CALC_2_SRC_VIEW_CREDIT_H_
