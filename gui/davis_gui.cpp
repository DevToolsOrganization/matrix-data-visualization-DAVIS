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
    QMenu  *menu_root = new QMenu("Menu");
    QAction  *action_help = new QAction("About");
    action_surface = new QAction("surface");
    action_surface->setCheckable(true);
    action_heatmap = new QAction("heatmap");
    action_heatmap->setCheckable(true);
    action_heatmap->setChecked(true);
    connect(action_heatmap,&QAction::triggered,[this](){action_surface->setChecked(false);});
    connect(action_surface,&QAction::triggered,[this](){action_heatmap->setChecked(false);});

    QMenu  *menu_view = new QMenu("View");
    menu_view->addAction(action_surface);
    menu_view->addAction(action_heatmap);
    mb->setFixedSize(QSize(50,20));
    mb->setStyleSheet("background-color:rgb(82,82,82);");
    menu_root->addMenu(menu_view);
    menu_root->addAction(action_help);
    mb->addMenu(menu_root);


    hbl->addWidget(mb);
    hbl->addItem(new QSpacerItem(2, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
    QPushButton *qpb = new QPushButton;
    connect(qpb,&QPushButton::clicked,[this](){this->close();});
    qpb->setFixedSize(QSize(20,20));
    qpb->setText("X");
    hbl->addWidget(qpb);
    //this->setLayout(hbl);
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
           if(action_heatmap->isChecked()){
           dv::show(data);
           }else if(action_surface->isChecked()){
           dv::Config config;
           config.typeVisual = dv::VISUALTYPE_SURFACE;
           dv::show(data,"surface",config);
           }
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

