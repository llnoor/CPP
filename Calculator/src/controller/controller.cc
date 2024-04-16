#include "controller.h"

namespace  {
Controller::Controller(Calculator* calc, CreditCalc* credit)
    : calc_(calc), credit_(credit){};
Controller::~Controller(){};

// Calculator
void Controller::SetExpression(std::string input_str) {
  calc_->SetExpression(input_str);
}
void Controller::SetX(double input_x) { calc_->SetX(input_x); }
bool Controller::NoErrors() { return calc_->NoErrors(); }
int Controller::GetErrorCode() { return calc_->GetErrorCode(); }
double Controller::GetResult() { return calc_->GetResult(); }

// Credit Calc
void Controller::SetData(double loan_amount, int months, double interest_rate) {
  credit_->SetData(loan_amount, months, interest_rate);
}
void Controller::CalcAnnuity() { credit_->CalcAnnuity(); }
void Controller::CalcDifferentiated() { credit_->CalcDifferentiated(); }
double Controller::GetMonthlyPayment() { return credit_->GetMonthlyPayment(); }
double Controller::GetMonthlyPaymentFirst() {
  return credit_->GetMonthlyPaymentFirst();
}
double Controller::GetMonthlyPaymentLast() {
  return credit_->GetMonthlyPaymentLast();
}
double Controller::GetOverPayment() { return credit_->GetOverPayment(); }
double Controller::GetTotalPayment() { return credit_->GetTotalPayment(); }
std::string Controller::GetAddData() { return credit_->GetAddData(); }
bool Controller::CreditNoErrors() { return credit_->NoErrors(); }

}  // namespace 
