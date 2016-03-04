#ifndef REGISTER_H
#define REGISTER_H
#include <QBitArray>
#include <QString>
#include <QDebug>
#include <inttypes.h>
#include <QObject>
 class Register : public QObject, public QBitArray
{
     Q_OBJECT
public:
    Register();
    Register(uint8_t);
    Register(const QString&);

    void setValue(const QString&);
    void setValue(int);

    QString toString();
    uint64_t toInt();
public slots:
//    void registerEdited(QString);
    void regFEditedFromRegDockFreg_SLOT(QString);
    void regEditedFromRegDock_SLOT(QString);
    void cellChangedFromMemDock(QString);
signals:
//    void registerChanged(QString);
//    void registerFChanged(QString);
    void regEditedInternally_SIG(QString);
    void regEditedFromRegDock_SIG(QString);
    void regFEditedFromRegDockFreg_SIG(QString);
    void regFEditedFromRegDockFlags_SIG(QString);
    void cellChangedInternally(QString);
};

#endif // REGISTER_H
