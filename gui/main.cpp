#include "davis_gui.h"
#include "../common_utils/common_constants.h"
#include "../common_utils/common_utils.h"
#include "QFile"
#include "QDebug"
#include "QUrl"

#include <QApplication>

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
    DavisGUI w;
    w.show();
    return a.exec();
}
