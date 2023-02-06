#include "back_calc.h"

using namespace s21;

Back::Back() : backCharLabel('\0'), temp("") {
  status = 0;
  countLeftBranch = 0;
  x = 0;
  countSymb = 0;
  result = 0;
}

Back::Back(QString Data) : backCharLabel('\0'), temp(""), input(Data) {
  status = 0;
  countLeftBranch = 0;
  x = 0;
  countSymb = 0;
  result = 0;
  polishConvert();
}

Back::~Back() {
  input.clear();
  polishStack.clear();
  mathStack.clear();
  input.clear();
  temp.clear();
}

Back::Back(const Back &other) {
  x = other.x;
  status = other.status;
  countSymb = other.countSymb;
  countLeftBranch = other.countLeftBranch;
  result = other.result;
}

Back::Back(Back &&other) {
  x = other.x;
  status = other.status;
  countSymb = other.countSymb;
  countLeftBranch = other.countLeftBranch;
  result = other.result;
}

double Back::getRes() { return result; }

void Back::setInput(QString data) { input = data; }

void Back::setX(double newX) { x = newX; }

void Back::polishConvert() {
  countSymb = 0;
  for (QChar *it = input.begin(); it != input.end(); ++it, ++countSymb) {
    if (*it == '(') {
      temp = "(";
      mathStack.push_back(temp);
    } else if (*it == ')')
      popLeftBracket();
    else if (*it == '-' &&
             (countSymb == 0 || (countSymb > 0 && mapOperation.contains(QString(
                                                      input[countSymb - 1])))))
      mathStack.push_back("~");
    else if (!(it->isDigit() || *it == '.' || *it == 'x')) {
      if (!(mapOperation.contains(*it))) {
        while (!(it->isDigit()) && (*it != '(')) {
          temp.append(*it);
          ++it;
          ++countSymb;
        }
        if (!mathStack.isEmpty())
          popMapFunction(temp);
        --it;
        --countSymb;
        mathStack.push_back(temp);
      } else {
        if (!mathStack.isEmpty())
          popMapOperation(it);
        mathStack.push_back(*it);
      }
    } else {
      if (*it == 'x') {
        ++countSymb;
        ++it;
        temp = QString::number(x);
      }

      while (it->isDigit() || *it == '.') {
        temp.append(*it);
        ++it;
        ++countSymb;
      }
      --it;
      --countSymb;
      polishStack.push_back(temp);
    }
    if (temp != nullptr)
      temp.clear();
  }
  if (!mathStack.isEmpty())
    popEnd();
}

void Back::popMapOperation(QChar *operation) {
  while (!mathStack.isEmpty()) {
    if (mapOperation.contains(mathStack.top())) {
      if (mapOperation[*operation] <= mapOperation[mathStack.top()])
        polishStack.push_back(mathStack.pop());
      else
        break;
    } else {
      if (mapOperation[*operation] <= mapFunction[mathStack.top()])
        polishStack.push_back(mathStack.pop());
      else
        break;
    }
  }
}

void Back::popMapFunction(QString function) {
  while (!mathStack.isEmpty()) {
    if (mapOperation.contains(mathStack.top())) {
      if (mapFunction[function] < mapOperation[mathStack.top()])
        polishStack.push_back(mathStack.pop());
      else
        break;
    } else {
      if (mapFunction[function] <= mapFunction[mathStack.top()])
        polishStack.push_back(mathStack.pop());
      else
        break;
    }
  }
}

void Back::popEnd() {
  while (!mathStack.isEmpty()) {
    polishStack.push_back(mathStack.pop());
  }
}

void Back::popLeftBracket() {
  while ((!mathStack.isEmpty()) && (mathStack.top() != '('))
    polishStack.push_back(mathStack.pop());
  mathStack.pop();
  while ((!mathStack.isEmpty()) && (mapFunction.contains(mathStack.top())))
    polishStack.push_back(mathStack.pop());
}

double Back::calculate() {
  double num1;
  double num2;
  result = 0;
  int i = 0;
  while (polishStack.size() != 1) {
    if (mapOperation.contains(polishStack[i]) ||
        mapFunction.contains(polishStack[i])) {
      if (polishStack[i] == "+" ||

          polishStack[i] == "-" ||

          polishStack[i] == "*" ||

          polishStack[i] == "/" ||

          polishStack[i] == "^" ||

          polishStack[i] == "e" ||

          polishStack[i] == "mod") {
        num1 = polishStack[i - 1].toDouble();
        if (polishStack.size() == 2) {
          result = num1;
          break;
        }
        num2 = polishStack[i - 2].toDouble();
        result = Execute(polishStack[i], num1, num2);
        polishStack.takeAt(i);
        polishStack.takeAt(i - 1);
        polishStack[i - 2] = QString::number(result, 'g', 25);
        i = 0;
      } else {
        if (i > 0 &&
            (polishStack[i - 1][0].isDigit() || polishStack[i - 1][0] == '-')) {
          num1 = polishStack[i - 1].toDouble();
          result = Execute(polishStack[i], num1, 0);
          polishStack.takeAt(i);
          polishStack[i - 1] = QString::number(result, 'g', 25);
        } else {
          result = NAN;
          break;
        }
        i = 0;
      }
    } else
      ++i;
  }
  if (!polishStack.isEmpty())
    polishStack.clear();
  if (!mathStack.isEmpty())
    mathStack.clear();
  return result;
}

