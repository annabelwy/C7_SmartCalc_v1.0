#include "s21_stack.h"

int check_brackets(char *expr) {  // проверка скобок
  int res = 1;
  int num_brackets = 0;  // счетчик скобок
  char expr_new[1000] = {0};
  strcpy(expr_new, expr);
  for (int i = 0; i < (int)strlen(expr_new) && res == 1; i++) {
    if (expr_new[i] == '(' &&
        (if_func(expr_new + i + 1) || expr_new[i + 1] == '+' ||
         expr_new[i + 1] == '-' || is_digit(expr_new + i + 1) ||
         expr_new[i + 1] == '(' || expr_new[i + 1] == 'x')) {
      num_brackets++;
    } else if (expr_new[i] == '(' &&
               (!if_func(expr_new + i + 1) && expr_new[i + 1] != '+' &&
                expr_new[i + 1] != '-' && !is_digit(expr_new + i + 1) &&
                expr_new[i + 1] != '(')) {
      res = 0;
    } else if (expr_new[i] == ')') {
      num_brackets--;
    }
  }
  if (num_brackets != 0 && res != 0) res = 0;
  return res;
}

int check_pow(char *expr) {  // после - число или скобка
  int res = 1;
  char expr_new[1000] = {0};
  strcpy(expr_new, expr);
  for (int i = 0; i < (int)strlen(expr_new) && res == 1;) {
    if (expr_new[i] == '^' &&
        ((!is_digit(expr_new + i - 1)) && expr_new[i - 1] != ')' &&
         expr_new[i - 1] !=
             'x'))  // перед степенью - либо число либо скобка либо x
    {
      res = 0;
    } else if (expr_new[i] == '^' &&
               ((is_digit(expr_new + i - 1)) || expr_new[i - 1] == ')' ||
                expr_new[i - 1] == 'x')) {
      res = check_after_pow(expr_new + i);
    }
    i++;
  }
  return res;
}

int check_after_pow(char *expr) {
  int res = 0;
  char expr_new[1000] = {0};
  strcpy(expr_new, expr);
  if (expr_new[0] == '^' &&
      ((is_digit(expr_new + 1)) || expr_new[1] == '(' || expr_new[1] == 'x' ||
       if_func(
           expr_new +
           1)))  // то что после степени -либо число, либо ( либо x либо функция
  {
    res = 1;
  }
  return res;
}

int after_x(char *expr) {  // после икса либо знак, либо закрывающая скобочка
  int res = 1;
  char expr_new[1000] = {0};
  strcpy(expr_new, expr);
  if (!(is_sign(expr_new)) && expr_new[0] != ')' && expr_new[0] != '^' &&
      expr_new[0] != '\0')
    res = 0;
  return res;
}

int check_sign(char *expr) {
  int res = 1;
  char expr_new[1000] = {0};

  strcpy(expr_new, expr);
  for (int i = 0; i < (int)strlen(expr_new) && res == 1;) {
    if (is_sign(expr_new + i) && !unary(expr_new + i, i) &&
        (is_digit(expr_new + i - 1) || expr_new[i - 1] == ')' ||
         expr_new[i - 1] == 'x'))  // то что знак не унарный и всё ок с иксом
    {
      res = after_sign(expr_new + i);
    } else if (is_sign(expr_new + i) && !unary(expr_new + i, i) &&
               (!is_digit(expr_new + i - 1) && expr_new[i - 1] != ')' &&
                !check_x(expr_new + i - 1) && expr_new[i - 1] != 'x')) {
      res = 0;
    }
    i++;
  }
  return res;
}

int after_sign(char *expr) {
  int res = 0;
  char expr_new[1000] = {0};
  strcpy(expr_new, expr);
  if (is_sign(expr_new) && expr_new[0] == 'm' &&
      (expr_new[3] == '(' || is_digit(expr_new + 3) || if_func(expr_new + 3) ||
       expr_new[3] == 'x'))  // то что знак не унарный и всё ок с иксом
  {
    res = 1;
  } else if (is_sign(expr_new) && expr_new[0] != 'm' &&
             (expr_new[1] == '(' || is_digit(expr_new + 1) ||
              if_func(expr_new + 1) || expr_new[1] == 'x')) {
    res = 1;
  }
  return res;
}

