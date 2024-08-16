#include "about_window.h"
#include "ui_about_window.h"
#include "QPushButton"
#include "QHBoxLayout"
#include "QMouseEvent"

About_window::About_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::about_window)
{
    ui->setupUi(this);

    //qpbExit->setText("✕");
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ui->label_nearLogo->setOpenExternalLinks(true);
}

About_window::~About_window()
{
    delete ui;
}

void About_window::on_pushButton_close_clicked()
{
    this->close();
}

void About_window::mousePressEvent(QMouseEvent* event) {
  m_point = event->pos();
}

void About_window::mouseMoveEvent(QMouseEvent* event) {
  move(event->globalPos() - m_point);

}
