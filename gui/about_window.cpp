#include "about_window.h"
#include "ui_about_window.h"
#include "QPushButton"
#include "QHBoxLayout"
#include "QMouseEvent"
#include <QDebug>
#include <QMediaPlayer>


About_window::About_window(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::about_window) {
  ui->setupUi(this);
  isMusicPlaying = false;
  clicks = 1;
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  ui->label_nearLogo->setOpenExternalLinks(true);
  ui->label_center->setOpenExternalLinks(true);

  ui->label_DevtoolsDavis->installEventFilter(this);
  setAttribute(Qt::WA_DeleteOnClose);
  QObject::connect(this, &About_window::tripleClick, [ = ]() {
    qDebug() << "tripple";
  });
}

About_window::~About_window() {
  delete ui;
  emit about_window_closed();
}

void About_window::on_pushButton_close_clicked() {
  close();
}

void About_window::mousePressEvent(QMouseEvent* event) {
  m_point = event->pos();
}

void About_window::mouseMoveEvent(QMouseEvent* event) {
  move(event->globalPos() - m_point);

}

bool About_window::eventFilter(QObject* o, QEvent* e) {
  if (o == ui->label_DevtoolsDavis && e->type() == QMouseEvent::MouseButtonRelease && !isMusicPlaying) {
    qint64 delta_ms = 250;
    qint64 elapsed = someTimer.restart(); //someTimer is QElapsedTimer member
    if (elapsed < delta_ms)
      ++clicks;
    else
      clicks = 1;
    qDebug() << clicks;
    if (4 == clicks) {
      QMediaPlayer* player = new QMediaPlayer(this);
      player->setMedia(QUrl("qrc:/res/davis.mp3"));
      player->play();
      isMusicPlaying = true;
      QObject::connect(player, &QMediaPlayer::stateChanged, [ = ](QMediaPlayer::State state) {
        if (state == QMediaPlayer::State::StoppedState)
          isMusicPlaying = false;
      });
    }
  }
  return QObject::eventFilter(o, e);
}
