#ifndef EXCEPTIONARGUMENTINVALIDE_H
#define EXCEPTIONARGUMENTINVALIDE_H

#include <QException>
#include <QString>

class ExceptionArgumentInvalide : public QException {
public:
    ExceptionArgumentInvalide(const QString s) : s_(s) {}
    QString what(){return s_;}
private:
    QString s_;


};
#endif // EXCEPTIONARGUMENTINVALIDE_H
