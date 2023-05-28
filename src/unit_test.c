#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_stack.h"
#define s21_EXS 1e-7
START_TEST(equation_test_1) {
  double x = sqrt(30) + pow(4, 5);
  ck_assert_double_eq_tol(logic("sqrt(30)+4^5", 0), x, s21_EXS);
}
END_TEST

START_TEST(equation_test_2) {
  double x = acos(cos(180)) - tan(30);
  ck_assert_double_eq_tol(logic("acos(cos(180))- tan(30)", 0), x, s21_EXS);
}
END_TEST

START_TEST(equation_test_3) {
  double x = asin(sin(180)) - atan(30);
  ck_assert_double_eq_tol(logic("asin(sin(180))- atan(30)", 0), x, s21_EXS);
}
END_TEST

START_TEST(equation_test_4) {
  double x = pow(5, 2) / 4;
  ck_assert_double_eq_tol(logic("5^2/4", 0), x, s21_EXS);
}
END_TEST

START_TEST(equation_test_5) {
  double x = 5.006 * 97.83 + pow(3.7, 8.37) / (-5.6) + log(25.6);
  ck_assert_double_eq_tol(logic("5.006* 97.83 +3.7^8.37/(-5.6) + ln(25.6)", 0),
                          x, s21_EXS);
}
END_TEST

START_TEST(equation_test_6) {
  char str[1000] =
      "5.006* 97.83 +3.7^8.37/(-5.6) + ln(25.6) + 5.006* 97.83 + pow(3.7, "
      "8.37)/(-5.6) + log(25.6)+ 5.006* 97.83 + pow(3.7, 8.37)/(-5.6) + "
      "log(25.6)+5.006* 97.83 + pow(3.7, 8.37)/(-5.6) + log(25.6)+5.006* 97.83 "
      "+3.7^8.37/(-5.6) + ln(25.6) + 5.006* 97.83 + pow(3.7, 8.37)/(-5.6) + "
      "log(25.6)+ 5.006* 97.83 + pow(3.7, 8.37)/(-5.6) + log(25.6)+5.006* "
      "97.83 + pow(3.7, 8.37)/(-5.6) + log(25.6)+5.006* 97.83 +3.7^8.37/(-5.6) "
      "+ ln(25.6) + 5.006* 97.83 + pow(3.7, 8.37)/(-5.6) + log(25.6)+ 5.006* "
      "97.83 + pow(3.7, 8.37)/(-5.6) + log(25.6)";
  ck_assert_double_nan(logic(str, 0));
}
END_TEST

START_TEST(equation_test_7) {
  ck_assert_double_nan(logic("5.006* 97.83 +3.7^8.37/(-5.6) + ln(", 0));
}
END_TEST

START_TEST(equation_test_8) {
  ck_assert_double_nan(logic("5.006* 97.83 +3.7^8.37/(-5.6) + (", 0));
}
END_TEST

START_TEST(equation_test_9) {
  double x = (5 + 3) * 6 + 20 * log10(25.6);
  ck_assert_double_eq_tol(logic("(5+3)*6+20*log(25.6)", 0), x, s21_EXS);
}
END_TEST

START_TEST(equation_test_10) {
  double x = 5.68 * (4 + log10(4.3 + cos(29.7)));
  ck_assert_double_eq_tol(logic("5.68*(4+log(4.3+ cos(29.7)))", 0), x, s21_EXS);
}
END_TEST

START_TEST(equation_test_11) {
  ck_assert_double_nan(logic("sin(24.5)+cos", 0));
}
END_TEST

START_TEST(equation_test_12) {
  double x = 5.34 * fmod(45.33, 3.563);
  ck_assert_double_eq_tol(logic("5.34 * (45.33 mod 3.563)", 0), x, s21_EXS);
}
END_TEST

START_TEST(equation_test_13) {
  ck_assert_double_nan(logic("5.34 * (45.33 mo 3.563)", 0));
}
END_TEST

START_TEST(eq_x_test_1) {
  double x = 30.567;
  double y = sqrt(x) + pow(4, 5);
  ck_assert_double_eq_tol(logic("sqrt(x)+4^5", x), y, s21_EXS);
}
END_TEST

START_TEST(eq_x_test_2) {
  double x = 180;
  double y = acos(cos(x)) - tan(30);
  ck_assert_double_eq_tol(logic("acos(cos(x))- tan(30)", x), y, s21_EXS);
}
END_TEST

