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
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QSignalTransition>
#include <QGraphicsColorizeEffect>



const int ANIMATION_DURATION = 300;
#include <QJsonArray>
#include "json_utils.h"
#include "QDateTime"
#include <QProcess>

DavisGUI::DavisGUI(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::DavisGUI)
{
    isAboutWindowShowed = false;
    m_isMinStyleWindow = false;
    ui->setupUi(this);
    this->setAcceptDrops(true);
    QHBoxLayout* hbl = ui->horizontalLayout_menu;
    QMenuBar* mb = new QMenuBar;
    QString menuStyle(
                "QMenuBar {"
                "    background-color: transparent;"
                "    font-size: 13px;"
                "}"
                "QMenuBar:hover {"
                "    background-color: rgb(42, 130, 218);"
                "}"
                );
    QMenu*  menu_root = new QMenu("Menu");
    mb->setStyleSheet(menuStyle);
    action_surface = new QAction("surface");
    action_surface->setCheckable(true);
    action_heatmap = new QAction("heatmap");
    action_heatmap->setCheckable(true);
    action_heatmap->setChecked(true);
    connect(action_heatmap, &QAction::triggered, [this]() {action_surface->setChecked(false);});
    connect(action_surface, &QAction::triggered, [this]() {action_heatmap->setChecked(false);});

    QMenu*  menu_view = new QMenu("View");
    menu_view->setStyleSheet(menuStyle);
    menu_view->addAction(action_surface);
    menu_view->addAction(action_heatmap);
    mb->setFixedSize(QSize(50, 25));
    //mb->setStyleSheet("background-color:rgb(82,82,82);");
    menu_root->addMenu(menu_view);
    mb->addMenu(menu_root);
    hbl->addWidget(mb);
    hbl->addItem(new QSpacerItem(2, 25, QSizePolicy::Expanding, QSizePolicy::Expanding));


    QString buttonStyle(
                "QPushButton {"
                "    background-color: none;"
                "    border: none;"
                "    font-size: 13px;"
                "}"
                "QPushButton:hover {"
                "    background-color: rgb(42, 130, 218);"
                "}"
                );
    QPushButton* qpbAbout = new QPushButton;
    qpbAbout->setFlat(true);
    qpbAbout->setStyleSheet(buttonStyle);
    qpbAbout->setToolTip("About");
    connect(qpbAbout, &QPushButton::clicked, this, &DavisGUI::showAboutWindow);
    qpbAbout->setFixedSize(QSize(25, 25));
    qpbAbout->setText("?");
    hbl->addWidget(qpbAbout);

    QPushButton* qpbMinMaxSize = new QPushButton;
    qpbMinMaxSize->setFlat(true);
    qpbMinMaxSize->setStyleSheet(buttonStyle);
    qpbMinMaxSize->setToolTip("Full/compact size");
    connect(qpbMinMaxSize, &QPushButton::clicked, [this]() {
        m_isMinStyleWindow = !m_isMinStyleWindow;
        if (m_isMinStyleWindow)
            setMinStyleWindow(ANIMATION_DURATION);
        else
            setMaxStyleWindow(ANIMATION_DURATION);
    });
    qpbMinMaxSize->setFixedSize(QSize(25, 25));
    qpbMinMaxSize->setText("◰");
    hbl->addWidget(qpbMinMaxSize);

    QPushButton* qpbMinim = new QPushButton;
    qpbMinim->setFlat(true);
    qpbMinim->setStyleSheet(buttonStyle);
    qpbMinim->setToolTip("Minimize");
    connect(qpbMinim, &QPushButton::clicked, [this]() {this->showMinimized();});
    qpbMinim->setFixedSize(QSize(25, 25));
    qpbMinim->setText("─");
    hbl->addWidget(qpbMinim);

    QString buttonStyleExit(
                "QPushButton {"
                "    background-color: none;"
                "    border: none;"
                "    font-size: 13px;"
                "}"
                "QPushButton:hover {"
                "    background-color: rgb(218, 42, 42);"
                "}"
                );
    QPushButton* qpbExit = new QPushButton;
    qpbExit->setFlat(true);
    qpbExit->setStyleSheet(buttonStyleExit);
    qpbExit->setToolTip("Close");
    connect(qpbExit, &QPushButton::clicked, [this]() {this->close();});
    qpbExit->setFixedSize(QSize(25, 25));
    qpbExit->setText("✕");
    hbl->addWidget(qpbExit);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


    qpbOpen = new AnimatedButton("Open", QColor(150, 150, 150), QColor(42, 130, 218), this);
    qpbOpen->setGeometry(70, 170, 90, 30);
    qpbOpen->setOriginalGeometry(qpbOpen->geometry());


    qpbBuffer = new AnimatedButton("Copy from buffer or Ctrl+V",
                                                    QColor(150, 150, 150),
                                                    QColor(42, 130, 218),
                                                    this);
    qpbBuffer->setGeometry(170, 170, 170, 30);
    qpbBuffer->setOriginalGeometry(qpbBuffer->geometry());

    connect(qpbOpen, &QPushButton::released, this, &DavisGUI::selectAndShowFiles);
    connect(qpbBuffer, &QPushButton::released, this, &DavisGUI::pasteFromClipboard);
}

