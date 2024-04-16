#ifndef SMART_CALC_2_SRC_CONTROLLER_CONTROLLER_H_
#define SMART_CALC_2_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model_calculator.h"
#include "../model/model_creditcalc.h"

namespace  {
class Controller {
 public:
  Controller(Calculator* calc, CreditCalc* credit);
  ~Controller();

  // Calculator:
  void SetExpression(std::string input_str);
  void SetX(double input_x);
  bool NoErrors();
  int GetErrorCode();
  double GetResult();

  // Credit Calc:
  void SetData(double loan_amount, int months, double interest_rate);
  void CalcAnnuity();
  void CalcDifferentiated();
  double GetMonthlyPayment();
  double GetMonthlyPaymentFirst();
  double GetMonthlyPaymentLast();
  double GetOverPayment();
  double GetTotalPayment();
  std::string GetAddData();
  bool CreditNoErrors();

 private:
  Calculator* calc_;
  CreditCalc* credit_;
};
}  // namespace 

#endif  // SMART_CALC_2_SRC_CONTROLLER_CONTROLLER_H_
