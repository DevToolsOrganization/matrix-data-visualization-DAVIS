#include "davis_gui.h"
#include "./ui_davis_gui.h"

#include "../davis_one/davis.h"

#include <QApplication>
#include "QDragEnterEvent"
#include "QMimeData"
#include "QDebug"
#include "QFileInfo"
#include "QPainter"
#include "QMenuBar"
#include "QHBoxLayout"
#include "QPushButton"
#include "QPainterPath"
#include "QFileDialog"
#include "QTextStream"
#include <QClipboard>
#include <QJsonArray>
#include "json_utils.h"
#include "QDateTime"

DavisGUI::DavisGUI(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::DavisGUI),
    m_copy_paste_action(new QAction("Вставить из буфера обмена")) {
  isAboutWindowShowed = false;
  ui->setupUi(this);
  ui->centralwidget->addAction(m_copy_paste_action);
  this->setAcceptDrops(true);
  QHBoxLayout* hbl = ui->horizontalLayout_menu;
  QMenuBar* mb = new QMenuBar;
  QMenu*  menu_root = new QMenu("Menu");
  QAction*  action_help = new QAction("About");
  action_surface = new QAction("surface");
  action_surface->setCheckable(true);
  action_heatmap = new QAction("heatmap");
  action_heatmap->setCheckable(true);
  action_heatmap->setChecked(true);
  connect(action_heatmap, &QAction::triggered, [this]() {action_surface->setChecked(false);});
  connect(action_surface, &QAction::triggered, [this]() {action_heatmap->setChecked(false);});
  connect(action_help, SIGNAL(triggered()), this, SLOT(showAboutWindow()));

  QMenu*  menu_view = new QMenu("View");
  menu_view->addAction(action_surface);
  menu_view->addAction(action_heatmap);
  mb->setFixedSize(QSize(50, 20));
  mb->setStyleSheet("background-color:rgb(82,82,82);");
  menu_root->addMenu(menu_view);
  menu_root->addAction(action_help);
  mb->addMenu(menu_root);


  hbl->addWidget(mb);
  hbl->addItem(new QSpacerItem(2, 20, QSizePolicy::Expanding, QSizePolicy::Expanding));
  QPushButton* qpbMinim = new QPushButton;
  connect(qpbMinim, &QPushButton::clicked, [this]() {this->showMinimized();});
  qpbMinim->setFixedSize(QSize(20, 20));
  qpbMinim->setText("─");
  hbl->addWidget(qpbMinim);
  QPushButton* qpbExit = new QPushButton;
  connect(qpbExit, &QPushButton::clicked, [this]() {this->close();});
  qpbExit->setFixedSize(QSize(20, 20));
  qpbExit->setText("✕");
  hbl->addWidget(qpbExit);
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

  connect(m_copy_paste_action, SIGNAL(triggered()), SLOT(pasteTextAdded()));
}

DavisGUI::~DavisGUI() {
  delete ui;
}

void DavisGUI::showAboutWindow() {
  if (isAboutWindowShowed) {
    delete aboutWindow;
  }
  aboutWindow = new About_window(); //NO LEAK because of Qt::WA_DeleteOnClose
  connect(aboutWindow, &About_window::about_window_closed, [ = ]() {isAboutWindowShowed = false;});
  aboutWindow->show();
  isAboutWindowShowed = true;
}

void DavisGUI::pasteTextAdded() {
  QClipboard* clipboard = QApplication::clipboard();
  QString clipboardText = clipboard->text();
  qDebug() << clipboardText;
  QStringList lines = clipboardText.split(QRegExp("[\r\n]+"));
  if (checkDateTimeVariant(lines) == false) {
    readPlotText(lines);
  };
}

