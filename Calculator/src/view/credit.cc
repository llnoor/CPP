#include "credit.h"

#include <QtWidgets>

Credit::Credit(QWidget *parent, ::Controller *controller)
    : QWidget(
          parent,
          Qt::Window | Qt::WindowStaysOnTopHint /*| Qt::FramelessWindowHint*/),
      controller_(controller) {
  QStringList buttonCalcQStringList = {"Calc", "Graph", "Credit", "Close"};

  for (int i = 0; i < 4; ++i) {
    pushButtonCalc[i] = new QPushButton(buttonCalcQStringList.at(i));
    pushButtonCalc[i]->setFixedSize(QSize(105, 30));
  }

  pushButtonCalc[2]->setStyleSheet(
      "background-color: #2d8f4c; color: #f2f2f3; border: 0.5px solid #2d8f4c; "
      "border-radius: 10%;");
  pushButtonCalc[3]->setStyleSheet(
      "background-color: #912423; color: #f2f2f3; border: 0.5px solid #912423; "
      "border-radius: 10%;");

  connect(pushButtonCalc[0], SIGNAL(clicked()), this, SIGNAL(openCalc()));
  connect(pushButtonCalc[1], SIGNAL(clicked()), this, SIGNAL(openGraph()));
  connect(pushButtonCalc[3], SIGNAL(clicked()), this, SIGNAL(closeAll()));

  mainLineEdit = new QLineEdit("0");
  mainLineEdit->setReadOnly(false);
  mainLineEdit->setMaxLength(255);
  mainLineEdit->setAlignment(Qt::AlignRight);

  label1 = new QLabel("  ");
  label1->setAlignment(Qt::AlignRight);
  label1->setFixedSize(QSize(20, 50));

  xLineEdit = new QLineEdit("0");
  xLineEdit->setReadOnly(false);
  xLineEdit->setMaxLength(50);
  xLineEdit->setAlignment(Qt::AlignLeft);

  loanAmountQLabel = new QLabel("Loan Amount, RUB");
  periodQLabel = new QLabel("Period, Months");
  interestRateQLabel = new QLabel("Interest Rate, %");
  typeQLabel = new QLabel("Type of monthly payments");
  monthlyPaymentQLabel = new QLabel("Monthly Payment, RUB");
  overPaymentQLabel = new QLabel("Over Payment, RUB");
  totalPaymentQLabel = new QLabel("Total Payment, RUB");

  loanAmountQLineEdit = new QLineEdit("1000000");
  periodQLineEdit = new QLineEdit("24");
  interestRateQLineEdit = new QLineEdit("10.00");
  typeQComboBox = new QComboBox();
  monthlyPaymentQLineEdit = new QLineEdit(" ");
  overPaymentQLineEdit = new QLineEdit(" ");
  totalPaymentQLineEdit = new QLineEdit(" ");
  editQTextEdit = new QTextEdit("");

  typeQComboBox->addItems({"Annuity", "Differentiated"});

  creditQPushButton = new QPushButton("Calculate a loan");
  connect(creditQPushButton, SIGNAL(clicked()), this, SLOT(handleButton()));

  loanAmountQLineEdit->setFixedSize(QSize(220, 40));
  periodQLineEdit->setFixedSize(QSize(220, 40));
  interestRateQLineEdit->setFixedSize(QSize(220, 40));
  monthlyPaymentQLineEdit->setFixedSize(QSize(220, 40));
  overPaymentQLineEdit->setFixedSize(QSize(220, 40));
  totalPaymentQLineEdit->setFixedSize(QSize(220, 40));
  creditQPushButton->setFixedSize(QSize(470, 40));
  typeQComboBox->setFixedSize(QSize(220, 40));

  loanAmountQLineEdit->setAlignment(Qt::AlignLeft);
  periodQLineEdit->setAlignment(Qt::AlignLeft);
  interestRateQLineEdit->setAlignment(Qt::AlignLeft);
  monthlyPaymentQLineEdit->setAlignment(Qt::AlignLeft);
  overPaymentQLineEdit->setAlignment(Qt::AlignLeft);
  totalPaymentQLineEdit->setAlignment(Qt::AlignLeft);

  loanAmountQLineEdit->setReadOnly(false);
  periodQLineEdit->setReadOnly(false);
  interestRateQLineEdit->setReadOnly(false);
  monthlyPaymentQLineEdit->setReadOnly(true);
  overPaymentQLineEdit->setReadOnly(true);
  totalPaymentQLineEdit->setReadOnly(true);
  editQTextEdit->setReadOnly(true);

  editQTextEdit->setFixedSize(600, 420);
  editQTextEdit->setAlignment(Qt::AlignTop);

  loanAmountQLineEdit->setValidator(new QIntValidator(0, 100000000, this));
  periodQLineEdit->setValidator(new QIntValidator(0, 120, this));
  interestRateQLineEdit->setValidator(new QDoubleValidator(0, 2, 2, this));

  loanAmountQLineEdit->setMaxLength(12);
  interestRateQLineEdit->setMaxLength(5);

  QFont font = mainLineEdit->font();
  font.setPointSize(font.pointSize() + 4);
  mainLineEdit->setFont(font);
  label1->setFont(font);
  xLineEdit->setFont(font);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);

  for (int i = 0; i < 2; i++) {
    mainLayout->addWidget(pushButtonCalc[i], 0, i * 2, 1, 2);
    mainLayout->addWidget(pushButtonCalc[2 + i], 0, (i + 2) * 2 + 1, 1, 2);
  }

  mainLayout->addWidget(label1, 1, 4, 1, 1);
  mainLayout->addWidget(loanAmountQLabel, 1, 0, 1, 4);
  mainLayout->addWidget(periodQLabel, 2, 0, 1, 4);
  mainLayout->addWidget(interestRateQLabel, 3, 0, 1, 4);
  mainLayout->addWidget(typeQLabel, 4, 0, 1, 4);

  mainLayout->addWidget(creditQPushButton, 5, 0, 1, 9);
  mainLayout->addWidget(monthlyPaymentQLabel, 6, 0, 1, 4);
  mainLayout->addWidget(overPaymentQLabel, 7, 0, 1, 4);
  mainLayout->addWidget(totalPaymentQLabel, 8, 0, 1, 4);

  mainLayout->addWidget(loanAmountQLineEdit, 1, 5, 1, 4);
  mainLayout->addWidget(periodQLineEdit, 2, 5, 1, 4);
  mainLayout->addWidget(interestRateQLineEdit, 3, 5, 1, 4);
  mainLayout->addWidget(typeQComboBox, 4, 5, 1, 4);

  mainLayout->addWidget(monthlyPaymentQLineEdit, 6, 5, 1, 4);
  mainLayout->addWidget(overPaymentQLineEdit, 7, 5, 1, 4);
  mainLayout->addWidget(totalPaymentQLineEdit, 8, 5, 1, 4);

  mainLayout->addWidget(editQTextEdit, 0, 9, 9, 7);
  mainLayout->setSpacing(5);
  setLayout(mainLayout);
  setWindowTitle(tr("Credit"));

  creditQPushButton->setStyleSheet(
      "background-color: #2d8f4c; color: #f2f2f3; border: 0.5px solid #2d8f4c; "
      "border-radius: 10%;");
  typeQComboBox->setStyleSheet(
      "background-color: #f2f2f3;color: black; border: 0.5px solid gray; "
      "border-radius: 10%;");

  setStyleSheet(
      "QLineEdit {background-color: #f2f2f3; border: 0.5px solid gray; "
      "border-radius: 10%; color: black;}"
      "QPushButton {background-color: #f2f2f3;color: black; border: 0.5px "
      "solid gray; border-radius: 10%;}"
      "QPushButton:pressed {background-color: #b2b2b2;color: black; border: "
      "0.5px solid gray; border-radius: 10%;}");
}

