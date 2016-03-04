#include "internal8085.h"
#include <QtDebug>
#include <QMessageBox>
#include "utils.h"

bool Internal8085::ACI(QString operand){
    return ADI(operand, getFlagC());
}
bool Internal8085::ADC(int  regIndex){
    return ADD(regIndex, getFlagC());
}
bool Internal8085::ADD(int regIndex, int carry){
    for(int i = 7;i >= 4;--i){
        int8_t Abit = A.testBit(i);
        int8_t Bbit = regs[regIndex]->testBit(i);
        int8_t Cbit = carry&1;
        int8_t sum = Abit ^ Bbit ^ Cbit;
        carry = (Abit & Bbit) | (Abit & Cbit) | (Bbit & Cbit);
        A.setBit(i, sum);
    }
    setFlagAC(carry);
    for(int i = 3;i >= 0;--i){
        int8_t Abit = A.testBit(i);
        int8_t Bbit = regs[regIndex]->testBit(i);
        int8_t Cbit = carry&1;
        int8_t sum = Abit ^ Bbit ^ Cbit;
        carry = (Abit & Bbit) | (Abit & Cbit) | (Bbit & Cbit);
        A.setBit(i, sum);
    }
    A.setValue(A.toInt());
    setFlagC(carry);
    emit(accumulatorChanged());
    return true;
}
bool Internal8085::ADI(QString operand, int carry){
    temp.setValue(operand);
    return ADD(8, carry);
}
bool Internal8085::HLT(){
    return false;
}
bool Internal8085::ANA(int regIndex){
    for(int i = 7;i >= 0;--i){
        A.setBit(i, (A.testBit(i)&regs[regIndex]->testBit(i)));
    }
    setFlagC(false);
    setFlagAC(true);
    emit(accumulatorChanged());
    return true;
}
bool Internal8085::ANI(QString val){
    temp.setValue(val);
    return ANA(8);
}
bool Internal8085::PUSH(int val){
    Register High;
    Register low;
    if(val == 0){
        High.setValue(B.toInt());
        low.setValue(C.toInt());
    } else if(val == 1){
        High.setValue(D.toInt());
        low.setValue(E.toInt());
    } else if(val == 2){
        High.setValue(H.toInt());
        low.setValue(L.toInt());
    } else if(val == 3){
        High.setValue(A.toInt());
        low.setValue(F.toInt());
    } else{
        return false;
    }
    SP.setValue(SP.toInt() - 1);
    int location = SP.toInt();
    if(!setValueAtCell(location, High.toInt())){
        return false;
    }
    SP.setValue(SP.toInt() - 1);
    location = SP.toInt();
    if(!setValueAtCell(location, low.toInt())){
        return false;
    }
    return true;
}
bool Internal8085::POP(int val){
    Register *High;
    Register *low;
    if(val == 0){
        High = &B;
        low = &C;
    } else if(val == 1){
        High = &D;
        low = &E;
    } else if(val == 2){
        High = &H;
        low = &L;
    } else if(val == 3){
        High = &A;
        low = &F;
    } else {
        return false;
    }
    bool ok;
    QString sVal = getValueAtCell(SP.toInt(), ok);
    if(!ok) return false;
    low->setValue(sVal);
    SP.setValue(SP.toInt() + 1);

    sVal = getValueAtCell(SP.toInt(), ok);
    if(!ok) return false;
    High->setValue(sVal);
    SP.setValue(SP.toInt() + 1);
    return true;
}
bool Internal8085::CALL(int address){
    Register w, z;
    w.setValue(H.toInt());
    z.setValue(L.toInt());

    H.setValue((PC.toInt() & 0xFF00) >> 8);
    L.setValue(PC.toInt() & 0x00FF);

    if(!PUSH(2)){
        return false;
    }
    PC.setValue(address);
    H.setValue(w.toInt());
    L.setValue(z.toInt());
    return true;
}
bool Internal8085::CC(int address){
    qDebug() << "cc internal";
    if(getFlagC()){
       return CALL(address);
    }
    return true;
}
bool Internal8085::CNC(int address){
    qDebug() << "cnc internal";
    if(!getFlagC()){
        return CALL(address);
    }
    return true;
}
bool Internal8085::CP(int address){
    qDebug() << "cp internal";
    if(!getFlagS()){
        return CALL(address);
    }
    return true;
}
bool Internal8085::CM(int address){
    qDebug() << "cm internal";
    if(getFlagS()){
        return CALL(address);
    }
    return true;
}
bool Internal8085::CPE(int address){
    qDebug() << "cpe internal";
    if(getFlagP()){
        return CALL(address);
    }
    return true;
}
bool Internal8085::CPO(int address){
    qDebug() << "cpo internal";
    if(!getFlagP()){
        return CALL(address);
    }
    return true;
}
bool Internal8085::CZ(int address){
    qDebug() << "cz internal";
    if(getFlagZ()){
        return CALL(address);
    }
    return true;
}
bool Internal8085::CNZ(int address){
    qDebug() << "cnz internal";
    if(!getFlagZ()){
        return CALL(address);
    }
    return true;
}
bool Internal8085::NOP(){
    return true;
}
bool Internal8085::CMA(){
    for(int i = 0;i < 8;++i){
        A.setBit(i, !A.testBit(i));
    }
    A.setValue(A.toInt());
    emit accumulatorChanged();
    return true;

}
bool Internal8085::CMC(){
    setFlagC(true^getFlagC());
    return true;
}
bool Internal8085::CMP(int val){
    for(int i = 0;i < 8;++i){
        if(A.testBit(i) && (!regs[val]->testBit(i))){
            setFlagC(false);
            setFlagZ(false);
            return true;
        }
        if(!A.testBit(i) && (regs[val]->testBit(i))){
            setFlagC(true);
            setFlagZ(false);
            return true;
        }
    }
    setFlagZ(true);
    setFlagC(false);
    return true;
}
bool Internal8085::CPI(QString val){
    temp.setValue(val);
    return CMP(8);
}

