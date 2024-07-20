#include <check.h>
#include <stdio.h>
#include "s21_smartCalc.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define eps 1e-7

START_TEST(test_sin) {
    ck_assert(fabs(0.008726535498 - smartCalc("sin(0.5)", 0, 0)) < eps);
    ck_assert(fabs(0.017452406437 - smartCalc("sin(1)", 0, 0)) < eps);
    ck_assert(fabs(0.866025403784 - smartCalc("sin(60)", 0, 0)) < eps);
    ck_assert(fabs(0 - smartCalc(" sin(180)", 0, 0)) < eps);
    ck_assert(fabs(-1 - smartCalc("sin(270)", 0, 0)) < eps);
    ck_assert(fabs(0 - smartCalc("sin(360 )", 0, 0)) < eps);
}
END_TEST

START_TEST(test_cos) {
    ck_assert(fabs(0.999961923064 - smartCalc("cos(0.5)", 0, 0)) < eps);
    ck_assert(fabs(0.999847695156 - smartCalc("cos(1)", 0, 0)) < eps);
    ck_assert(fabs(0.5 - smartCalc("cos(60)", 0, 0)) < eps);
    ck_assert(fabs(-1 - smartCalc("cos(180)", 0, 0)) < eps);
    ck_assert(fabs(0 - smartCalc("cos(270)", 0, 0)) < eps);
    ck_assert(fabs(1 - smartCalc(" cos  (360)", 0, 0)) < eps);
}
END_TEST

START_TEST(test_acos) {
    ck_assert(fabs(180 - smartCalc("acos(-1)", 0, 0)) < eps);
    ck_assert(fabs(120 - smartCalc("acos( -   0.5)", 0, 0)) < eps);
    ck_assert(fabs(90 - smartCalc("acos(0)", 0, 0)) < eps);
    ck_assert(fabs(60 - smartCalc("acos(0.5)", 0, 0)) < eps);
    ck_assert(fabs(0 - smartCalc("acos(1)", 0, 0)) < eps);
}
END_TEST

START_TEST(test_asin) {
    ck_assert(fabs(-90 - smartCalc("asin(-1)", 0, 0)) < eps);
    ck_assert(fabs(-30 - smartCalc("asin(-0.5)", 0, 0)) < eps);
    ck_assert(fabs(0 - smartCalc("asin(0)", 0, 0)) < eps);
    ck_assert(fabs(30 - smartCalc("asin(0.5   )", 0, 0)) < eps);
    ck_assert(fabs(90 - smartCalc("asin(1)", 0, 0)) < eps);
}
END_TEST

START_TEST(test_tan) {
    ck_assert(fabs(0.017455064928 - smartCalc("tan(1)", 0, 0)) < eps);
    ck_assert(fabs(1.732050807569 - smartCalc("tan(60)", 0, 0)) < eps);
    ck_assert(fabs(0.839099631177 - smartCalc("tan(-500)", 0, 0)) < eps);
    ck_assert(fabs(0.0017453310241888 - smartCalc("tan(0.1)", 0, 0)) < eps);
    ck_assert(fabs(-0.0017453310241888 - smartCalc("tan(-0.1)", 0, 0)) < eps);
}
END_TEST

START_TEST(test_atan) {
    ck_assert(fabs(45 - smartCalc("atan(1)", 0, 0)) < eps);
    ck_assert(fabs(89.0451587461278 - smartCalc("atan(60)", 0, 0)) < eps);
    ck_assert(fabs(89.8854085937622 - smartCalc("atan(  500)", 0, 0)) < eps);
    ck_assert(fabs(5.71059313749964 - smartCalc("atan(0.1)", 0, 0)) < eps);
    ck_assert(fabs(-5.71059313749964 - smartCalc("atan(-0.1)", 0, 0)) < eps);
}
END_TEST

START_TEST(test_sqrt) {
    ck_assert(fabs(1 - smartCalc("sqrt (1 )", 0, 0)) < eps);
    ck_assert(fabs(1.414213562373095 - smartCalc("sqrt(2)", 0, 0)) < eps);
    ck_assert(fabs(1.0954451150103322 - smartCalc("sqrt(1.2)", 0, 0)) < eps);
}
END_TEST

START_TEST(test_ln) {
    ck_assert(fabs(0 - smartCalc("ln(1)", 0, 0)) < eps);
    ck_assert(fabs(0.18232155679395 - smartCalc("ln(1.2)", 0, 0)) < eps);
    ck_assert(fabs(0.69314718055995 - smartCalc("ln(2)", 0, 0)) < eps);
}
END_TEST

START_TEST(test_log) {
    ck_assert(fabs(0 - smartCalc("log (1)", 0, 0)) < eps);
    ck_assert(fabs(0.0791812460 - smartCalc("log( 1.2)", 0, 0)) < eps);
    ck_assert(fabs(0.3010299957 - smartCalc("log(2 )", 0, 0)) < eps);
}
END_TEST

START_TEST(another_test) {
    ck_assert(fabs(-2996.7082644628099174 - smartCalc("2.3 - 0.7 * (6 ^ 3 / 3.3)^2", 0, 0)) < eps);
    ck_assert(fabs(-2 - smartCalc("-2", 0, 0)) < eps);
    ck_assert(fabs(-2 - smartCalc("-( -(- 2) )", 0, 0)) < eps);
    ck_assert(fabs(1 - smartCalc("5 mod 2", 0, 0)) < eps);
    ck_assert(fabs(0.8 - smartCalc("5.6 mod 1.2", 0, 0)) < eps);
    ck_assert(fabs(-519.6 - smartCalc("3.4 + 44 - 3 ^ 4 * 7", 0, 0)) < eps);
    ck_assert(fabs(0.0123456790123457 - smartCalc("3^-4", 0, 0)) < eps);
    ck_assert(fabs(1.2 - smartCalc("1.2", 0, 0)) < eps);
    ck_assert(fabs(1.2 - smartCalc("1,2", 0, 0)) < eps);
    ck_assert(fabs(1.2 - smartCalc("+1,2", 0, 0)) < eps);
    ck_assert(fabs(isnanl(smartCalc("sqrt(-1)", 0, 0))));
    ck_assert(fabs(isnanl(smartCalc("acos(2)", 0, 0))));
    ck_assert(fabs(isnanl(smartCalc("asin(2)", 0, 0))));
    ck_assert(fabs(isnanl(smartCalc("ln(0)", 0, 0))));
    ck_assert(fabs(isnanl(smartCalc("log(-1)", 0, 0))));
}
END_TEST

int main(void) {
    Suite *s1 = suite_create("Core");  // Объявляем сьюит
    SRunner *sr = srunner_create(s1);  // Лаунчер сьюита
    int failed_count;  // Статус тестов сьюита
    TCase *Case = tcase_create("Test");  // Новый кейс
    suite_add_tcase(s1, Case);  // Добавляем кейс

    tcase_add_test(Case, test_sin);
    tcase_add_test(Case, test_asin);
    tcase_add_test(Case, test_cos);
    tcase_add_test(Case, test_acos);
    tcase_add_test(Case, test_tan);
    tcase_add_test(Case, test_atan);
    tcase_add_test(Case, test_sqrt);
    tcase_add_test(Case, test_ln);
    tcase_add_test(Case, test_log);
    tcase_add_test(Case, another_test);

    srunner_run_all(sr, CK_ENV);
    failed_count = srunner_ntests_failed(sr);
    srunner_free(sr);

    return 0;
}