double Back::Execute(QString op, double first, double second) {
  double res = 0;
  if (op == "+")
    res = first + second;
  else if (op == "-")
    res = second - first;
  else if (op == "*")
    res = second * first;
  else if (op == "/")
    res = second / first;
  else if (op == "^")
    res = powf(second, first);
  else if (op == "~")
    res = first * (-1);
  else if (op == "e")
    res = second * powf(10, first);
  else if (op == "cos")
    res = cosf(first);
  else if (op == "sin")
    res = sinf(first);
  else if (op == "tan")
    res = tanf(first);
  else if (op == "acos")
    res = acosf(first);
  else if (op == "asin")
    res = asinf(first);
  else if (op == "atan")
    res = atanf(first);
  else if (op == "sqrt")
    res = sqrtf(first);
  else if (op == "ln")
    res = logf(first);
  else if (op == "log")
    res = log10f(first);
  else if (op == "mod")
    res = fmod(second, first);
  return res;
}

QString Back::on_pushButton_clicked(QString data) {
  if (data == ".") {
    on_pushButton_dot_clicked();
  } else if (data == "e") {
    on_pushButton_e_clicked();
  } else if (data == "+") {
    on_pushButton_sum_clicked();
  } else if (data == "-") {
    on_pushButton_sub_clicked();
  } else if (data == "*") {
    on_pushButton_mul_clicked();
  } else if (data == "/") {
    on_pushButton_div_clicked();
  } else if (data == "(") {
    on_pushButton_bl_clicked();
  } else if (data == ")") {
    on_pushButton_br_clicked();
  } else if (data == "^") {
    on_pushButton_deg_clicked();
  } else if (data == "sin") {
    on_pushButton_sin_clicked();
  } else if (data == "cos") {
    on_pushButton_cos_clicked();
  } else if (data == "tan") {
    on_pushButton_tan_clicked();
  } else if (data == "asin") {
    on_pushButton_asin_clicked();
  } else if (data == "sqrt") {
    on_pushButton_sqrt_clicked();
  } else if (data == "atan") {
    on_pushButton_atan_clicked();
  } else if (data == "acos") {
    on_pushButton_acos_clicked();
  } else if (data == "ln") {
    on_pushButton_ln_clicked();
  } else if (data == "log") {
    on_pushButton_log_clicked();
  } else if (data == "mod") {
    on_pushButton_mod_clicked();
  } else if (data == "1") {
    on_pushButton_1_clicked();
  } else if (data == "2") {
    on_pushButton_2_clicked();
  } else if (data == "3") {
    on_pushButton_3_clicked();
  } else if (data == "4") {
    on_pushButton_4_clicked();
  } else if (data == "5") {
    on_pushButton_5_clicked();
  } else if (data == "6") {
    on_pushButton_6_clicked();
  } else if (data == "7") {
    on_pushButton_7_clicked();
  } else if (data == "8") {
    on_pushButton_8_clicked();
  } else if (data == "9") {
    on_pushButton_9_clicked();
  } else if (data == "0") {
    on_pushButton_0_clicked();
  } else if (data == "x") {
    on_pushButton_un_clicked();
  }
  return input;
}

QString Back::on_pushButton_dot_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if (checkDot() == 0 || checkDot() == 1) {
      if ((backCharLabel >= '0' && backCharLabel <= '9') ||
          backCharLabel == 'x') {
        input.push_back(".");
      }
    }
  }
  return input;
}

QString Back::on_pushButton_clear_clicked() {
  if (!input.isEmpty())
    input.clear();
  status = 0;
  countLeftBranch = 0;
  backCharLabel = '\0';
  return input;
}

QString Back::on_pushButton_CE_clicked() {
  if (!input.isEmpty()) {
    if (input.back() == 'd')
      input.chop(3);
    else if (input.back() == '(') {
      input.chop(1);
      countLeftBranch--;
      while (!input.isEmpty() && input.back() != '(' &&
             (input.back() >= 'a' && input.back() <= 'z')) {
        input.chop(1);
      }
    } else {
      if (input.back() == ')')
        countLeftBranch++;
      input.chop(1);
    }
  }
  return input;
}

QString Back::on_pushButton_eq_clicked(QString x) {
  if (countLeftBranch) {
    while (countLeftBranch) {
      input.push_back(")");
      countLeftBranch--;
    }
  } else {
    for (QChar *it = input.begin(); it != input.end(); ++it) {
      if (*it == 'x') {
        for (QChar *newIt = x.begin(); newIt != x.end(); ++newIt)
          if (*newIt == ',')
            *newIt = '.';
        setX(x.toDouble());
        polishConvert();
        input = QString::number(calculate());
        status = 1;
        break;
      }
    }
    if (status != 1) {
      polishConvert();
      input = QString::number(calculate());
      status = 1;
    }
  }
  return input;
}

