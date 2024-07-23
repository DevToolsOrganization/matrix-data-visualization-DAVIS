#include "davis_gui.h"
#include "./ui_davis_gui.h"

#include "../davis_one/davis.h"
#include "QDragEnterEvent"
#include "QMimeData"
#include "QDebug"
#include "QFileInfo"

DavisGUI::DavisGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DavisGUI)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
}

DavisGUI::~DavisGUI()
{
    delete ui;
}

void DavisGUI::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
     {
         event->acceptProposedAction();
     }
     else{
         qDebug()<<"not drop";
     }
}

void DavisGUI::dropEvent(QDropEvent *event)
{
    QString filePath =  event->mimeData()->urls().first().toLocalFile();
    QFileInfo info(filePath);
    if(info.exists())
    {
        std::vector<std::vector<double>> data;
        dvs::readMatrix(data,filePath.toStdString(),';');
        if(data.size()>1){
        dv::show(data);
        }else{
            dv::Config config;
            config.typeVisual = dv::VISUALTYPE_CHART;
            dv::show(data[0],"chart",config);
        }
    }
    else
        qDebug()<<"not exist";
}

