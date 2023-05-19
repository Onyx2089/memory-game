#include "mainwindow.h"
#include "cardwidget.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QVector>
#include <QRandomGenerator>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QLabel *difficultyLabel = new QLabel("Choisissez la difficulté :", this);
                              mainLayout->addWidget(difficultyLabel);

    QPushButton *easyButton = new QPushButton("Facile", this);
    QPushButton *mediumButton = new QPushButton("Moyen", this);
    QPushButton *hardButton = new QPushButton("Difficile", this);
    mainLayout->addWidget(easyButton);
    mainLayout->addWidget(mediumButton);
    mainLayout->addWidget(hardButton);

    connect(easyButton, &QPushButton::clicked, this, &MainWindow::startGameEasy);
    connect(mediumButton, &QPushButton::clicked, this, &MainWindow::startGameMedium);
    connect(hardButton, &QPushButton::clicked, this, &MainWindow::startGameHard);

    setCentralWidget(centralWidget);

    interactionBlocked = false;

    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &MainWindow::resetCards);
}

void MainWindow::startGameEasy()
{
    clearCards();
    createCards(EASY_CARDS);
}

void MainWindow::startGameMedium()
{
    clearCards();
    createCards(MEDIUM_CARDS);
}

void MainWindow::startGameHard()
{
    clearCards();
    createCards(HARD_CARDS);
}

void MainWindow::cardClicked(CardWidget* card)
{
    if (interactionBlocked) {
        return;
    }


    card->flip();
    flippedCards.append(card);

    if (flippedCards.size() == 2) {
        CardWidget* firstCard = flippedCards[0];
        CardWidget* secondCard = flippedCards[1];

        if (firstCard->getValue() == secondCard->getValue()) {
            // C'est une paire !
            QTimer::singleShot(500, [this, firstCard, secondCard]() {
                firstCard->hide();
                secondCard->hide();
                firstCard->setEnabled(false);
                secondCard->setEnabled(false);

                flippedCards.clear();

                // Vérifier si toutes les paires ont été trouvées
                if (allPairsFound()) {
                    QMessageBox::information(this, "Victoire", "Vous avez trouvé toutes les paires !");
                    // Réinitialiser le jeu ici si nécessaire
                }
            });
        } else {
            // Ce n'est pas une paire, attendez 5 secondes avant de retourner les cartes
            interactionBlocked = true;
            timer->start(5000);
        }
    }
}

void MainWindow::resetCards()
{
    for (CardWidget* card : flippedCards) {
        card->flip();
    }
    flippedCards.clear();

    interactionBlocked = false;
}

void MainWindow::createCards(int numCards)
{
    cardLayout = new QGridLayout;

    QVector<int> cardValues = generateCardValues(numCards / 2);

    for (int i = 0; i < numCards; i++) {
        CardWidget* card = new CardWidget(this);
        card->setFrontImage(QPixmap(":/cartes/" + QString::number(cardValues[i]) + ".png"));
        card->setBackImage(QPixmap(":/cartes/back.png"));
        card->setValue(cardValues[i]);

        cards.append(card);
        connect(card, &CardWidget::clickedWindow, this, &MainWindow::cardClicked /*[=](){
            qInfo()<<"First";
            //cardClicked(nullptr);
        }*/);
        cardLayout->addWidget(card, i / 8, i % 8);
    }

    QWidget *gameWidget = new QWidget(this);
    gameWidget->setLayout(cardLayout);
    setCentralWidget(gameWidget);
}

void MainWindow::clearCards()
{
    for (CardWidget *card : cards) {
        card->deleteLater();
    }
    cards.clear();
}

QVector<int> MainWindow::generateCardValues(int numPairs)
{
    QVector<int> cardValues;
    for (int i = 1; i <= numPairs; i++) {
        cardValues.append(i);
        cardValues.append(i);
    }

    QVector<int> shuffledCardValues;
    while (!cardValues.isEmpty()) {
        int index = QRandomGenerator::global()->bounded(cardValues.size());
        shuffledCardValues.append(cardValues.takeAt(index));
    }

    return shuffledCardValues;
}

bool MainWindow::allPairsFound() const
{
    for (CardWidget* card : cards) {
        if (!card->isHidden()) {
            return false;
        }
    }
    return true;
}
