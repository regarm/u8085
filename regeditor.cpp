#include "regeditor.h"
#include "utils.h"
RegEditor::RegEditor(QString title, Internal8085
                     *__8085_temp, QWidget* parent) :
    QDockWidget(title, parent),
    A(new QLineEdit(parent)),
    B(new QLineEdit(parent)),
    C(new QLineEdit(parent)),
    D(new QLineEdit(parent)),
    E(new QLineEdit(parent)),
    F(new QLineEdit(parent)),
    H(new QLineEdit(parent)),
    L(new QLineEdit(parent)),
    M(new QLineEdit(parent)),
    PC(new QLineEdit(parent)),
    SP(new QLineEdit(parent)),
    __8085(__8085_temp)
{
    QVBoxLayout *mainLay = new QVBoxLayout();
    QWidget *mainW = new QWidget();

    int fieldMaxLen = 40;
    QVBoxLayout *regLay = new QVBoxLayout();
    regLay->setAlignment(Qt::AlignTop);

    //AF
    QHBoxLayout *AF = new QHBoxLayout();
    QLabel *labelA = new QLabel(parent);
    labelA -> setText(tr("A: "));
    AF -> addWidget(labelA);
    AF -> addWidget(A);
    A->setMaxLength(2);
    A->setMaximumWidth(fieldMaxLen);
    QLabel *labelF = new QLabel(parent);
    labelF -> setText(tr("F: "));
    AF -> addWidget(labelF);
    AF -> addWidget(F);
    F->setMaxLength(2);
    F->setMaximumWidth(fieldMaxLen);
    regLay -> addLayout(AF);

    //BC
    QHBoxLayout *BC = new QHBoxLayout();
    QLabel *labelB = new QLabel(parent);
    labelB -> setText(tr("B: "));
    BC -> addWidget(labelB);
    BC -> addWidget(B);
    B->setMaxLength(2);
    B->setMaximumWidth(fieldMaxLen);
    QLabel *labelC = new QLabel(parent);
    labelC -> setText(tr("C: "));
    BC -> addWidget(labelC);
    BC -> addWidget(C);
    C->setMaxLength(2);
    C->setMaximumWidth(fieldMaxLen);
    regLay -> addLayout(BC);

    //DE
    QHBoxLayout *DE = new QHBoxLayout();
    QLabel *labelD = new QLabel(parent);
    labelD -> setText(tr("D: "));
    DE -> addWidget(labelD);
    DE -> addWidget(D);
    D->setMaxLength(2);
    D->setMaximumWidth(fieldMaxLen);
    QLabel *labelE = new QLabel(parent);
    labelE -> setText(tr("E: "));
    DE -> addWidget(labelE);
    DE -> addWidget(E);
    E->setMaxLength(2);
    E->setMaximumWidth(fieldMaxLen);
    regLay -> addLayout(DE);

    //HL
    QHBoxLayout *HL = new QHBoxLayout();
    QLabel *labelH = new QLabel(parent);
    labelH -> setText(tr("H: "));
    HL -> addWidget(labelH);
    HL -> addWidget(H);
    H->setMaxLength(2);
    H->setMaximumWidth(fieldMaxLen);
    QLabel *labelL = new QLabel(parent);
    labelL -> setText(tr("L: "));
    HL -> addWidget(labelL);
    HL -> addWidget(L);
    L->setMaxLength(2);
    L->setMaximumWidth(fieldMaxLen);
    regLay -> addLayout(HL);

    QHBoxLayout *MLay = new QHBoxLayout();
    QLabel *labelM = new QLabel(parent);
    labelM -> setText(tr("M: "));
    MLay -> addWidget(labelM);
    MLay -> addWidget(M);
    M->setMaxLength(2);
    M->setMaximumWidth(fieldMaxLen);
    regLay -> addLayout(MLay);

    QHBoxLayout *PCLay = new QHBoxLayout();
    QLabel *labelPC = new QLabel(parent);
    labelPC -> setText(tr("PC:  "));
    PCLay -> addWidget(labelPC);
    PCLay -> addWidget(PC);
    PC->setMaxLength(4);
    PC->setMaximumWidth(2*fieldMaxLen);
    regLay -> addLayout(PCLay);

    QHBoxLayout *SPLay = new QHBoxLayout();
    QLabel *labelSP = new QLabel(parent);
    labelSP -> setText(tr("SP:  "));
    SPLay -> addWidget(labelSP);
    SPLay -> addWidget(SP);
    SP->setMaxLength(4);
    SP->setMaximumWidth(2*fieldMaxLen);
    regLay -> addLayout(SPLay);


    QObject::connect(A, SIGNAL(textEdited(QString)), &__8085->A, SLOT(regEditedFromRegDock_SLOT(QString)));
    QObject::connect(B, SIGNAL(textEdited(QString)), &__8085->B, SLOT(regEditedFromRegDock_SLOT(QString)));
    QObject::connect(C, SIGNAL(textEdited(QString)), &__8085->C, SLOT(regEditedFromRegDock_SLOT(QString)));
    QObject::connect(D, SIGNAL(textEdited(QString)), &__8085->D, SLOT(regEditedFromRegDock_SLOT(QString)));
    QObject::connect(E, SIGNAL(textEdited(QString)), &__8085->E, SLOT(regEditedFromRegDock_SLOT(QString)));
    QObject::connect(F, SIGNAL(textEdited(QString)), &__8085->F, SLOT(regFEditedFromRegDockFreg_SLOT(QString)));
    QObject::connect(H, SIGNAL(textEdited(QString)), &__8085->H, SLOT(regEditedFromRegDock_SLOT(QString)));
    QObject::connect(L, SIGNAL(textEdited(QString)), &__8085->L, SLOT(regEditedFromRegDock_SLOT(QString)));
    QObject::connect(PC, SIGNAL(textEdited(QString)), &__8085->PC, SLOT(regEditedFromRegDock_SLOT(QString)));
    QObject::connect(SP, SIGNAL(textEdited(QString)), &__8085->SP, SLOT(regEditedFromRegDock_SLOT(QString)));

    QObject::connect(&__8085->H, SIGNAL(regEditedInternally_SIG(QString)), this, SLOT(HLChanged()));
    QObject::connect(&__8085->L, SIGNAL(regEditedInternally_SIG(QString)), this, SLOT(HLChanged()));
    QObject::connect(&__8085->H, SIGNAL(regEditedFromRegDock_SIG(QString)), this, SLOT(HLChanged()));
    QObject::connect(&__8085->L, SIGNAL(regEditedFromRegDock_SIG(QString)), this, SLOT(HLChanged()));

    QObject::connect(&__8085->A, SIGNAL(regEditedInternally_SIG(QString)), A, SLOT(setText(QString)));
    QObject::connect(&__8085->B, SIGNAL(regEditedInternally_SIG(QString)), B, SLOT(setText(QString)));
    QObject::connect(&__8085->C, SIGNAL(regEditedInternally_SIG(QString)), C, SLOT(setText(QString)));
    QObject::connect(&__8085->D, SIGNAL(regEditedInternally_SIG(QString)), D, SLOT(setText(QString)));
    QObject::connect(&__8085->E, SIGNAL(regEditedInternally_SIG(QString)), E, SLOT(setText(QString)));
    QObject::connect(&__8085->F, SIGNAL(regFEditedFromRegDockFlags_SIG(QString)), F, SLOT(setText(QString)));
    QObject::connect(&__8085->F, SIGNAL(regEditedInternally_SIG(QString)), F, SLOT(setText(QString)));
    QObject::connect(&__8085->H, SIGNAL(regEditedInternally_SIG(QString)), H, SLOT(setText(QString)));
    QObject::connect(&__8085->L, SIGNAL(regEditedInternally_SIG(QString)), L, SLOT(setText(QString)));
    QObject::connect(&__8085->PC, SIGNAL(regEditedInternally_SIG(QString)), PC,SLOT(setText(QString)));
    QObject::connect(&__8085->SP, SIGNAL(regEditedInternally_SIG(QString)), SP,SLOT(setText(QString)));


    //flags
    QVBoxLayout *flagBox = new QVBoxLayout();
    flagBox->setAlignment(Qt::AlignTop);
    QHBoxLayout *flagHeadLay = new QHBoxLayout();

    int flagFieldLen = 20;

    QLabel *flagHeading = new QLabel(tr("Flags"));
    flagHeadLay->addWidget(flagHeading);

    QHBoxLayout *flagLay = new QHBoxLayout();
    QVBoxLayout *v[8];
    for(int i = 0;i < 8;++i){
        v[i] = new QVBoxLayout();
    }

    //0 sign flag
    QLabel *labelFlagS = new QLabel(tr("S"));
    flagS = new QLineEdit(parent);
    v[0]->addWidget(labelFlagS);
    v[0]->addWidget(flagS);
    flagLay->addLayout(v[0]);

    //1 zero flag
    QLabel *labelFlagZ = new QLabel(tr("Z"));
    flagZ = new QLineEdit(parent);
    v[1]->addWidget(labelFlagZ);
    v[1]->addWidget(flagZ);
    flagLay->addLayout(v[1]);

    //2 no flag
    QLabel *labelFlagNo1 = new QLabel(tr(" "));
    QLineEdit *flagNo1 = new QLineEdit(parent);
    v[2]->addWidget(labelFlagNo1);
    v[2]->addWidget(flagNo1);
    flagLay->addLayout(v[2]);

    //3 AC flag
    QLabel *labelFlagAC = new QLabel(tr("AC"));
    flagAC = new QLineEdit(parent);
    v[3]->addWidget(labelFlagAC);
    v[3]->addWidget(flagAC);
    flagLay->addLayout(v[3]);

    //4 no flag
    QLabel *labelFlagNo2 = new QLabel(tr(" "));
    QLineEdit *flagNo2 = new QLineEdit(parent);
    v[4]->addWidget(labelFlagNo2);
    v[4]->addWidget(flagNo2);
    flagLay->addLayout(v[4]);

    //5 P flag
    QLabel *labelFlagP = new QLabel(tr("P"));
    flagP = new QLineEdit(parent);
    v[5]->addWidget(labelFlagP);
    v[5]->addWidget(flagP);
    flagLay->addLayout(v[5]);

    //6 no flag
    QLabel *labelFlagNo3 = new QLabel(tr(" "));
    QLineEdit *flagNo3 = new QLineEdit(parent);
    v[6]->addWidget(labelFlagNo3);
    v[6]->addWidget(flagNo3);
    flagLay->addLayout(v[6]);

    //7 c flag
    QLabel *labelFlagC = new QLabel(tr("C"));
    flagC = new QLineEdit(parent);
    v[7]->addWidget(labelFlagC);
    v[7]->addWidget(flagC);
    flagLay->addLayout(v[7]);


    flagS->setMaxLength(1);
    flagS->setMaximumWidth(flagFieldLen);
    flagS->setInputMask(tr("B"));

    flagZ->setMaxLength(1);
    flagZ->setMaximumWidth(flagFieldLen);
    flagZ->setInputMask(tr("B"));

    flagP->setMaxLength(1);
    flagP->setMaximumWidth(flagFieldLen);
    flagP->setInputMask(tr("B"));

    flagAC->setMaxLength(1);
    flagAC->setMaximumWidth(flagFieldLen);
    flagAC->setInputMask(tr("B"));

    flagC->setMaxLength(1);
    flagC->setMaximumWidth(flagFieldLen);
    flagC->setInputMask(tr("B"));

    flagNo1 ->setMaxLength(1);
    flagNo1 ->setMaximumWidth(flagFieldLen);
    flagNo1->setDisabled(true);

    flagNo2 ->setMaxLength(1);
    flagNo2 ->setMaximumWidth(flagFieldLen);
    flagNo2->setDisabled(true);

    flagNo3 ->setMaxLength(1);
    flagNo3 ->setMaximumWidth(flagFieldLen);
    flagNo3->setDisabled(true);

    QObject::connect(flagS, SIGNAL(textEdited(QString)), __8085, SLOT(setFlagSFromOutside(QString)));
    QObject::connect(flagP, SIGNAL(textEdited(QString)), __8085, SLOT(setFlagPFromOutside(QString)));
    QObject::connect(flagZ, SIGNAL(textEdited(QString)), __8085, SLOT(setFlagZFromOutside(QString)));
    QObject::connect(flagAC, SIGNAL(textEdited(QString)), __8085, SLOT(setFlagACFromOutside(QString)));
    QObject::connect(flagC, SIGNAL(textEdited(QString)), __8085, SLOT(setFlagCFromOutside(QString)));

    QObject::connect(&__8085->F, SIGNAL(regFEditedFromRegDockFreg_SIG(QString)), this, SLOT(setFlags(QString)));
    QObject::connect(&__8085->F, SIGNAL(regEditedInternally_SIG(QString)), this, SLOT(setFlags(QString)));



    flagBox->addLayout(flagHeadLay);
    flagBox->addLayout(flagLay);


    mainLay->addLayout(regLay);
    mainLay->addLayout(flagBox);

    mainW -> setLayout(mainLay);
    this->setWidget(mainW);
    updateContents();
}
void RegEditor::updateContents(){
    if(__8085->getFlagAC()){
        flagAC->setText(tr("1"));
    } else flagAC->setText(tr("0"));

    if(__8085->getFlagS()){
        flagS->setText(tr("1"));
    } else flagS->setText(tr("0"));

    if(__8085->getFlagZ()){
        flagZ->setText(tr("1"));
    } else flagZ->setText(tr("0"));

    if(__8085->getFlagP()){
        flagP->setText(tr("1"));
    } else flagP->setText(tr("0"));

    if(__8085->getFlagC()){
        flagC->setText(tr("1"));
    } else flagC->setText(tr("0"));

    A->setText(__8085->A.toString());
    B->setText(__8085->B.toString());
    C->setText(__8085->C.toString());
    D->setText(__8085->D.toString());
    E->setText(__8085->E.toString());
    F->setText(__8085->F.toString());
    H->setText(__8085->H.toString());
    L->setText(__8085->L.toString());
    previousHL = ((__8085->H.toInt()) << 8) + __8085->L.toInt();
    PC->setText(__8085->PC.toString());
    SP->setText(__8085->SP.toString());
}
void RegEditor::freeze(){
    A->setDisabled(true);
    B->setDisabled(true);
    C->setDisabled(true);
    D->setDisabled(true);
    E->setDisabled(true);
    F->setDisabled(true);
    H->setDisabled(true);
    L->setDisabled(true);
    M->setDisabled(true);
    PC->setDisabled(true);
    SP->setDisabled(true);

    flagC->setDisabled(true);
    flagAC->setDisabled(true);
    flagP->setDisabled(true);
    flagZ->setDisabled(true);
    flagS->setDisabled(true);

}
void RegEditor::unfreeze(){
    A->setDisabled(false);
    B->setDisabled(false);
    C->setDisabled(false);
    D->setDisabled(false);
    E->setDisabled(false);
    F->setDisabled(false);
    H->setDisabled(false);
    L->setDisabled(false);
    M->setDisabled(false);
    PC->setDisabled(false);
    SP->setDisabled(false);

    flagC->setDisabled(false);
    flagAC->setDisabled(false);
    flagP->setDisabled(false);
    flagZ->setDisabled(false);
    flagS->setDisabled(false);
}
void RegEditor::setFlags(QString str){
    int val = hexToNumber(str);
    if(val&0x01){
        flagC->setText(tr("1"));
    } else{
        flagC->setText(tr("0"));
    }
    if(val&0x04){
        flagP->setText(tr("1"));
    } else{
        flagP->setText(tr("0"));
    }
    if(val&0x10){
        flagAC->setText(tr("1"));
    } else{
        flagAC->setText(tr("0"));
    }
    if(val&0x40){
        flagZ->setText(tr("1"));
    } else{
        flagZ->setText(tr("0"));
    }
    if(val&0x80){
        flagS->setText(tr("1"));
    } else{
        flagS->setText(tr("0"));
    }

}
void RegEditor::HLChanged(){
    bool ok;
    M->setText(__8085->getValueOfM(ok));
    M->setDisabled(!ok);
}
void RegEditor::MCellChanged(QString str){
    str = str.toUpper().rightJustified(2, QLatin1Char('0'));
    M->setText(str);
}
