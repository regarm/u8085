#ifndef LOGDOCK_H
#define LOGDOCK_H
#include <QDockWidget>
#include <QTextEdit>
class logDock : public QDockWidget
{
public:
    logDock(QString, QWidget *parent = 0);

    QTextEdit *logBase;
    const static int Normal = 0;
    const static int Success = 1;
    const static int Error = 2;
    const static int Redacted = 3;
    const static int Init = 4;
    const static int Ins = 5;
    int cnt;
    void appendLog(QString, int mark = 0);
    void setRedacted();
    QString NormalColor;
    QString RedactedColor;
    QString SuccessColor;
    QString ErrorColor;
    QString InitColor;

};

#endif // LOGDOCK_H