bool Internal8085::DAA(){
    bool storeC = getFlagC();
    int valA = A.toInt();
    int addend = 0;
    if(getFlagAC() || (valA & 0x0F) > 9){
        addend = 0x06;
    }
    if(getFlagC() || ((valA & 0xF0)>>4) > 9){
        addend += 0x60;
    }
    temp.setValue(addend);
    ADD(8);
    setFlagC(getFlagC()|storeC);
    return true;
}
bool Internal8085::DCR(int val){
    bool found = false;
    for(int i = 7;i >= 4;--i){
        if(regs[val]->toggleBit(i)){
            found = true;
            break;
        }
    }
    if(found){
        setFlagAC(true);
    } else{
        setFlagAC(false);
    }
    for(int i = 3;i >= 0 && (!found);--i){
        if(regs[val]->toggleBit(i)){
            found = true;
        }
    }
    if(val == 7)
        emit accumulatorChanged();
    return true;
}
bool Internal8085::DCX(int val){
    Register *high;
    Register *low;
    if(val == 3){
        SP.setValue(SP.toInt() - 1);
        return true;
    }
    if(val == 0){
        high = &B;
        low = &C;
    } else if(val == 1){
        high = &D;
        low = &E;
    } else if(val == 2){
        high = &H;
        low = &L;
    } else return false;
    for(int i = 7;i >= 0;--i){
        if(low->toggleBit(i)){
            return true;
        }
    }
    for(int i = 7;i >= 0;--i){
        if(high->toggleBit(i)){
            return true;
        }
    }
    return true;
}
bool Internal8085::INR(int val){
    bool found = false;
    for(int i = 7;i >= 4;--i){
        if(!regs[val]->toggleBit(i)){
            found = true;
            break;
        }
    }
    if(!found){
        setFlagAC(true);
    } else{
        setFlagAC(false);
    }
    for(int i = 3;i >= 0 && (!found);--i){
        if(!regs[val]->toggleBit(i)){
            found = true;
        }
    }
    if(val == 7)
        emit accumulatorChanged();
    return true;
}
bool Internal8085::INX(int val){
    Register *high;
    Register *low;
    if(val == 3){
        SP.setValue(SP.toInt() + 1);
        return true;
    }
    if(val == 0){
        high = &B;
        low = &C;
    } else if(val == 1){
        high = &D;
        low = &E;
    } else if(val == 2){
        high = &H;
        low = &L;
    } else return false;
    for(int i = 7;i >= 0;--i){
        if(!low->toggleBit(i)){
            return true;
        }
    }
    for(int i = 7;i >= 0;--i){
        if(!high->toggleBit(i)){
            return true;
        }
    }
    return true;
}
bool Internal8085::DAD(int val){
    int storeF = F.toInt();
    int storeA = A.toInt();
    int high, low;
    switch(val){
        case 0: high = B.toInt(); low = C.toInt(); break;
        case 1: high = D.toInt(); low = E.toInt(); break;
        case 2: high = H.toInt(); low = L.toInt(); break;
        case 3: high = (SP.toInt() & 0xFF00)>>8; low = (SP.toInt() & 0x00FF); break;
        default: return false;
    }
    bool ok = true;
    A.setValue(low);
    ok &= ADD(5);
    L.setValue(A.toInt());
    A.setValue(high);
    ok &= ADC(4);
    H.setValue(A.toInt());
    if(getFlagC()){
        storeF |= 1;
    }
    F.setValue(storeF);
    A.setValue(storeA);
    return ok;
}

