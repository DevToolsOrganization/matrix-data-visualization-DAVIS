#include "davis_gui.h"
#include "../davis_one/davis.h"
#include "./ui_davis_gui.h"

#include "json_utils.h"
#include <QApplication>
#include <QClipboard>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMimeData>
#include <QMovie>
#include <QPainter>
#include <QPainterPath>
#include <QParallelAnimationGroup>
#include <QProcess>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QScreen>
#include <QSignalTransition>
#include <QStateMachine>
#include <QTextStream>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

using std::string;
using std::vector;
using namespace dvs;
const int ANIMATION_DURATION = 300;
const double OPACITY_IF_NOT_ACTIVE = 0.94;

DavisGUI::DavisGUI(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::DavisGUI) {
  jsn::getJsonArrayFromFile(":/keys.json", service_json_keys);
  ui->setupUi(this);
  isAboutWindowShowed = false;
  m_isMinStyleWindow = false;
  m_isUseCustomSkins = false;
  m_skin = checkSkin();
  this->setAcceptDrops(true);
  QHBoxLayout *hbl = ui->horizontalLayout_menu;

  QLabel *labelIco = new QLabel;
  QString davisIconPath = ":/res/icon/D-16x16.png";
  labelIco->setPixmap(davisIconPath);
  labelIco->setContentsMargins(10, 0, 0, 0);
  hbl->addWidget(labelIco);

  QMenuBar *mb = new QMenuBar;
  QString menuStyle(
      "QMenuBar {"
      "    background-color: transparent;"
      "    font-size: 13px;"
      "}"
      "QMenuBar::item {"
      "    background-color: transparent;"
      "    height: 20px;" // Set a fixed height
      "}"
      "QMenuBar::item:selected {"
      "    background-color: rgb(42, 130, 218);"
      "    height: 20px;" // Ensure the height remains the same on hover
      "}");
  mb->setStyleSheet(menuStyle);
  mb->setFixedSize(QSize(50, 25));
  QMenu *menu_root = new QMenu("Menu");

  action_fitPlotToBrowserWindow = new QAction("Fit graph to window");
  action_fitPlotToBrowserWindow->setCheckable(true);
  menu_root->addAction(action_fitPlotToBrowserWindow);
  action_holidaysSkins = new QAction("Holidays custom skins");
  action_holidaysSkins->setCheckable(true);
  menu_root->addAction(action_holidaysSkins);
  connect(action_holidaysSkins, &QAction::triggered, [this]() {
    m_isUseCustomSkins = action_holidaysSkins->isChecked();
    Skins skin = m_skin;
    m_skin = checkSkin();
    if (m_skin == skin) {
      return;
    }
    if (m_isMinStyleWindow) {
      setMinStyleWindow(0);
    } else {
      setMaxStyleWindow(0);
    }
  });
  action_autodeleteGeneratedHtmls = new QAction("Auto delete generated htmls");
  action_autodeleteGeneratedHtmls->setCheckable(true);
  menu_root->addAction(action_autodeleteGeneratedHtmls);
  mb->addMenu(menu_root);
  hbl->addWidget(mb);
  hbl->addItem(
      new QSpacerItem(2, 25, QSizePolicy::Expanding, QSizePolicy::Expanding));

  ui->label_text->setStyleSheet("background-color: rgba(255, 255, 255, 0);");

  QString buttonStyle("QPushButton {"
                      "    background-color: none;"
                      "    border: none;"
                      "    font-size: 13px;"
                      "}"
                      "QPushButton:hover {"
                      "    background-color: rgb(42, 130, 218);"
                      "}");
  QPushButton *qpbAbout = new QPushButton;
  qpbAbout->setFlat(true);
  qpbAbout->setStyleSheet(buttonStyle);
  qpbAbout->setToolTip("About");
  connect(qpbAbout, &QPushButton::clicked, this, &DavisGUI::showAboutWindow);
  qpbAbout->setFixedSize(QSize(25, 25));
  qpbAbout->setText("?");
  hbl->addWidget(qpbAbout);

  QPushButton *qpbMinMaxSize = new QPushButton;
  qpbMinMaxSize->setFlat(true);
  qpbMinMaxSize->setStyleSheet(buttonStyle);
  qpbMinMaxSize->setToolTip("Full/compact size");
  connect(qpbMinMaxSize, &QPushButton::clicked, [this]() {
    m_isMinStyleWindow = !m_isMinStyleWindow;
    if (m_isMinStyleWindow) {
      setMinStyleWindow(ANIMATION_DURATION);
    } else {
      setMaxStyleWindow(ANIMATION_DURATION);
    }
  });
  qpbMinMaxSize->setFixedSize(QSize(25, 25));
  qpbMinMaxSize->setText("◰");
  hbl->addWidget(qpbMinMaxSize);

  QPushButton *qpbMinim = new QPushButton;
  qpbMinim->setFlat(true);
  qpbMinim->setStyleSheet(buttonStyle);
  qpbMinim->setToolTip("Minimize");
  connect(qpbMinim, &QPushButton::clicked, [this]() { this->showMinimized(); });
  qpbMinim->setFixedSize(QSize(25, 25));
  qpbMinim->setText("─");
  hbl->addWidget(qpbMinim);

  QString buttonStyleExit("QPushButton {"
                          "    background-color: none;"
                          "    border: none;"
                          "    font-size: 13px;"
                          "}"
                          "QPushButton:hover {"
                          "    background-color: rgb(218, 42, 42);"
                          "}");
  QPushButton *qpbExit = new QPushButton;
  qpbExit->setFlat(true);
  qpbExit->setStyleSheet(buttonStyleExit);
  qpbExit->setToolTip("Close");
  connect(qpbExit, &QPushButton::clicked, [this]() { this->close(); });
  qpbExit->setFixedSize(QSize(25, 25));
  qpbExit->setText("✕");
  hbl->addWidget(qpbExit);
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint |
                       Qt::WindowStaysOnTopHint);

  barCool =
      new coolProgressBar(QColor(52, 52, 52), QColor(42, 130, 218), 2500, this);
  barCool->setGeometry(70, 220, 270, 2);
  this->layout()->addWidget(barCool);
  connect(this, &DavisGUI::showProgressBar, barCool,
          &coolProgressBar::startAnimation);
  connect(this, &DavisGUI::hideProgressBar, barCool,
          &coolProgressBar::stopAnimation);

  qpbOpen = new AnimatedButton("Open", QColor(120, 120, 120),
                               QColor(42, 130, 218), this);
  qpbBuffer =
      new AnimatedButton("Past from clipboard (Ctrl+V)", QColor(120, 120, 120),
                         QColor(42, 130, 218), this);

  connect(qpbOpen, &QPushButton::released, this, &DavisGUI::selectAndShowFiles);
  connect(qpbBuffer, &QPushButton::released, this,
          &DavisGUI::pasteFromClipboard);

  // New Year
  QString fileGifPath = ":/res/newYear.gif";
  QMovie *movie = new QMovie(fileGifPath);
  label_gif = new QLabel(this);
  label_gif->setMovie(movie);
  label_gif->setScaledContents(true);
  movie->start();
  label_gif->setGeometry(0, 28, 397, 380);
  label_gif->lower();
  label_gif->setVisible(false);

  settingsFilePath = "settings.json";
  QJsonObject settings = loadSettings(settingsFilePath);
  applySettings(settings);
  animationOpacity = new QPropertyAnimation(this, "windowOpacity");
  animationOpacity->setDuration(
      ANIMATION_DURATION); // Длительность анимации в миллисекундах
  animationOpacity->setEasingCurve(
      QEasingCurve::InOutQuad); // Задаем плавность кривой
}

