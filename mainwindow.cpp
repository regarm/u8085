#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentFileName(tr(""))
{
    ui->setupUi(this);
    setWindowTitle(QString(tr("%1[*] - %2").arg(tr("untitled")).arg(tr("u8085"))));
    documentWidget = new QTextEdit();
    setCentralWidget(documentWidget);

    connect(documentWidget->document(), SIGNAL(modificationChanged(bool)), this, SLOT(setWindowModified(bool)));

    createActions();
    createMenus();
    createToolbars();
    createDocks();
    statusBar()->showMessage(tr("done"));

    connect(regDock->M, SIGNAL(textEdited(QString)), memDock, SLOT(MCellChanged(QString)));
    connect(regDock->M, SIGNAL(textEdited(QString)),&__8085, SLOT(MCellChanged(QString)));
    connect(&__8085.H, SIGNAL(regEditedInternally_SIG(QString)), this, SLOT(HLChanged()));
    connect(&__8085.L, SIGNAL(regEditedInternally_SIG(QString)), this, SLOT(HLChanged()));
    connect(&__8085.H, SIGNAL(regEditedFromRegDock_SIG(QString)), this, SLOT(HLChanged()));
    connect(&__8085.L, SIGNAL(regEditedFromRegDock_SIG(QString)), this, SLOT(HLChanged()));
    previousHL = (__8085.H.toInt() << 8) + __8085.L.toInt();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions(){
    newFileAction = new QAction(tr("&New"), this);
    newFileAction->setShortcut(QKeySequence::New);
    newFileAction->setStatusTip(tr("Create a new file"));
    connect(newFileAction, SIGNAL(triggered()), this, SLOT(newFile()));

    openFileInNewWindowAction = new QAction(tr("&Open in new window"), this);
    openFileInNewWindowAction -> setShortcut(QKeySequence::Open);
    openFileInNewWindowAction -> setStatusTip(tr("Open in new window"));
    connect(openFileInNewWindowAction, SIGNAL(triggered(bool)), this, SLOT(fileOpenInNewWindow()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction -> setShortcut(QKeySequence::Save);
    saveAction -> setStatusTip(tr("Save current document"));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(saveDoc()));

    saveAsAction = new QAction(tr("&Save &as"), this);
    saveAsAction -> setShortcut(QKeySequence::SaveAs);
    saveAsAction -> setStatusTip(tr("Save current document with differnt file name"));
    connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveAsDoc()));

    exitAction = new QAction(tr("&Close"), this);
    exitAction -> setShortcut(QKeySequence::Close);
    exitAction -> setStatusTip(tr("Close"));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(exit()));

    undoAction = new QAction(tr("&Undo"), this);
    undoAction -> setShortcut(QKeySequence::Undo);
    undoAction -> setStatusTip(tr("Undo"));
    connect(undoAction, SIGNAL(triggered(bool)), documentWidget->document(), SLOT(undo()));

    redoAction = new QAction(tr("&Redo"), this);
    redoAction -> setShortcut(QKeySequence::Redo);
    redoAction -> setStatusTip(tr("Redo"));
    connect(redoAction, SIGNAL(triggered(bool)), documentWidget->document(), SLOT(redo()));

    cutAction = new QAction(tr("&Cut"), this);
    cutAction -> setShortcut(QKeySequence::Cut);
    cutAction -> setStatusTip(tr("Cut selected text"));
//    connect(cutAction, SIGNAL(triggered(bool)), documentWidget->document(), SLOT());

    copyAction = new QAction(tr("&Copy"), this);
    copyAction -> setShortcut(QKeySequence::Copy);
    copyAction -> setStatusTip(tr("Copy"));
//    connect(undoAction, SIGNAL(triggered(bool)), documentWidget->document(), SLOT(undo()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction -> setShortcut(QKeySequence::Paste);
    pasteAction -> setStatusTip(tr("Undo"));
