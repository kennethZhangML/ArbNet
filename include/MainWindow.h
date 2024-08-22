#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();  

private slots:
    void onLoadInstrument();
    void onApplyStrategy();

private:
    QComboBox *instrumentSelector;
    QComboBox *strategySelector;
    QTextEdit *outputArea;
    QPushButton *loadButton;
    QPushButton *applyButton;

    void initializeUI();
    void populateInstruments();
    void populateStrategies();
};

#endif // MAINWINDOW_H
