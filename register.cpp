#include "register.h"

Register::Register():
    QObject(),
    QBitArray(8, false)
{

}
Register::Register(const QString &str):
    QObject(),
    QBitArray(8, false)
{
    bool ok;
    uint8_t val = str.toLongLong(&ok, 16);
    for(int i = 0;i < 8;++i){
        setBit(i,(val&(1<<(7 - i))));
    }
}
Register::Register(uint8_t val):
    QObject(),
    QBitArray(8, false)
{
    for(int i = 0;i < 8;++i){
        setBit(i,(val&(1<<(7 - i))));
    }

}

void Register::setValue(const QString& str){
    bool ok;
    uint64_t val = str.toLongLong(&ok, 16);
    for(int i = 0;i < this->size();++i){
        setBit(i,(val&(1LL<<(this->size() - i - 1))));
    }
    emit regEditedInternally_SIG(str);
    emit cellChangedInternally(str);
}
void Register::setValue(int val){
    for(int i = 0;i < this->size();++i){
        setBit(i,(val&(1LL<<(this->size() - i - 1))));
    }
    emit regEditedInternally_SIG(this->toString());
    emit cellChangedInternally(this->toString());
}
QString Register::toString(){
    QString sval;
    sval.setNum(this->toInt(), 16);
    return sval.toUpper().rightJustified(2,QLatin1Char('0'));
}
uint64_t Register::toInt(){
    uint64_t val = 0;
    for(int i = 0;i < this->size();++i){
        val |= testBit(i)<<(this->size() - i - 1);
    }
    return val;
}
void Register::regFEditedFromRegDockFreg_SLOT(QString str){
    bool ok;
    uint64_t val = str.toLongLong(&ok, 16);
    for(int i = 0;i < this->size();++i){
        setBit(i,(val&(1LL<<(this->size() - i - 1))));
    }
    emit regFEditedFromRegDockFreg_SIG(this->toString());
    emit regEditedFromRegDock_SIG(this->toString());
}
void Register::regEditedFromRegDock_SLOT(QString str){
    bool ok;
    uint64_t val = str.toLongLong(&ok, 16);
    for(int i = 0;i < this->size();++i){
        setBit(i,(val&(1LL<<(this->size() - i - 1))));
    }
    emit regEditedFromRegDock_SIG(this->toString());
}
void Register::cellChangedFromMemDock(QString str){
    bool ok;
    uint64_t val = str.toLongLong(&ok, 16);
    for(int i = 0;i < this->size();++i){
        setBit(i,(val&(1LL<<(this->size() - i - 1))));
    }
}