DavisGUI::~DavisGUI() {
    delete ui;
}

void DavisGUI::show() {
    QMainWindow::show();
    setMaxStyleWindow(0);
}

void DavisGUI::setMaxStyleWindow(int animDuration) {
    m_isMinStyleWindow = false;
    ui->label_doc->setVisible(false);
    ui->label_arrow->setVisible(false);
    ui->label_graph->setVisible(false);
    ui->label_text->setVisible(false);
    qpbBuffer->setVisible(false);
    qpbOpen->setVisible(false);
    update();

    QPropertyAnimation* animationFrame = new QPropertyAnimation(ui->frame_panel, "geometry");
    animationFrame->setEasingCurve(QEasingCurve::InOutQuad);
    animationFrame->setDuration(animDuration);
    animationFrame->setStartValue(ui->frame_panel->geometry());
    animationFrame->setEndValue(QRect(0, 0, 397, 25));

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(animDuration);
    animation->setEasingCurve(QEasingCurve::InOutQuad);
    // Начальное и конечное значение анимации
    animation->setStartValue(this->geometry());
    int xOld = this->geometry().x();
    int yOld = this->geometry().y();
    int newWidth = 397;
    int newHeight = 370;
    int deltaW = newWidth - this->geometry().width();
    animation->setEndValue(QRect(xOld - deltaW, yOld, newWidth, newHeight));
    connect(animation, &QPropertyAnimation::finished, this, [this]() {
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
        update();
    });

    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    group->addAnimation(animation);
    group->addAnimation(animationFrame);
    group->start();



}

