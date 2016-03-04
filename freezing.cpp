#include "mainwindow.h"

void MainWindow::assembleFreeze(){
    log->setRedacted();
    regDock->freeze();
    memDock->freeze();
}
void MainWindow::assembleUnfreeze(){
    regDock->unfreeze();
    memDock->unfreeze();
}
void MainWindow::runFreeze(){
    log->setRedacted();
    regDock->freeze();
    memDock->freeze();
}
void MainWindow::runUnfreeze(){
    regDock->unfreeze();
    memDock->unfreeze();
}
