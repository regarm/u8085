#include "utils.h"
#include <QString>
#include <QObject>
int hexToNumber(QString s){
    bool ok;
    return s.toLongLong(&ok, 16);
}
QString numberToHex(int x){
    return QString::number(x, 16).toUpper();
}

QString nextAddress(QString Address){
    bool ok;
    qlonglong num = Address.toLongLong(&ok, 16);
    ++num;
    QString res;
    res.setNum(num, 16);
    return res;
}

//single register operand [A, B, C, D, E, H, L, M]
bool isRegister(QString& op){
    if(op == QObject::tr("A") || op == QObject::tr("B") || op == QObject::tr("C")){
        return true;
    }
    if(op == QObject::tr("D") || op == QObject::tr("E") || op == QObject::tr("H")){
        return true;
    }
    if(op == QObject::tr("L") || op == QObject::tr("M")){
        return true;
    }
    return false;
}
bool isData(QString& op){
    if(op.size() != 2){
        return false;
    } else {
        if(!((op[0] >= QLatin1Char('0') && op[0] <=QLatin1Char('9'))||(op[0] >= QLatin1Char('A') && op[0] <=QLatin1Char('F')))){
            return false;
        }
        if(!((op[1] >= QLatin1Char('0') && op[1] <=QLatin1Char('9'))||(op[1] >= QLatin1Char('A') && op[1] <=QLatin1Char('F')))){
            return false;
        }
    }
    return true;
}
bool isValidAddress(QString& op){
    if(op.size() != 4){
        return false;
    } else {
        if(!((op[0] >= QLatin1Char('0') && op[0] <= QLatin1Char('9'))||(op[0] >= QLatin1Char('A') && op[0] <= QLatin1Char('F')))){
            return false;
        }
        if(!((op[1] >= QLatin1Char('0') && op[1] <= QLatin1Char('9'))||(op[1] >= QLatin1Char('A') && op[1] <=QLatin1Char('F')))){
            return false;
        }
        if(!((op[2] >= QLatin1Char('0') && op[2] <= QLatin1Char('9'))||(op[2] >= QLatin1Char('A') && op[2] <= QLatin1Char('F')))){
            return false;
        }
        if(!((op[3] >= QLatin1Char('0') && op[3] <= QLatin1Char('9'))||(op[3] >= QLatin1Char('A') && op[3] <=QLatin1Char('F')))){
            return false;
        }
    }
    return true;
}

bool isRpair4(QString& op){
    if(op == QObject::tr("B") || op == QObject::tr("D")){
        return true;
    }
    if(op == QObject::tr("H") || op == QObject::tr("SP")){
        return true;
    }
    return false;
}

bool isRpw4(QString& op){
    if(op == QObject::tr("B") || op == QObject::tr("D")){
        return true;
    }
    if(op == QObject::tr("H") || op == QObject::tr("PSW")){
        return true;
    }
    return false;
}

bool isRp2(QString& op){
    if(op == QObject::tr("B") || op == QObject::tr("D")){
        return true;
    }
    return false;
}
bool isValidLabel(QString& op){
    QChar ch;
    foreach(ch, op){
        if(!ch.isLetterOrNumber()){
            return false;
        }
    }
    return true;
}
