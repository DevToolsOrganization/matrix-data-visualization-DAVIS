#ifndef DAVISGUI_H
#define DAVISGUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DavisGUI; }
QT_END_NAMESPACE

class DavisGUI : public QMainWindow {
  Q_OBJECT

 public:
  DavisGUI(QWidget* parent = nullptr);
  ~DavisGUI();

 private slots:
  void showAboutWindow();

 private:
  Ui::DavisGUI* ui;
  QPoint m_point;
  QAction*  action_surface;
  QAction*  action_heatmap;

  // QWidget interface
 protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dropEvent(QDropEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
};
#endif // DAVISGUI_H
