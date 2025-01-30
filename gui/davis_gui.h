#ifndef DAVISGUI_H
#define DAVISGUI_H

#include <QMainWindow>
#include <QAction>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>

#include "cool_progressbar.h"
#include "about_window.h"
#include "animated_button.h"


QT_BEGIN_NAMESPACE
namespace Ui { class DavisGUI; }
QT_END_NAMESPACE


enum class Skins {DEFAULT, NEWYEAR};


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
  void setGeometryForMaxStyle_defaultSkin();
  void setGeometryForMinStyle_defaultSkin();
  void setGeometryForMaxStyle_newYearSkin();
  void setGeometryForMinStyle_newYearSkin();
  void readPlotText(QStringList& str_lines, QString titleTopOfPlotly = "");
  void selectAndShowFiles();
  bool checkDateTimeVariant(const QStringList& lines);
  bool isFileContainsSingleChart(const QString& pathToFile,
                                 std::vector<double>& outX,
                                 std::vector<double>& outY);
  void visualizeFiles(const QStringList& file_list);
  void hideElementsDuringResize();
  void saveSettings(const QString& fileName);
  QJsonObject loadSettings(const QString& fileName);
  void applySettings(const QJsonObject& settings);
  void readJsonToPlot(const QString& pathToFile);
  void matrixAnalyzer(std::vector<std::vector<double>>& matrix,
                      const bool isRow);
  Skins checkSkin();
  bool getDateTimeData(const QStringList& lines,
                       QString& dates,
                       std::vector<double>& values,
                       std::vector<double>& force,
                       std::vector<std::vector<double>>& multicharts);

  QStringList getLinesFromFile(const QString& pathToFile);
  bool mayBeShowBIN(const QString& path);

 private slots:
  void showAboutWindow();
  void pasteFromClipboard();

 private:
  Ui::DavisGUI* ui;
  QPoint m_point;
  QAction*  action_surface;
  QAction*  action_heatmap;
  QAction*  action_fitPlotToAllWindow;
  QAction*  action_holidaysSkins;
  About_window* aboutWindow;
  bool isAboutWindowShowed;
  QAction* m_copy_paste_action;
  bool m_isMinStyleWindow;
  AnimatedButton*  qpbBuffer;
  AnimatedButton*  qpbOpen;
  QString settingsFilePath;
  QJsonArray service_json_keys;
  coolProgressBar* barCool;
  QLabel* label_gif;
  bool m_isUseCustomSkins;
  Skins m_skin;

};
#endif // DAVISGUI_H
