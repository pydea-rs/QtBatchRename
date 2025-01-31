#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->operationMode = OperationMode::SUBSTITUE;
    this->changeOperationMode();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSelectFolder_clicked()
{
    const QString selectedFolder = QFileDialog::getExistingDirectory(this, "Select Target Folder");
    if(!selectedFolder.isEmpty()) {
        ui->txtFolderPath->setText(selectedFolder);
    }
}

void MainWindow::changeOperationMode() {
    this->operationMode = static_cast<OperationMode>((this->operationMode + 1) % OPERATIONS_COUNT);
    switch(this->operationMode) {
    case OperationMode::PREPEND:
        ui->btnOperationMode->setText("Prepend");
        ui->btnOperationMode->setStyleSheet("QToolButton { background-color: orange; }");
        break;
    case OperationMode::APPEND:
        ui->btnOperationMode->setText("Append");
        ui->btnOperationMode->setStyleSheet("QToolButton { background-color: yellow; }");
        break;
    default:
        ui->btnOperationMode->setText("Subsitute");
        ui->btnOperationMode->setStyleSheet("QToolButton { background-color: red; }");
        break;
    }
    ui->txtSubstitute->setEnabled(this->operationMode == OperationMode::SUBSTITUE);
}

void MainWindow::on_btnApply_clicked()
{
    // TODO:
}

void MainWindow::on_btnOperationMode_clicked()
{
    this->changeOperationMode();
}
