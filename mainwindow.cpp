#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include "batch-modifier.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QBuffer>
#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->operationMode = OperationMode::SUBSTITUTE;
    this->changeOperationMode();
    this->initUiStyles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUiStyles() {
    ui->txtChangesLog->setStyleSheet(R"(
            QTextEdit {
                background-color: #f8f9fa; /* Light gray background */
                border: 1px solid #ccc; /* Soft border */
                border-radius: 8px; /* Rounded corners */
                padding: 10px; /* Inner spacing */
                font-family: "Courier New", monospace; /* Monospace for log feel */
                font-size: 11px;
                color: #333; /* Dark gray text */
            }
            QTextEdit::viewport {
                background-color: transparent; /* Ensure the viewport matches */
            }
        )");
        ui->currentPathContentList->setStyleSheet(R"(
            QListWidget {
                background-color: #f8f9fa; /* Light gray background */
                border: 1px solid #ccc; /* Soft border */
                border-radius: 8px; /* Rounded corners */
                padding: 5px;
                font-family: "Consolas", monospace;
                font-size: 11px;
                color: #333;
            }
            QListWidget::item {
                background: #ffffff;
                padding: 8px;
                border-bottom: 1px solid #ddd; /* Separator between items */
            }
            QListWidget::item:selected {
                background: #007bff; /* Highlighted selection */
                color: white;
                border-radius: 4px;
            }
            QListWidget::item:hover {
                background: #e9ecef; /* Light hover effect */
            }
        )");
}

void MainWindow::on_btnSelectFolder_clicked() {
    const QString selectedFolder = QFileDialog::getExistingDirectory(this, "Select Target Folder");
    if(!selectedFolder.isEmpty()) {
        ui->txtFolderPath->setText(selectedFolder);
        updateCurrentPathContents();
    }
}

void MainWindow::updateCurrentPathContents() {
    BatchModifier manager(this->ui->txtFolderPath->text());
    try {
        const auto contents = manager.fetchFilenames();
        ui->currentPathContentList->clear();
        QFileIconProvider iconProvider;
    //    ui->currentPathContentList->setIconSize(QSize(DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT));
        for(const auto &item: contents) {
            QListWidgetItem *itemView = new QListWidgetItem(
                resizeIcon(iconProvider.icon(QFileInfo(item))), item
            );
            ui->currentPathContentList->addItem(itemView);
        }
    } catch(const std::invalid_argument& ex) {
        QMessageBox::critical(this, "Error", ex.what());
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

QIcon MainWindow::resizeIcon(const QIcon &icon, const uint8_t targetWidth, const uint8_t targetHeight) {
    QSize iconSize(targetWidth, targetHeight);
    QPixmap pixmap = icon.pixmap(iconSize); // Force scaling
    pixmap = pixmap.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QIcon scaledIcon(pixmap); // Convert back to QIcon
    return scaledIcon;
}

QString MainWindow::iconToBase64(const QIcon &icon, const uint8_t width, const uint8_t height) const {
    QPixmap pixmap = icon.pixmap(width, height); // Convert QIcon to QPixmap
    QImage image = pixmap.toImage();
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    return QString("data:image/png;base64,") + byteArray.toBase64(); // Convert to Base64
}

void MainWindow::updateChangeLog(const QMap<QString, QString> changes) {
    ui->txtChangesLog->clear();
    QFileIconProvider iconProvider;

    QString changesLogContentHtml = "<h4 style='text-align:center;color: red;'>Changes Log</h4>";
    for(const auto &changedPair: changes.toStdMap()) {
        QIcon icon = iconProvider.icon(QFileInfo(changedPair.second));
        changesLogContentHtml += QString(
        "<hr><div style='display: flex; align-items: center; padding: 8px; "
        "border-left: 4px solid #007bff; margin-bottom: 4px;'>"
        "<img src='%1' width='24' height='24' style='vertical-align: middle; margin-right: 10px;'>"
        "<span>&nbsp;&nbsp;Renamed '<span style='color:coral;'>%2</span>' to '<span style='color:green;'>%3</span>'.</span>"
        "</div>"
        ).arg(iconToBase64(icon), changedPair.first, BatchModifier::getShortFilename(changedPair.second));

    }
    ui->txtChangesLog->setHtml(changesLogContentHtml);
}

void MainWindow::on_btnApply_clicked()
{

    try {
        const QString selectedPath = this->ui->txtFolderPath->text();
        if(selectedPath.trimmed().isEmpty())
            throw std::invalid_argument("No directory selected!");
        BatchModifier manager(selectedPath);
        QMap<QString, QString> changes;

        switch(this->operationMode) {
        // TODO: It seems that Qt entryList func returns short filename; So prepend and replace functions could be simpler
        case OperationMode::PREPEND:
        case OperationMode::APPEND: {
            const QString addingText = ui->txtPartialText->text();
            if(addingText.trimmed().isEmpty())
                throw std::invalid_argument("Additional text not specified!");

            changes = manager.batchExtend(addingText, this->operationMode == OperationMode::PREPEND);
            QMessageBox::information(this, "Success", "Applied Successfully!");
            break;
        }
        case OperationMode::SUBSTITUTE: {
            const QString patternText = ui->txtPartialText->text();
            if(patternText.isEmpty())
                 throw std::invalid_argument("Pattern text to replace, not specified!");

            const QString substituteText = ui->txtSubstitute->text();
            if(substituteText.isEmpty())
                throw std::invalid_argument("Substitute text not specified!");

            changes = manager.batchReplace(patternText, substituteText);
            QMessageBox::information(this, "Success", "Applied Successfully!");
            break;
        }
        default:
            throw std::out_of_range("Invalid Operation! Please select operation properly!");
        }
        if(!changes.empty()) {
            updateChangeLog(changes);
            updateCurrentPathContents();
        } else {
            QMessageBox::information(this, "Nothing Changed", "No changes happened!");
        }
    } catch(const std::invalid_argument& ex) {
        QMessageBox::warning(this, "Error", ex.what());
    } catch(const std::out_of_range& ex) {
        QMessageBox::critical(this, "Error", ex.what());
    } catch(const std::exception& ex) {
        QMessageBox::critical(this, "ERROR", QString("An unexpected error happened: ") + ex.what());
    }

}

void MainWindow::on_btnOperationMode_clicked()
{
    this->changeOperationMode();
}

void MainWindow::on_currentPathContentList_itemSelectionChanged()
{

}
