#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include "batch-modifier.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->operationMode = OperationMode::SUBSTITUTE;
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
    ui->txtSubstitute->setEnabled(this->operationMode == OperationMode::SUBSTITUTE);
}

void MainWindow::on_btnApply_clicked()
{
    BatchModifier manager(this->ui->txtFolderPath->text());
    switch(this->operationMode) {
    // TODO: Add error handling esp on input mismatch!

    // TODO: It seems that Qt entryList func returns short filename; So prepend and replace functions could be simpler
    case OperationMode::PREPEND:
    case OperationMode::APPEND:
        manager.batchExtend(ui->txtPartialText->text(), this->operationMode == OperationMode::PREPEND);
        QMessageBox::information(this, "Success", "Applied Successfully!");
        break;
    case OperationMode::SUBSTITUTE:
        manager.batchReplace(ui->txtPartialText->text(), ui->txtSubstitute->text());
        QMessageBox::information(this, "Success", "Applied Successfully!");
        break;
    default:
        QMessageBox::critical(this, "Error!", "Invalid Operation! Please select operation properly!");
        break;
    }
}

void MainWindow::on_btnOperationMode_clicked()
{
    this->changeOperationMode();
}