DavisGUI::~DavisGUI() {
  saveSettings(settingsFilePath);
  if (action_autodeleteGeneratedHtmls->isChecked()) {
    QDir dir(kOutFolderName);
    // Настраиваем фильтр только на HTML-файлы
    QStringList filters;
    filters << "*.html";

    // Получаем список только файлов, исключая папки
    QStringList htmlFiles = dir.entryList(filters, QDir::Files);

    // Удаляем каждый файл
    for (const QString &fileName : htmlFiles) {
      dir.remove(fileName);
    }
  }
  delete ui;
}

void DavisGUI::show() { QMainWindow::show(); }

void DavisGUI::hideElementsDuringResize() {
  ui->label_doc->setVisible(false);
  ui->label_arrow->setVisible(false);
  ui->label_graph->setVisible(false);
  ui->label_text->setVisible(false);
  qpbBuffer->setVisible(false);
  qpbOpen->setVisible(false);
  barCool->setVisible(false);
  update();
}

void DavisGUI::saveSettings(const QString &fileName) {
  QJsonObject settings;
  settings["windowPosX"] = pos().x();
  settings["windowPosY"] = pos().y();
  settings["isMinStyleWindow"] = m_isMinStyleWindow;
  settings["isUseCustomSkins"] = m_isUseCustomSkins;
  settings["isFitGraphToWindow"] = action_fitPlotToBrowserWindow->isChecked();
  settings["isAutoDelete"] = action_autodeleteGeneratedHtmls->isChecked();
  bool isSaved = jsn::saveJsonObjectToFile(fileName, settings);
  if (!isSaved) {
    qWarning("Couldn't save settings file.");
  }
  return;
}

QJsonObject DavisGUI::loadSettings(const QString &fileName) {
  QJsonObject settings;
  bool isOpen = jsn::getJsonObjectFromFile(fileName, settings);
  if (!isOpen) {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    settings["windowPosX"] = x;
    settings["windowPosY"] = y;
    settings["isMinStyleWindow"] = false;
    settings["isUseCustomSkins"] = false;
    settings["isFitGraphToWindow"] = false;
  }
  return settings;
}

void DavisGUI::applySettings(const QJsonObject &settings) {
  m_isMinStyleWindow = settings["isMinStyleWindow"].toBool();
  if (m_isMinStyleWindow) {
    setMinStyleWindow(0);
  } else {
    setMaxStyleWindow(0);
  }
  int x = settings["windowPosX"].toInt();
  int y = settings["windowPosY"].toInt();
  move(x, y);
  action_fitPlotToBrowserWindow->setChecked(
      settings["isFitGraphToWindow"].toBool());
  action_holidaysSkins->setChecked(settings["isUseCustomSkins"].toBool());
  action_autodeleteGeneratedHtmls->setChecked(
      settings["isAutoDelete"].toBool());
}

