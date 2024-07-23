#ifndef DAVISGUI_H
#define DAVISGUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DavisGUI; }
QT_END_NAMESPACE

class DavisGUI : public QMainWindow
{
    Q_OBJECT

public:
    DavisGUI(QWidget *parent = nullptr);
    ~DavisGUI();

private:
    Ui::DavisGUI *ui;

    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};
#endif // DAVISGUI_H