void DavisGUI::readPlotText(QStringList& str_lines) {
  std::vector<double>lines;
  std::vector<std::vector<double>> data;
  char separator;
  for (int i = 0; i < str_lines.size(); ++i) {
    std::vector<double>values;
    auto res = dvs::find_separator(str_lines[i].toStdString(), separator);
    //qDebug() << "sep result: " << separator << "--->" << res;
    bool is_one_value = false;
    std::replace(str_lines[i].begin(), str_lines[i].end(), ',', '.');
    if (res != dvs::GOOD_SEPARATOR) {
      if (dvs::is_string_convertable_to_digit(str_lines[i].toStdString()) == false) {
        continue;
      } else {
        is_one_value = true;
      }
    }
    if (is_one_value == false) {
      QStringList str_values = str_lines[i].split(separator);
      for (int j = 0; j < str_values.size(); ++j) {
        if (dvs::is_string_convertable_to_digit(str_values[j].toStdString()) == false) {
          continue;
        }
        values.emplace_back(std::stod(str_values[j].toStdString()));
      }
    } else {
      values.emplace_back(std::stod(str_lines[i].toStdString()));
    }
    data.emplace_back(values);
  }

  if (data.empty()) {
    qDebug() << "Empty file";
    return;
  }

  if (data.size() == 2 || data[0].size() == 2) { //chartXY
    dv::show(data, "chartXY");
  } else if (data.size() > 1 && data[0].size() > 1) {
    if (action_heatmap->isChecked()) {
      dv::show(data);
    } else if (action_surface->isChecked()) {
      dv::Config config;
      config.typeVisual = dv::VISUALTYPE_SURFACE;
      dv::show(data, "surface", config);
    }
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
    dv::show(showVector, "chart", config);
  }
}

bool DavisGUI::checkDateTimeVariant(const QStringList& lines) {

  QJsonArray jarr;
  if(jsn::getJsonArrayFromFile("date_time_formats.json", jarr)==false){
  jsn::getJsonArrayFromFile(":/date_time_formats.json", jarr);
  }
  qDebug() << jarr;
  QString dates;
  std::vector<double> values;

  for (int i = 0; i < lines.size(); ++i) {
    QString test = lines[i];
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
        //2013-10-04 22:23:00
        qDebug() << dt.toString("yyyy-MM-dd hh:mm:ss");
        dates.append("'");
        dates.append(dt.toString("yyyy-MM-dd hh:mm:ss"));
        dates.append("'");
        if (i < lines.size() - 1) {
          dates.append(",");
        }

        auto values_list = test.split(separator);
        if (values_list.size() != 2) {
          continue;
        }
        double value = values_list[1].toDouble();
        qDebug()<<value;
        values.emplace_back(value);

      }
    }
  }
  if (values.size() == 0)
    return false;
  qDebug() << "check sizes: " << lines.size() << values.size();
  if (lines.size() != values.size()) {
    return false;
  }
  dvs::showDateTimeChart(dates.toStdString(), values);
  return true;


}

void DavisGUI::dragEnterEvent(QDragEnterEvent* event) {
  if (event->mimeData()->hasUrls()) {
    event->acceptProposedAction();
  } else {
    qDebug() << "not drop";
  }
}

void DavisGUI::dropEvent(QDropEvent* event) {
  QString filePath =  event->mimeData()->urls().first().toLocalFile();
  QFileInfo info(filePath);
  qDebug() << "---file path--->" << filePath;
  if (info.exists()) {
    qDebug() << "exist";
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
      str_lines.append(line);
    }
    if (str_lines.empty()) {
      dvs::showReportFileEmpty();
      return;
    }
    file.close();
    if (checkDateTimeVariant(str_lines) == false) {
      readPlotText(str_lines);
    };
  } else {
    qDebug() << "not exist";
    dvs::showReportFileNotFounded();
  }
}

void DavisGUI::paintEvent(QPaintEvent* event) {
  const int PADDING = 20;
  QRectF rectangle(PADDING, PADDING + 20, this->width() - 2 * PADDING, this->height() - 2 * PADDING - 20);
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing);
  QPainterPath path;
  path.addRoundedRect(rectangle, 10, 10);
  QPen dashpen;
  dashpen.setStyle(Qt::DashLine);
  dashpen.setColor(QColor(150, 150, 150));
  dashpen.setWidth(3);
  painter.setPen(dashpen);
  painter.fillPath(path, QColor(60, 60, 60));
  painter.drawPath(path);
  painter.end();
  event->accept();
}

void DavisGUI::mousePressEvent(QMouseEvent* event) {
  m_point = event->pos();
}

void DavisGUI::mouseMoveEvent(QMouseEvent* event) {
  move(event->globalPos() - m_point);
}

