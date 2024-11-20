#include "cool_progressbar.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOption>


coolProgressBar::coolProgressBar(const QColor& backgroundColor,
                                 const QColor& animatedColor,
                                 int animationTimeMs,
                                 QWidget* parent) {
  setVisible(false);
  m_backgroundColor = backgroundColor;
  m_animatedColor = animatedColor;
  m_animationTimeMs = animationTimeMs;
  QString styleBack(
      "    background-color: %1;"
      "    border-radius: 1px;"
      "    border: none;"
  );
  setStyleSheet(styleBack.arg(m_backgroundColor.name()));


  QWidget* movingSquare = new QWidget(this);

  m_movingSquare = movingSquare;
  QString styleMoving(
      "    background-color: %1;"
      "    border-radius: 1px;"
      "    border: none;"
  );
  m_movingSquare->setStyleSheet(styleMoving.arg(m_animatedColor.name()));

  m_animation = new QPropertyAnimation(m_movingSquare, "geometry");
  m_animation->setDuration(m_animationTimeMs);
  m_animation->setLoopCount(-1);
}

void coolProgressBar::startAnimation() {
  m_animation->setStartValue(QRect(-m_movingSquare->width(),
                                   m_movingSquare->y(),
                                   m_movingSquare->width(),
                                   m_movingSquare->height()));
  m_animation->setEndValue(QRect(width(),
                                 m_movingSquare->y(),
                                 m_movingSquare->width(),
                                 m_movingSquare->height()));
  m_animation->setEasingCurve(QEasingCurve::InOutCubic);
  m_animation->start();
  setVisible(true);
}

void coolProgressBar::stopAnimation() {
  m_animation->stop();
  setVisible(false);
}

void coolProgressBar::paintEvent(QPaintEvent* event) {
  QStyleOption opt;
  opt.init(this);
  QPainter p(this);
  style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void coolProgressBar::showEvent(QShowEvent* event) {
  m_movingSquare->setGeometry(0, 0, width() / 2, height());
}