bool Internal8085::SUB(int val){
    temp.setValue(regs[val]->toInt());
    if(temp.toInt() == 0x00){
        return ADD(8);
    }
    for(int i = 0;i < 8;++i){
        temp.toggleBit(i);
    }
    for(int i = 7;i >= 0;--i){
        temp.toggleBit(i);
        if(temp.testBit(i)){
            break;
        }
    }
    bool ok = ADD(8);
    setFlagC(!getFlagC());
    return ok;
}
bool Internal8085::SBB(int val){
    if(!getFlagC()){
        return SUB(val);
    }
    int subtrahend = regs[val]->toInt();
    if(subtrahend == 0xFF){
        if(A.toInt() == 0x00){
            setFlagC(true);
            setFlagAC(false);
            return true;
        } else{
            for(int i = 7;i >= 0;--i){
                A.toggleBit(i);
                if(!A.testBit(i)){
                    break;
                 }
            }
            return SUB(val);
        }
    }
    temp.setValue(subtrahend + 1);
    return SUB(8);
}
bool Internal8085::SBI(QString operand){
    temp.setValue(operand);
    return SUB(8);
}
bool Internal8085::JMP(int address){
    PC.setValue(address);
    return true;
}
bool Internal8085::JC(int address){
    if(getFlagC()){
        JMP(address);
    }
    return true;
}
bool Internal8085::JNC(int address){
    if(!getFlagC()){
        JMP(address);
    }
    return true;
}
bool Internal8085::JP(int address){
    if(!getFlagS()){
        JMP(address);
    }
    return true;
}
bool Internal8085::JM(int address){
    if(getFlagS()){
        JMP(address);
    }
    return true;
}
bool Internal8085::JPE(int address){
    if(getFlagP()){
        JMP(address);
    }
    return true;
}
bool Internal8085::JPO(int address){
    if(!getFlagP()){
        JMP(address);
    }
    return true;
}
bool Internal8085::JZ(int address){
    if(getFlagZ()){
        JMP(address);
    }
    return true;
}
bool Internal8085::JNZ(int address){
    if(!getFlagZ()){
        JMP(address);
    }
    return true;
}
bool Internal8085::LDA(int address){
    bool ok;
    A.setValue(getValueAtCell(address, ok));
    qDebug() << address;
    return true;
}
bool Internal8085::LDAX(int val){
    int address;
    if(val == 0){
        address = ((B.toInt()) << 8) + C.toInt();
    } else if(val == 1){
        address = ((D.toInt()) << 8) + E.toInt();
    } else return false;
    bool ok;
    A.setValue(getValueAtCell(address, ok));
    return true;
}
bool Internal8085::STA(int address){
    setValueAtCell(address, A.toInt());
    return true;
}
bool Internal8085::STAX(int val){
    int address;
    if(val == 0){
        address = ((B.toInt()) << 8) + C.toInt();
    } else if(val == 1){
        address = ((D.toInt()) << 8) + E.toInt();
    } else return false;
    setValueAtCell(address, A.toInt());
    return true;
}
bool Internal8085::LHLD(int address){
    bool ok;
    L.setValue(getValueAtCell(address, ok));
    ++address;
    H.setValue(getValueAtCell(address, ok));
    return true;
}
bool Internal8085::SHLD(int address){
    setValueAtCell(address, L.toInt());
    ++address;
    setValueAtCell(address, H.toInt());
    return true;
}
bool Internal8085::LXI(int val, QString lowByte, QString highByte){
    switch(val){
        case 0: C.setValue(lowByte);B.setValue(highByte);
            break;
        case 1: E.setValue(lowByte);D.setValue(highByte);
            break;
        case 2: L.setValue(lowByte);H.setValue(highByte);
            break;
        case 3: SP.setValue((hexToNumber(highByte)<<8) + hexToNumber(lowByte));
            break;
        default: return false;
    }
    return true;
}