//    connect(undoAction, SIGNAL(triggered(bool)), documentWidget->document(), SLOT(undo()));



    assembleAction = new QAction(tr("&Assemble"), this);
    assembleAction -> setShortcut(tr("Ctrl+B"));
    assembleAction -> setStatusTip(tr("Assemble program"));
    connect(assembleAction, SIGNAL(triggered(bool)), this, SLOT(assemble()));

    assembleAndRunAction = new QAction(tr("&Assemble and run"), this);
    assembleAndRunAction -> setShortcut(tr("Ctrl+Shift+B"));
    assembleAndRunAction -> setStatusTip(tr("Assemble and run program"));
    connect(assembleAndRunAction, SIGNAL(triggered(bool)), this, SLOT(assembleAndRun()));

    runAction = new QAction(tr("&Run"), this);
    runAction -> setShortcut(tr("Ctrl+R"));
    runAction -> setStatusTip(tr("Run"));
    connect(runAction, SIGNAL(triggered(bool)), this, SLOT(runAt2000()));

    singleStepingAction = new QAction(tr("Single Steping"), this);
    singleStepingAction -> setStatusTip(tr("Single Steping"));
    connect(singleStepingAction,SIGNAL(triggered(bool)), this, SLOT(singleSteping()));

    nextAction = new QAction(tr("Next"), this);
    nextAction -> setStatusTip(tr("Ahead to next Instruction"));
    connect(nextAction, SIGNAL(triggered(bool)), this, SLOT(next()));

    previousAction = new QAction(tr("Previous"), this);
    previousAction -> setStatusTip(tr("Go one Instruction back"));
    connect(previousAction, SIGNAL(triggered(bool)), this, SLOT(previous()));

//    QIcon docNewIcon;
//    docNewIcon.addFile(tr(":/icons/document_icon&16.png"),QSize(16,16));
//    docNewIcon.addFile(tr(":/icons/document_icon&24.png"),QSize(24,24));
//    docNewIcon.addFile(tr(":/icons/document_icon&32.png"),QSize(32,32));
//    docNewIcon.addFile(tr(":/icons/document_icon&48.png"),QSize(48,48));
//    newAction->setIcon(docNewIcon);
}
void MainWindow::createMenus(){
    QMenu *menu;
    menu = menuBar()->addMenu(tr("&File"));
    menu->addAction(newFileAction);
    menu->addAction(openFileInNewWindowAction);
    menu->addAction(saveAction);
    menu->addAction(saveAsAction);
    menu->addAction(exitAction);

    menu = menuBar()->addMenu(tr("&Edit"));
    menu->addAction(undoAction);
    menu->addAction(redoAction);
    menu->addAction(cutAction);
    menu->addAction(copyAction);
    menu->addAction(pasteAction);

    menu = menuBar()->addMenu(tr("Build"));
    menu->addAction(assembleAction);
    menu->addAction(runAction);
    menu->addAction(assembleAndRunAction);

    menu = menuBar()->addMenu(tr("Debug"));
    menu->addAction(singleStepingAction);
    menu->addAction(nextAction);
    menu->addAction(previousAction);

}

void MainWindow::createToolbars(){
    QToolBar *toolBar;
    toolBar = addToolBar(tr("File"));
    toolBar->addAction(newFileAction);
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(isSafeToClose()){
        event->accept();
    } else{
        event->ignore();
    }
}