void DavisGUI::readJsonToPlot(const QString &pathToFile) {
  QFileInfo fileInfo(pathToFile);
  QString jsonName = fileInfo.fileName();
  QJsonObject user_stamp_keys;
  QJsonArray matrix_to_matrix_stamps;

  if (jsn::getJsonObjectFromFile("user_keys_list.json", user_stamp_keys) ==
      false) {
    jsn::getJsonObjectFromFile(":/user_keys_list.json", user_stamp_keys);
  }

  if (user_stamp_keys.keys().contains("matrix_to_matrix")) {
    matrix_to_matrix_stamps =
        user_stamp_keys.value("matrix_to_matrix").toArray();
  } else {
    QJsonObject user_stamp_keys;
    jsn::getJsonObjectFromFile(":/user_keys_list.json", user_stamp_keys);
    matrix_to_matrix_stamps =
        user_stamp_keys.value("matrix_to_matrix").toArray();
  }

  QJsonValue jv;
  QJsonArray result;
  if (jsn::getJsonValueFromFile(pathToFile, jv) == false) {
    qDebug() << "Json open error.....................";
    return;
  };
  jsn::extractAllObjects(jv, result);
  // qDebug()<<"result all objects size:"<<result.size();

  for (int i = 0; i < result.size(); ++i) {

    // Проверяем является ли объект MATRIX TO MATRIX типом
    // qDebug()<<"MATRIX TO MATRIX: "<<matrix_to_matrix_stamps;
    for (int j = 0; j < matrix_to_matrix_stamps.size(); ++j) {
      auto obj = result[i].toObject();
      QStringList check_keys;

      check_keys << matrix_to_matrix_stamps[j]
                        .toObject()
                        .value("attribute_key")
                        .toString();
      check_keys
          << matrix_to_matrix_stamps[j].toObject().value("x_values").toString();
      check_keys
          << matrix_to_matrix_stamps[j].toObject().value("y_values").toString();

      bool is_matrix_to_matrix_result =
          jsn::isObjectMatrixToMatrixType(check_keys, obj);
      // qDebug()<<matrix_to_matrix_stamps[j].toObject().keys();
      if (is_matrix_to_matrix_result) {
        if (check_keys.size() != 3) {
          qDebug() << "********************** MATRIX TO MATRIX KEYS EXCEPTION "
                      "***************************";
          continue;
        };
        qDebug() << "MATRIX_TO_MATRIX_PROCESS.......";
        // 0 - atr metadata
        // 1 - x array of arrays values
        // 2 - y array  of arrays values
        auto attr_arr = obj.value(check_keys[0]).toArray();
        auto x_arr = obj.value(check_keys[1]).toArray();
        auto y_arr = obj.value(check_keys[2]).toArray();
        if (x_arr.size() != y_arr.size()) {
          qDebug() << "********************** MATRIX TO MATRIX ARRAY ARRAY "
                      "SIZES EXCEPTION ***************************";
          continue;
        };
        for (int k = 0; k < x_arr.size(); ++k) {
          auto attr = attr_arr[k].toObject();
          auto x_vals = jsn::getVectorDoubleFromJsonArray(x_arr[k].toArray())
                            .toStdVector();
          auto y_vals = jsn::getVectorDoubleFromJsonArray(y_arr[k].toArray())
                            .toStdVector();
          dv::Config conf;
          conf.chart.yLabel = attr.value("type").toString().toStdString();
          conf.chart.title = attr.value("instrument").toString().toStdString();
          conf.chart.isFitPlotToWindow =
              action_fitPlotToBrowserWindow->isChecked();
          dv::show(x_vals, y_vals, dvs::makeUniqueDavisHtmlName(), conf);
        }
        return; // выход если это был MATRIX_TO_MATRIX_TYPE
      }
    }

    auto json_object_result = jsn::isJsonObjectContainsUserKeys(
        result[i].toObject(), service_json_keys, user_stamp_keys);

    if (json_object_result.first) {
      QJsonObject result_obj = json_object_result.second;
      QJsonArray x_values = result_obj["x_values"].toArray();
      QJsonArray y_values = result_obj["y_values"].toArray();
      QJsonArray matrix_values = result_obj["matrix_values"].toArray();

      auto x_vector = jsn::getVectorDoubleFromJsonArray(x_values);
      auto y_vector = jsn::getVectorDoubleFromJsonArray(y_values);
      auto matrix_vector = jsn::getMatrixFromJsonArray(matrix_values);

      qDebug() << "MATRIX SIZE: " << matrix_vector.size();
      dv::Config conf;
      conf.chart.isFitPlotToWindow = action_fitPlotToBrowserWindow->isChecked();
      conf.heatmap.isFitPlotToWindow = conf.chart.isFitPlotToWindow;
      if (x_vector.empty() == false && y_vector.empty() == false) {
        dv::show(x_vector.toStdVector(), y_vector.toStdVector(),
                 dvs::makeUniqueDavisHtmlName(), conf);
      } else if (x_vector.empty() == true && y_vector.empty() == false) {
        dv::show(y_vector.toStdVector(), dvs::makeUniqueDavisHtmlName(), conf);
      } else if (x_vector.empty() == false && y_vector.empty() == true) {
        dv::show(x_vector.toStdVector(), dvs::makeUniqueDavisHtmlName(), conf);
      }
      if (matrix_vector.empty() == false) {
        dv::show(matrix_vector, dvs::makeUniqueDavisHtmlName(), conf);
      }
    } else {
      qDebug() << "Check JSON!";
    }
  }
}

