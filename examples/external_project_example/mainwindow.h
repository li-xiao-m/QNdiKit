#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTestNdiSource();
    void onTestNdiManager();

private:
    void setupUI();
    void createNdiSourceGroup();
    void createNdiManagerGroup();

    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;
    QGroupBox *m_ndiSourceGroup;
    QGroupBox *m_ndiManagerGroup;
};

#endif // MAINWINDOW_H 