bool MainWindow::isSafeToClose(){
    if(isWindowModified()){
        switch(QMessageBox::warning(this, tr("u8085"),
                tr("This Docment have unsaved changes.\n"
                   "Do you want to save it before closed?"),
                QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel)){
            case QMessageBox::Cancel:
                return false;
            case QMessageBox::Save:
                return saveDoc();
            default:
                return true;
        }
    }
    return true;
}
void MainWindow::createDocks(){
    log = new logDock(tr("Logs"), this);
    addDockWidget(Qt::BottomDockWidgetArea, log);

    memDock = new MemEditorDock(tr("Memory Editor"),&__8085,this);
    addDockWidget(Qt::RightDockWidgetArea, memDock);
    memDock->setStyleSheet(tr("QDockWidget > QWidget {border : 1px solid black}"));

    regDock = new RegEditor(tr("Register Editor"), &__8085, this);
    addDockWidget(Qt::LeftDockWidgetArea, regDock);

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void MainWindow::newFile(){
    if(!currentFileName.isEmpty())
        (new MainWindow())->show();
}
void MainWindow::fileOpenInNewWindow(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Document"),
                                                    tr("."),
                                                    tr("u8085 files (*.u8085)\n"
                                                       "All files (*)")
                                                    );
    if(fileName.isEmpty()){
        return ;
    } else if(currentFileName.isEmpty() && !documentWidget->document()->isModified()){
        loadFile(fileName);
    } else{
        MainWindow *nw = new MainWindow();
        nw->loadFile(fileName);
        nw->show();
    }
}
void MainWindow::loadFile(const QString& fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(this,tr("File opening error"),tr("Failed to open file."));
        return ;
    }
    QTextStream stream(&file);
    documentWidget->document()->setPlainText(stream.readAll());
    currentFileName = fileName;
    documentWidget->document()->setModified(false);
    setWindowTitle(tr("%1[*] - %2").arg(fileName).arg(tr("u8085")));
}
bool MainWindow::saveFile(const QString& fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this, tr("File saving error"), tr("Failed to save file."));
        return false;
    }
    QTextStream stream(&file);
    stream << documentWidget->document()->toPlainText();
    currentFileName = fileName;
    documentWidget->document()->setModified(false);
    setWindowTitle(tr("%1[*] - %2").arg(fileName).arg(tr("u8085")));
    return true;
}

bool MainWindow::saveDoc(){
    if(!documentWidget->document()->isModified()){
        return true;
    }
    if(currentFileName.isEmpty()){
        return saveAsDoc();
    } else{
        return saveFile(currentFileName);
    }
}
bool MainWindow::saveAsDoc(){
    QFileDialog *myFileDialog = new QFileDialog(this);
    myFileDialog->setDefaultSuffix(tr(".u8085"));
    QString fileName = myFileDialog->getSaveFileName(this,
                                                    tr("Save Document"),
                                                    QDir::currentPath(),
                                                    tr("u8085 files (*.u8085)\n"
                                                       "All files (*)")
                                                    );
    if(fileName.isEmpty()){
        return false;
    }
    return saveFile(fileName);
}
void MainWindow::exit(){
    QApplication::exit();
}
void MainWindow::singleSteping(){}
void MainWindow::next(){}
void MainWindow::previous(){}
void MainWindow::HLChanged(){
    if(previousHL >= __8085.lowAddressLimit && previousHL < __8085.upAddressLimit){
        disconnect(&__8085.cells[previousHL - __8085.lowAddressLimit], SIGNAL(cellChangedInternally_SIG(QString)), regDock->M,SLOT(setText(QString)));
        if(previousHL >= memDock->base && previousHL < memDock->base + memDock->gridS*memDock->gridS){
            disconnect(memDock->values[previousHL - memDock->base], SIGNAL(textEdited(QString)), regDock->M,SLOT(setText(QString)));
        }
    }
    previousHL = (__8085.H.toInt() << 8) + __8085.L.toInt();
    if(previousHL >= __8085.lowAddressLimit && previousHL < __8085.upAddressLimit){
        connect(&__8085.cells[previousHL - __8085.lowAddressLimit], SIGNAL(cellChangedInternally_SIG(QString)), regDock->M,SLOT(setText(QString)));
        if(previousHL >= memDock->base && previousHL < memDock->base + memDock->gridS*memDock->gridS){
            connect(memDock->values[previousHL - memDock->base], SIGNAL(textEdited(QString)), regDock->M,SLOT(setText(QString)));
        }
    }
}
