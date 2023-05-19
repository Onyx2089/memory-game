#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QTimer>

class CardWidget : public QWidget {
    Q_OBJECT

public:
    CardWidget(QWidget* parent = nullptr);
    CardWidget(const QPixmap& frontImage, const QPixmap& backImage, int value, QWidget* parent = nullptr);
    int getValue() const;
    void setValue(int val);

signals:
    //void clicked();
    void clickedWindow(CardWidget*);

public slots:
    void flip();
    void setFrontImage(const QPixmap& frontImage);
    void setBackImage(const QPixmap& frontImage);

private slots:
    void handleClick();
    void resetFlip();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QLabel* frontLabel;
    QLabel* backLabel;
    bool isFlipped;
    int value;
    QTimer* flipTimer;
};

#endif // CARDWIDGET_H
