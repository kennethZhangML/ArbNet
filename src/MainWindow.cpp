#include "MainWindow.h"
#include "InstrumentDataFactory.h"
#include "StrategyExamples/MeanReversionStrategy.h"
#include "StrategyExamples/MomentumStrategy.h"
#include "StrategyExamples/BreakoutStrategy.h"
#include "StrategyExamples/RSIStrategy.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    initializeUI();
}

MainWindow::~MainWindow() {}

void MainWindow::initializeUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    instrumentSelector = new QComboBox(this);
    strategySelector = new QComboBox(this);
    outputArea = new QTextEdit(this);
    loadButton = new QPushButton("Load Instrument", this);
    applyButton = new QPushButton("Apply Strategy", this);

    layout->addWidget(instrumentSelector);
    layout->addWidget(strategySelector);
    layout->addWidget(loadButton);
    layout->addWidget(applyButton);
    layout->addWidget(outputArea);

    setCentralWidget(centralWidget);

    populateInstruments();
    populateStrategies();

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadInstrument);
    connect(applyButton, &QPushButton::clicked, this, &MainWindow::onApplyStrategy);
}

void MainWindow::populateInstruments() {
    instrumentSelector->addItem("AAPL");
    instrumentSelector->addItem("EURUSD");
    instrumentSelector->addItem("US10Y");
}

void MainWindow::populateStrategies() {
    strategySelector->addItem("Mean Reversion");
    strategySelector->addItem("Momentum");
    strategySelector->addItem("Breakout");
    strategySelector->addItem("RSI");
}

void MainWindow::onLoadInstrument() {
    QString instrument = instrumentSelector->currentText();
    outputArea->append("Loaded instrument: " + instrument);
}

void MainWindow::onApplyStrategy() {
    QString strategy = strategySelector->currentText();
    QString instrument = instrumentSelector->currentText();

    auto instrumentData = InstrumentDataFactory::createInstrumentData("equity", instrument.toStdString());

    std::shared_ptr<TradingStrategy> selectedStrategy;
    if (strategy == "Mean Reversion") {
        selectedStrategy = std::make_shared<MeanReversionStrategy>();
    } else if (strategy == "Momentum") {
        selectedStrategy = std::make_shared<MomentumStrategy>();
    } else if (strategy == "Breakout") {
        selectedStrategy = std::make_shared<BreakoutStrategy>();
    } else if (strategy == "RSI") {
        selectedStrategy = std::make_shared<RSIStrategy>();
    }

    if (selectedStrategy && instrumentData) {
        selectedStrategy->execute(instrumentData);
        outputArea->append("Applied " + strategy + " strategy on " + instrument);
    }
}