int check_logs(char *expr)  // проверка логарифмов
{
  int res = 1;
  char *expr_new = expr;
  while (*expr_new && res == 1) {
    if ((*expr_new == 'l' && *(expr_new + 1) == 'o' &&
         strncmp(expr_new + 1, "og(", 3) != 0) ||  // проверка
        (*expr_new == 'l' && *(expr_new + 1) == 'n' &&
         strncmp(expr_new + 1, "n(", 2) != 0)) {
      res = 0;
    } else if (*expr_new == 'l' && strncmp(expr_new + 1, "og(", 3) == 0) {
      expr_new = expr_new + 4;
    }
    // проверка
    else if (*expr_new == 'l' && strncmp(expr_new + 1, "n(", 2) != 0) {
      expr_new = expr_new + 3;
    } else {
      expr_new++;
    }
  }
  return res;
}

int check_len(char *expr) {
  int res = 1;
  if ((int)strlen(expr) > 255) {
    res = 0;
  }
  return res;
}

int before_func(char *expr) {
  int res = 1;
  char expr_new[1000] = "";
  strcpy(expr_new, expr);
  for (int i = 0; i < (int)strlen(expr_new) && res == 1; i++) {
    if (i == 0 && if_func(expr_new + i)) {
      if (expr_new[i] == 'a') {
        i = i + 2;
      }
      res = 1;
    } else if (i != 0 && if_func(expr_new + i)) {
      if (expr_new[i] == 'a') {
        if (!is_sign(expr_new + i - 1) &&
            !((expr_new[i - 1]) == 'd' && (expr_new[i - 2]) == 'o' &&
              (expr_new[i - 3]) == 'm') &&
            !((expr_new[i - 1]) == '(' && (expr_new[i - 2]) == 'd' &&
              (expr_new[i - 3]) == 'o' && (expr_new[i - 4]) == 'm') &&
            expr_new[i - 1] != '^' && expr_new[i - 1] != '(') {
          res = 0;
        } else {
          i = i + 2;
        }
      } else if (!is_sign(expr_new + i - 1) &&
                 !((expr_new[i - 1]) == 'd' && (expr_new[i - 2]) == 'o' &&
                   (expr_new[i - 3]) == 'm') &&
                 !((expr_new[i - 1]) == '(' && (expr_new[i - 2]) == 'd' &&
                   (expr_new[i - 3]) == 'o' && (expr_new[i - 4]) == 'm') &&
                 expr_new[i - 1] != '^' && expr_new[i - 1] != '(') {
        res = 0;
      }
    }
  }
  return res;
}

int if_func(char *expr) {
  int res = 0;
  char *expr_new = malloc(strlen(expr) + 1);
  strcpy(expr_new, expr);
  if (strncmp(expr_new, "acos(", 5) == 0 ||
      strncmp(expr_new, "asin(", 5) == 0 ||
      strncmp(expr_new, "atan(", 5) == 0 || strncmp(expr_new, "cos(", 4) == 0 ||
      strncmp(expr_new, "sin(", 4) == 0 || strncmp(expr_new, "tan(", 4) == 0 ||
      strncmp(expr_new, "log(", 4) == 0 || strncmp(expr_new, "ln(", 3) == 0 ||
      strncmp(expr_new, "sqrt(", 4) == 0) {
    res = 1;
  }
  free(expr_new);
  return res;
}

int check_point(char *expr)  // что до запятой и после
{
  int res = 1;
  char expr_new[1000] = "";
  strcpy(expr_new, expr);
  for (int i = 0; i < (int)strlen(expr_new) && res == 1;) {
    if ((expr_new[i] == '.') &&
        ((!is_digit(expr_new + i - 1)) || (!is_digit(expr_new + i + 1)))) {
      res = 0;
    } else {
      i++;
    }
  }
  return res;
}

