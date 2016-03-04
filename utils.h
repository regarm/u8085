#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDebug>

int hexToNumber(QString);
QString numberToHex(int);

bool isRegister(QString&);
bool isData(QString&);
bool isValidAddress(QString&);
bool isRpair4(QString&);
bool isRpw4(QString&);
bool isRp2(QString&);
bool isValidLabel(QString&);
QString nextAddress(QString);
#endif // UTILS_H
