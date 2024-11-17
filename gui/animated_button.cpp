#include "animated_button.h"
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

QString buttonStyle(
        "QPushButton {"
        "    background-color: %1;"
        "    border: none;"
        "    color:white;" // text color
        "    text-align: center;"
        "    font-size: 13px;"
        "    border-radius: 14px;"
        "}"
        );


AnimatedButton::AnimatedButton(const QString &text, QColor startColor, QColor endColor, QWidget *parent) : QPushButton(text, parent) {
    setStyleSheet(buttonStyle.arg(startColor.name()));
    m_startColor = startColor;
    m_endColor = endColor;
    connect(this, &QPushButton::pressed, this, &AnimatedButton::animateButtonPress);
    connect(this, &QPushButton::released, this, &AnimatedButton::animateButtonRelease);
}

void AnimatedButton::enterEvent(QEvent *event) {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "backgroundColor");
    animation->setDuration(250);
    animation->setStartValue(m_startColor);
    animation->setEndValue(m_endColor);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    QPushButton::enterEvent(event);
    QPushButton::enterEvent(event);
}

void AnimatedButton::leaveEvent(QEvent *event) {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "backgroundColor");
    animation->setDuration(250);
    animation->setStartValue(m_endColor);
    animation->setEndValue(m_startColor);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    QPushButton::leaveEvent(event);
}

void AnimatedButton::animateButtonPress() {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(geometry());
    animation->setEndValue(QRect(m_originalGeometry.x(), m_originalGeometry.y()+5,
                                 m_originalGeometry.width(), m_originalGeometry.height()));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void AnimatedButton::animateButtonRelease() {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(100);
    animation->setStartValue(geometry());
    animation->setEndValue(m_originalGeometry);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void AnimatedButton::setOriginalGeometry(const QRect &newOriginalGeometry)
{
    m_originalGeometry = newOriginalGeometry;
}

QColor AnimatedButton::backgroundColor() const {
    return m_backgroundColor;
}

void AnimatedButton::setBackgroundColor(const QColor &color) {
    m_backgroundColor = color;
    setStyleSheet(buttonStyle.arg(color.name()));
}
