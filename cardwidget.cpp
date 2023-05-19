#include "cardwidget.h"

#include <QHBoxLayout>

CardWidget::CardWidget(QWidget* parent)
    : QWidget(parent), isFlipped(false)
{
    frontLabel = new QLabel(this);
    backLabel = new QLabel(this);

    frontLabel->setFixedSize(100, 100);
    backLabel->setFixedSize(100, 100);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(frontLabel);
    layout->addWidget(backLabel);

    backLabel->setVisible(true);
    frontLabel->setVisible(false);

    setFixedSize(100, 100);

    //connect(this, &CardWidget::clicked, this, &CardWidget::handleClick);

    flipTimer = new QTimer(this);
    flipTimer->setSingleShot(true);
    connect(flipTimer, &QTimer::timeout, this, &CardWidget::resetFlip);
}

CardWidget::CardWidget(const QPixmap& frontImage, const QPixmap& backImage, int value, QWidget* parent)
    : CardWidget(parent)
{
    frontLabel->setPixmap(frontImage.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    backLabel->setPixmap(backImage.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->value = value;
}

void CardWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {

        emit clickedWindow(this);
    }
}

void CardWidget::flip()
{
    isFlipped = !isFlipped;
    frontLabel->setVisible(isFlipped);
    backLabel->setVisible(!isFlipped);
}

void CardWidget::handleClick()
{
    flip();
    emit clickedWindow(this);
}

void CardWidget::setFrontImage(const QPixmap& frontImage)
{
    frontLabel->setPixmap(frontImage.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void CardWidget::setBackImage(const QPixmap& backImage)
{
    backLabel->setPixmap(backImage.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

int CardWidget::getValue() const
{
    return value;
}

void CardWidget::setValue(int val)
{
    value = val;
}


void CardWidget::resetFlip()
{
    if (isFlipped) {
        flip();
    }
}
