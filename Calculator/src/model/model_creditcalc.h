#ifndef SMART_CALC_2_SRC_MODEL_MODEL_CREDITCALC_H_
#define SMART_CALC_2_SRC_MODEL_MODEL_CREDITCALC_H_

#include <iomanip>
#include <sstream>

#include "model_calculator.h"

namespace  {
class CreditCalc {
 public:
  CreditCalc();
  ~CreditCalc();
  void SetData(double loan_amount, int months, double interest_rate);

  void CalcAnnuity();
  void CalcDifferentiated();
  double GetMonthlyPayment();
  double GetMonthlyPaymentFirst();
  double GetMonthlyPaymentLast();
  double GetOverPayment();
  double GetTotalPayment();
  std::string GetAddData();
  bool NoErrors();

 private:
  int flag_;
  double loan_amount_;
  int months_;
  double interest_rate_;
  double monthly_payment_;
  double monthly_payment_first_;
  double monthly_payment_last_;
  double over_payment_;
  double total_payment_;
  std::ostringstream string_stream_;
};
}  // namespace 
#endif  // SMART_CALC_2_SRC_MODEL_MODEL_CREDITCALC_H_