int after_digit(char *expr) {
  int res = 1;
  char expr_new[1000] = "";
  strcpy(expr_new, expr);
  if (!is_digit(expr_new) && expr_new[0] != ')' && !is_sign(expr_new) &&
      expr_new[0] != '^' && expr_new[0] != '.' && expr_new[0] != '\0') {
    res = 0;
  }
  return res;
}

int check_x(char *expr) {  // чекаю, что вокруг не числа и точки
  int res = 1;
  char expr_new[1000] = "";
  strcpy(expr_new, expr);
  for (int i = 0; i < (int)strlen(expr_new) && res == 1;) {
    if (expr_new[i] == 'x') {
      if (i == 0) {
        res = after_x(expr + 1);  // чекаю, что после x
      } else if ((is_digit(expr_new + i - 1)) || expr_new[i - 1] == ')' ||
                 expr_new[i - 1] == '.') {  // на то что перед иксом
        res = 0;
      } else {
        res = after_x(expr_new + i + 1);  // чекаю, что после xc
      }
    }
    i++;
  }
  return res;
}

int check_digit(char *expr) {
  int res = 1;
  // char *expr_new = expr;
  char expr_new[1000] = "";
  strcpy(expr_new, expr);
  for (int i = 0; i < (int)strlen(expr_new) && res == 1;) {
    if (i == 0 && is_digit(expr_new))  // проверка что в начале строки стоит
    {
      res = after_digit(expr_new + i + 1);
    } else {
      if (is_digit(expr_new + i)) {
        if (is_digit(expr_new + i) &&
            (expr[i - 1] == '(' || expr[i - 1] == '^' ||
             is_digit(expr_new + i - 1) || expr[i - 1] == '.' ||
             (is_sign(expr_new + i - 1) ||
              ((expr_new[i - 1]) == 'd' && (expr_new[i - 2]) == 'o' &&
               (expr_new[i - 3]) == 'm') ||
              ((expr_new[i - 1]) == '(' && (expr_new[i - 2]) == 'd' &&
               (expr_new[i - 3]) == 'o' && (expr_new[i - 4]) == 'm')))) {
          res = after_digit(expr_new + i + 1);
        } else {
          res = 0;
        }
      }
    }

    i++;
  }
  return res;
}

int is_digit(char *numb) {
  int res = 0;
  if (*numb >= 48 && *numb <= 57) {
    res = 1;
  }
  return res;
}

int is_sign(char *expr_sign) {  // проверка на то, что знак
  int res = 0;
  if (*expr_sign == '+' || *expr_sign == '-' || *expr_sign == '*' ||
      *expr_sign == '/' ||
      (*expr_sign == 'm' && (strncmp(expr_sign + 1, "od", 2) == 0))) {
    res = 1;
  }
  return res;
}

int check_trigonometry(char *expr) {
  int res = 1;
  char expr_new[1000] = "";
  strcpy(expr_new, expr);
  for (int i = 0; i < (int)strlen(expr_new) && res == 1; i++) {
    if (expr_new[i] == 's' && strncmp(expr_new + i + 1, "qrt(", 4) != 0 &&
        expr_new[i - 1] == 'o') {
      if (expr_new[i + 1] != 'i' || expr_new[i + 2] != 'n' ||
          expr_new[i + 3] != '(') {
        res = 0;
      } else {
        i = i + 2;
      }
    } else if (expr_new[i] == 'c') {
      if (expr_new[i + 1] != 'o' || expr_new[i + 2] != 's' ||
          expr_new[i + 3] != '(') {
        res = 0;
      } else {
        i = i + 2;
      }
    } else if (expr_new[i] == 't' && expr_new[i - 1] != 'r') {
      if (expr_new[i + 1] != 'a' || expr_new[i + 2] != 'n' ||
          expr_new[i + 3] != '(') {
        res = 0;
      } else {
        res = 1;
      }
    }
  }
  return res;
}

char *remove_sp(char *old) {
  char *new_str = (char *)calloc(strlen(old) + 1, sizeof(char));
  if (new_str != NULL) {
    int end = 0;
    for (int i = 0, j = 0; i < (int)strlen(old); i++) {
      if (old[i] != ' ') {
        new_str[j] = old[i];
        j++;
        end = j;
      }
    }
    new_str[end] = '\0';
  }
  return new_str;
}