void DavisGUI::setMinStyleWindow(int animDuration) {
    m_isMinStyleWindow = true;
    ui->label_doc->setVisible(false);
    ui->label_arrow->setVisible(false);
    ui->label_graph->setVisible(false);
    ui->label_text->setVisible(false);
    qpbBuffer->setVisible(false);
    qpbOpen->setVisible(false);
    //ui->frame_panel->setVisible(false);
    update();

    QPropertyAnimation* animationFrame = new QPropertyAnimation(ui->frame_panel, "geometry");
    animationFrame->setDuration(animDuration);
    animationFrame->setEasingCurve(QEasingCurve::InOutQuad);
    animationFrame->setStartValue(ui->frame_panel->geometry());
    animationFrame->setEndValue(QRect(0, 0, 159, 25));

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(animDuration); // Длительность анимации в миллисекундах
    animation->setEasingCurve(QEasingCurve::InOutQuad); // Кривая анимации
    // Начальное и конечное значение анимации
    animation->setStartValue(this->geometry());

    int xOld = this->geometry().x();
    int yOld = this->geometry().y();
    int newWidth = 159;
    int newHeight = 137;
    int deltaW = newWidth - this->geometry().width();
    animation->setEndValue(QRect(xOld - deltaW, yOld, newWidth, newHeight)); // Пример конечного размера
    //    animation->setEndValue(QRect(this->geometry().x(), this->geometry().y(), 159, 137)); // Пример конечного размера
    connect(animation, &QPropertyAnimation::finished, this, [this]() {
        ui->label_doc->setVisible(true);
        ui->label_arrow->setVisible(true);
        ui->label_graph->setVisible(true);
        ui->frame_panel->setVisible(true);
        ui->label_doc->setGeometry(30, 60, 41, 41);
        ui->label_arrow->setGeometry(60, 60, 41, 41);
        ui->label_graph->setGeometry(90, 60, 41, 41);
        update();
    });
    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    group->addAnimation(animation);
    group->addAnimation(animationFrame);
    group->start();
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

void DavisGUI::pasteFromClipboard() {
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
        dvs::showReportFileEmpty();
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
void DavisGUI::selectAndShowFiles() {
    QApplication::processEvents();
    QStringList fileNames = QFileDialog::getOpenFileNames(this,
                                                          QObject::tr("Open Files"),
                                                          "",
                                                          QObject::tr("All Files (*)"));

    visualizeFiles(fileNames);

}

bool DavisGUI::isFileContainsSingleChart(const QString& pathToFile,
                                         QString& outX,
                                         QString& outY)
{
    QFile file(pathToFile);
    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    if (file.open(QIODevice::ReadWrite) == false) {
        return false;
    };
    QString line;
    QStringList str_lines;
    while (ts.readLineInto(&line)) {
        str_lines.append(line);
    }
    if (str_lines.empty()) {
        return false;
    }
    file.close();

    std::vector<std::vector<double>> data;
    char separator;
    for (int i = 0; i < str_lines.size(); ++i) {
        std::vector<double>values;
        auto res = dvs::find_separator(str_lines[i].toStdString(), separator);
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
    if(data.empty())return false;

    for(size_t i=0;i<data.size();++i){
        if(data[i].size()==1){

            double value = data[i][0];
            outX.append(QString::number(i+1));
            if(i<data.size()-1)outX.append(",");
            outY.append(QString::number(value));
            if(i<data.size()-1)outY.append(",");

        }else if(data[i].size()==2){

            outX.append(QString::number(data[i][0]));
            if(i<data.size()-1)outX.append(",");
            outY.append(QString::number(data[i][1]));
            if(i<data.size()-1)outY.append(",");

        }else{


            for(size_t j=0;j<data[i].size();++j){
                outX.append(QString::number(j+1));
                if(j<data[i].size()-1)outX.append(",");
                outY.append(QString::number(data[i][j]));
                if(j<data[i].size()-1)outY.append(",");
            }

        }
    }
    qDebug()<<outX;
    qDebug()<<outY;
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
    QList<QUrl> file_list_urls = event->mimeData()->urls();
    QStringList file_list;
    for (int i = 0; i < file_list_urls.size(); ++i) {
        file_list.append(file_list_urls[i].toLocalFile());
    }
    visualizeFiles(file_list);
}

void DavisGUI::visualizeFiles(const QStringList &file_list)
{
    if(file_list.isEmpty()){
        return;
    }
    QString all_chart_blocks;
    const QString trace_name = "trace%1";
    QString all_traces_names;
    if(file_list.size()>1){
        QStringList onlySingleChartList;
        qDebug()<<"file list size: "<<file_list.size();
        for(int i=0;i<file_list.size();++i){
            QString outX,outY;
            QString trace_block = dvs::kHtmlMultiChartBlock;
            if(isFileContainsSingleChart(file_list[i],outX,outY)){
                //qDebug()<<file_list[i].toLocalFile();
                all_chart_blocks.append(trace_block.arg(QString::number(i+1),outX,outY));
                all_traces_names.append(QString(trace_name).arg(i+1));
                if(i<file_list.size()-1){
                    all_traces_names.append(",");
                }
            }
        }
        QString multichartPage = dvs::kHtmlMultiChartModel;
        multichartPage = multichartPage.arg(dvs::kPlotlyJsName,all_chart_blocks,all_traces_names);
        qDebug()<<multichartPage;
        dvs::saveStringToFile(dvs::kReportPagePath, multichartPage.toStdString());
        dvs::openFileBySystem(dvs::kReportPagePath);
        return;
    }
    QString filePath =  file_list.first();
    QFileInfo info(filePath);
    if (info.exists()) {
        QFile file(filePath);
        QTextStream ts(&file);
        ts.setCodec("UTF-8");
        if (file.open(QIODevice::ReadWrite) == false) {
            dvs::showReportFileNotFounded();
            return;
        };

        QString suffix = info.suffix();
        QStringList suffixes = {"jpg","bmp","png","svg","mp4","json"};
        for(int i=0;i<suffixes.size();++i){
            if(suffix == suffixes[i]){
                QProcess process;
                process.startDetached("cmd.exe", QStringList() << "/C" << filePath);
                return;
            }
        }

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
    const int PADDING = 10;
    QRectF rectangle(PADDING, PADDING + 20, this->width() - 2 * PADDING, this->height() - 2 * PADDING - 20);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(rectangle, 5, 5);
    QPen dashpen;
    dashpen.setStyle(Qt::DashLine);
    dashpen.setColor(QColor(150, 150, 150));
    dashpen.setWidth(2);
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

void DavisGUI::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_V) {
        pasteFromClipboard();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

