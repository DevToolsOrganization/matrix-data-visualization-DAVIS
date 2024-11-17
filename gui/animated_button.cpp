#include "animated_button.h"
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

QString buttonStyle(
            "QPushButton {"
            "    background-color: %1;" // Цвет фона
            "    border: none;" // Без границ
            "    color:white;" // Цвет текста
            "    text-align: center;" // Выравнивание текста
            "    text-decoration: none;" // Без подчеркивания текста
            "    font-size: 13px;" // Размер шрифта
            "    border-radius: 8px;" // Закругленные углы
            "}"
            );


AnimatedButton::AnimatedButton(const QString &text, QColor startColor, QColor endColor, QWidget *parent) : QPushButton(text, parent) {
        setStyleSheet(buttonStyle.arg(startColor.name()));
//        "QPushButton:hover {"
//        "    background-color: rgb(42, 130, 218);" // Цвет фона при наведении
//        "    color: white;" // Цвет текста
//        "}"
//        "QPushButton:pressed {"
//        "    background-color: #45a049;" // Цвет фона при нажатии
//        "}"
        m_startColor = startColor;
        m_endColor = endColor;
        connect(this, &QPushButton::pressed, this, &AnimatedButton::animateButtonPress);
        connect(this, &QPushButton::released, this, &AnimatedButton::animateButtonRelease);
}

void AnimatedButton::enterEvent(QEvent *event) {
    startColorAnimation(m_startColor, m_endColor);

    QPushButton::enterEvent(event);
}

void AnimatedButton::leaveEvent(QEvent *event) {
    startColorAnimation(m_endColor, m_startColor);
    QPushButton::leaveEvent(event);
}

void AnimatedButton::animateButtonPress() {
    qDebug()<<"current: "<<geometry();
    qDebug()<<"origin: "<<m_originalGeometry;

    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(geometry());
    animation->setEndValue(QRect(m_originalGeometry.x(), m_originalGeometry.y()+5,
                                 m_originalGeometry.width(), m_originalGeometry.height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void AnimatedButton::animateButtonRelease() {
    qDebug()<<"current: "<<geometry();
    qDebug()<<"origin: "<<m_originalGeometry;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(geometry());
    animation->setEndValue(m_originalGeometry);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void AnimatedButton::startColorAnimation(const QColor &startColor, const QColor &endColor) {
    QTimer *timer = new QTimer(this);
    timer->setInterval(15); // Интервал обновления в миллисекундах
    int duration = 210; // Длительность анимации в миллисекундах (кратно ^)
    int steps = duration / timer->interval();
    int currentStep = 0;

    connect(timer, &QTimer::timeout, this, [=] () mutable {
        if (currentStep > steps) {
            timer->stop();
            timer->deleteLater();
            return;
        }

        qreal progress = static_cast<qreal>(currentStep) / steps;
        QColor currentColor = startColor;
        currentColor.setRed(startColor.red() + progress * (endColor.red() - startColor.red()));
        currentColor.setGreen(startColor.green() + progress * (endColor.green() - startColor.green()));
        currentColor.setBlue(startColor.blue() + progress * (endColor.blue() - startColor.blue()));
        setStyleSheet(buttonStyle.arg(currentColor.name()));
        currentStep++;
    });

    timer->start();
}

void AnimatedButton::setOriginalGeometry(const QRect &newOriginalGeometry)
{
    m_originalGeometry = newOriginalGeometry;
}