Skins DavisGUI::checkSkin() {
  if (!m_isUseCustomSkins) {
    return Skins::DEFAULT;
  }
  Skins skin;
  QDate currentDate = QDate::currentDate();
  if ((currentDate.month() == 12 && currentDate.day() >= 15) ||
      (currentDate.month() == 1 && currentDate.day() <= 15)) {
    skin = Skins::NEWYEAR;
  } else {
    skin = Skins::DEFAULT;
  }
  return skin;
}

bool DavisGUI::getDateTimeData(const QStringList &lines, QString &dates,
                               std::vector<double> &values,
                               std::vector<double> &force,
                               std::vector<std::vector<double>> &multicharts) {
  QJsonArray jarr;
  if (jsn::getJsonArrayFromFile("date_time_formats.json", jarr) == false) {
    jsn::getJsonArrayFromFile(":/date_time_formats.json", jarr);
  }

  for (int i = 0; i < lines.size(); ++i) {
    QString test = lines[i];
    test.replace("'", "");
    for (int j = 0; j < jarr.size(); ++j) {
      int template_time_stamp_size = jarr[j].toString().size();
      QString template_time_stamp = jarr[j].toString();
      if (test.size() < template_time_stamp_size + 1) {
        continue;
      }
      QString separator = QString(test[template_time_stamp_size]);
      QString substr = test.mid(0, template_time_stamp_size);
      QDateTime dt = QDateTime::fromString(substr, template_time_stamp);
      if (dt.isValid()) {
        dates.append("'");
        dates.append(dt.toString("yyyy-MM-dd hh:mm:ss"));
        dates.append("'");
        if (i < lines.size() - 1) {
          dates.append(",");
        }
        auto values_list = test.split(separator);
        // Clear empty values
        for (int ch = 0; ch < values_list.size(); ++ch) {
          if (values_list[ch].isEmpty()) {
            values_list.removeAt(ch);
          }
        }
        if (values_list.size() < 2) {
          continue;
        }
        if (values_list.size() > 3) {
          std::vector<double> temp(values_list.size() - 1);
          for (int j = 1; j < values_list.size(); ++j) {
            temp[j - 1] = values_list[j].toDouble();
          }
          multicharts.push_back(temp);
        }
        double value = values_list[1].toDouble();
        values.emplace_back(value);
        if (values_list.size() == 3) {
          double value = values_list[2].toDouble();
          force.emplace_back(value);
        }
      }
    }
  }
  return true;
}

QStringList DavisGUI::getLinesFromFile(const QString &pathToFile) {
  QFile file(pathToFile);
  QTextStream ts(&file);
  ts.setCodec("UTF-8");
  if (file.open(QIODevice::ReadWrite) == false) {
    return QStringList();
  };
  QString line;
  QStringList str_lines;
  while (ts.readLineInto(&line)) {
    str_lines.append(line);
  }
  if (str_lines.empty()) {
    return QStringList();
  }
  file.close();
  return str_lines;
}

bool DavisGUI::mayBeShowBIN(const QString &path) {
  QFileInfo info(path);
  QJsonArray bins;
  if (jsn::getJsonArrayFromFile("bin.json", bins) == false) {
    jsn::getJsonArrayFromFile(":/bin.json", bins);
  }
  for (int i = 0; i < bins.size(); ++i) {
    int file_size = bins[i].toObject().value("file_size_in_bytes").toInt();
    int numbers_in_line = bins[i].toObject().value("numbers_in_line").toInt();
    QString data_type = bins[i].toObject().value("data_type").toString();
    if (info.size() == file_size) {
      if (data_type == "uint8") {
        std::vector<std::vector<uint8_t>> data = dvs::readBinaryFile<uint8_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "uint16") {
        std::vector<std::vector<uint16_t>> data = dvs::readBinaryFile<uint16_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "uint32") {
        std::vector<std::vector<uint32_t>> data = dvs::readBinaryFile<uint32_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "uint64") {
        std::vector<std::vector<uint64_t>> data = dvs::readBinaryFile<uint64_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "int8") {
        std::vector<std::vector<int8_t>> data = dvs::readBinaryFile<int8_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "int16") {
        std::vector<std::vector<int16_t>> data = dvs::readBinaryFile<int16_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "int32") {
        std::vector<std::vector<int32_t>> data = dvs::readBinaryFile<int32_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "int64") {
        std::vector<std::vector<int64_t>> data = dvs::readBinaryFile<int64_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "float32") {
        std::vector<std::vector<float_t>> data = dvs::readBinaryFile<float_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      } else if (data_type == "float64") {
        std::vector<std::vector<double_t>> data = dvs::readBinaryFile<double_t>(
            path.toLatin1().data(), numbers_in_line);
        dv::show(data);
      }
      return true;
    }
  }
  return false;
}

