#include "mainwindow.h"
#include "register.h"
#include "utils.h"
void MainWindow::genOpcodes(QString & text){
    log->appendLog(tr("Generating Opcodes"), logDock::Init);
    QTextStream stream(&text);
    QString line;
    QString store;
    uint16_t address = 0x2000;
    int lineNum = 0;
    bool ok;
    while(!(store = stream.readLine().toUpper()).isNull()){
        ++lineNum;
        int x;
        line = store.simplified();

        //remove comment
        x = line.indexOf(tr("//"));
        if(x != -1){
            line = line.left(x);
        }

        //remove label
        x = line.indexOf(tr(":"));
        if(x != -1){
            line = line.right(line.size() - x - 1);
        }
        line = line.simplified();
        if(line.isEmpty()){
            continue;
        }

        x = line.indexOf(tr(" "));
        QString mnem = line.left(x).simplified();
        QString rem;
        if(x != -1){
            rem = line.right(line.size() - x).simplified();
        } else {
            rem = tr("");
        }
        QString leftOp = tr("");
        QString rightOp = tr("");
        x = rem.indexOf(tr(","));
        if(x != -1){
            leftOp = rem.left(x).simplified();
            rightOp = rem.right(rem.size() - x - 1).simplified();
        }
        log->appendLog(tr("Line %1: %2 %3").arg(lineNum).arg(mnem).arg(rem));
        qDebug() << tr("Line %1: %2 %3").arg(lineNum).arg(mnem).arg(rem);

        //-------------------no operand------------------
        //CMA
        if(mnem == tr("CMA")){
            __8085.setValueAtCell(address, tr("2F").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CMC
        if(mnem == tr("CMC")){
            __8085.setValueAtCell(address, tr("3F").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //DAA
        if(mnem == tr("DAA")){
            __8085.setValueAtCell(address, tr("27").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //HLT
        if(mnem == tr("HLT")){
            __8085.setValueAtCell(address, tr("76").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //NOP
        if(mnem == tr("NOP")){
            __8085.setValueAtCell(address, tr("00").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //PCHL
        if(mnem == tr("PCHL")){
            __8085.setValueAtCell(address, tr("E9").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RAL
        if(mnem == tr("RAL")){
            __8085.setValueAtCell(address, tr("17").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RAR
        if(mnem == tr("RAR")){
            __8085.setValueAtCell(address, tr("1F").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RC
        if(mnem == tr("RC")){
            __8085.setValueAtCell(address, tr("D8").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RET
        if(mnem == tr("RET")){
            __8085.setValueAtCell(address, tr("C9").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RLC
        if(mnem == tr("RLC")){
            __8085.setValueAtCell(address, tr("07").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RM
        if(mnem == tr("RM")){
            __8085.setValueAtCell(address, tr("F8").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RNC
        if(mnem == tr("RNC")){
            __8085.setValueAtCell(address, tr("D0").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RNZ
        if(mnem == tr("RNZ")){
            __8085.setValueAtCell(address, tr("C0").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RP
        if(mnem == tr("RP")){
            __8085.setValueAtCell(address, tr("F0").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RPE
        if(mnem == tr("RPE")){
            __8085.setValueAtCell(address, tr("E8").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RPO
        if(mnem == tr("RPO")){
            __8085.setValueAtCell(address, tr("E0").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RRC
        if(mnem == tr("RRC")){
            __8085.setValueAtCell(address, tr("0F").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //RZ
        if(mnem == tr("RZ")){
            __8085.setValueAtCell(address, tr("C8").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //SPHL
        if(mnem == tr("SPHL")){
            __8085.setValueAtCell(address, tr("F9").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //STC
        if(mnem == tr("STC")){
            __8085.setValueAtCell(address, tr("37").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //XCHG
        if(mnem == tr("XCHG")){
            __8085.setValueAtCell(address, tr("EB").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //XTHL
        if(mnem == tr("XTHL")){
            __8085.setValueAtCell(address, tr("E3").toUpper());
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }



        //-----------------------data-----------------------
        //ACI
        if(mnem == tr("ACI")){
            __8085.setValueAtCell(address, tr("CE").toUpper() );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;

            continue;
        }
        //ADI
        if(mnem == tr("ADI")){
            __8085.setValueAtCell(address, tr("C6") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //ANI
        if(mnem == tr("ANI")){
            __8085.setValueAtCell(address, tr("E6").toUpper() );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CPI
        if(mnem == tr("CPI")){
            __8085.setValueAtCell(address, tr("FE").toUpper() );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //ORI
        if(mnem == tr("ORI")){
            __8085.setValueAtCell(address, tr("F6").toUpper() );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //SBI
        if(mnem == tr("SBI")){
            __8085.setValueAtCell(address, tr("DE").toUpper() );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //SUI
        if(mnem == tr("SUI")){
            __8085.setValueAtCell(address, tr("D6").toUpper() );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //XRI
        if(mnem == tr("XRI")){
            __8085.setValueAtCell(address, tr("EE").toUpper() );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        // ---------------- address --------------------
        //CALL
        if(mnem == tr("CALL")){
            __8085.setValueAtCell(address, tr("CD").toUpper() );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CC
        if(mnem == tr("CC")){
            __8085.setValueAtCell(address, tr("DC") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CM
        if(mnem == tr("CM")){
            __8085.setValueAtCell(address, tr("FC") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CNC
        if(mnem == tr("CNC")){
            __8085.setValueAtCell(address, tr("D4") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CNZ
        if(mnem == tr("CNZ")){
            __8085.setValueAtCell(address, tr("C4") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CP
        if(mnem == tr("CP")){
            __8085.setValueAtCell(address, tr("F4") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CPE
        if(mnem == tr("CPE")){
            __8085.setValueAtCell(address, tr("EC") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CPO
        if(mnem == tr("CPO")){
            __8085.setValueAtCell(address, tr("E4") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CZ
        if(mnem == tr("CZ")){
            __8085.setValueAtCell(address, tr("CC") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JC
        if(mnem == tr("JC")){
            __8085.setValueAtCell(address, tr("DA") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JM
        if(mnem == tr("JM")){
            __8085.setValueAtCell(address, tr("FA") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JMP
        if(mnem == tr("JMP")){
            __8085.setValueAtCell(address, tr("C3") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JNC
        if(mnem == tr("JNC")){
            __8085.setValueAtCell(address, tr("D2") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JNZ
        if(mnem == tr("JNZ")){
            __8085.setValueAtCell(address, tr("C2") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JP
        if(mnem == tr("JP")){
            __8085.setValueAtCell(address, tr("F2") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JPE
        if(mnem == tr("JPE")){
            __8085.setValueAtCell(address, tr("EA") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JPO
        if(mnem == tr("JPO")){
            __8085.setValueAtCell(address, tr("E2") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //JZ
        if(mnem == tr("JZ")){
            __8085.setValueAtCell(address, tr("CA") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, (labelAddressMap[rem]&0x00FF));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, ((labelAddressMap[rem]&0xFF00)>>8));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //LDA
        if(mnem == tr("LDA")){
            __8085.setValueAtCell(address, tr("3A") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            qDebug() << rem ;
            __8085.setValueAtCell(address, rem.right(2));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem.left(2));
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //LHLD
        if(mnem == tr("LHLD")){
            __8085.setValueAtCell(address, tr("2A") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;

            __8085.setValueAtCell(address, rem.right(2) );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem.left(2) );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //SHLD
        if(mnem == tr("SHLD")){
            __8085.setValueAtCell(address, tr("22") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;

            __8085.setValueAtCell(address, rem.right(2) );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem.left(2) );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //STA
        if(mnem == tr("STA")){
            __8085.setValueAtCell(address, tr("32") );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;

            __8085.setValueAtCell(address, rem.right(2) );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rem.left(2) );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }


        //--------------------Reg operand----------------
        //ADC
        if(mnem == tr("ADC")){
            uint8_t op = 0x88;
            op |= __8085.rIndexMap[rem];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //ADD
        if(mnem == tr("ADD")){
            uint8_t op = 0x80;
            op |= __8085.rIndexMap[rem];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //ANA
        if(mnem == tr("ANA")){
            uint8_t op = 0xA0;
            op |= __8085.rIndexMap[rem];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //CMP
        if(mnem == tr("CMP")){
            uint8_t op = 0xB8;
            op |= __8085.rIndexMap[rem];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //DCR
        if(mnem == tr("DCR")){
            uint8_t op = 0x05;
            op |= __8085.rIndexMap[rem]<<3;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //INR
        if(mnem == tr("INR")){
            uint8_t op = 0x04;
            op |= __8085.rIndexMap[rem]<<3;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //ORA
        if(mnem == tr("ORA")){
            uint8_t op = 0xB0;
            op |= __8085.rIndexMap[rem];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //SBB
        if(mnem == tr("SBB")){
            uint8_t op = 0x98;
            op |= __8085.rIndexMap[rem];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //SUB
        if(mnem == tr("SUB")){
            uint8_t op = 0x90;
            op |= __8085.rIndexMap[rem];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //XRA
        if(mnem == tr("XRA")){
            uint8_t op = 0xA8;
            op |= __8085.rIndexMap[rem];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }

        //---------------------Reg Pair ----------------
        //DAD
        if(mnem == tr("DAD")){
            uint8_t op = 0x09;
            op |= __8085.rpIndexMap[rem]<<4;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //DCX
        if(mnem == tr("DCX")){
            uint8_t op = 0x0B;
            op |= __8085.rpIndexMap[rem]<<4;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //INX
        if(mnem == tr("INX")){
            uint8_t op = 0x03;
            op |= __8085.rpIndexMap[rem]<<4;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }

        //--------- Rps---------
        //LDAX
        if(mnem == tr("LDAX")){
            uint8_t op = 0x0A;
            op |= __8085.rpsIndexMap[rem]<<4;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //STAX
        if(mnem == tr("STAX")){
            uint8_t op = 0x02;
            op |= __8085.rpsIndexMap[rem]<<4;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }

        //-------------Rpw---------
        //PUSH
        if(mnem == tr("PUSH")){
            uint8_t op = 0xC5;
            op |= __8085.rpwIndexMap[rem]<<4;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //POP
        if(mnem == tr("POP")){
            uint8_t op = 0xC1;
            op |= __8085.rpwIndexMap[rem]<<4;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //----------reg,reg---------
        if(mnem == tr("MOV")){
            uint8_t op = 0x40;
            op |= __8085.rIndexMap[leftOp]<<3;
            op |= __8085.rIndexMap[rightOp];
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            continue;
        }
        //---------reg,data----------
        if(mnem == tr("MVI")){
            uint8_t op = 0x06;
            op |= __8085.rIndexMap[leftOp]<<3;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rightOp );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
        }
        //---------reg,address-------
        if(mnem == tr("LXI")){
            uint8_t op = 0x01;
            op |= __8085.rpIndexMap[leftOp]<<4;
            __8085.setValueAtCell(address, op );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rightOp.right(2) );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
            __8085.setValueAtCell(address, rightOp.left(2) );
            log->appendLog(tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address)), logDock::Success);
            qDebug() << tr("%1  stored at  %2").arg(__8085.getValueAtCell(address, ok)).arg(numberToHex(address));
            ++address;
        }
    }
    log->appendLog(tr("Opcodes Generated Successfully..."));
}
