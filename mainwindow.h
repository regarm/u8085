#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QAction>
#include <QToolBar>
#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>
#include <QIcon>
#include <QDockWidget>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>
#include <QDebug>
#include <QMap>
#include "internal8085.h"
#include "memeditordock.h"
#include "regeditor.h"
#include "logdock.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createActions();
    void createToolbars();
    void createMenus();
    void closeEvent(QCloseEvent *);
    bool isSafeToClose();
    void createDocks();
    bool labelVerify(QString &);
    bool synCheck(QString&);
    Internal8085 __8085;
    MemEditorDock *memDock;
    RegEditor *regDock;
    logDock *log;
    QMap<QString, bool> labelExists;
    QMap<QString, int> labelAddressMap;

    void genOpcodes(QString& );
    void assembleFreeze();
    void assembleUnfreeze();
    void runFreeze();
    void runUnfreeze();

public slots:
    void newFile();
    void fileOpenInNewWindow();
    bool saveDoc();
    bool saveAsDoc();
    void exit();

    void loadFile(const QString& );
    bool saveFile(const QString& );

    bool assemble();
    bool assembleAndRun();
    bool runAt2000();

    void singleSteping();
    void next();
    void previous();
private:
    Ui::MainWindow *ui;
    QAction *newFileAction;
    QAction *openFileInNewWindowAction;
    QAction *saveAction;
    QAction *saveAsAction;
    QAction *exitAction;

    QAction *undoAction;
    QAction *redoAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;

    QAction *assembleAction;
    QAction *runAction;
    QAction *assembleAndRunAction;

    QAction *singleStepingAction;
    QAction *nextAction;
    QAction *previousAction;
    QString currentFileName;
    QTextEdit *documentWidget;
};

#endif // MAINWINDOW_H
