#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QWidget>
#include <QTreeView>
#include <QStandardItem>
#include "libhw/gpu.h"

class TreeView: public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget *parent = nullptr);
    void init(GPUInfo& gpuinfo);
signals:
#ifdef DEV
    void sig_CPU_show(int idx);
#endif
    void sig_GPU_show(int idx);
    void sig_GPU_Monitor_show(int idx_GPU, int idx_monitor);
private:
    QStandardItemModel* model = nullptr;
    QStandardItem *cpu = nullptr;
    QStandardItem *gpu = nullptr;
    QStandardItem *mem = nullptr;
    QStandardItem *disk = nullptr;
    QStandardItem *disk_hard = nullptr;
    QStandardItem *disk_nvme = nullptr;

    QStandardItem *netcard = nullptr;
};

#endif // TREEVIEW_H
