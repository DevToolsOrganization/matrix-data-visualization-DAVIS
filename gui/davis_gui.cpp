#include "davis_gui.h"
#include "./ui_davis_gui.h"

#include "../davis_one/davis.h"
#include "QDragEnterEvent"
#include "QMimeData"
#include "QDebug"
#include "QFileInfo"
#include "QPainter"
#include "QMenuBar"
#include "QHBoxLayout"
#include "QPushButton"

DavisGUI::DavisGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DavisGUI)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    QHBoxLayout *hbl = ui->horizontalLayout_menu;
    QMenuBar *mb = new QMenuBar;
    mb->setFixedSize(QSize(50,20));
    mb->setStyleSheet("background-color:rgb(82,82,82);");
    mb->addAction(new QAction("Help"));
    hbl->addWidget(mb);
    hbl->addItem(new QSpacerItem(2, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    QPushButton *qpb = new QPushButton;
    connect(qpb,&QPushButton::pressed,[this](){this->close();});
    qpb->setFixedSize(QSize(20,20));
    qpb->setText("X");
    hbl->addWidget(qpb);
    this->setLayout(hbl);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);//(Qt::WindowStaysOnTopHint);
    //this->setAttribute(Qt::WA_TranslucentBackground, true);
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

void DavisGUI::paintEvent(QPaintEvent *event)
{
    qDebug()<<"---------PAINT----------->";
    const int PADDING = 20;
    QRectF rectangle(PADDING, PADDING+20, this->width()-2*PADDING, this->height()-2*PADDING-20);
    QPainter painter(this);
      //Creating and customizing the pen and brush ; pen for the outline and brush for filling

       // Cutomised Pen; color:black , style:dashed
       QPen dashpen;
       dashpen.setStyle(Qt::DashLine);
       dashpen.setColor(QColor(82, 82, 82));
dashpen.setWidth(7);

       painter.setPen(dashpen);


       painter.drawRect(rectangle);
       painter.end();
       event->accept();
}

void DavisGUI::mousePressEvent(QMouseEvent *event)
{
     m_point = event->pos();
}

void DavisGUI::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - m_point);
}

