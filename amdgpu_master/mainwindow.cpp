#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QStandardItemModel>
#include <QLabel>
#include <QScrollArea>
#include "treeview.h"
void MainWindow::infos_create(QWidget* parent, QString prefix){
    QWidget*areaWidget = new QWidget();
    QGridLayout* glayout = new QGridLayout();
    glayout->setSpacing(0);
    areaWidget->setLayout(glayout);

    QScrollArea* area = new QScrollArea();
    area->setWidgetResizable(true);
    area->setWidget(areaWidget);

    parent->setLayout(new QGridLayout(parent));
    parent->layout()->addWidget(area);

    int i =0, j=0;
    for(auto& group:gpu_info_now_->infos){
        QGroupBox* box = new QGroupBox(QString::fromStdString(group.first));
        QFormLayout* layout = new QFormLayout(box);
        box->setLayout(layout);
        string prefix_info;
        size_t off = group.first.find_first_of(" ");
        if(off == string::npos){
            prefix_info = group.first;
        }else{
            prefix_info = group.first.substr(0,off);
        }
        if(prefix_info == prefix.toStdString()){
            glayout->addWidget(box,i,j++);
            if(j == 3){
                j = 0;
                i++;
            }
        }
        for(auto& info:group.second){
            layout->addRow(QString::fromStdString(info.first), new QLabel(QString::fromStdString(info.second)));
        }
    }
}

