#ifndef COOLPROGRESSBAR_H
#define COOLPROGRESSBAR_H

#include <QObject>
#include <QWidget>
#include <QPropertyAnimation>

class coolProgressBar : public QWidget {
  Q_OBJECT
 public:
  explicit coolProgressBar(const QColor& backgroundColor,
                           const QColor& animatedColor,
                           int animationTimeMs,
                           QWidget* parent = nullptr);
 public slots:
  void startAnimation();
  void stopAnimation();
 protected:
  void paintEvent(QPaintEvent* event) override;
  void showEvent(QShowEvent* event) override;
 private:
  QColor m_backgroundColor;
  QColor m_animatedColor;
  int m_animationTimeMs;
  QWidget* m_movingSquare;
  QPropertyAnimation* m_animation;
};

#endif // COOLPROGRESSBAR_H
