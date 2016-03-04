#ifndef REGEDITOR_H
#define REGEDITOR_H

#include <QDockWidget>
#include <QLineEdit>
#include <QLayout>
#include <QLabel>
#include <QSizePolicy>
#include "internal8085.h"

class RegEditor : public QDockWidget
{
    Q_OBJECT
public:
    RegEditor(QString title, Internal8085 *__8085 = 0, QWidget* parent = 0);
    QLineEdit *A;
    QLineEdit *B;
    QLineEdit *C;
    QLineEdit *D;
    QLineEdit *E;
    QLineEdit *F;
    QLineEdit *H;
    QLineEdit *L;
    QLineEdit *M;
    QLineEdit *PC;
    QLineEdit *SP;

    QLineEdit *flagC, *flagAC, *flagP, *flagS, *flagZ;
    Internal8085 *__8085;
public:
    void freeze();
    void unfreeze();

public slots:
    void updateContents();
    void setFlags(QString);
    void HLChanged();
    void MCellChanged(QString);
};

#endif // REGEDITOR_H
