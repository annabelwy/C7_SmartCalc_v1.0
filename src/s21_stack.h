#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum {
  digit = 0,           // цифра
  open_bracket = 2,    //  (
  closed_bracket = 3,  //  )
  sum = 4,             // +
  sub = 5,             // -
  mul = 6,             // *
  di = 7,              // /
  mod = 8,             // mod
  po = 9,              // ^
  lo = 10,             // -  log()
  ln = 11,             // -  ln()
  si = 12,             // sin()
  asi = 13,            // asin()
  co = 14,             // cos()
  aco = 15,            // acos()
  ta = 16,             // tan()
  ata = 17,            // atan()
  sqr = 18,            // -   sqrt()
} type_t;

typedef struct node {
  type_t type;   // чтоб чекнуть какой тип
  double value;  // если тип - число
  int priority;
  struct node *next;  // след узел
} lexeme;

typedef struct que {
  lexeme *end, *head;
} que;
void free_stack(lexeme **head);
double logic(const char *expr_old, double x);
void merge(lexeme **digits, lexeme **signs);
void s21_push(double value, int priority, int type, lexeme **stack);
void s21_pop(lexeme **head);
lexeme *start(lexeme **head);
int return_ind(char *expr, double *digit);
int is_empty(lexeme *head);
void reverse_stack(lexeme **new_stack, lexeme **old_stack);
int check_brackets(char *expr);
int is_digit(char *numb);     // на то, что число
int check_point(char *expr);  // что до запятой и после
int is_sign(char *expr);
int check_trigonometry(char *expr);
int after_sign(char *expr);
int check_sign(char *expr);
char *remove_sp(char *old);
int give_priority_and_value(char *expr, lexeme **znak);
int give_lexeme_to_trig(char *expr, lexeme **trig);
int give_to_lg(char *expr, lexeme **log);
double math(int type, double a);  // чтоб с одним числом
double math_check(int type, double a, double b);  // вместе math_s
int unary(char *expr, int ind);
void pusher(
    lexeme **digits, lexeme **signs,
    lexeme znak);  // пушит и убирает, если приоритетность вставляемого больше,
                   // передаем два стека чтоб менять и то что вставляем
int validator(char *expr);
int parser(char *expr_old, double x, lexeme **digits);
int after_x(char *expr);
int check_x(char *expr);
int check_after_pow(char *expr);
int check_pow(char *expr);
int check_logs(char *expr);  // проверка логарифмов
int check_len(char *expr);
int after_sign(char *expr);
int if_func(char *expr);
int check_digit(char *expr);
int after_digit(char *expr);
#endif  // SRC_S21_STACK_H_