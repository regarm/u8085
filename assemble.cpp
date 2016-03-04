#include "mainwindow.h"
#include "utils.h"
#include <QStatusBar>
#include <QThread>
#include <QApplication>

bool MainWindow::assemble(){
    if(documentWidget->document()->isModified() || currentFileName.isEmpty()){
        if(!saveDoc())
            return false;
    }

    assembleFreeze();
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents, 4000);
    labelExists.clear();
    labelAddressMap.clear();
    QString text = documentWidget->document()->toPlainText();
    if(!labelVerify(text)){
        assembleUnfreeze();
        return false;
    }
    if(!synCheck(text)){
        assembleUnfreeze();
        return false;
    }
    genOpcodes(text);
    assembleUnfreeze();
    return true;
}
bool MainWindow::assembleAndRun(){
    if(!assemble()){
        return false;
    }
    return runAt2000();
}

bool MainWindow::labelVerify(QString& text){
    QTextStream stream(&text);
    QString line;
    QString store;
    int lineNum = 0;
    log->appendLog(tr("Starting Label Verifying ..."), logDock::Init);
    qDebug() << tr("Starting Label Verifying ...");
    //Label Verifying
    while(!(store = stream.readLine().toUpper()).isNull()){
        line = store.simplified();
        ++lineNum; // increase line number
        int x = line.indexOf(tr("//")); // get first index of "//"
        if(x != -1){
            line = line.left(x);
        }
        if(line.count(tr(":"))>1){
            log->appendLog(tr("Line %1: \"%2\"\nOnly one label per line is allowed.")
                           .arg(lineNum)
                           .arg(store), logDock::Error);
            log->appendLog(tr("Stopping here."));
            return false;
        }
        x = line.indexOf(tr(":"));
        if(x == -1){ // no labels
            continue;
        }
        QString label = line.left(x).simplified();
        if(label.isEmpty()){
            log->appendLog(tr("Line %1: \"%2\"\nEmpty label is not allowed.")
                           .arg(lineNum).arg(store), logDock::Error);
            log->appendLog(tr("Stopping here."));
            return false;
        }
        if(!isValidLabel(label)){
            log->appendLog(tr("Line %1: \"%2\"\nOnly alphanumerics characters are allowed in label.")
                           .arg(lineNum).arg(store), logDock::Error);
            log->appendLog(tr("Stopping here."));
            return false;
        }
        if(labelExists.find(label) != labelExists.end()){
            log->appendLog(tr("Line %1: \"%2\"\n\"%3\" is also defined elsewhere.")
                           .arg(lineNum).arg(store).arg(label), logDock::Error);
            log->appendLog(tr("Stopping here."));
            return false;
        }
        labelExists[label] = true;
        ++lineNum;
    }
    log->appendLog(tr("All labels are ok."));
    return true;
}
bool MainWindow::synCheck(QString& text){
    log->appendLog(tr("Syntax checking"), logDock::Init);
    qDebug() << tr("Syntax checking");
    QTextStream stream(&text);
    QString line;
    QString store;
    int address = 0x2000;
    int lineNum = 0;
    //Syntax Checking
    while(!(store = stream.readLine()).isNull()){
        line = store.simplified().toUpper();
        ++lineNum;
        int x = line.indexOf(tr("//"));
        if(x != -1){
            line = line.left(x).simplified();
        }
        x = line.indexOf(tr(":"));
        if(x != -1){
            labelAddressMap[line.left(x).simplified()] = address;
            line = line.right(line.size() - x - 1).simplified();
        }
        if(line.isEmpty()){
            continue;
        }
        QString mnem;
        QString rem;
        x = line.indexOf(tr(" "));
        if(x == -1){
            mnem = line;
            rem = tr("");
        } else{
            mnem = line.left(x).simplified();
            rem = line.right(line.size() - x).simplified();
        }
        bool error = false;
        QString errorVal = tr("");
        QString suggestion = tr("");
        log->appendLog(tr("Line %1: \"%2\"").arg(lineNum).arg(store));
        switch(__8085.instructionType[mnem]){
            case 1:
            {
                //no operand
                if(!rem.isEmpty()){
                    error = true;
                    errorVal = tr("No operands are required here.");
                }
                break;
            }
            case 2:
            {
                //8-bit data operand
                if(!isData(rem)){
                    error = true;
                    errorVal = tr("8-bit data operand is required in hexadecimal.");
                }
                break;
            }
            case 3:
            {
                //single register operand [A, B, C, D, E, H, L, M]
                if(!isRegister(rem)){
                    errorVal = tr("Single register operand is required [A, B, C, D, E, H, L, M] .");
                    error = true;
                }
                break;
            }
            case 4:
            {
                //CALL, JMP Require Label
                if(mnem.startsWith(tr("C")) || mnem.startsWith(tr("J"))){
                    if(!isValidLabel(rem)){
                        errorVal = tr("%3 is not a valid label.").arg(rem);
                        error = true;
                    }
                    if(labelExists.find(rem) == labelExists.end()){
                        errorVal = tr("Label \"%3\" is not defined.").arg(rem);
                        error = true;
                    }
                } else{//STA, LDA, LHLD, SHLD require an address
                    if(!isValidAddress(rem)){
                        error = true;
                        errorVal = tr("%1 requires a 16-bit address in hexadecimal.\ni.e. %1 2000").arg(mnem);
                    }
                }
                break;
            }
            case 5:
            {
                //Rpair4 {BC, DE, HL, SP}
                if(!isRpair4(rem)){
                    error = true;
                    errorVal = tr("%1 requires an register pair [B, D, H, SP]").arg(mnem);
                }
                break;
            }
            case 6:
            {
                //Rp2 {BC, DE}
                if(!isRp2(rem)){
                    error = true;
                    errorVal = tr("%1 requires an register pair [B, D]").arg(mnem);
                }
                break;
            }
            case 7:
            {
                //Rpw4 {BC, DE, HL, PSW}
                if(!isRpw4(rem)){
                    error = true;
                    errorVal = tr("%1 requires an register pair [B, D, H, PSW]").arg(mnem);
                }
                break;
            }
            case 8:
            {
                x = rem.count(tr(","));
                if(x != 1){
                    error = true;
                    errorVal = tr("%1 requires two comma separated oprands. i.e. MOV A, B").arg(mnem);
                } else{
                    x = rem.indexOf(tr(","));
                    QString left = rem.left(x).simplified();
                    QString right = rem.right(rem.size() - x - 1).simplified();
                    if(!(isRegister(left)&&isRegister(right))){
                        error = true;
                        errorVal = tr("%1 requires two valid register operands.i.e. MOV A, B").arg(mnem);
                    } else if(left == tr("M") && right == tr("M")){
                        error = true;
                        errorVal = tr("\"Mov M, M\" is not an instruction in 8085.");
                    }
                }
                break;
            }
            case 9:
            {
                x = rem.count(tr(","));
                if(x != 1){
                    error = true;
                    errorVal = tr("%1 requires two comma separated oprands.\ni.e. MVI A, FE").arg(mnem);
                } else{
                    x = rem.indexOf(tr(","));
                    QString left = rem.left(x).simplified();
                    QString right = rem.right(rem.size() - x - 1).simplified();
                    if(!(isRegister(left)&&isData(right))){
                        error = true;
                        errorVal = tr("%1 requires two comma separated oprands.i.e. MVI A, FE").arg(mnem);
                    }
                }
                break;
            }
            case 10:
            {
                x = rem.count(tr(","));
                if(x != 1){
                    error = true;
                    errorVal = tr("%1 requires two comma separated oprands.i.e. LXI H, 2000").arg(mnem);
                } else{
                    x = rem.indexOf(tr(","));
                    QString left = rem.left(x).simplified();
                    QString right = rem.right(rem.size() - x - 1).simplified();
                    if(!(isRpair4(left)&&isValidAddress(right))){
                        error = true;
                        errorVal = tr("%1 requires two comma separated oprands.i.e. LXI H, 2000").arg(mnem);
                    }
                }
                break;
            }
            case 11:
            {
                error = true;
                errorVal = tr("%1 is not currently supported by this software").arg(mnem);
                break;
            }
            default:
            {
                error = true;
                errorVal = tr("%1 is not a recognized MNEMONIC.").arg(mnem);
            }
        }
        if(error){
            log->appendLog(errorVal, logDock::Error);
            log->appendLog(tr("Error occured, stopping here."));
            return false;
        } else{
            log->appendLog(tr("Success"), logDock::Success);
        }
        address += __8085.byteCnt[mnem];
    }
    log->appendLog(tr("Successfull syntax check. :)"));
    return true;
}
