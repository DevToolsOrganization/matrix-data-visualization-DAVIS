#include "animated_button.h"
#include <QTimer>
#include <QDebug>




AnimatedButton::AnimatedButton(const QString &text, QColor &startColor, QColor &endColor, QWidget *parent) : QPushButton(text, parent) {
        QString buttonStyle(
                    "QPushButton {"
                    "    background-color: rgb(150,150,150);" // Цвет фона
                    "    border: none;" // Без границ
                    "    color:white;" // Цвет текста
                    "    text-align: center;" // Выравнивание текста
                    "    text-decoration: none;" // Без подчеркивания текста
                    "    font-size: 13px;" // Размер шрифта
                    "    border-radius: 8px;" // Закругленные углы
                    "}"

                    );
        setStyleSheet(buttonStyle);
//        "QPushButton:hover {"
//        "    background-color: rgb(42, 130, 218);" // Цвет фона при наведении
//        "    color: white;" // Цвет текста
//        "}"
//        "QPushButton:pressed {"
//        "    background-color: #45a049;" // Цвет фона при нажатии
//        "}"
        m_startColor = startColor;
        m_endColor = endColor;
}

void AnimatedButton::enterEvent(QEvent *event) {
    startColorAnimation(m_startColor, m_endColor);

    QPushButton::enterEvent(event);
}

void AnimatedButton::leaveEvent(QEvent *event) {
    startColorAnimation(m_endColor, m_startColor);
    QPushButton::leaveEvent(event);
}

void AnimatedButton::startColorAnimation(const QColor &startColor, const QColor &endColor) {
    QTimer *timer = new QTimer(this);
    timer->setInterval(15); // Интервал обновления в миллисекундах
    int duration = 300; // Длительность анимации в миллисекундах
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
        qDebug()<<currentColor.red();
        qDebug()<<currentStep <<" / "<<steps;
        QString buttonStyle(
                    "QPushButton {"
                    "    background-color: %1;" // Цвет фона
                    "    border: none;" // Без границ

                    "    text-align: center;" // Выравнивание текста
                    "    text-decoration: none;" // Без подчеркивания текста
                    "    font-size: 13px;" // Размер шрифта
                    "    border-radius: 8px;" // Закругленные углы
                    "}"
                    );

        //"    color: rgb(220, 220, 220);" // Цвет текста
        setStyleSheet(buttonStyle.arg(currentColor.name()));

        currentStep++;
    });

    timer->start();
}
