#ifndef ABOUT_WINDOW_H
#define ABOUT_WINDOW_H

#include <QMainWindow>
#include <QElapsedTimer>

namespace Ui {
class about_window;
}

class About_window : public QMainWindow {
  Q_OBJECT

 signals:
  void about_window_closed();
  void tripleClick();

 public:
  explicit About_window(QWidget* parent = nullptr);
  ~About_window();

 protected:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  bool eventFilter(QObject* o, QEvent* e) override;

 private slots:
  void on_pushButton_close_clicked();

 private:
  Ui::about_window* ui;
  QPoint m_point;
  bool isMusicPlaying;
  uint clicks;
  QElapsedTimer someTimer;
};

#endif // ABOUT_WINDOW_H
