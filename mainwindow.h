#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardwidget.h"

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(){};

public slots:
    void startGameEasy();
    void startGameMedium();
    void startGameHard();
    void cardClicked(CardWidget* card);
    void resetCards();

private:
    Ui::MainWindow *ui;

    QGridLayout *cardLayout;
    QVector<CardWidget*> cards;

    const int EASY_CARDS = 24;
    const int MEDIUM_CARDS = 32;
    const int HARD_CARDS = 48;

    void createCards(int numCards);
    void clearCards();
    QVector<int> generateCardValues(int numPairs);
    QTimer* timer;
    QVector<CardWidget*> flippedCards;
    bool interactionBlocked;
    bool allPairsFound() const;

};
#endif // MAINWINDOW_H
