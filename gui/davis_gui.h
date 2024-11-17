#ifndef DAVISGUI_H
#define DAVISGUI_H

#include <QMainWindow>
#include "about_window.h"
#include "QAction"

QT_BEGIN_NAMESPACE
namespace Ui { class DavisGUI; }
QT_END_NAMESPACE

class DavisGUI : public QMainWindow {
  Q_OBJECT

 public:
  DavisGUI(QWidget* parent = nullptr);
  ~DavisGUI();
  void show();

 private:
  void setMaxStyleWindow(int animDuration);
  void setMinStyleWindow(int animDuration);
  void readPlotText(QStringList& str_lines);
  QStringList selectFiles();

 private slots:
  void showAboutWindow();
  void pasteTextAdded();

 private:
  Ui::DavisGUI* ui;
  QPoint m_point;
  QAction*  action_surface;
  QAction*  action_heatmap;
  About_window* aboutWindow;
  bool isAboutWindowShowed;
  QAction* m_copy_paste_action;
  bool m_isMinStyleWindow;
  void readPlotText(QStringList& str_lines);
  bool checkDateTimeVariant(const QStringList& lines);
  bool isFileContainsSingleChart(const QString &pathToFile,
                                 QString &outX,
                                 QString &outY);

  // QWidget interface
 protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dropEvent(QDropEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
};
#endif // DAVISGUI_H