void DavisGUI::setMaxStyleWindow(int animDuration) {
  m_isMinStyleWindow = false;
  hideElementsDuringResize();
  setWindowOpacity(1);
  QPropertyAnimation *animationFrame =
      new QPropertyAnimation(ui->frame_panel, "geometry");
  animationFrame->setEasingCurve(QEasingCurve::InOutQuad);
  animationFrame->setDuration(animDuration);
  animationFrame->setStartValue(ui->frame_panel->geometry());
  animationFrame->setEndValue(QRect(0, 0, 397, 25));

  QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
  animation->setDuration(animDuration);
  animation->setEasingCurve(QEasingCurve::InOutQuad);
  animation->setStartValue(this->geometry());
  int xOld = this->geometry().x();
  int yOld = this->geometry().y();
  int newWidth = 397;
  int newHeight = 370;
  int deltaW = newWidth - this->geometry().width();
  animation->setEndValue(QRect(xOld - deltaW, yOld, newWidth, newHeight));

  connect(animation, &QPropertyAnimation::finished, this, [this]() {
    switch (m_skin) {
    case Skins::DEFAULT:
      setGeometryForMaxStyle_defaultSkin();
      break;
    case Skins::NEWYEAR:
      setGeometryForMaxStyle_newYearSkin();
      break;
    default:
      setGeometryForMaxStyle_defaultSkin();
      break;
    }
    update();
  });

  QParallelAnimationGroup *group = new QParallelAnimationGroup;
  group->addAnimation(animation);
  group->addAnimation(animationFrame);
  group->start();
}

void DavisGUI::setMinStyleWindow(int animDuration) {
  m_isMinStyleWindow = true;
  hideElementsDuringResize();
  setWindowOpacity(OPACITY_IF_NOT_ACTIVE);
  QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
  animation->setDuration(animDuration);
  animation->setEasingCurve(QEasingCurve::InOutQuad);
  animation->setStartValue(this->geometry());
  int xOld = this->geometry().x();
  int yOld = this->geometry().y();
  int newWidth = 179;
  int newHeight = 137;
  int deltaW = newWidth - this->geometry().width();
  animation->setEndValue(QRect(xOld - deltaW, yOld, newWidth, newHeight));

  QPropertyAnimation *animationFrame =
      new QPropertyAnimation(ui->frame_panel, "geometry");
  animationFrame->setDuration(animDuration);
  animationFrame->setEasingCurve(QEasingCurve::InOutQuad);
  animationFrame->setStartValue(ui->frame_panel->geometry());
  animationFrame->setEndValue(QRect(0, 0, newWidth, 25));

  connect(animation, &QPropertyAnimation::finished, this, [this]() {
    switch (m_skin) {
    case Skins::DEFAULT:
      setGeometryForMinStyle_defaultSkin();
      break;
    case Skins::NEWYEAR:
      setGeometryForMinStyle_newYearSkin();
      break;
    default:
      setGeometryForMinStyle_defaultSkin();
      break;
    }
    update();
  });

  QParallelAnimationGroup *group = new QParallelAnimationGroup;
  group->addAnimation(animation);
  group->addAnimation(animationFrame);
  group->start();
}

void DavisGUI::setGeometryForMaxStyle_defaultSkin() {
  label_gif->setVisible(false);
  label_gif->movie()->stop();
  ui->label_doc->setVisible(true);
  ui->label_arrow->setVisible(true);
  ui->label_graph->setVisible(true);
  ui->label_text->setVisible(true);
  ui->frame_panel->setVisible(true);
  qpbBuffer->setVisible(true);
  qpbOpen->setVisible(true);
  ui->label_doc->setGeometry(90, 60, 91, 91);
  ui->label_arrow->setGeometry(170, 90, 50, 50);
  ui->label_graph->setGeometry(210, 70, 81, 81);
  ui->label_text->setGeometry(0, 230, 391, 111);
  barCool->setGeometry(97, 155, 187, 2);
  qpbOpen->setGeometry(65, 180, 90, 30);
  qpbBuffer->setGeometry(165, 180, 170, 30);
}

void DavisGUI::setGeometryForMinStyle_defaultSkin() {
  label_gif->setVisible(false);
  label_gif->movie()->stop();
  ui->label_doc->setVisible(true);
  ui->label_arrow->setVisible(true);
  ui->label_graph->setVisible(true);
  ui->frame_panel->setVisible(true);
  ui->label_doc->setGeometry(40, 60, 41, 41);
  ui->label_arrow->setGeometry(70, 60, 41, 41);
  ui->label_graph->setGeometry(100, 60, 41, 41);
  barCool->setGeometry(45, 105, 90, 2);
}

void DavisGUI::setGeometryForMaxStyle_newYearSkin() {
  label_gif->setVisible(true);
  label_gif->movie()->start();
  ui->label_doc->setVisible(false);
  ui->label_arrow->setVisible(false);
  ui->label_graph->setVisible(false);
  ui->label_text->setVisible(false);
  ui->frame_panel->setVisible(true);
  qpbBuffer->setVisible(true);
  qpbOpen->setVisible(true);
  barCool->setGeometry(97, 367, 187, 2);
  qpbOpen->setGeometry(65, 335, 90, 30);
  qpbBuffer->setGeometry(165, 335, 170, 30);
  label_gif->setGeometry(0, 28, 397, 380);
}

