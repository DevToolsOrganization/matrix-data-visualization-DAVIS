#ifndef ANIMATED_BUTTON_H
#define ANIMATED_BUTTON_H
#include <QApplication>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsColorizeEffect>
#include <QEvent>

class AnimatedButton : public QPushButton {
    Q_OBJECT

public:
    AnimatedButton(const QString &text, QColor &startColor, QColor &endColor, QWidget *parent = nullptr);
protected:
    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;

private:
    void startColorAnimation(const QColor &startColor, const QColor &endColor);

    QColor m_startColor;
    QColor m_endColor;


};




#endif // ANIMATED_BUTTON_H
