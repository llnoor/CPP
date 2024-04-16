#include "graph.h"

Graph::Graph(QWidget *parent, ::Controller *controller)
    : QWidget(
          parent,
          Qt::Window | Qt::WindowStaysOnTopHint /*| Qt::FramelessWindowHint*/),
      controller_(controller) {
  QStringList buttonQStringList = {"AC",
                                   "(",
                                   ")",
                                   "^",
                                   "7",
                                   "8",
                                   "9",
                                   "/",
                                   "4",
                                   "5",
                                   "6",
                                   "*",
                                   "1",
                                   "2",
                                   "3",
                                   "-",
                                   "0",
                                   ".",
                                   "mod",
                                   "+",

                                   "cos",
                                   "sin",
                                   "tan",
                                   "cot",
                                   "acos",
                                   "asin",
                                   "atan",
                                   "acot",
                                   "exp",
                                   "sqrt",
                                   "ln",
                                   "log",
                                   "CE",
                                   "MS",
                                   "M+",
                                   "M-",
                                   "Draw a graph",
                                   "x",
                                   "=",
                                   "=",
                                   "=",
                                   "=",
                                   "=",
                                   "="};

  QStringList buttonCalcQStringList = {"Calc", "Graph", "Credit", "Close"};

  for (int i = 0; i < 4; ++i) {
    pushButtonCalc[i] = new QPushButton(buttonCalcQStringList.at(i));
    pushButtonCalc[i]->setFixedSize(QSize(105, 30));
  }

  pushButtonCalc[1]->setStyleSheet(
      "background-color: #2d8f4c; color: #f2f2f3; border: 0.5px solid #2d8f4c; "
      "border-radius: 10%;");
  pushButtonCalc[3]->setStyleSheet(
      "background-color: #912423; color: #f2f2f3; border: 0.5px solid #912423; "
      "border-radius: 10%;");

  connect(pushButtonCalc[0], SIGNAL(clicked()), this, SIGNAL(openCalc()));
  connect(pushButtonCalc[2], SIGNAL(clicked()), this, SIGNAL(openCredit()));
  connect(pushButtonCalc[3], SIGNAL(clicked()), this, SIGNAL(closeAll()));

  for (int i = 0; i < MAX_BUTTON; ++i) {
    digitPushButton[i] = new QPushButton(buttonQStringList.at(i));
    connect(digitPushButton[i], SIGNAL(clicked()), this, SLOT(handleButton()));
    digitPushButton[i]->setFixedSize(QSize(50, 50));
  }
  digitPushButton[36]->setFixedSize(QSize(220, 50));

  mainLineEdit = new QLineEdit("sin(x)");
  mainLineEdit->setReadOnly(false);
  mainLineEdit->setMaxLength(255);
  mainLineEdit->setAlignment(Qt::AlignRight);

  label1 = new QLabel("  ");
  label1->setAlignment(Qt::AlignRight);
  label1->setFixedSize(QSize(20, 50));

  xLineEdit = new QLineEdit("");
  xLineEdit->setReadOnly(false);
  xLineEdit->setMaxLength(255);
  xLineEdit->setDisabled(true);
  xLineEdit->setAlignment(Qt::AlignLeft);

  xFromLineEdit = new QLineEdit("-10");
  xFromLineEdit->setReadOnly(false);
  xFromLineEdit->setMaxLength(15);
  xFromLineEdit->setAlignment(Qt::AlignCenter);
  xFromLineEdit->setFixedSize(QSize(160, 50));

  xToLineEdit = new QLineEdit("10");
  xToLineEdit->setReadOnly(false);
  xToLineEdit->setMaxLength(255);
  xToLineEdit->setAlignment(Qt::AlignCenter);
  xToLineEdit->setFixedSize(QSize(160, 50));

  xFromToLineEdit = new QLineEdit("From  |  X  |  To");
  xFromToLineEdit->setReadOnly(true);
  xFromToLineEdit->setMaxLength(255);
  xFromToLineEdit->setAlignment(Qt::AlignCenter);
  xFromToLineEdit->setFixedSize(QSize(130, 50));

  QFont font = mainLineEdit->font();
  font.setPointSize(font.pointSize() + 24);
  mainLineEdit->setFont(font);
  label1->setFont(font);
  xLineEdit->setFont(font);

  chartView = new QChartView(this);
  series = new QLineSeries();
  int k = -100;
  while (k <= 100) {
    *series << QPointF(k * 0.1, sin(k * 0.1));
    ++k;
  }

  chart = new QChart();
  chart->addSeries(series);
  chart->legend()->hide();

  axisX = new QValueAxis();
  axisX->setTitleText("X");
  axisX->setTickCount(11);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  axisY = new QValueAxis();
  axisY->setTitleText("Y");
  axisY->setTickCount(11);
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chartView->setChart(chart);

  chartView->setFixedSize(600, 420);
  chartView->setAlignment(Qt::AlignTop);

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
  mainLayout->addWidget(xFromLineEdit, 8, 0, 1, 3);
  mainLayout->addWidget(xFromToLineEdit, 8, 3, 1, 3);
  mainLayout->addWidget(xToLineEdit, 8, 6, 1, 3);
  mainLayout->addWidget(chartView, 0, 10, 9, 5);

  mainLayout->setSpacing(5);
  setLayout(mainLayout);
  setWindowTitle(tr("Graph"));

  setStyleSheet(
      "QLineEdit {background-color: #f2f2f3; border: 0.5px solid gray; "
      "border-radius: 10%; color: black;}"
      "QPushButton {background-color: #f2f2f3;color: black; border: 0.5px "
      "solid gray; border-radius: 10%;}"
      "QPushButton:pressed {background-color: #b2b2b2;color: black; border: "
      "0.5px solid gray; border-radius: 10%;}");
  digitPushButton[0]->setStyleSheet(
      "background-color: #912423; color: #f2f2f3; border: 0.5px solid #912423; "
      "border-radius: 10%;");
  digitPushButton[36]->setStyleSheet(
      "background-color: #2d8f4c; color: #f2f2f3; border: 0.5px solid #2d8f4c; "
      "border-radius: 10%;");
}

