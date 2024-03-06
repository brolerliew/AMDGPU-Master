#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QTimer>
#include <QProgressBar>
#include <QMap>
#include <QGroupBox>
#include <QGridLayout>
#include "libhw/gpu.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void status_groupBoxUpdate(QGridLayout* parent_layout, HardwareStatus_per* status);
    void infos_create(QWidget* parent, QString prefix);
    GPUInfo gpuinfo;
    Ui::MainWindow *ui;
    QTimer* timer;
    GPUInfo_per* gpu_info_now_ = nullptr;
};
#endif // MAINWINDOW_H