START_TEST(eq_x_test_3) {
  double x = 30;
  double y = asin(sin(x)) - atan(x);
  ck_assert_double_eq_tol(logic("asin(sin(x))- atan(x)", x), y, s21_EXS);
}
END_TEST

START_TEST(eq_x_test_4) {
  double x = 5.8;
  double y = pow(x, 2) / 4;
  ck_assert_double_eq_tol(logic("x^2/4", x), y, s21_EXS);
}
END_TEST

START_TEST(eq_x_test_5) {
  double x = 25.6;
  double y = 5.006 * 97.83 + pow(3.7, 8.37) / (-5.6) * x + log(x);
  ck_assert_double_eq_tol(logic("5.006* 97.83 +3.7^8.37/(-5.6)*x + ln(x)", x),
                          y, s21_EXS);
}
END_TEST

START_TEST(eq_x_test_6) {
  double x = 5;
  ck_assert_double_nan(logic("5.006* 97.83 +x^8.37/(-5.6) + ln(", x));
}
END_TEST

START_TEST(eq_x_test_7) {
  double x = 5;
  ck_assert_double_nan(logic("5.006* 97.83 +x^8.37/(-5.6) + (", x));
}
END_TEST

START_TEST(eq_x_test_8) {
  double x = 6;
  double y = (5 + 3) * x + 20 * log10(25.6);
  ck_assert_double_eq_tol(logic("(5+3)*x+20*log(25.6)", x), y, s21_EXS);
}
END_TEST

START_TEST(eq_x_test_9) {
  double x = 4;
  double y = 5.68 * (x + log10(4.3 + cos(29.7)));
  ck_assert_double_eq_tol(logic("5.68*(x+log(4.3+ cos(29.7)))", x), y, s21_EXS);
}
END_TEST

START_TEST(eq_x_test_10) {
  double x = 5;
  ck_assert_double_nan(logic("sin(x)+cos", x));
}
END_TEST

START_TEST(eq_x_test_11) {
  double x = 45.33;
  double y = 5.34 * fmod(x, 3.563);
  ck_assert_double_eq_tol(logic("5.34 * (x mod 3.563)", x), y, s21_EXS);
}
END_TEST

START_TEST(eq_x_test_12) {
  double x = 5;
  ck_assert_double_nan(logic("5.34 * (x mo 3.563)", x));
}
END_TEST

Suite *main_suite(void) {
  Suite *suite = suite_create("Main");
  TCase *tc_equation = tcase_create("equation");
  TCase *tc_eq_x = tcase_create("eq_x");
  TCase *tc_credit = tcase_create("credit");

  suite_add_tcase(suite, tc_equation);
  suite_add_tcase(suite, tc_eq_x);
  suite_add_tcase(suite, tc_credit);

  tcase_add_test(tc_equation, equation_test_1);
  tcase_add_test(tc_equation, equation_test_2);
  tcase_add_test(tc_equation, equation_test_3);
  tcase_add_test(tc_equation, equation_test_4);
  tcase_add_test(tc_equation, equation_test_5);
  tcase_add_test(tc_equation, equation_test_6);
  tcase_add_test(tc_equation, equation_test_7);
  tcase_add_test(tc_equation, equation_test_8);
  tcase_add_test(tc_equation, equation_test_9);
  tcase_add_test(tc_equation, equation_test_10);
  tcase_add_test(tc_equation, equation_test_11);
  tcase_add_test(tc_equation, equation_test_12);
  tcase_add_test(tc_equation, equation_test_13);

  tcase_add_test(tc_eq_x, eq_x_test_1);
  tcase_add_test(tc_eq_x, eq_x_test_2);
  tcase_add_test(tc_eq_x, eq_x_test_3);
  tcase_add_test(tc_eq_x, eq_x_test_4);
  tcase_add_test(tc_eq_x, eq_x_test_5);
  tcase_add_test(tc_eq_x, eq_x_test_6);
  tcase_add_test(tc_eq_x, eq_x_test_7);
  tcase_add_test(tc_eq_x, eq_x_test_8);
  tcase_add_test(tc_eq_x, eq_x_test_9);
  tcase_add_test(tc_eq_x, eq_x_test_10);
  tcase_add_test(tc_eq_x, eq_x_test_11);
  tcase_add_test(tc_eq_x, eq_x_test_12);

  return suite;
}

int main() {
  Suite *suite = main_suite();
  int fails = 0;

  SRunner *runner;
  runner = srunner_create(suite);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);

  fails = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (fails == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
