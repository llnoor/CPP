#include "model_creditcalc.h"
namespace  {
CreditCalc::CreditCalc() {
  flag_ = 0;
  loan_amount_ = 1000000;
  months_ = 12;
  interest_rate_ = 15;
  monthly_payment_ = 0;
  monthly_payment_first_ = 0;
  monthly_payment_last_ = 0;
  over_payment_ = 0;
  total_payment_ = 0;
  string_stream_.str(std::string());
};

CreditCalc::~CreditCalc() = default;

bool CreditCalc::NoErrors() { return flag_; }

void CreditCalc::SetData(double loan_amount, int months, double interest_rate) {
  if (loan_amount <= 0 || months <= 0 || interest_rate <= 0)
    flag_ = 1;
  else {
    loan_amount_ = loan_amount;
    months_ = months;
    interest_rate_ = interest_rate;
  }
};

double CreditCalc::GetMonthlyPayment() { return monthly_payment_; }
double CreditCalc::GetMonthlyPaymentFirst() { return monthly_payment_first_; }
double CreditCalc::GetMonthlyPaymentLast() { return monthly_payment_last_; }
double CreditCalc::GetOverPayment() { return over_payment_; }
double CreditCalc::GetTotalPayment() { return total_payment_; }
std::string CreditCalc::GetAddData() { return string_stream_.str(); }

void CreditCalc::CalcAnnuity() {
  string_stream_.str(std::string());
  double monthly_interest_rate = interest_rate_ / 12 / 100;
  double temp_ar = pow(monthly_interest_rate + 1, months_);
  double annuity_ratio = monthly_interest_rate * temp_ar / (temp_ar - 1);
  monthly_payment_ = annuity_ratio * loan_amount_;
  total_payment_ = monthly_payment_ * months_;
  over_payment_ = total_payment_ - loan_amount_;
  string_stream_ << std::fixed << std::setprecision(2)
                 << "Month\t\tPayment\t\tInterest\t\tBalance owed\n";
  double balance_owed = loan_amount_;
  double interest_payment = balance_owed * monthly_interest_rate;
  int checker = 0;
  for (int current_month = 0; current_month < months_; current_month++) {
    balance_owed = balance_owed - monthly_payment_ + interest_payment;
    if (months_ > 25 && current_month == 11 && checker == 0) {
      string_stream_ << "........\n";
      checker = 1;
    }
    if (months_ < 25 || (months_ > 25 && current_month < 10) ||
        (months_ > 25 && current_month > months_ - 11)) {
      string_stream_ << (current_month + 1) << "\t\t" << monthly_payment_
                     << "\t\t" << interest_payment << "\t\t"
                     << fabs(balance_owed) << "\n";
    }
    interest_payment = balance_owed * monthly_interest_rate;
  }
}

void CreditCalc::CalcDifferentiated() {
  string_stream_.str(std::string());
  double basic_payment = loan_amount_ / months_;
  double balance_owed = loan_amount_;
  double monthly_payment = 0;
  double interest_payment = 0;
  monthly_payment_first_ =
      basic_payment + loan_amount_ * interest_rate_ / 12 / 100;
  monthly_payment_last_ = 0.0;
  string_stream_ << std::fixed << std::setprecision(2)
                 << "Month\t\tPayment\t\tInterest\t\tBalance owed\n";
  int checker = 0;
  for (int current_month = 0; current_month < months_; current_month++) {
    interest_payment = balance_owed * interest_rate_ / 12 / 100;
    monthly_payment = basic_payment + interest_payment;
    total_payment_ = total_payment_ + monthly_payment;
    balance_owed = loan_amount_ - basic_payment * (current_month + 1);
    if (months_ > 25 && current_month == 11 && checker == 0) {
      string_stream_ << "........\n";
      checker = 1;
    }
    if (months_ < 25 || (months_ > 25 && current_month < 10) ||
        (months_ > 25 && current_month > months_ - 11)) {
      string_stream_ << (current_month + 1) << "\t\t" << monthly_payment_
                     << "\t\t" << interest_payment << "\t\t"
                     << fabs(balance_owed) << "\n";
    }
    monthly_payment_last_ = monthly_payment;
  }
  over_payment_ = total_payment_ - loan_amount_;
}
}  // namespace 
