#ifndef MEMEDITORDOCK_H
#define MEMEDITORDOCK_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QRegExpValidator>
#include "internal8085.h"


class MemEditorDock : public QDockWidget
{
    Q_OBJECT
public:
    MemEditorDock(QString,Internal8085 *__8085 = 0, QWidget *parent = 0);
private:
    QVBoxLayout *cells[100];
    QWidget *memWidget;
    int base;
    QLineEdit *showStartAddress;
    QGridLayout *memLay;
    Internal8085 *__8085;
    const static int gridS = 8;
    QLabel *addresses[gridS * gridS];
    QLineEdit *values[gridS * gridS];
    QPushButton *goButton;
public:
    void freeze();
    void unfreeze();
signals:
    void MCellEdited(QString);
public slots:
    void updateMemEdit();
    void MCellChanged(QString);
    void checkForMCell();
};

#endif // MEMEDITORDOCK_H
