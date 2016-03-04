#include "mainwindow.h"
#include "utils.h"
#include "debugmode.h"
#include <QtDebug>
#include <QApplication>
bool MainWindow::runAt2000(){
    qDebug() << "running";
    runFreeze();
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents, 4000);
    log->appendLog(tr("Starting the program..."), logDock::Init);
    /*-------------------no operand------------------*/
    QString missing = tr("10:18:28:38:CB:D9:DD:ED:FD");
    __8085.PC.setValue(tr("2000"));
    __8085.SP.setValue(tr("2050"));
    bool noBug = true;
    int stopper = 0;
    int limit = 100;
    int multiPlier = 10;
    QString bugVal = tr("");
    while(noBug){
        qDebug() << stopper;
        ++stopper;
        if(stopper == limit){
            switch(QMessageBox::warning(this, tr("Probable infinite running"),
                                        tr("You program has ran more than expected!(%1 instructions tillnow). Do you want to stop it?")
                                        .arg(QString::number(stopper)),
                                        QMessageBox::Yes|QMessageBox::No))
            {
                case QMessageBox::Yes:
                        log->appendLog(tr("Program was forcibly stopped."), logDock::Error);
                        runUnfreeze();
                        return false;
                default:
                    break;
            }
            limit *= multiPlier;
            if(multiPlier > 2){
                multiPlier >>= 1;
            }
        }
        log->appendLog(tr("Running at #%1: ").arg(__8085.PC.toString()));
        bool ok;
        QString opcode = __8085.getValueAtCell(__8085.PC.toInt(), ok);
        if(!ok){
            noBug = false;
            bugVal = tr("Program Counter is out of address space.");
            break;
        }
        __8085.PC.setValue(__8085.PC.toInt() + 1);
        if(missing.contains(opcode)){
            noBug = false;
            bugVal = tr("This opcode in not included in 8085");
            break;
        }

        //CMA
        if(opcode == tr("2F")){
            if(DEBUG_MODE){
                qDebug() << "running CMA";
            }
            log->appendLog(tr("CMA : 2F"), logDock::Ins);
            if(!__8085.CMA()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //CMC
        if(opcode == tr("3F")){
            if(DEBUG_MODE){
                qDebug() << "running CMC";
            }
            log->appendLog(tr("CMC : 3F"), logDock::Ins);
            if(!__8085.CMC()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //DAA
        if(opcode == tr("27")){
            if(DEBUG_MODE){
                qDebug() << "running DAA";
            }
            log->appendLog(tr("DAA : 27"), logDock::Ins);
            if(!__8085.DAA()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //HLT
        if(opcode == tr("76")){
            if(DEBUG_MODE){
                qDebug() << "running HLT";
            }
            log->appendLog(tr("HLT : 76"), logDock::Ins);
            if(!__8085.HLT()){
                log->appendLog(tr("Success"), logDock::Success);
                log->appendLog(tr("Program ran successfully!"));
                runUnfreeze();
                return true;
            }
            continue;
        }
        //NOP
        if(opcode == tr("00")){
            if(DEBUG_MODE){
                qDebug() << "running NOP";
            }
            log->appendLog(tr("NOP : 00"), logDock::Ins);
            if(!__8085.NOP()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //PCHL
        if(opcode == tr("E9")){
            if(DEBUG_MODE){
                qDebug() << "running PCHL";
            }
            log->appendLog(tr("PCHL : E9"), logDock::Ins);
            if(!__8085.PCHL()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RAL
        if(opcode == tr("17")){
            if(DEBUG_MODE){
                qDebug() << "running RAL";
            }
            log->appendLog(tr("RAL : 17"), logDock::Ins);
            if(!__8085.RAL()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RAR
        if(opcode == tr("1F")){
            if(DEBUG_MODE){
                qDebug() << "running RAR";
            }
            log->appendLog(tr("HLT : 1F"), logDock::Ins);
            if(!__8085.RAR()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RET
        if(opcode == tr("C9")){
            if(DEBUG_MODE){
                qDebug() << "running RET";
            }
            log->appendLog(tr("RET : C9"), logDock::Ins);
            if(!__8085.RET()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RC
        if(opcode == tr("D8")){
            if(DEBUG_MODE){
                qDebug() << "running RC";
            }
            if(!__8085.RC()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RLC
        if(opcode == tr("07")){
            if(DEBUG_MODE){
                qDebug() << "running RLC";
            }
            if(!__8085.RLC()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RM
        if(opcode == tr("F8")){
            if(DEBUG_MODE){
                qDebug() << "running RM";
            }
            if(!__8085.RM()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RNC
        if(opcode == tr("D0")){
            if(DEBUG_MODE){
                qDebug() << "running RNC";
            }
            if(!__8085.RNC()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RNZ
        if(opcode == tr("C0")){
            if(DEBUG_MODE){
                qDebug() << "running RNZ";
            }
            if(!__8085.RNZ()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RP
        if(opcode == tr("F0")){
            if(DEBUG_MODE){
                qDebug() << "running RP";
            }
            if(!__8085.RP()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RPE
        if(opcode == tr("E8")){
            if(DEBUG_MODE){
                qDebug() << "running RPE";
            }
            if(!__8085.RPE()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RPO
        if(opcode == tr("E0")){
            if(DEBUG_MODE){
                qDebug() << "running RPO";
            }
            if(!__8085.RPO()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RRC
        if(opcode == tr("0F")){
            if(DEBUG_MODE){
                qDebug() << "running RRC";
            }
            if(!__8085.RRC()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //RZ
        if(opcode == tr("C8")){
            if(DEBUG_MODE){
                qDebug() << "running RZ";
            }
            if(!__8085.RZ()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //SPHL
        if(opcode == tr("F9")){
            if(DEBUG_MODE){
                qDebug() << "running SPHL";
            }
            if(!__8085.SPHL()){
                noBug = false;
                break;
            }
        }
        //STC
        if(opcode == tr("37")){
            if(DEBUG_MODE){
                qDebug() << "running STC";
            }
            if(!__8085.STC()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //XCHG
        if(opcode == tr("EB")){
            if(DEBUG_MODE){
                qDebug() << "running XCHG";
            }
            if(!__8085.XCHG()){
                noBug = false;
                break;
            }
            log->appendLog(tr("Success"), logDock::Success);
            continue;
        }
        //XTHL
        if(opcode == tr("E3")){
            if(DEBUG_MODE){
                qDebug() << "running XTHL";
            }
           if(!__8085.XTHL()){
               noBug = false;
               break;
           }
           log->appendLog(tr("Success"), logDock::Success);
           continue;
        }
        //zz






















        int opcodeIntVal = hexToNumber(opcode);
        if(DEBUG_MODE){
            qDebug() << "opcode: " << opcode << " " << "PC" << __8085.PC.toInt();
            qDebug() << stopper << " " << limit << "\n";
        }
        //ACI
        if(opcode == tr("CE")){
            if(DEBUG_MODE){
                qDebug() << "running ACI";
            }
            int address = __8085.PC.toInt();
            bool ok;
            QString operand = __8085.getValueAtCell(address, ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.ACI(operand)){
                noBug = false;
                break;
            }
            continue;
        }


        //ADC
        if((opcodeIntVal&0xF8) == 0x88){
            if(DEBUG_MODE){
                qDebug() << "running ADC";
            }
            if(!__8085.ADC(opcodeIntVal & 0x07)){
                noBug = false;
                break;
            }
            continue;
        }


        //ADD
        if((opcodeIntVal&0xF8) == 0x80){
            if(DEBUG_MODE){
                qDebug() << "running ADD";
            }
            if(!__8085.ADD(opcodeIntVal & 0x07)){
                noBug = false;
                break;
            }
            continue;
        }


        //ADI
        if(opcode == tr("C6")){
            if(DEBUG_MODE){
                qDebug() << "running ADI";
            }
            int address = __8085.PC.toInt();
            bool ok;
            QString operand = __8085.getValueAtCell(address, ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.ADI(operand)){
                noBug = false;
                break;
            }
            continue;
        }

        //ANI
       if(opcode == tr("E6")){
           if(DEBUG_MODE){
               qDebug() << "running ANI";
           }
           int address = __8085.PC.toInt();
           bool ok;
           QString operand = __8085.getValueAtCell(address, ok);
           __8085.PC.setValue(__8085.PC.toInt() + 1);
           if(!__8085.ANI(operand)){
               noBug = false;
               break;
           }
           continue;
       }

        //ANA
        if((opcodeIntVal&0xF8) == 0xA0){
            if(DEBUG_MODE){
                qDebug() << "running ANA";
            }
            if(!__8085.ANA(opcodeIntVal & 0x07)){
                noBug = false;
                break;
            }
            continue;
        }
        //PUSH
        if((opcodeIntVal&0xCF) == 0xC5){
            if(DEBUG_MODE){
                qDebug() << "running PUSH";
            }
            int operand = (opcodeIntVal&0x30) >> 4;
            if(!__8085.PUSH(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //POP
        if((opcodeIntVal&0xCF) == 0xC1){
            if(DEBUG_MODE){
                qDebug() << "running POP";
            }
            int operand = (opcodeIntVal&0x30) >> 4;
            if(!__8085.POP(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //CALL
        if(opcode == tr("CD")){
            if(DEBUG_MODE){
                qDebug() << "running CALL";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CALL(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CC
        if(opcode == tr("DC")){
            if(DEBUG_MODE){
                qDebug() << "running CC";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CC(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CNC
        if(opcode == tr("D4")){
            if(DEBUG_MODE){
                qDebug() << "running CNC";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CNC(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CP
        if(opcode == tr("F4")){
            if(DEBUG_MODE){
                qDebug() << "running CP";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CP(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CM
        if(opcode == tr("FC")){
            if(DEBUG_MODE){
                qDebug() << "running CM";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CM(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CPE
        if(opcode == tr("EC")){
            if(DEBUG_MODE){
                qDebug() << "running CPE";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CPE(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CPO
        if(opcode == tr("E4")){
            if(DEBUG_MODE){
                qDebug() << "running CPO";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CPO(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CZ
        if(opcode == tr("CC")){
            if(DEBUG_MODE){
                qDebug() << "running CZ";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CZ(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CNZ
        if(opcode == tr("C4")){
            if(DEBUG_MODE){
                qDebug() << "running CNZ";
            }
            bool ok;
            int address = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            address = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok)) << 8) + address;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CNZ(address)){
                noBug = false;
                break;
            }
            continue;
        }
        //CMP
        if((opcodeIntVal&0xF8) == 0xB8){
            if(DEBUG_MODE){
                qDebug() << "running CMP";
            }
            int operand = opcodeIntVal&0x07;
            if(!__8085.CMP(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //CPI
        if(opcode == tr("FE")){
            if(DEBUG_MODE){
                qDebug() << "running CPI";
            }
            bool ok;
            QString operand = __8085.getValueAtCell(__8085.PC.toInt(), ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.CPI(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //DAD
        if((opcodeIntVal&0xCF) == 0x09){
            if(DEBUG_MODE){
               qDebug() << "running DAD";
            }
            int operand = (opcodeIntVal & 0x30) >> 4;
            if(!__8085.DAD(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //DCR
        if((opcodeIntVal&0xC7) == 0x05){
            if(DEBUG_MODE){
                qDebug() << "running DCR";
            }
            int operand = (opcodeIntVal & 0x38) >> 3;
            if(!__8085.DCR(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //DCX
        if((opcodeIntVal & 0xCF) == 0x0B){
            if(DEBUG_MODE){
                qDebug() << "running DCX";
            }
            int operand = (opcodeIntVal & 0x30) >> 4;
            if(!__8085.DCX(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //SUB
        if((opcodeIntVal&0xF8) == 0x90){
            if(DEBUG_MODE){
                qDebug() << "running SUB";
            }
            int operand = (opcodeIntVal & 0x07);
            if(!__8085.SUB(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //SBB
        if((opcodeIntVal&0xF8) == 0x98){
            if(DEBUG_MODE){
                qDebug() << "running SBB";
            }
            int operand = (opcodeIntVal & 0x07);
            if(!__8085.SBB(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //SBI
        if(opcode == tr("DE")){
            if(DEBUG_MODE){
                qDebug() << "running SBI";
            }
            bool ok;
            QString operand = __8085.getValueAtCell(__8085.PC.toInt(), ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.SBI(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //INR
        if((opcodeIntVal&0xC7) == 0x04){
            if(DEBUG_MODE){
                qDebug() << "running INR";
            }
            int operand = (opcodeIntVal&0x38)>>3;
            if(!__8085.INR(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //INX
        if((opcodeIntVal&0xCF) == 0x03){
            if(DEBUG_MODE){
                qDebug() << "running INX";
            }
            int operand = (opcodeIntVal&0x30)>>4;
            if(!__8085.INX(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JMP
        if(opcode ==tr("C3")){
            if(DEBUG_MODE){
                qDebug() << "running JMP";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JMP(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JC
        if(opcode ==tr("DA")){
            if(DEBUG_MODE){
                qDebug() << "running JC";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JC(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JNC
        if(opcode ==tr("D2")){
            if(DEBUG_MODE){
                qDebug() << "running JNC";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JNC(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JP
        if(opcode ==tr("F2")){
            if(DEBUG_MODE){
                qDebug() << "running JP";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JP(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JM
        if(opcode ==tr("FA")){
            if(DEBUG_MODE){
                qDebug() << "running JM";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JM(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JPE
        if(opcode ==tr("EA")){
            if(DEBUG_MODE){
                qDebug() << "running JPE";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JPE(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JPO
        if(opcode ==tr("E2")){
            if(DEBUG_MODE){
                qDebug() << "running JPO";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JPO(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JZ
        if(opcode ==tr("CA")){
            if(DEBUG_MODE){
                qDebug() << "running JZ";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JZ(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //JNZ
        if(opcode ==tr("C2")){
            if(DEBUG_MODE){
                qDebug() << "running JNZ";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.JNZ(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //LDA
        if(opcode == tr("3A")){
            if(DEBUG_MODE){
                qDebug() << "running LDA";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.LDA(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //LDAX
        if((opcodeIntVal&0xEF) == 0x0A){
            if(DEBUG_MODE){
                qDebug() << "running LDAX";
            }
            int operand = (opcodeIntVal&0x10)>>4;
            if(!__8085.LDAX(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //STA
        if(opcode == tr("32")){
            if(DEBUG_MODE){
                qDebug() << "running STA";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.STA(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //STAX
        if((opcodeIntVal&0xEF) == 0x02){
            if(DEBUG_MODE){
                qDebug() << "running STAX";
            }
            int operand = (opcodeIntVal&0x10)>>4;
            if(!__8085.STAX(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //LHLD
        if((opcode == tr("2A"))){
            if(DEBUG_MODE){
                qDebug() << "running LHLD";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.LHLD(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //SHLD
        if((opcode == tr("22"))){
            if(DEBUG_MODE){
                qDebug() << "running SHLD";
            }
            bool ok;
            int operand = hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok));
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            operand = (hexToNumber(__8085.getValueAtCell(__8085.PC.toInt(), ok))<<8) + operand;
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.SHLD(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //LXI
        if((opcodeIntVal&0xCF) == 0x01){
            if(DEBUG_MODE){
                qDebug() << "running LXI";
            }
            bool ok;
            int operand = (opcodeIntVal&0x30) >> 4;
            QString lowByte = __8085.getValueAtCell(__8085.PC.toInt(), ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            QString highByte = __8085.getValueAtCell(__8085.PC.toInt(), ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.LXI(operand, lowByte, highByte)){
                noBug = false;
                break;
            }
            continue;
        }
        //MOV
        if(opcode != tr("76") && (opcodeIntVal&0xC0) == 0x40){
            if(DEBUG_MODE){
                qDebug() << "running MOV";
            }
            int Rd = (opcodeIntVal & 0x38) >> 3;
            int Rs = (opcodeIntVal & 0x07);
            if(!__8085.MOV(Rd, Rs)){
                noBug = false;
                break;
            }
            continue;
        }
        //MVI
        if((opcodeIntVal&0xC7) == 0x06){
            if(DEBUG_MODE){
                qDebug() << "running MVI";
            }
            bool ok;
            int reg = (opcodeIntVal&0x38)>>3;
            QString operand = __8085.getValueAtCell(__8085.PC.toInt(), ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.MVI(reg, operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //ORA
        if((opcodeIntVal&0xF8) == 0xB0){
            if(DEBUG_MODE){
                qDebug() << "running ORA";
            }
            int operand = (opcodeIntVal & 0x07);
            if(!__8085.ORA(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //ORI
        if(opcode == tr("F6")){
            if(DEBUG_MODE){
                qDebug() << "running ORI";
            }
            bool ok;
            QString operand = __8085.getValueAtCell(__8085.PC.toInt(), ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.ORI(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        
        //XCHG
        if(opcode == tr("EB")){
            if(DEBUG_MODE){
                qDebug() << "running XCHG";
            }
            if(!__8085.XCHG()){
                noBug = false;
                break;
            }
            continue;
        }
        //XRA
        if((opcodeIntVal&0xFE) == 0xA8){
            if(DEBUG_MODE){
                qDebug() << "running XRA";
            }
            int operand = (opcodeIntVal & 0x07);
            if(!__8085.XRA(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //XRI
        if(opcode == tr("EE")){
            if(DEBUG_MODE){
                qDebug() << "running XRI";
            }
            bool ok;
            QString operand = __8085.getValueAtCell(__8085.PC.toInt(), ok);
            __8085.PC.setValue(__8085.PC.toInt() + 1);
            if(!__8085.XRI(operand)){
                noBug = false;
                break;
            }
            continue;
        }
        //XTHL
        if(opcode == tr("E3")){
            if(DEBUG_MODE){
                qDebug() << "running XTHL";
            }
           if(!__8085.XTHL()){
               noBug = false;
               break;
           }
           continue;
        }
    }
    log->appendLog(bugVal   , logDock::Error);
    log->appendLog(tr("Stopping here."));
    runUnfreeze();
    qDebug() << tr("Successfully done!! :)");
//    removeDockWidget(memDock);
//    memDock = new MemEditorDock(tr("Memory Editor"),&__8085,this);
//    addDockWidget(Qt::RightDockWidgetArea, memDock);
//    memDock->setStyleSheet(tr("QDockWidget > QWidget {border : 1px solid black}"));

//    emit changedRegisterDock();
    return true;
}
