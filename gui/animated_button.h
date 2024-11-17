#ifndef ANIMATED_BUTTON_H
#define ANIMATED_BUTTON_H
#include <QApplication>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsColorizeEffect>
#include <QEvent>

class AnimatedButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)

public:
    AnimatedButton(const QString &text, QColor startColor, QColor endColor, QWidget *parent = nullptr);

    void setOriginalGeometry(const QRect &newOriginalGeometry);

    QColor backgroundColor() const;

    void setBackgroundColor(const QColor &color);

protected:
    void enterEvent(QEvent *event) override;

    void leaveEvent(QEvent *event) override;
private slots:
    void animateButtonPress();

    void animateButtonRelease();

private:
    void startColorAnimation(const QColor &startColor, const QColor &endColor);

    QColor m_startColor;
    QColor m_endColor;
    QRect m_originalGeometry;

    QColor m_backgroundColor;
};




#endif // ANIMATED_BUTTON_H