void Credit::handleButton() {
  editQTextEdit->clear();
  if (loanAmountQLineEdit->text().toDouble() <= 0 ||
      periodQLineEdit->text().toInt() <= 0 ||
      interestRateQLineEdit->text().toDouble() <= 0) {
    monthlyPaymentQLineEdit->setText("ERROR");
    overPaymentQLineEdit->setText("ERROR");
    totalPaymentQLineEdit->setText("ERROR");
  } else {
    controller_->SetData(loanAmountQLineEdit->text().toDouble(),
                         periodQLineEdit->text().toInt(),
                         interestRateQLineEdit->text().toDouble());
    if (typeQComboBox->currentIndex() == 0) {
      controller_->CalcAnnuity();
      monthlyPaymentQLineEdit->setText(
          QString("%1").arg(controller_->GetMonthlyPayment()));
    } else {
      controller_->CalcDifferentiated();
      monthlyPaymentQLineEdit->setText(
          QString("%1...%2")
              .arg(controller_->GetMonthlyPaymentFirst())
              .arg(controller_->GetMonthlyPaymentLast()));
    }
    overPaymentQLineEdit->setText(
        QString::number(controller_->GetOverPayment(), 'f', 2));
    totalPaymentQLineEdit->setText(
        QString::number(controller_->GetTotalPayment(), 'f', 2));
    editQTextEdit->setPlainText(
        QString::fromStdString(controller_->GetAddData()));
  }
}

Credit::~Credit() {}
