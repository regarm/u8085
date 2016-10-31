#include "internal8085.h"

void Internal8085::setFlagC(bool val){
    F.setBit(7, val);
    emit F.regEditedInternally_SIG(F.toString());
}
void Internal8085::setFlagP(bool val){
    F.setBit(5, val);
    emit F.regEditedInternally_SIG(F.toString());
}
void Internal8085::setFlagAC(bool val){
    F.setBit(3, val);
    emit F.regEditedInternally_SIG(F.toString());
}
void Internal8085::setFlagZ(bool val){
    F.setBit(1, val);
    emit F.regEditedInternally_SIG(F.toString());
}
void Internal8085::setFlagS(bool val){
    F.setBit(0, val);
    emit F.regEditedInternally_SIG(F.toString());
}

void Internal8085::setFlagCFromOutside(QString val){
    bool bitVal = (((val == tr(""))|(val == tr("0")))?0:1);
    F.setBit(7, bitVal);
    emit F.regFEditedFromRegDockFlags_SIG(F.toString());
}
void Internal8085::setFlagPFromOutside(QString val){
    bool bitVal = (((val == tr(""))|(val == tr("0")))?0:1);
    F.setBit(5, bitVal);
    emit F.regFEditedFromRegDockFlags_SIG(F.toString());

}
void Internal8085::setFlagACFromOutside(QString val){
    bool bitVal = (((val == tr(""))|(val == tr("0")))?0:1);
    F.setBit(3, bitVal);
    emit F.regFEditedFromRegDockFlags_SIG(F.toString());
}
void Internal8085::setFlagZFromOutside(QString val){
    bool bitVal = (((val == tr(""))|(val == tr("0")))?0:1);
    F.setBit(1, bitVal);
    emit F.regFEditedFromRegDockFlags_SIG(F.toString());
}
void Internal8085::setFlagSFromOutside(QString val){
    bool bitVal = (((val == tr(""))|(val == tr("0")))?0:1);
    F.setBit(0, bitVal);
    emit F.regFEditedFromRegDockFlags_SIG(F.toString());
}

bool Internal8085::getFlagC(){
   return F.testBit(7);
}
bool Internal8085::getFlagP(){
    return F.testBit(5);
}
bool Internal8085::getFlagAC(){
    return F.testBit(3);
}
bool Internal8085::getFlagZ(){
    return F.testBit(1);
}
bool Internal8085::getFlagS(){
    return F.testBit(0);
}

void Internal8085::updateFlags(){
    bool isZero = true;
    bool xr = false;
    for(int i = 0;i < 8;++i){
        isZero &= (!A.testBit(i));
        xr ^= A.testBit(i);
    }
    setFlagS(A.testBit(0));
    setFlagP(!xr);
    setFlagZ(isZero);
    // cout<< isZero <<endl;
}
