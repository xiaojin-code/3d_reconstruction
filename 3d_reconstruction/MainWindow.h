#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = Q_NULLPTR);

private:
    
    bool copyFile(QString srcFile, QString dstFile, bool cover);
    
    void enableReconstruction(bool enable);

    QPushButton* pushButtonReconstruction;
};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = Q_NULLPTR) : QMainWindow(parent) { setCentralWidget(new MainWidget(this)); }
};