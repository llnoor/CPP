#include "calc.h"
//#include "graph.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  ::Calculator calc;
  ::CreditCalc credit_calc;
  ::Controller controller(&calc, &credit_calc);

  Calc w(nullptr, &controller);
  w.show();
  return a.exec();
}
