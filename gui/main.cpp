#include "davis_gui.h"
#include "../common_utils/common_constants.h"
#include "../common_utils/common_utils.h"
#include "QFile"
#include "QDebug"
#include "QUrl"
#include "QStyleFactory"

#include <QApplication>

void applyDark(){
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    QColor gray(230,230,230);
    darkPalette.setColor(QPalette::Window,QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText,gray);
    darkPalette.setColor(QPalette::Disabled,QPalette::WindowText,QColor(127,127,127));
    darkPalette.setColor(QPalette::Base,QColor(42,42,42));
    darkPalette.setColor(QPalette::AlternateBase,QColor(66,66,66));
    darkPalette.setColor(QPalette::ToolTipBase,gray);
    darkPalette.setColor(QPalette::ToolTipText,gray);
    darkPalette.setColor(QPalette::Text,gray);
    darkPalette.setColor(QPalette::Disabled,QPalette::Text,QColor(127,127,127));
    darkPalette.setColor(QPalette::Dark,QColor(35,35,35));
    darkPalette.setColor(QPalette::Shadow,QColor(20,20,20));
    darkPalette.setColor(QPalette::Button,QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText,gray);
    darkPalette.setColor(QPalette::Disabled,QPalette::ButtonText,QColor(127,127,127));
    darkPalette.setColor(QPalette::BrightText,Qt::red);
    darkPalette.setColor(QPalette::Link,QColor(42,130,218));
    darkPalette.setColor(QPalette::Highlight,QColor(42,130,218));
    darkPalette.setColor(QPalette::Disabled,QPalette::Highlight,QColor(80,80,80));
    darkPalette.setColor(QPalette::HighlightedText,gray);
    darkPalette.setColor(QPalette::Disabled,QPalette::HighlightedText,QColor(127,127,127));

    qApp->setPalette(darkPalette);
};

int main(int argc, char *argv[])
{
    dvs::mayBeCreateJsWorkingFolder();
    if(dvs::isPlotlyScriptExists()==false){
       qDebug()<<"try to copy file.....";
       QFile::copy(":/plotly_maker/"+QString(dvs::kPlotlyJsName),dvs::kPlotlyJsWorkPath);
    }else{
        qDebug()<<"js exists...";
    }
    QApplication a(argc, argv);
    applyDark();
    DavisGUI w;
    w.show();
    return a.exec();
}