int give_priority_and_value(char *expr,
                            lexeme **znak) {  // переделываю знак в лексему
  int res = 1;
  *znak = calloc(1, sizeof(lexeme));
  if (znak != NULL) {
    if (expr[0] == '+') {
      (*znak)->priority = 1;
      (*znak)->type = 4;
      (*znak)->value = 0;
    } else if (expr[0] == '-') {
      (*znak)->priority = 1;
      (*znak)->type = 5;
      (*znak)->value = 0;
    } else if (expr[0] == '*') {
      (*znak)->priority = 2;
      (*znak)->type = 6;
      (*znak)->value = 0;
    } else if (expr[0] == '/') {
      (*znak)->priority = 2;
      (*znak)->type = 7;
      (*znak)->value = 0;
    } else if (expr[0] == 'm') {
      (*znak)->priority = 2;
      (*znak)->type = 8;
      (*znak)->value = 0;
    } else if (expr[0] == '^') {
      (*znak)->priority = 3;
      (*znak)->type = 9;
      (*znak)->value = 0;
    }
  } else {
    res = 0;
  }
  return res;
}

int give_lexeme_to_trig(char *expr, lexeme **trig) {
  int res = 1;
  *trig = calloc(1, sizeof(lexeme));
  if (trig != NULL) {
    if (expr[0] == 's' && expr[1] == 'i') {
      (*trig)->priority = 4;
      (*trig)->type = 12;
      (*trig)->value = 0;
    } else if (expr[0] == 'c') {
      (*trig)->priority = 4;
      (*trig)->type = 14;
      (*trig)->value = 0;
    } else if (expr[0] == 't') {
      (*trig)->priority = 4;
      (*trig)->type = 16;
      (*trig)->value = 0;
    } else if (expr[0] == 'a' && expr[1] == 's') {
      (*trig)->priority = 4;
      (*trig)->type = 13;
      (*trig)->value = 0;
    } else if (expr[0] == 'a' && expr[1] == 'c') {
      (*trig)->priority = 4;
      (*trig)->type = 15;
      (*trig)->value = 0;
    } else if (expr[0] == 'a' && expr[1] == 't') {
      (*trig)->priority = 4;
      (*trig)->type = 17;
      (*trig)->value = 0;
    } else if (expr[0] == 'l') {
      res = give_to_lg(expr, trig);
    } else if (expr[0] == 's' && expr[1] == 'q') {
      (*trig)->priority = 4;
      (*trig)->type = 18;
      (*trig)->value = 0;
    }
  } else {
    res = 0;
  }

  return res;
}

int give_to_lg(char *expr, lexeme **log) {
  int res = 1;
  //*log = calloc(1, sizeof(lexeme));
  if (*expr == 'l' && *(expr + 1) == 'n') {
    (*log)->priority = 4;
    (*log)->type = 11;
    (*log)->value = 0;
  }
  if (*expr == 'l' && *(expr + 1) == 'o') {
    (*log)->priority = 4;
    (*log)->type = 10;
    (*log)->value = 0;
  }
  return res;
}

int is_empty(lexeme *head) {
  int res = 0;
  if (head == NULL) {
    res = 1;  // если пустой список -> 1
  }
  return res;
}

void pusher(
    lexeme **digits, lexeme **signs,
    lexeme znak)  // пушит и убирает, если приоритетность вставляемого больше,
                  // передаем два стека чтоб менять и то что вставляем
{
  if (is_empty(*signs)) {
    s21_push(znak.value, znak.priority, znak.type, signs);
  } else {
    lexeme *old_head = *signs;
    if ((old_head->priority > znak.priority) ||
        (old_head->priority == znak.priority && old_head->type != 9 &&
         znak.type != 9)) {
      s21_push(old_head->value, old_head->priority, old_head->type,
               digits);  //  запушала это начало в другой стек
      s21_pop(signs);  // удалила это начало
      pusher(digits, signs, znak);
    } else {
      s21_push(znak.value, znak.priority, znak.type, signs);
    }
  }
}

//