void DavisGUI::setGeometryForMinStyle_newYearSkin() {
  label_gif->setVisible(true);
  label_gif->movie()->start();
  ui->label_doc->setVisible(false);
  ui->label_arrow->setVisible(false);
  ui->label_graph->setVisible(false);
  ui->frame_panel->setVisible(true);
  ui->label_doc->setGeometry(40, 60, 41, 41);
  ui->label_arrow->setGeometry(70, 60, 41, 41);
  ui->label_graph->setGeometry(100, 60, 41, 41);
  barCool->setGeometry(45, 105, 90, 2);
  label_gif->setGeometry(0, 28, 179, 155);
}

void DavisGUI::showAboutWindow() {
  if (isAboutWindowShowed) {
    delete aboutWindow;
  }
  aboutWindow = new About_window(); // NO LEAK because of Qt::WA_DeleteOnClose
  connect(aboutWindow, &About_window::about_window_closed,
          [=]() { isAboutWindowShowed = false; });
  aboutWindow->show();
  isAboutWindowShowed = true;
}

void DavisGUI::pasteFromClipboard() {
  auto lambdaFunction = [this]() {
    emit showProgressBar();
    QClipboard *clipboard = QApplication::clipboard();
    QString clipboardText = clipboard->text();
    QStringList lines = clipboardText.split(QRegExp("[\r\n]+"));
    if (checkDateTimeVariant(lines) == false) {
      readPlotText(lines);
    };
  };
  QFuture<void> future = QtConcurrent::run(lambdaFunction);
  QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
  connect(watcher, &QFutureWatcher<void>::finished, this,
          &DavisGUI::hideProgressBar);
  watcher->setFuture(future);
}

void DavisGUI::readPlotText(QStringList &str_lines, QString titleTopOfPlotly) {
  qDebug() << "dvs::makeUniqueDavisHtmlName() << "
           << QString::fromStdString(dvs::makeUniqueDavisHtmlName());
  std::vector<double> lines;
  std::vector<std::vector<double>> data;
  char separator;
  for (int i = 0; i < str_lines.size(); ++i) {
    std::vector<double> values;
    auto res = dvs::find_separator(str_lines[i].toStdString(), separator);
    // qDebug() << "sep result: " << separator << "--->" << res;

    if (dvs::MORE_THAN_ONE_SEPARATOR == res)
      continue;
    if (dvs::MABE_COMMA_MABE_DOT == res)
      continue;
    if (dvs::UNDEFINED_BEHAVIOR == res)
      continue;

    bool is_one_value = false;
    std::replace(str_lines[i].begin(), str_lines[i].end(), ',', '.');
    if (res != dvs::GOOD_SEPARATOR) {
      if (dvs::is_string_convertable_to_digit(str_lines[i].toStdString()) ==
          false) {
        continue;
      } else {
        is_one_value = true;
      }
    }
    if (is_one_value == false) {
      QStringList str_values = str_lines[i].split(separator);
      for (int j = 0; j < str_values.size(); ++j) {
        if (dvs::is_string_convertable_to_digit(str_values[j].toStdString()) ==
            false) {
          continue;
        }
        values.emplace_back(std::stod(str_values[j].toStdString()));
      }
    } else {
      values.emplace_back(std::stod(str_lines[i].toStdString()));
    }
    if (values.empty() == false) {
      data.emplace_back(values);
    }
  }

  if (data.empty()) {
    dvs::showReportFileEmpty();
    return;
  }

  if (data[0].size() == 3) {
    qDebug() << "CLOUD_OF_POINTS........";
    std::vector<double> x(data.size(), 0);
    std::vector<double> y(data.size(), 0);
    std::vector<double> color(data.size(), 0);
    for (size_t i = 0; i < data.size(); ++i) {
      x[i] = data[i][0];
      y[i] = data[i][1];
      color[i] = data[i][2];
    }
    dvs::showCloudOfPointsChart(x, y, color,
                                action_fitPlotToBrowserWindow->isChecked());
    return;
  }

  if (data.size() == 2 || data[0].size() == 2) { // chartXY
    dv::Config config;
    config.chart.title = titleTopOfPlotly.toStdString();
    config.chart.isFitPlotToWindow = action_fitPlotToBrowserWindow->isChecked();
    dv::show(data, dvs::makeUniqueDavisHtmlName(), config);
  } else if (data.size() > 1 && data[0].size() > 1) {
    dv::Config config;
    config.heatmap.title = titleTopOfPlotly.toStdString();
    config.heatmap.isFitPlotToWindow =
        action_fitPlotToBrowserWindow->isChecked();
    dv::show(data, dvs::makeUniqueDavisHtmlName(), config);
  } else {
    std::vector<double> showVector;
    if (data.size() > 1 && data[0].size() == 1) {
      std::vector<double> new_data(data.size());
      for (size_t i = 0; i < new_data.size(); ++i) {
        new_data[i] = data[i][0];
      }
      showVector = new_data;
    } else {
      showVector = data[0];
    }
    dv::Config config;
    config.typeVisual = dv::VISUALTYPE_CHART;
    config.chart.title = titleTopOfPlotly.toStdString();
    config.chart.isFitPlotToWindow = action_fitPlotToBrowserWindow->isChecked();
    dv::show(showVector, dvs::makeUniqueDavisHtmlName(), config);
  }
}

