#include "internal8085.h"

Internal8085::Internal8085(QObject *parent) :
    QObject(parent),
    upAddressLimit(0x3000),
    lowAddressLimit(0x2000)
{
    instructionTypeMapping();
    byteCntMapping();
    for(int address = lowAddressLimit;address < upAddressLimit;++address){
        //qDebug() << address << "\n";
        cells[address - lowAddressLimit].resize(8);
    }
    A.resize(8);
    B.resize(8);
    C.resize(8);
    D.resize(8);
    E.resize(8);
    F.resize(8);
    H.resize(8);
    L.resize(8);
    PC.resize(16);
    SP.resize(16);
    rIndexMap[tr("B")] = 0;
    rIndexMap[tr("C")] = 1;
    rIndexMap[tr("D")] = 2;
    rIndexMap[tr("E")] = 3;
    rIndexMap[tr("H")] = 4;
    rIndexMap[tr("L")] = 5;
    rIndexMap[tr("M")] = 6;
    rIndexMap[tr("A")] = 7;


    rpIndexMap[tr("B")] =0;
    rpIndexMap[tr("D")] =1;
    rpIndexMap[tr("H")] =2;
    rpIndexMap[tr("SP")] =3;

    rpsIndexMap[tr("B")] = 0;
    rpsIndexMap[tr("D")] = 1;

    rpwIndexMap[tr("B")] = 0;
    rpwIndexMap[tr("D")] = 1;
    rpwIndexMap[tr("H")] = 2;
    rpwIndexMap[tr("PSW")] = 3;

    regs[0] = &B;
    regs[1] = &C;
    regs[2] = &D;
    regs[3] = &E;
    regs[4] = &H;
    regs[5] = &L;
    regs[6] = NULL;
    regs[7] = &A;
    regs[8] = &temp;

    connect(this, SIGNAL(accumulatorChanged()), this, SLOT(updateFlags()));
}
QString Internal8085::getValueAtCell(int index, bool &ok){
    if(index < lowAddressLimit || index >= upAddressLimit){
        ok = false;
        return tr("");
    }
    ok = true;
    return cells[index - lowAddressLimit].toString();
}
bool Internal8085::setValueAtCell(int index, QString val){
    if(index < lowAddressLimit || index >= upAddressLimit){
        return false;
    }
    cells[index - lowAddressLimit].setValue(val);
    return true;
}
bool Internal8085::setValueAtCell(int index, int val){
    if(index < lowAddressLimit || index >= upAddressLimit){
        return false;
    }
    qDebug() << "in SetValueAtCell";
    cells[index - lowAddressLimit].setValue(val);
    return true;
}

void Internal8085::flagCChangedByUser(QString val){
    setFlagC(val == tr("1"));
}
void Internal8085::flagPChangedByUser(QString val){
    setFlagP(val == tr("1"));
}
void Internal8085::flagACChangedByUser(QString val){
    setFlagAC(val == tr("1"));
}
void Internal8085::flagZChangedByUser(QString val){
    setFlagZ(val == tr("1"));
}
void Internal8085::flagSChangedByUser(QString val){
    setFlagS(val == tr("1"));
}
QString Internal8085::getValueOfM(bool &ok){
    return getValueAtCell(((H.toInt()<<8) + L.toInt()), ok);
}
bool Internal8085::setValueofM(QString val){
    qDebug() << "in SetValueofM";
    val = val.toUpper().rightJustified(2, QLatin1Char('0'));
    return setValueAtCell(((H.toInt()<<8) + L.toInt()), val);
}
void Internal8085::MCellChanged(QString str){
    str = str.toUpper().rightJustified(2, QLatin1Char('0'));
    int address = (H.toInt() << 8) + L.toInt();
    if(address >= lowAddressLimit && address < upAddressLimit){
        Register *MCell = &cells[address - lowAddressLimit];
        bool ok;
        uint64_t val = str.toLongLong(&ok, 16);
        for(int i = 0;i < MCell->size();++i){
            MCell->setBit(i,(val&(1LL<<(MCell->size() - i - 1))));
        }
    }
}