QString Back::on_pushButton_sum_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == ')' || backCharLabel == 'x') {
      input.push_back("+");
    }
  }
  return input;
}

QString Back::on_pushButton_sub_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if (backCharLabel == '-' || backCharLabel == '*' || backCharLabel == '/' ||
        backCharLabel == '^') {
      countLeftBranch++;
      input.push_back("(-");
    } else if (backCharLabel != '.' && backCharLabel != '+') {
      input.push_back("-");
    }
  } else
    input.push_back("-");
  return input;
}

QString Back::on_pushButton_mul_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == ')' || backCharLabel == 'x') {
      input.push_back("*");
    }
  }
  return input;
}

QString Back::on_pushButton_div_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == ')' || backCharLabel == 'x') {
      input.push_back("/");
    }
  }
  return input;
}

QString Back::on_pushButton_bl_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if (((backCharLabel >= '0' && backCharLabel <= '9') ||
         backCharLabel == ')' || backCharLabel == 'x') &&
        backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("*(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("(");
    }
  } else {
    countLeftBranch++;
    input.push_back("(");
  }
  return input;
}

QString Back::on_pushButton_br_clicked() {
  if (countLeftBranch) {
    clearLabel();
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      input.push_back(")");
      countLeftBranch--;
    }
  }
  return input;
}

QString Back::on_pushButton_deg_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == ')' || backCharLabel == 'x') {
      input.push_back("^");
    }
  }
  return input;
}

QString Back::on_pushButton_sin_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*sin(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("sin(");
    }
  } else {
    countLeftBranch++;
    input.push_back("sin(");
  }
  return input;
}

QString Back::on_pushButton_cos_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*cos(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("cos(");
    }
  } else {
    countLeftBranch++;
    input.push_back("cos(");
  }
  return input;
}

QString Back::on_pushButton_tan_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*tan(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("tan(");
    }
  } else {
    countLeftBranch++;
    input.push_back("tan(");
  }
  return input;
}

QString Back::on_pushButton_asin_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*asin(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("asin(");
    }
  } else {
    countLeftBranch++;
    input.push_back("asin(");
  }
  return input;
}

QString Back::on_pushButton_sqrt_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*sqrt(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("sqrt(");
    }
  } else {
    countLeftBranch++;
    input.push_back("sqrt(");
  }
  return input;
}

QString Back::on_pushButton_atan_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*atan(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("atan(");
    }
  } else {
    countLeftBranch++;
    input.push_back("atan(");
  }
  return input;
}

QString Back::on_pushButton_acos_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*acos(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("acos(");
    }
  } else {
    countLeftBranch++;
    input.push_back("acos(");
  }
  return input;
}

QString Back::on_pushButton_ln_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*ln(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("ln(");
    }
  } else {
    countLeftBranch++;
    input.push_back("ln(");
  }
  return input;
}

QString Back::on_pushButton_log_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      countLeftBranch++;
      input.push_back("*log(");
    } else if (backCharLabel != '.') {
      countLeftBranch++;
      input.push_back("log(");
    }
  } else {
    countLeftBranch++;
    input.push_back("log(");
  }
  return input;
}

QString Back::on_pushButton_mod_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      input.push_back("mod");
    }
  }
  return input;
}

QString Back::on_pushButton_0_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if (backCharLabel == '0' && (checkDot() == 0 || checkDot() == 1)) {
      input.push_back(".0");
    } else
      input.push_back("0");
  } else {
    if (checkBr())
      input.push_back("*");
    input.push_back("0");
  }
  return input;
}

QString Back::on_pushButton_1_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("1");
  return input;
}

QString Back::on_pushButton_2_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("2");
  return input;
}

QString Back::on_pushButton_3_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("3");
  return input;
}

QString Back::on_pushButton_4_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("4");
  return input;
}

QString Back::on_pushButton_5_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("5");
  return input;
}

QString Back::on_pushButton_6_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("6");
  return input;
}

QString Back::on_pushButton_7_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("7");
  return input;
}

QString Back::on_pushButton_8_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("8");
  return input;
}

QString Back::on_pushButton_9_clicked() {
  clearLabel();
  if (checkBr())
    input.push_back("*");
  input.push_back("9");
  return input;
}

QString Back::on_pushButton_un_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      input.push_back("*x");
    } else if (backCharLabel != '.') {
      input.push_back("x");
    }
  } else
    input.push_back("x");
  return input;
}

QString Back::on_pushButton_e_clicked() {
  clearLabel();
  if (!input.isEmpty()) {
    backCharLabel = input.back();
    if ((backCharLabel >= '0' && backCharLabel <= '9') ||
        backCharLabel == 'x' || backCharLabel == ')') {
      input.push_back("e");
    }
  }
  return input;
}

int Back::checkDot() {
  int check = 0;
  return check;
}

int Back::checkBr() {
  int check = 0;
  if (!input.isEmpty()) {
    if (input.back() == ')') {
      check = 1;
    }
  }
  return check;
}

void Back::clearLabel() {
  if (status) {
    on_pushButton_clear_clicked();
  }
}