bool DavisGUI::checkDateTimeVariant(const QStringList &lines) {

  QString dates;
  std::vector<double> values;
  std::vector<double> force;
  std::vector<std::vector<double>> multicharts;
  getDateTimeData(lines, dates, values, force, multicharts);

  if (multicharts.empty() == false) {
    dvs::transponeMatrix(multicharts);
    dvs::showMultiChart(dates.toStdString(), multicharts,
                        action_fitPlotToBrowserWindow->isChecked());
    return true;
  }

  if (values.size() == 0)
    return false;

  if (force.empty() == false) {
    dvs::showCloudOfPointsChartStr(dates.toStdString(), values, force,
                                   action_fitPlotToBrowserWindow->isChecked());
    return true;
  }
  dvs::showDateTimeChart(dates.toStdString(), values,
                         action_fitPlotToBrowserWindow->isChecked());
  return true;
}

void DavisGUI::selectAndShowFiles() {

  QStringList fileNames = QFileDialog::getOpenFileNames(
      this, QObject::tr("Open Files"), "", QObject::tr("All Files (*)"));
  emit showProgressBar();
  QFuture<void> future =
      QtConcurrent::run(this, &DavisGUI::visualizeFiles, fileNames);
  QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
  connect(watcher, &QFutureWatcher<void>::finished, this,
          &DavisGUI::hideProgressBar);
  watcher->setFuture(future);
}

bool DavisGUI::isFileContainsSingleChart(const QString &pathToFile,
                                         std::vector<double> &outX,
                                         std::vector<double> &outY) {

  QStringList str_lines = getLinesFromFile(pathToFile);

  std::vector<std::vector<double>> data;
  char separator;
  for (int i = 0; i < str_lines.size(); ++i) {
    std::vector<double> values;
    auto res = dvs::find_separator(str_lines[i].toStdString(), separator);
    bool is_one_value = false;
    std::replace(str_lines[i].begin(), str_lines[i].end(), ',', '.');
    if (res != dvs::GOOD_SEPARATOR) {
      if (dvs::is_string_convertable_to_digit(str_lines[i].toStdString()) ==
          false) {
        continue;
      } else {
        is_one_value = true;
      }
    }
    if (is_one_value == false) {
      QStringList str_values = str_lines[i].split(separator);
      for (int j = 0; j < str_values.size(); ++j) {
        if (dvs::is_string_convertable_to_digit(str_values[j].toStdString()) ==
            false) {
          continue;
        }
        values.emplace_back(std::stod(str_values[j].toStdString()));
      }
    } else {
      values.emplace_back(std::stod(str_lines[i].toStdString()));
    }
    data.emplace_back(values);
  }
  if (data.empty())
    return false;

  for (size_t i = 0; i < data.size(); ++i) {
    if (data[i].size() == 1) {

      double value = data[i][0];
      outX.push_back(i + 1);
      outY.push_back(value);

    } else if (data[i].size() == 2) {

      outX.push_back(data[i][0]);
      outY.push_back(data[i][1]);

    } else {

      for (size_t j = 0; j < data[i].size(); ++j) {
        outX.push_back(j + 1);
        outY.push_back(data[i][j]);
      }
    }
  }
  return true;
}

void DavisGUI::dragEnterEvent(QDragEnterEvent *event) {

  QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);

  QRect originalGeometry = geometry();
  int shakeDistance = 6; // Distance to shake
  int duration = 70;     // Duration of each shake step

  for (int i = 0; i < 6; ++i) {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(duration);
    if (i % 4 == 0) {
      animation->setStartValue(originalGeometry.translated(-shakeDistance, 0));
      animation->setEndValue(originalGeometry.translated(shakeDistance, 0));
    } else if (i % 4 == 1) {
      animation->setStartValue(originalGeometry.translated(shakeDistance, 0));
      animation->setEndValue(originalGeometry.translated(-shakeDistance, 0));
    } else if (i % 4 == 2) {
      animation->setStartValue(originalGeometry.translated(0, -shakeDistance));
      animation->setEndValue(originalGeometry.translated(0, shakeDistance));
    } else if (i % 4 == 3) {
      animation->setStartValue(originalGeometry.translated(0, shakeDistance));
      animation->setEndValue(originalGeometry.translated(0, -shakeDistance));
    }
    group->addAnimation(animation);
  }

  group->start(QAbstractAnimation::DeleteWhenStopped);

  setFullOpacity();
  if (event->mimeData()->hasUrls()) {
    event->acceptProposedAction();
  } else {
    qDebug() << "not drop";
  }
}

void DavisGUI::dragLeaveEvent(QDragLeaveEvent *event) {
  if (m_isMinStyleWindow) {
    setSemiOpacity();
  }
}

