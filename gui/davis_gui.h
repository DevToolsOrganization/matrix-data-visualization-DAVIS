#ifndef DAVISGUI_H
#define DAVISGUI_H

#include <QMainWindow>
#include "about_window.h"
#include "QAction"
#include "animated_button.h"
#include "cool_progressbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DavisGUI; }
QT_END_NAMESPACE

class DavisGUI : public QMainWindow {
  Q_OBJECT

 signals:
  void showProgressBar();
  void hideProgressBar();

 public:
  DavisGUI(QWidget* parent = nullptr);
  ~DavisGUI();
  void show();

 protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dropEvent(QDropEvent* event) override;
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;

 private:
  void setMaxStyleWindow(int animDuration);
  void setMinStyleWindow(int animDuration);
  void readPlotText(QStringList& str_lines);
  void selectAndShowFiles();
  bool checkDateTimeVariant(const QStringList& lines);
  bool isFileContainsSingleChart(const QString& pathToFile,
                                 QString& outX,
                                 QString& outY);
  void visualizeFiles(const QStringList& file_list);
  void hideElementsDuringResize();

 private slots:
  void showAboutWindow();
  void pasteFromClipboard();

 private:
  Ui::DavisGUI* ui;
  QPoint m_point;
  QAction*  action_surface;
  QAction*  action_heatmap;
  About_window* aboutWindow;
  bool isAboutWindowShowed;
  QAction* m_copy_paste_action;
  bool m_isMinStyleWindow;
  AnimatedButton*  qpbBuffer;
  AnimatedButton*  qpbOpen;
  coolProgressBar* barCool;
};
#endif // DAVISGUI_H