static void status_groupBoxCreate(QGridLayout* parent_layout, QString name, int r, int c, std::map<std::string, StatusValue> status_ingroup){
    QGroupBox* box = new QGroupBox(name);
    QFormLayout* layout = new QFormLayout();
    box->setLayout(layout);
    parent_layout->addWidget(box,r,c);
    for(auto& iter: status_ingroup){
        if(iter.second.counter){
            layout->addRow(new QLabel(iter.first.c_str()), new QLabel());
        }else{
            layout->addRow(new QLabel(iter.first.c_str()), new QProgressBar());
        }
    }
}
void MainWindow::status_groupBoxUpdate(QGridLayout* parent_layout, HardwareStatus_per* status){
    if(parent_layout->count() == 0){
        if(parent_layout == ui->tab_status_advance->layout()){
            status_groupBoxCreate(parent_layout,"GRBM",0,0,status->status["GRBM"]);
            status_groupBoxCreate(parent_layout,"GRBM2",0,1,status->status["GRBM2"]);
            status_groupBoxCreate(parent_layout,"TA",1,0,status->status["TA"]);
            status_groupBoxCreate(parent_layout,"VGT",1,1,status->status["VGT"]);
        }else if(parent_layout == ui->tab_status_basic->layout()){
            status_groupBoxCreate(parent_layout,"Core",0,0,status->status["Core"]);
            status_groupBoxCreate(parent_layout,"Mem",0,1,status->status["Mem"]);
            status_groupBoxCreate(parent_layout,"Overall",1,0,status->status["Overall"]);
            status_groupBoxCreate(parent_layout,"Mem Counter",1,1,status->status["Mem Counter"]);
        }
    }
    for (int i = 0; i < parent_layout->count(); ++i) {
        QGroupBox* box = (QGroupBox*)parent_layout->itemAt(i)->widget();
        std::map<std::string, StatusValue> status_ingroup = status->status[box->title().toStdString()];

        QFormLayout* layout = (QFormLayout*)box->layout();
        int j = 0;
        for(auto& iter: status_ingroup){
            if(iter.second.counter){
                QLabel* label = (QLabel*)layout->itemAt(j++,QFormLayout::FieldRole)->widget();
                label->setText(QString::number(iter.second.value));
            }else{
                QProgressBar* bar = (QProgressBar*)layout->itemAt(j++,QFormLayout::FieldRole)->widget();
                bar->setValue(iter.second.value);

                if(iter.second.value > iter.second.value_max){
                    float max = bar->property("max").toFloat();
                    if(iter.second.value > max){
                        bar->setProperty("max", iter.second.value);
                        bar->setMaximum(iter.second.value);
                    }else{
                        bar->setMaximum(max);
                    }
                }else{
                    bar->setMaximum(iter.second.value_max);
                }
                bar->setMinimum(iter.second.value_min);
                if(iter.second.counter){
                    bar->setValue(iter.second.value - bar->value());
                }else{
                    bar->setValue(iter.second.value);
                }
                bar->setToolTip(QString::fromStdString(iter.second.longname));
                bar->setFormat("%p%(%v/%m"+QString::fromStdString(iter.second.unit) +")");
            }
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#ifdef DEV
    connect(ui->treeView, &TreeView::sig_CPU_show, this, [this](int idx){
        ui->stackedWidget->setCurrentIndex(0);
        CPUInfo_per* cpu_info = (CPUInfo_per*)Sysinfo::get()->cpuinfo.hwinfos[idx];
        std::map<std::string, std::string> infos = cpu_info->infos();
        ui->basic_family->setText(QString::fromStdString(infos["cpu family"]));
        ui->basic_addrsize->setText(QString::fromStdString(infos["address sizes"]));
        ui->basic_cpuid->setText(QString::fromStdString(infos["cpuid level"]));
        ui->basic_vendor->setText(QString::fromStdString(infos["vendor_id"]));
        ui->basic_microcode->setText(QString::fromStdString(infos["microcode"]));
        ui->basic_wp->setText(QString::fromStdString(infos["wp"]));
        ui->basic_tlb->setText(QString::fromStdString(infos["TLB size"]));
        ui->basic_bogomips->setText(QString::fromStdString(infos["bogomips"]));

        std::map<std::string, std::string> flags = cpu_info->flags();
        ui->flags_function->setText(QString::fromStdString(flags["function"]));


        ui->cache_l1data->setText(QString::fromStdString(infos["l1 data"]));
        ui->cache_l1inst->setText(QString::fromStdString(infos["l1 instruction"]));
        ui->cache_l2->setText(QString::fromStdString(infos["l2"]));
        ui->cache_l3->setText(QString::fromStdString(infos["l3"]));
        ui->cache_align->setText(QString::fromStdString(infos["cache_alignment"]));

        ui->bugs_bugs->setText(QString::fromStdString(infos["bugs"]));

        QFormLayout* layout_power = (QFormLayout*)ui->info_power->layout();
        //   layout_cache->addRow("l1 data",new QLabel(QString::fromStdString(infos["clflush size"])));
        QFormLayout* layout_topo = (QFormLayout*)ui->info_topology->layout();
    });
#endif

    connect(ui->treeView, &TreeView::sig_GPU_show, this, [this](int idx){
        ui->stackedWidget->setCurrentIndex(1);
        gpu_info_now_ = (GPUInfo_per*)gpuinfo.hwinfos[idx];
        qDeleteAll(ui->tab_status_basic->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->tab_status_advance->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

        qDeleteAll(ui->tab_infos_mem->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->tab_infos_chip->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->tab_infos_gfx->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->tab_infos_pci->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->tab_infos_vce->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->tab_infos_ip->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        qDeleteAll(ui->tab_infos_firmware->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));

        infos_create(ui->tab_infos_mem, "Mem");
        infos_create(ui->tab_infos_gfx, "GFX");
        infos_create(ui->tab_infos_chip, "Chip");
        infos_create(ui->tab_infos_pci, "PCI");
        infos_create(ui->tab_infos_vce, "VCE");
        infos_create(ui->tab_infos_ip, "IP");
        infos_create(ui->tab_infos_firmware, "Firmware");


          //  ui->gpu_path_local_cpu->setText(QString::fromStdString(infos["cpu family"]));
          //  ui->gpu_path_numa_node->setText(QString::fromStdString(infos["address sizes"]));
            //ui->gpu_ip_vbios_version->setText(QString::fromStdString(infos["vbios version"]));
            //ui->gpu_mem_vram->setText(QString::fromStdString(infos["vram"]));
            //ui->gpu_mem_vram_vis->setText(QString::fromStdString(infos["vram vis"]));
            //ui->gpu_mem_vram_vendor->setText(QString::fromStdString(infos["vram vendor"]));
            //ui->gpu_mem_gtt->setText(QString::fromStdString(infos["gtt"]));
            //ui->gpu_mem_gds->setText(QString::fromStdString(infos["vram"]));

            /*
            ui->basic_cpuid->setText(QString::fromStdString(infos["cpuid level"]));
            ui->basic_vendor->setText(QString::fromStdString(infos["vendor_id"]));
            ui->basic_microcode->setText(QString::fromStdString(infos["microcode"]));
            ui->basic_wp->setText(QString::fromStdString(infos["wp"]));
            ui->basic_tlb->setText(QString::fromStdString(infos["TLB size"]));
            ui->basic_bogomips->setText(QString::fromStdString(infos["bogomips"]));

            std::map<std::string, std::string> flags = cpu_info->flags();
            ui->flags_function->setText(QString::fromStdString(flags["function"]));


            ui->cache_l1data->setText(QString::fromStdString(infos["l1 data"]));
            ui->cache_l1inst->setText(QString::fromStdString(infos["l1 instruction"]));
            ui->cache_l2->setText(QString::fromStdString(infos["l2"]));
            ui->cache_l3->setText(QString::fromStdString(infos["l3"]));
            ui->cache_align->setText(QString::fromStdString(infos["cache_alignment"]));

            ui->bugs_bugs->setText(QString::fromStdString(infos["bugs"]));

            QFormLayout* layout_power = (QFormLayout*)ui->info_power->layout();
            //   layout_cache->addRow("l1 data",new QLabel(QString::fromStdString(infos["clflush size"])));
            QFormLayout* layout_topo = (QFormLayout*)ui->info_topology->layout();
*/
    });
    ui->treeView->init(gpuinfo);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [this](){
        std::shared_ptr<HardwareStatus_per> status = gpu_info_now_->status_get_per();
        status_groupBoxUpdate((QGridLayout*)ui->tab_status_basic->layout(), status.get());
        status_groupBoxUpdate((QGridLayout*)ui->tab_status_advance->layout(), status.get());
    });
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