int unary(char *expr, int ind) {  // проверка на то что знак унарный
  int res = 0;
  if ((*expr == '-' || *expr == '+') &&
      *(expr - 1) == '(')  //  не в начале, после скобки
  {
    res = 1;
  }
  if (ind == 0 && (*expr == '-' || *expr == '+'))  // типо в начаде строки
  {
    res = 1;
  }
  return res;
}

int validator(char *expr_old)  // проверить на число в строке
{
  int res = 1;
  if (check_len(expr_old)) {
    // проверить на нулл, для того чтоб пробельчики поставить
    char *expr = remove_sp(expr_old);
    if (expr != NULL) {
      if (!check_brackets(expr) || !before_func(expr) || !check_point(expr) ||
          !check_trigonometry(expr) || !check_sign(expr) || !check_pow(expr) ||
          !check_logs(expr) ||
          // !check_sqrt(expr) ||
          !check_x(expr) || !check_digit(expr))  //
      {
        res = 0;
      }
      free(expr);
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
  return res;
}

void free_stack(lexeme **head) {
  while (*head != NULL) {
    s21_pop(head);
  }
}

int return_ind(char *expr, double *digit) {
  char number[256];
  // number[0] = '\0';
  int count_in_number = 0;
  int for_point = 0;
  // double num = 0;
  for (int i = 0; i < (int)strlen(expr);) {
    while ((is_digit(expr + i) || expr[i] == '.') && for_point <= 1) {
      if (expr[i] == '.') {
        for_point += 1;
      }
      number[count_in_number] = expr[i];
      count_in_number++;
      i++;  // чтоб полностью по цифре пройтись в цикле
    }
    i = (int)strlen(expr);
  }
  if (for_point > 1) {
    count_in_number = 0;
  } else {
    number[count_in_number] = '\0';
    *digit = atof(number);
  }
  return count_in_number;
}

int parser(char *expr_old, double x,
           lexeme **digits)  // lexeme digits занести в скобки
{
  int res = validator(expr_old);
  if (res) {
    char *expr = remove_sp(expr_old);
    // проверить на нулл, для того чтоб пробельчики поставить
    if (expr != NULL) {
      int length = (int)strlen(expr);

      lexeme *signs = NULL;
      for (int i = 0; i < length;) {
        if (is_digit(expr + i) || expr[i] == 'x') {
          double num = 0;
          if (expr[i] == 'x') {
            num = x;  // вносим число из скобочек икс
            i++;
          } else {
            int sdvig = return_ind(expr + i, &num);
            if (sdvig == 0) {
              res = 0;
            } else {
              i = i + sdvig;
            }
          }
          s21_push(num, -1, 0, digits);  // в стэк чисел
        } else if ((is_sign(expr + i) && !unary(expr + i, i)) ||
                   expr[i] == '^') {
          lexeme *znak = NULL;
          res = give_priority_and_value(expr + i, &znak);
          if (res) {
            pusher(digits, &signs, *znak);
          }
          if (znak != NULL) {
            free_stack(&znak);
          }
          i++;
        } else if (if_func(expr + i)) {
          lexeme *znak = NULL;
          res = give_lexeme_to_trig(expr + i, &znak);
          if (res) {
            pusher(digits, &signs, *znak);
            if (expr[i] == 'a') {
              i = i + 3;  // до скобки
            } else {
              i++;
            }
          }
          if (znak != NULL) {
            free_stack(&znak);
          }
        } else if (expr[i] == '(') {
          s21_push(0, -1, 2, &signs);
          i++;
        } else if (expr[i] == ')') {
          //  z++;
          lexeme *old_head = NULL;
          old_head = start(&signs);
          if (old_head != NULL) {
            while (old_head->type != 2) {
              s21_push(old_head->value, old_head->priority, old_head->type,
                       digits);
              s21_pop(&signs);
              old_head = start(&signs);
            }
            s21_pop(&signs);
            i++;
          } else {
            res = 0;
          }
        } else if (unary(expr + i, i)) {
          if (expr[i] == '-') {
            s21_push(0, 1, 5, &signs);
            s21_push(0, -1, 0, digits);
            i++;
          } else {
            s21_push(0, 1, 4, &signs);
            s21_push(0, -1, 0, digits);
            i++;
          }
        } else {
          i++;
        }
      }
      merge(digits, &signs);  // тут всё обнуляется в signs
      free(expr);
    } else {
      res = 0;
    }
  } else {
    res = 0;
  }
  return res;
}

void merge(lexeme **digits, lexeme **signs) {
  while (*signs != NULL) {
    lexeme *head = NULL;
    head = start(signs);
    s21_push(head->value, head->priority, head->type, digits);
    s21_pop(signs);
  }
}

double math(int type, double a)  // перезагрузка чтоб с одним числом
{
  double res = NAN;
  switch (type) {
    case 10:
      res = log10(a);
      break;
    case 11:
      res = log(a);
      break;
    case 12:
      res = sin(a);
      break;
    case 13:
      res = asin(a);
      break;
    case 14:
      res = cos(a);
      break;
    case 15:
      res = acos(a);
      break;
    case 16:
      res = tan(a);
      break;
    case 17:
      res = atan(a);
      break;
    case 18:
      res = sqrt(a);  // здесь проблемка и в тригонометрии, потому что одну
                      // цифру передаем
      break;
  }
  return res;
}

double math_check(int type, double a,
                  double b)  // даублы не передавать, тк они в значение
{
  double res = NAN;
  switch (type) {
    case 4:
      res = a + b;
      break;
    case 5:
      res = a - b;
      break;
    case 6:
      res = a * b;
      break;
    case 7:
      res = a / b;
      break;
    case 8:
      res = fmod(a, b);  // нормальный мод написать
      break;
    case 9:
      res = pow(a, b);
      break;
  }

  return res;
}

double logic(const char *expr_old, double x) {
  int len = (int)strlen(expr_old);
  char expr[len + 1];
  strcpy(expr, expr_old);
  double result = NAN;
  lexeme *pars = NULL;
  int res = 1;
  res = parser(expr, x, &pars);  // получили начальный стек
  if (res) {
    lexeme *new = NULL;
    reverse_stack(&new, &pars);  // получили нормальный стек
    // НЕ НАДО ФРИШИТЬ ПАРС ОН И ТАК УДАЛЯЕТСЯ В РЕВЕРСЕ
    lexeme *stack_results = NULL;
    while (new != NULL) {
      if (new->type == 0) {
        s21_push(new->value, new->priority, new->type,
                 &stack_results);  // пушим в конечный стек
        s21_pop(&new);
      } else if (new->type >= 4 && new->type <= 9) {
        double b = stack_results->value;
        s21_pop(&stack_results);
        double a = stack_results->value;
        s21_pop(&stack_results);
        result = math_check(new->type, a, b);
        s21_pop(&new);
        s21_push(result, -1, 0, &stack_results);
      } else {
        double c = stack_results->value;
        result = math(new->type, c);
        s21_pop(&stack_results);
        s21_pop(&new);
        s21_push(result, -1, 0, &stack_results);
      }
      if (start(&new) == NULL) break;
    }
    if (stack_results != NULL) {
      free_stack(&stack_results);
    }
  }
  return result;
}

void s21_push(double value, int priority, int type,
              lexeme **stack) {  // пушу в начало
  lexeme *new_lex = calloc(1, sizeof(lexeme));
  if (new_lex == NULL) {
    // Обработка ошибки
    return;
  }
  new_lex->value = value;
  new_lex->priority = priority;
  new_lex->type = type;
  new_lex->next = *stack;
  *stack = new_lex;
}

lexeme *start(lexeme **head) {  // чтоб  узнать что в конце зашло
  return *head;
}

void s21_pop(lexeme **head) {  // удаляем первого
  if (*head != NULL) {
    lexeme *tmp = NULL;
    tmp = (*head)->next;
    free(*head);
    *head = tmp;
  }
}

void reverse_stack(lexeme **new_stack, lexeme **old_stack) {
  while (*old_stack != NULL) {
    s21_push((*old_stack)->value, (*old_stack)->priority, (*old_stack)->type,
             new_stack);
    s21_pop(old_stack);
  }
}
