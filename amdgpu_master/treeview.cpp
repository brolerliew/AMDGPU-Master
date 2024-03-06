#include "treeview.h"
void TreeView::init(GPUInfo& gpuinfo){
    gpu = new QStandardItem("显卡");
    gpu->setFlags(gpu->flags() & ~Qt::ItemIsEditable);
#ifdef DEV
    cpu = new QStandardItem("CPU");
    cpu->setFlags(cpu->flags() & ~Qt::ItemIsEditable);
    mem = new QStandardItem("系统内存");
    mem->setFlags(mem->flags() & ~Qt::ItemIsEditable);
    disk = new QStandardItem("硬盘");
    disk->setFlags(disk->flags() & ~Qt::ItemIsEditable);
    disk_hard = new QStandardItem("磁盘");
    disk_hard->setFlags(disk_hard->flags() & ~Qt::ItemIsEditable);
    disk_nvme = new QStandardItem("NVME硬盘");
    disk_nvme->setFlags(disk_nvme->flags() & ~Qt::ItemIsEditable);
    netcard = new QStandardItem("网卡");
    netcard->setFlags(netcard->flags() & ~Qt::ItemIsEditable);
#endif

    model = new QStandardItemModel;
    QStandardItem *root = model->invisibleRootItem();

    root->appendRow(gpu);

    for(auto gpuphy:gpuinfo.hwinfos){
        QString name = QString::fromStdString(gpuphy->name);
        QStandardItem* itemGpu = new QStandardItem(name);
        itemGpu->setFlags(itemGpu->flags() & ~Qt::ItemIsEditable);
        itemGpu->setToolTip(name);
        //itemGpu->setStatusTip(name);
        gpu->appendRow(itemGpu);
    }
#ifdef DEV
    root->appendRow(cpu);
    for(auto cpuphy: Sysinfo::get()->cpuinfo.phys){
        std::string name = cpuphy.second.infos()["Name"];
        QStandardItem* itemCpu = new QStandardItem(QString::fromStdString(name));
        itemCpu->setFlags(itemCpu->flags() & ~Qt::ItemIsEditable);
        cpu->appendRow(itemCpu);
        for(auto cpucore: cpuphy.second.cpuinfos){
            std::string name = cpucore->infos()["core id"]+":"+cpucore->infos()["processor"];
            QStandardItem* itemCore = new QStandardItem(QString::fromStdString(name));
            itemCore->setFlags(itemCore->flags() & ~Qt::ItemIsEditable);
            itemCpu->appendRow(itemCore);
        }
    }
    root->appendRow(disk);
    disk->appendRow(disk_hard);
    disk->appendRow(disk_nvme);
    root->appendRow(netcard);
#endif
    setModel(model);
    connect(this, &QTreeView::clicked, this, [this](const QModelIndex &index){
        QStandardItem* item = model->itemFromIndex(index);
        if(cpu && (item == cpu || item->parent() == cpu || (item->parent() && item->parent()->parent() == cpu))){
            //emit sig_CPU_show(item->index().row());
            qDebug()<<"item cpu";
        }else if(gpu && (item == gpu || item->parent() == gpu)){
            emit sig_GPU_show(item->index().row());
        }else{
            qDebug()<<"item:"<<item->text();
        }
    });
    expandAll();
    //setCurrentIndex(model->index(1,0));
    emit sig_GPU_show(0);
}
TreeView::TreeView(QWidget *parent):QTreeView(parent)
{

}
