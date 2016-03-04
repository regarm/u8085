#include "memeditordock.h"
#include "utils.h"

   MemEditorDock::MemEditorDock(QString title,Internal8085 *__8085_temp, QWidget *parent) :
    QDockWidget(title, parent),
    memWidget(new QWidget(parent)),
    base(0x2000),
    showStartAddress(new QLineEdit(parent)),
    memLay(new QGridLayout),
     __8085(__8085_temp)
{
    QVBoxLayout *mainLay = new QVBoxLayout();
    QWidget *mainW = new QWidget(parent);
    mainW->setLayout(mainLay);

    QHBoxLayout *navHelperLay = new QHBoxLayout;
    QWidget *navHelperW = new QWidget(parent);
    navHelperW->setLayout(navHelperLay);

    QLabel *showFrom = new QLabel(parent);
    showFrom->setText(tr("Show from:"));

    showStartAddress->setText(tr("2000"));
    showStartAddress->setInputMask(tr("HHHH"));

    goButton = new QPushButton(tr("Go"));
    QObject::connect(goButton, SIGNAL(clicked(bool)), this, SLOT(updateMemEdit()));
    navHelperLay->addWidget(showFrom);
    navHelperLay->addWidget(showStartAddress);
    navHelperLay->addWidget(goButton);

    mainLay->addWidget(navHelperW,0,Qt::AlignTop);
    this->setWidget(mainW);

    for(int i = 0;i < gridS*gridS;++i){
        addresses[i] = new QLabel(parent);
        values[i] = new QLineEdit(parent);
        values[i]->setInputMask(tr("HH"));
    }

    updateMemEdit();

    memLay->setSpacing(10);

    memWidget->setLayout(memLay);
    mainLay->addWidget(memWidget,0,Qt::AlignJustify);
}
void MemEditorDock::updateMemEdit(){
    showStartAddress->setDisabled(true);
    showStartAddress->setText(showStartAddress->text().toUpper());
    for(int i = 0;i < gridS * gridS;++i){
       if(base + i >= __8085->lowAddressLimit && base + i < __8085->upAddressLimit){
            disconnect(values[i], SIGNAL(textEdited(QString)), &__8085->cells[base + i - 0x2000], SLOT(cellChangedFromMemDock(QString)));
            disconnect(&__8085->cells[base + i - 0x2000], SIGNAL(cellChangedInternally(QString)), values[i], SLOT(setText(QString)));
        }
    }

    if(showStartAddress->text() == tr("")){
        showStartAddress->setText(numberToHex(base));
    }
    int newBase = hexToNumber(showStartAddress->text());
    if(newBase < __8085->lowAddressLimit || newBase >= __8085->upAddressLimit){
        showStartAddress->setText(numberToHex(base));
    } else{
        base = newBase;
    }
    for(int i = 0;i < gridS * gridS;++i){
        QString index = numberToHex(base + i);
        addresses[i]->setText(index.toUpper());
        if(base + i < __8085->lowAddressLimit || base + i >= __8085->upAddressLimit){
            values[i]->setText(tr("00"));
            values[i]->setDisabled(true);
        } else{
            bool ok;
            values[i]->setText(__8085->getValueAtCell(base + i, ok));
            connect(values[i], SIGNAL(textEdited(QString)), &__8085->cells[base + i - 0x2000], SLOT(cellChangedFromMemDock(QString)));
            connect(&__8085->cells[base + i - 0x2000], SIGNAL(cellChangedInternally(QString)), values[i], SLOT(setText(QString)));
            values[i]->setEnabled(true);
        }
        values[i]->setMaximumWidth(25);
        values[i]->setMaxLength(2);
        cells[i] = new QVBoxLayout;
        cells[i]->setSpacing(0);
        cells[i]->addWidget(values[i]);
        cells[i]->addWidget(addresses[i]);
        memLay->addLayout(cells[i],(i/gridS),i%gridS);
    }
    showStartAddress->setDisabled(false);
}
void MemEditorDock::freeze(){
    showStartAddress->setDisabled(true);
    goButton->setDisabled(true);
    for(int i = 0;i < gridS*gridS;++i){
        values[i]->setDisabled(true);
    }
}
void MemEditorDock::unfreeze(){
    showStartAddress->setDisabled(false);
    goButton->setDisabled(false);
    for(int i = 0;i < gridS*gridS;++i){
        if(base + i >= __8085->lowAddressLimit && base + i < __8085->upAddressLimit){
            values[i]->setDisabled(false);
        }
    }
}
void MemEditorDock::MCellChanged(QString str){
    str = str.toUpper().rightJustified(2, QLatin1Char('0'));
    int address = (__8085->H.toInt() << 8) + __8085->L.toInt();
    if(address >= __8085->lowAddressLimit && address < __8085->upAddressLimit){
        if(address >= base && address < base + gridS*gridS){
            values[address - base]->setText(str);
        }
    }
}
