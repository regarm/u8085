#include "logdock.h"
#include <QDebug>
#include <QScrollBar>
logDock::logDock(QString title, QWidget *parent):
    QDockWidget(title, parent),
    logBase(new QTextEdit(parent)),
    cnt(0)
{
    this->setWidget(logBase);
    logBase->setReadOnly(true);

    QFont *font = new QFont(tr("Helvetica"));
    font->setPixelSize(12);
    font->setBold(true);
    logBase->setFont(*font);

    NormalColor = tr("#0000FF");
    ErrorColor = tr("#FF0000");
    RedactedColor = tr("#808080");
    SuccessColor = tr("#008000");
    InitColor = tr("#FFA500");
}
void logDock::appendLog(QString val, int mark){
    QString tab = tr("&nbsp;&nbsp;&nbsp;&nbsp;");
    tab += tab;
    switch(mark){
        case logDock::Error:
            logBase->insertHtml(tr("<span style=\"color:%1\">%2%3</span><br></br>").arg(ErrorColor).arg(tab).arg(val));
            break;
        case logDock::Success:
            logBase->insertHtml(tr("<span style=\"color:%1\">%2%3</span><br></br>").arg(SuccessColor).arg(tab).arg(val));
            break;
        case logDock::Redacted:
            logBase->setHtml(tr("<p style=\"color:%1\">%2</p><br></br>").arg(RedactedColor).arg(val));
            break;
        case logDock::Init:
            logBase->insertHtml(tr("<br></br><span style=\"color:%1\">%2........Go</span><br></br>").arg(InitColor).arg(val));
            break;
        case logDock::Ins:
            logBase->insertHtml(tr("<span style=\"color:%1;padding-left:16em\">%2%3</span><br></br>").arg(NormalColor).arg(tab).arg(val));
        break;
        case logDock::Normal:
        default:
            logBase->insertHtml(tr("<span style=\"color:%1\">%2</span><br></br>").arg(NormalColor).arg(val));
    }
    logBase->verticalScrollBar()->setValue(logBase->verticalScrollBar()->maximum());
}
void logDock::setRedacted(){
    QString data = logBase->toHtml();
    data.replace(NormalColor, RedactedColor, Qt::CaseInsensitive);
    data.replace(ErrorColor, RedactedColor, Qt::CaseInsensitive);
    data.replace(SuccessColor, RedactedColor, Qt::CaseInsensitive);
    data.replace(InitColor, RedactedColor, Qt::CaseInsensitive);
    logBase->clear();
    logBase->setHtml(data);
    logBase->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}
