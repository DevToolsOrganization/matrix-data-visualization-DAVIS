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
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
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
        if(data.size()>1 && data[0].size()>1){
        dv::show(data);
        }else{
            std::vector<double> showVector;
            if(data.size()>1 && data[0].size()==1){
               std::vector<double> new_data(data.size());
               for(size_t i = 0;i<new_data.size();++i){
                   new_data[i] = data[i][0];
               }
               showVector = new_data;
            }else{
                showVector = data[0];
            }
            dv::Config config;
            config.typeVisual = dv::VISUALTYPE_CHART;
            dv::show(showVector,"chart",config);


        }
    }
    else
        qDebug()<<"not exist";
}

