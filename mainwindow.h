#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdint.h>
#include <QMap>

#define DEFAULT_ICON_WIDTH 24
#define DEFAULT_ICON_HEIGHT 24
#define OPERATIONS_COUNT 3

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum OperationMode {
    PREPEND = 0,
    APPEND,
    SUBSTITUTE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeOperationMode();
    void updateCurrentPathContents();
    void initUiStyles();
    QIcon resizeIcon(const QIcon &icon, const uint8_t targetWidth = DEFAULT_ICON_WIDTH, const uint8_t targetHeight = DEFAULT_ICON_HEIGHT);
    void updateChangeLog(const QMap<QString, QString> changes);
    QString iconToBase64(const QIcon &icon, const uint8_t width = DEFAULT_ICON_WIDTH, const uint8_t height = DEFAULT_ICON_HEIGHT) const;
private slots:
    void on_btnSelectFolder_clicked();

    void on_btnApply_clicked();

    void on_btnOperationMode_clicked();

    void on_currentPathContentList_itemSelectionChanged();
private:
    Ui::MainWindow *ui;
    OperationMode operationMode;
};
#endif // MAINWINDOW_H
