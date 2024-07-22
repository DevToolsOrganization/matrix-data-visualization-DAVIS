#include "davis_gui.h"
#include "./ui_davis_gui.h"

#include "../davis_one/davis.h"

DavisGUI::DavisGUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DavisGUI)
{
    ui->setupUi(this);
    //std::vector<double> test_data = {5,6,8};
    //dv::show(test_data);
}

DavisGUI::~DavisGUI()
{
    delete ui;
}