void Graph::handleButton() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  QString buttonText = button->text();
  static QRegularExpression rx(
      "cos|sin|tan|cot|acos|asin|atan|acot|exp|sqrt|ln|log");

  if (xFromLineEdit->text() == "") {
    xFromLineEdit->setText("-10");
  }

  if (xToLineEdit->text() == "") {
    xToLineEdit->setText("-10");
  }

  if (buttonText.contains("AC")) {
    mainLineEdit->setText("0");
    is_result = 1;
  } else if (buttonText.contains("Draw a graph")) {
    int flag = 0;
    controller_->SetExpression(mainLineEdit->text().toStdString());
    controller_->SetX(xFromLineEdit->text().toDouble());

    double resultDouble = 0.0;
    if (controller_->NoErrors()) {
      resultDouble = controller_->GetResult();
    } else {
      flag = controller_->GetErrorCode();
      xLineEdit->setText(QString("ERROR:%1").arg(flag));
    }

    is_result = 1;

    series->clear();

    double doubleFrom = xFromLineEdit->text().toDouble();
    double doubleTo = xToLineEdit->text().toDouble();
    double step = (doubleTo - doubleFrom) / 1000;
    double minY = resultDouble;
    double maxY = minY;

    for (int i = 0; i < 1000; i++) {
      controller_->SetX(doubleFrom + step * i);
      resultDouble = controller_->GetResult();
      if (minY > resultDouble) minY = resultDouble;
      if (maxY < resultDouble) maxY = resultDouble;
      if (flag == 0) *series << QPointF(doubleFrom + step * i, resultDouble);
    }

    minY = minY < 0 ? minY * 1.1 : minY * 0.85;
    maxY = maxY > 0 ? maxY * 1.1 : maxY * 0.85;

    axisX->setRange(doubleFrom, doubleTo);
    axisY->setRange(minY, maxY);

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

Graph::~Graph() {}
