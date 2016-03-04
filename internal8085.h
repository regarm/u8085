#ifndef INTERNAL8085_H
#define INTERNAL8085_H

#include <QObject>
#include <QMap>
#include <QBitArray>
#include "register.h"
class Internal8085 : public QObject
{
    Q_OBJECT
public:
    explicit Internal8085(QObject *parent = 0);
    QMap<QString, int> byteCnt;
    QMap<QString, int> instructionType;

    void instructionTypeMapping();
    void byteCntMapping();

    Register cells[4096];
    QMap<QString, int8_t> rIndexMap;
    QMap<QString, int8_t> rpIndexMap;
    QMap<QString, int8_t> rpsIndexMap;
    QMap<QString, int8_t> rpwIndexMap;
    QMap<int8_t, QString> revrIndexMap;
    Register A, B, C, D, E, F, H, L, PC, SP;
    Register temp;
    Register *regs[9];

    bool setValueAtCell(int, QString);
    bool setValueAtCell(int, int);
    QString getValueOfM(bool &);


    bool getFlagC();
    bool getFlagAC();
    bool getFlagZ();
    bool getFlagP();
    bool getFlagS();

    QString getValueAtCell(int, bool &);


    //Instructions
    bool ACI(QString);
    bool ADC(int);
    bool ADD(int, int carry = 0);
    bool ADI(QString, int carry = 0);
    bool ANA(int);
    bool ANI(QString);
    bool PUSH(int);
    bool POP(int);
    bool CALL(int);
    bool CC(int);
    bool CNC(int);
    bool CP(int);
    bool CM(int);
    bool CPE(int);
    bool CPO(int);
    bool CZ(int);
    bool CNZ(int);
    bool CMA();
    bool CMC();
    bool CMP(int);
    bool CPI(QString);
    bool DAA();
    bool DAD(int);
    bool DCR(int);
    bool DCX(int);
    bool NOP();
    bool SUB(int);
    bool SBI(QString);
    bool SBB(int);
    bool INR(int);
    bool INX(int);
    bool JMP(int);
    bool JC(int);
    bool JNC(int);
    bool JP(int);
    bool JM(int);
    bool JPE(int);
    bool JPO(int);
    bool JZ(int);
    bool JNZ(int);
    bool LDA(int);
    bool LDAX(int);
    bool STA(int);
    bool STAX(int);
    bool LHLD(int);
    bool SHLD(int);
    bool LXI(int, QString, QString);
    bool MOV(int, int);
    bool MVI(int, QString);
    bool ORA(int);
    bool ORI(QString);
    bool PCHL();
    bool STC();
    bool RET();
    bool RC();
    bool RNC();
    bool RP();
    bool RM();
    bool RPE();
    bool RPO();
    bool RZ();
    bool RNZ();
    bool RAR();
    bool RAL();
    bool RLC();
    bool RRC();
    bool SPHL();
    bool XCHG();
    bool XRA(int);
    bool XRI(QString);
    bool XTHL();
    bool HLT();
    int upAddressLimit;
    int lowAddressLimit;
signals:
    void accumulatorChanged();
    void flagCChangedByProg(QString);
    void flagACChangedByProg(QString);
    void flagPChangedByProg(QString);
    void flagZChangedByProg(QString);
    void flagSChangedByProg(QString);
public slots:
    void updateFlags();
    void flagCChangedByUser(QString);
    void flagPChangedByUser(QString);
    void flagACChangedByUser(QString);
    void flagZChangedByUser(QString);
    void flagSChangedByUser(QString);
    bool setValueofM(QString);

    //Flag Manipulation
    void setFlagC(bool);
    void setFlagAC(bool);
    void setFlagZ(bool);
    void setFlagP(bool);
    void setFlagS(bool);

    void setFlagCFromOutside(QString);
    void setFlagACFromOutside(QString);
    void setFlagZFromOutside(QString);
    void setFlagPFromOutside(QString);
    void setFlagSFromOutside(QString);

    void MCellChanged(QString);
};

#endif // INTERNAL8085_H
