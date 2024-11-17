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
    AnimatedButton(const QString &text, QWidget *parent = nullptr);
protected:
    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;

private:
    void startColorAnimation(const QColor &startColor, const QColor &endColor);

    QGraphicsColorizeEffect *effect;
    QPropertyAnimation *hoverAnimation;
    QPropertyAnimation *leaveAnimation;
    QColor m_backgroundColor;
};




#endif // ANIMATED_BUTTON_H
