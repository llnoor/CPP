#include <cmath>

#define EXS 1.e-7

#include "../controller/controller.h"
#include "../model/model_calculator.h"
#include "../model/model_creditcalc.h"
#include "gtest/gtest.h"

using namespace ;

TEST(Calc, test_1) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("sqrt(30)+4^5");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_EQ(controller.GetResult(), sqrt(30) + pow(4, 5));
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}

TEST(Calc, test_1_1) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("0.1*6");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0.1 * 6, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}

TEST(Calc, test_1_2) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("sin(45)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), sin(45), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}

TEST(Calc, test_2) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("acos(cos(180))-tan(30)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), acos(cos(180)) - tan(30), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_3) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("asin(sin(180))-atan(30)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), asin(sin(180)) - atan(30), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_4) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.006*97.83+3.7^8.37/(-5.6)+ln(25.6)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(),
                5.006 * 97.83 + pow(3.7, 8.37) / (-5.6) + log(25.6), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_5) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression(
      "5.006* 97.83 +3.7^8.37/(-5.6) + ln(25.6) + 5.006* 97.83 + "
      "pow(8.37)/(-5.6) + log(25.6)+ 5.006* 97.83 + pow(3.7, 8.37)/(-5.6) + "
      "log(25.6)+5.006* 97.83 + pow(3.7, 8.37)/(-5.6) + log(25.6)+5.006* "
      "97.83+3.7^8.37/");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 1);
  }
}
TEST(Calc, test_6) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.006* 97.83 +3.7^8.37/(-5.6) + ln(");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 1);
  }
}
TEST(Calc, test_7) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5^2/4");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), pow(5, 2) / 4, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_8) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.006* 97.83 +3.7^8.37/(-5.6) + (");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 1);
  }
}
TEST(Calc, test_9) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("(5+3)*6+20*log(25.6)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), (5 + 3) * 6 + 20 * log10(25.6), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_10) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.68*(4+log(4.3+cos(29.7)))");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 5.68 * (4 + log10(4.3 + cos(29.7))),
                EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_10_1) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("+5.68*(4+log(4.3+ cos(29.7)))");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 1);
  }
}
TEST(Calc, test_10_2) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("u");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0.1 * 6, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 1);
  }
}
TEST(Calc, test_10_3) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("sinsin(4)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 4);
  }
}
TEST(Calc, test_10_4) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("---1+--2");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 3);
  }
}
TEST(Calc, test_10_5) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("x45");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 8);
  }
}
TEST(Calc, test_10_6) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("0.-");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 7);
  }
}
TEST(Calc, test_10_7) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("(cos(45)+exp(3)+cot(1)+acot(4))*0");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_11) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("sin(24.5)**(cos)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 3);
  }
}
TEST(Calc, test_12) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.34*(45.33mod3.563)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 5.34 * fmod(45.33, 3.563), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_13) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("-1E-1+1E1+1E+1");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), -0.1 + 10 + 10, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_14) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("sqrt(x)+4^5");
  controller.SetX(30.567);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), sqrt(30.567) + pow(4, 5), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_15) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("acos(cos(x))-tan(30)");
  controller.SetX(180);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), acos(cos(180)) - tan(30), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_16) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("asin(sin(x))-atan(x)");
  controller.SetX(30);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), asin(sin(30)) - atan(30), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_17) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("x^2/4");
  controller.SetX(5.8);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), pow(5.8, 2) / 4, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_18) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.006*97.83+3.7^8.37/(-5.6)*x+ln(x)");
  controller.SetX(25.6);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(),
                5.006 * 97.83 + pow(3.7, 8.37) / (-5.6) * 25.6 + log(25.6),
                EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_19) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.006* 97.83 +x^8.37/(-5.6) + ln(");
  controller.SetX(0.12);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 1);
  }
}
TEST(Calc, test_21) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("(5+3)*x+20*log(25.6)");
  controller.SetX(6);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), (5 + 3) * 6 + 20 * log10(25.6), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_22) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.68*(x+log(4.3+cos(29.7)))");
  controller.SetX(4);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 5.68 * (4 + log10(4.3 + cos(29.7))),
                EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_23) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("sin(x)+cos");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 4);
  }
}
TEST(Calc, test_24) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("5.34*(xmod3.563)");
  controller.SetX(45.33);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 5.34 * fmod(45.33, 3.563), EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}
TEST(Calc, test_25) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("(-5.34)*(xmod3.563)++1");
  controller.SetX(45.33);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), (-5.34) * fmod(45.33, 3.563) + 1, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}

TEST(Calc, test_26) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetExpression("()");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 10);
  }
}

TEST(Calc, test_27) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  std::string temp_str = "";
  for (int i = 0; i < 26; i++) {
    temp_str += "qwertyuihtfjygkuhjy";
  }
  controller.SetExpression(temp_str);
  controller.SetX(0);
  // EXPECT_NEAR(controller.GetResult(), 0.0 / 0.0, EXS);
  double nan_double = controller.GetResult();
  EXPECT_EQ(controller.GetErrorCode(), 1);
  EXPECT_EQ((nan_double != nan_double), true);
}

TEST(Calc, test_28) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);

  controller.SetExpression("-1+2");
  controller.SetX(0);
  EXPECT_NEAR(controller.GetResult(), 1, EXS);
  EXPECT_EQ(controller.GetErrorCode(), 0);
}

TEST(Calc, test_29) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);

  controller.SetExpression("(1+2)0(1+2)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 6);
  }
}

TEST(Calc, test_30) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);

  controller.SetExpression("((1+2)~)+(1+2)");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 5);
  }
}

TEST(Calc, test_31) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);

  controller.SetExpression(")1+3+(");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 0, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 10);
  }
}

TEST(Calc, test_32) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);

  controller.SetExpression("1^1^4");
  controller.SetX(0);
  if (controller.NoErrors()) {
    EXPECT_NEAR(controller.GetResult(), 1, EXS);
  } else {
    EXPECT_EQ(controller.GetErrorCode(), 0);
  }
}

TEST(Credit, annuity) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetData(2000000, 40, 12);
  controller.CalcAnnuity();
  controller.GetAddData();
  EXPECT_NEAR(controller.GetMonthlyPayment(), 60911.20, 1);
  EXPECT_NEAR(controller.GetOverPayment(), 436448.00, 1);
  EXPECT_NEAR(controller.GetTotalPayment(), 2436448, 1);
}

TEST(Credit, annuity_error) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetData(2000000, -40, -12);
  EXPECT_EQ(controller.CreditNoErrors(), true);
}

TEST(Credit, differentiated) {
  Calculator calc_test;
  CreditCalc credit_test;
  Controller controller(&calc_test, &credit_test);
  controller.SetData(2000000, 40, 12);
  controller.CalcDifferentiated();
  controller.GetAddData();
  EXPECT_NEAR(controller.GetMonthlyPaymentFirst(), 70000, 1);
  EXPECT_NEAR(controller.GetMonthlyPaymentLast(), 50500, 1);
  EXPECT_NEAR(controller.GetOverPayment(), 410000, 1);
  EXPECT_NEAR(controller.GetTotalPayment(), 2410000, 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
