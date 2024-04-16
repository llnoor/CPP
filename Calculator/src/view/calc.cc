#include "calc.h"

#include <QtWidgets>

Calc::Calc(QWidget *parent, ::Controller *controller)
    : QWidget(
          parent,
          Qt::Window | Qt::WindowStaysOnTopHint /*| Qt::FramelessWindowHint*/),
      controller_(controller) {
  QStringList buttonQStringList = {
      "AC",  "(",   ")",   "^",   "7",    "8",    "9",    "/",    "4",   "5",
      "6",   "*",   "1",   "2",   "3",    "-",    "0",    ".",    "mod", "+",

      "cos", "sin", "tan", "cot", "acos", "asin", "atan", "acot", "exp", "sqrt",
      "ln",  "log", "CE",  "MS",  "M+",   "M-",   "=",    "x",    "=",   "=",
      "=",   "=",   "=",   "="};

  QStringList buttonCalcQStringList = {"Calc", "Graph", "Credit", "Close"};

  for (int i = 0; i < 4; ++i) {
    pushButtonCalc[i] = new QPushButton(buttonCalcQStringList.at(i));
    pushButtonCalc[i]->setFixedSize(QSize(105, 30));
  }

  pushButtonCalc[0]->setStyleSheet(
      "background-color: #2d8f4c; color: #f2f2f3; border: 0.5px solid #2d8f4c; "
      "border-radius: 10%;");
  pushButtonCalc[3]->setStyleSheet(
      "background-color: #912423; color: #f2f2f3; border: 0.5px solid #912423; "
      "border-radius: 10%;");

  for (int i = 0; i < MAX_BUTTON; ++i) {
    digitPushButton[i] = new QPushButton(buttonQStringList.at(i));
    connect(digitPushButton[i], SIGNAL(clicked()), this, SLOT(handleButton()));
    digitPushButton[i]->setFixedSize(QSize(50, 50));
  }
  digitPushButton[36]->setFixedSize(QSize(220, 50));

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

  QFont font = mainLineEdit->font();
  font.setPointSize(font.pointSize() + 24);
  mainLineEdit->setFont(font);
  label1->setFont(font);
  xLineEdit->setFont(font);
  xLineEdit->setValidator(new QDoubleValidator(this));

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->setSizeConstraint(QLayout::SetFixedSize);

  for (int i = 0; i < 2; i++) {
    mainLayout->addWidget(pushButtonCalc[i], 0, i * 2, 1, 2);
    mainLayout->addWidget(pushButtonCalc[2 + i], 0, (i + 2) * 2 + 1, 1, 2);
  }

  mainLayout->addWidget(mainLineEdit, 1, 0, 1, 9);
  mainLayout->addWidget(label1, 2, 4, 1, 1);
  mainLayout->addWidget(xLineEdit, 2, 6, 1, 3);

  int count = 0;
  for (int row = 0; row < 5; row++) {
    for (int column = 0; column < 4; column++) {
      mainLayout->addWidget(digitPushButton[count], row + 2, column);
      if (count < 12)
        mainLayout->addWidget(digitPushButton[count + 20], row + 3, column + 5);
      count++;
      if (count == 20) break;
    }
  }
  mainLayout->addWidget(digitPushButton[37], 2, 5, 1, 1);
  mainLayout->addWidget(digitPushButton[36], 6, 5, 1, 4);

  mainLayout->setSpacing(5);
  setLayout(mainLayout);
  setWindowTitle(tr("Calculator"));

  digitPushButton[0]->setStyleSheet(
      "background-color: #912423; color: #f2f2f3; border: 0.5px solid #912423; "
      "border-radius: 10%;");
  digitPushButton[36]->setStyleSheet(
      "background-color: #2d8f4c; color: #f2f2f3; border: 0.5px solid #2d8f4c; "
      "border-radius: 10%;");
  setStyleSheet(
      "QLineEdit {background-color: #f2f2f3; border: 0.5px solid gray; "
      "border-radius: 10%; color: black;}"
      "QPushButton {background-color: #f2f2f3;color: black; border: 0.5px "
      "solid gray; border-radius: 10%;}"
      "QPushButton:pressed {background-color: #b2b2b2;color: black; border: "
      "0.5px solid gray; border-radius: 10%;}");

  g = new Graph(this, controller_);
  g->show();
  g->hide();

  c = new Credit(this, controller_);
  c->show();
  c->hide();

  connect(pushButtonCalc[1], SIGNAL(clicked()), g, SLOT(show()));
  connect(pushButtonCalc[1], SIGNAL(clicked()), this, SLOT(hide()));

  connect(pushButtonCalc[2], SIGNAL(clicked()), c, SLOT(show()));
  connect(pushButtonCalc[2], SIGNAL(clicked()), this, SLOT(hide()));

  connect(pushButtonCalc[3], SIGNAL(clicked()), g, SLOT(close()));
  connect(pushButtonCalc[3], SIGNAL(clicked()), c, SLOT(close()));
  connect(pushButtonCalc[3], SIGNAL(clicked()), this, SLOT(close()));

  connect(g, SIGNAL(openCalc()), this, SLOT(show()));
  connect(g, SIGNAL(openCalc()), g, SLOT(hide()));
  connect(g, SIGNAL(openCredit()), c, SLOT(show()));
  connect(g, SIGNAL(openCredit()), g, SLOT(hide()));
  connect(g, SIGNAL(closeAll()), c, SLOT(close()));
  connect(g, SIGNAL(closeAll()), g, SLOT(close()));
  connect(g, SIGNAL(closeAll()), this, SLOT(close()));

  connect(c, SIGNAL(openCalc()), this, SLOT(show()));
  connect(c, SIGNAL(openCalc()), c, SLOT(hide()));
  connect(c, SIGNAL(openGraph()), g, SLOT(show()));
  connect(c, SIGNAL(openGraph()), c, SLOT(hide()));
  connect(c, SIGNAL(closeAll()), c, SLOT(close()));
  connect(c, SIGNAL(closeAll()), g, SLOT(close()));
  connect(c, SIGNAL(closeAll()), this, SLOT(close()));
}

void Calc::openCalc() {
  this->show();
  g->hide();
}

void Calc::openGraph() {
  this->hide();
  g->show();
}

void Calc::openCredit() {
  this->hide();
  g->show();
}

void Calc::openDeposit() {
  this->hide();
  g->show();
}

void Calc::handleButton() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QString buttonText = button->text();
  static QRegularExpression rx(
      "cos|sin|tan|cot|acos|asin|atan|acot|exp|sqrt|ln|log");

  if (xLineEdit->text() == "") {
    xLineEdit->setText("0");
  }

  if (buttonText.contains("AC")) {
    mainLineEdit->setText("0");
    is_result = 1;
  } else if (buttonText.contains("=")) {
    int flag = 0;
    controller_->SetExpression(mainLineEdit->text().toStdString());
    controller_->SetX(xLineEdit->text().toDouble());

    double resultDouble = 0.0;
    if (controller_->NoErrors()) {
      resultDouble = controller_->GetResult();
      mainLineEdit->setText(QString("%1").arg(resultDouble));
    } else {
      flag = controller_->GetErrorCode();
      mainLineEdit->setText(QString("ERROR:%1").arg(flag));
    }
    is_result = 1;
  } else {
    if (is_result == 1) {
      is_result = 0;
      mainLineEdit->setText("");
    }
    if (buttonText.contains(rx)) {
      buttonText = buttonText + "(";
    }
    mainLineEdit->setText(mainLineEdit->text() += buttonText);
  }
}

Calc::~Calc(){};