void DavisGUI::dropEvent(QDropEvent *event) {
  emit showProgressBar();
  QList<QUrl> file_list_urls = event->mimeData()->urls();
  QStringList file_list;
  for (int i = 0; i < file_list_urls.size(); ++i) {
    file_list.append(file_list_urls[i].toLocalFile());
  }

  QFuture<void> future =
      QtConcurrent::run(this, &DavisGUI::visualizeFiles, file_list);
  QFutureWatcher<void> *watcher = new QFutureWatcher<void>(this);
  connect(watcher, &QFutureWatcher<void>::finished, this,
          &DavisGUI::hideProgressBar);
  watcher->setFuture(future);
}

void DavisGUI::visualizeFiles(const QStringList &file_list) {
  if (file_list.isEmpty()) {
    return;
  }

  if (file_list.size() > 1) {
    QVector<QString> dates_list;
    std::vector<std::vector<double>> all_values;
    for (int i = 0; i < file_list.size(); ++i) {
      QStringList lines;
      QString dates;
      std::vector<double> values;
      std::vector<double> force;
      std::vector<std::vector<double>> multicharts;
      qDebug() << "we are here";
      lines = getLinesFromFile(file_list[i]);

      getDateTimeData(lines, dates, values, force, multicharts);
      if (dates.isEmpty() == false) {
        dates_list.append(dates);
        all_values.emplace_back(values);
      }
    }
    if (dates_list.isEmpty() == false) {
      dvs::showMultiChart(dates_list[0].toStdString(), all_values,
                          action_fitPlotToBrowserWindow->isChecked());
      return;
    }
    dv::holdOn();
    for (int i = 0; i < file_list.size(); ++i) {
      std::vector<double> outX, outY;

      if (isFileContainsSingleChart(file_list[i], outX, outY)) {

        dv::show(outX, outY, file_list[i].split("/").last().toStdString());
      }
    }
    dv::holdOff();
    return;
  }
  QString filePath = file_list.first();
  QFileInfo info(filePath);

  QString suffix = info.suffix();
  QStringList suffixes = {"jpg", "bmp", "png", "svg", "mp4"};
  for (int i = 0; i < suffixes.size(); ++i) {
    if (suffix == suffixes[i]) {
      QProcess process;
      process.startDetached("cmd.exe", QStringList() << "/C" << filePath);
      return;
    }
  }
  if (suffix == "json") {
    readJsonToPlot(filePath);
    return;
  }
  if (suffix == "bin") {
    if (mayBeShowBIN(filePath)) {
      return;
    };
  }

  if (info.exists()) {
    QTime time;
    time.start();
    QFile file(filePath);
    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    if (file.open(QIODevice::ReadWrite) == false) {
      dvs::showReportFileNotFounded();
      return;
    };

    QString line;
    QStringList str_lines;
    while (ts.readLineInto(&line)) {
      if (line.isEmpty())
        continue;
      str_lines.append(line);
    }
    if (str_lines.empty()) {
      dvs::showReportFileEmpty();
      return;
    }
    file.close();
    if (checkDateTimeVariant(str_lines) == false) {
      readPlotText(str_lines, info.baseName());
      qDebug() << "matrix read MAKER: " << time.elapsed();
    };
  } else {
    qDebug() << "not exist";
    dvs::showReportFileNotFounded();
  }
}

void DavisGUI::paintEvent(QPaintEvent *event) {
  const int PADDING = 10;
  QRectF rectangle(PADDING, PADDING + 20, this->width() - 2 * PADDING,
                   this->height() - 2 * PADDING - 20);
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);
  QPainterPath path;
  path.addRoundedRect(rectangle, 5, 5);

  QPen dashpen;
  dashpen.setStyle(Qt::DashLine);
  dashpen.setColor(QColor(150, 150, 150));
  dashpen.setWidth(2);
  painter.setPen(dashpen);
  painter.fillPath(path, QColor(160, 60, 60));
  painter.drawPath(path);
  painter.fillPath(path, QColor(60, 60, 60));
  painter.drawPath(path);
  painter.end();
  event->accept();
}

void DavisGUI::mousePressEvent(QMouseEvent *event) { m_point = event->pos(); }

void DavisGUI::mouseMoveEvent(QMouseEvent *event) {
  move(event->globalPos() - m_point);
}

void DavisGUI::keyPressEvent(QKeyEvent *event) {
  if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_V) {
    pasteFromClipboard();
  } else {
    QMainWindow::keyPressEvent(event);
  }
}

void DavisGUI::setFullOpacity() {
  if (m_isMinStyleWindow) {
    animationOpacity->stop();
    animationOpacity->setStartValue(windowOpacity());
    animationOpacity->setEndValue(1.0); // Непрозрачное окно
    animationOpacity->start();
  }
}

void DavisGUI::enterEvent(QEvent *event) {
  setFullOpacity();
  QMainWindow::enterEvent(event);
}

void DavisGUI::setSemiOpacity() {
  if (m_isMinStyleWindow) {
    animationOpacity->stop();
    animationOpacity->setStartValue(windowOpacity());
    animationOpacity->setEndValue(OPACITY_IF_NOT_ACTIVE); // Полупрозрачное окно
    animationOpacity->start();
  }
}

void DavisGUI::leaveEvent(QEvent *event) {
  setSemiOpacity();
  QMainWindow::leaveEvent(event);
}
