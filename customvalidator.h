/* Создаем свой валидатор для проверки вещественных чисел на основе QDoubleValidator
 * т.к. у QDoubleValidator изначально допучкается только ввод ",", а формат double
 * поддерживает только точки. Поддержим ввод и того и другого, но
 * воспринисать все это будем как точки
 * */
#ifndef CUSTOMVALIDATOR_H
#define CUSTOMVALIDATOR_H

#include <QDoubleValidator>
#include <QStringList>
#include <QString>
#include "ostream"

class CustomValidator : public QDoubleValidator{
    QStringList _decimalPoints;
public:
    CustomValidator(){
        _decimalPoints.append(".");
        _decimalPoints.append(",");   //почему-то не вышло, поддерживается ввод только точки
    }
    State validate(QString &str, int &pos) const{
        str.replace(",",".");       //т.к. запятая тоже допустимый символ, сразу меняем его на точку
        QString s(str);

        for(QStringList::ConstIterator point = _decimalPoints.begin(); point != _decimalPoints.end(); point++){
            s.replace(*point, locale().decimalPoint());     // заменяем на допустимые символы
        }
        return QDoubleValidator::validate(s, pos);
    }
};

#endif // CUSTOMVALIDATOR_H
