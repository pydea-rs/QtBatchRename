#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define OPERATIONS_COUNT 3

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum OperationMode {
    PREPEND = 0,
    APPEND,
    SUBSTITUE
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeOperationMode();
private slots:
    void on_btnSelectFolder_clicked();

    void on_btnApply_clicked();

    void on_btnOperationMode_clicked();

private:
    Ui::MainWindow *ui;
    OperationMode operationMode;
};
#endif // MAINWINDOW_H