bool Internal8085::MOV(int Rd, int Rs){
    if(Rd == 6 && Rs == 6){
        return false;
    }
    if(Rd == 6){
        setValueofM(regs[Rs]->toString());
        return true;
    }
    if(Rs == 6){
        bool ok;
        QString Mval = getValueOfM(ok);
        if(!ok) return false;
        regs[Rd]->setValue(Mval);
        return true;
    }
    Register *Rdg = regs[Rd];
    Register *Rsg = regs[Rs];
    Rdg->setValue(Rsg->toInt());
    return true;
}
bool Internal8085::MVI(int R, QString val){
    if(R < 0 || R > 8) return false;
    if(R == 6){
        setValueofM(val);
        return true;
    }
    regs[R]->setValue(val);
    return true;
}
bool Internal8085::ORA(int reg){
    A |= *regs[reg];
    return true;
}
bool Internal8085::ORI(QString val){
    temp.setValue(val);
    ORA(8);
    return true;
}
bool Internal8085::PCHL(){
    PC.setValue((H.toInt()<<8) + L.toInt());
    return true;
}
bool Internal8085::STC(){
    setFlagC(true);
    return true;
}
bool Internal8085::RET(){
    int storeH = H.toInt();
    int storeL = L.toInt();
    POP(2);
    PC.setValue((H.toInt()<<8) + L.toInt());
    H.setValue(storeH);
    L.setValue(storeL);
    return true;
}
bool Internal8085::RC(){
    if(getFlagC()){
        return RET();
    }
    return true;
}
bool Internal8085::RNC(){
    if(!getFlagC()){
        return RET();
    }
    return true;
}
bool Internal8085::RP(){
    if(!getFlagS()){
        return RET();
    }
    return true;
}
bool Internal8085::RM(){
    if(getFlagS()){
        return RET();
    }
    return true;
}
bool Internal8085::RPE(){
    if(getFlagP()){
        return RET();
    }
    return true;
}
bool Internal8085::RPO(){
    if(!getFlagP()){
        return RET();
    }
    return true;
}
bool Internal8085::RZ(){
    if(getFlagZ()){
        return RET();
    }
    return true;
}
bool Internal8085::RNZ(){
    if(!getFlagZ()){
        return RET();
    }
    return true;
}
bool Internal8085::RAL(){
    bool storeC = getFlagC();
    setFlagC(A.testBit(0));
    for(int i = 0;i < 7;++i){
        A.setBit(i, A.testBit(i + 1));
    }
    A.setBit(7, storeC);
    A.setValue(A.toInt());
    emit(accumulatorChanged());
    return true;
}
bool Internal8085::RAR(){
    bool storeC = getFlagC();
    setFlagC(A.testBit(7));
    for(int i = 7;i > 0;--i){
        A.setBit(i, A.testBit(i - 1));
    }
    A.setBit(0, storeC);
    A.setValue(A.toInt());
    emit(accumulatorChanged());
    return true;
}
bool Internal8085::RLC(){
    setFlagC(A.testBit(0));
    return RAL();
}
bool Internal8085::RRC(){
    setFlagC(A.testBit(7));
    return RAR();
}
bool Internal8085::XCHG(){
    int storeH = H.toInt();
    H.setValue(D.toInt());
    D.setValue(storeH);
    int storeL = L.toInt();
    L.setValue(E.toInt());
    E.setValue(storeL);
    return true;
}
bool Internal8085::XRA(int operand){
    A ^= *regs[operand];
    return true;
}
bool Internal8085::XRI(QString val){
    temp.setValue(val);
    return XRA(8);
}
bool Internal8085::XTHL(){
    int address = SP.toInt();
    setValueAtCell(address, L.toInt());
    setValueAtCell(address + 1, H.toInt());
    return true;
}
bool Internal8085::SPHL(){
    SP.setValue((H.toInt()<<8) + L.toInt());
    return true;
}
