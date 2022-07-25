#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

#include <QGridLayout>

#include <QLineEdit>
#include <QFileDialog>
#include <QProcess>
#include <QDebug>

#include <QMessageBox>

#include <QCoreApplication>

MainWidget::MainWidget(QWidget* parent)
    : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(new QLabel("图片文件夹: ", this), 0, 0, 1, 3);
    QLineEdit* lineEditImageDir = new QLineEdit(this);
    layout->addWidget(lineEditImageDir, 0, 3, 1, 7);
    QPushButton* pushButtonImageDir = new QPushButton("选择文件夹", this);

    layout->addWidget(pushButtonImageDir, 0, 10, 1, 6);
    layout->addWidget(new QLabel("输出文件夹: ", this), 1, 0, 1, 3);
    QLineEdit* lineEditColmapOutput = new QLineEdit(this);
    layout->addWidget(lineEditColmapOutput, 1, 3, 1, 7);
    QPushButton* pushButtonColmapOutput = new QPushButton("选择文件夹", this);
    layout->addWidget(pushButtonColmapOutput, 1, 10, 1, 6);

    pushButtonReconstruction = new QPushButton("一键重建", this);

    QTextEdit* textEditShellOutput = new QTextEdit(this);
    textEditShellOutput->setMinimumSize(500, 200);

    layout->addWidget(pushButtonReconstruction, 2, 0, 2, 16);
    layout->setAlignment(Qt::AlignTop);

    layout->addWidget(textEditShellOutput, 5, 0, 1, 16);

    textEditShellOutput->setReadOnly(true);
    connect(pushButtonImageDir, &QPushButton::clicked, [=]() {

        QString dirName = QFileDialog::getExistingDirectory(Q_NULLPTR, "image dir", ".");
        if (dirName.isEmpty()) {
            return;
        }
        lineEditImageDir->setText(dirName);
    });

    connect(pushButtonColmapOutput, &QPushButton::clicked, [=]() {
        QString dirName = QFileDialog::getExistingDirectory(Q_NULLPTR, "colmap output", ".");
        if (dirName.isEmpty()) {
            return;

        }
        lineEditColmapOutput->setText(dirName);
    });

    QProcess* shellProcess = new QProcess(this);

    connect(pushButtonReconstruction, &QPushButton::clicked, [=]() {

        shellProcess->setWorkingDirectory(".");

        QString scriptProgram = QString("./script.exe");
        QStringList scriptArguments;

        scriptArguments << "./dependency/colmap/libs/colmap.exe" << lineEditColmapOutput->text() << lineEditImageDir->text() << "./dependency/openmvs/libs";
        shellProcess->start(scriptProgram, scriptArguments);

        qDebug() << QString::fromLocal8Bit(shellProcess->readAll());
        pushButtonReconstruction->setEnabled(false);
    });

    connect(shellProcess, &QProcess::errorOccurred, [=](QProcess::ProcessError error) {
        qDebug() << error;
        exit(-1);
    });









    connect(shellProcess, &QProcess::readyReadStandardOutput, [=]() {

        textEditShellOutput->append(QString::fromLocal8Bit(shellProcess->readAllStandardOutput()));
    });
    connect(shellProcess, &QProcess::readyReadStandardError, [=]() {

        textEditShellOutput->append(QString::fromLocal8Bit(shellProcess->readAllStandardError()));
    });

    connect(shellProcess, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),



        [=](int exitCode, QProcess::ExitStatus exitStatus) {
        pushButtonReconstruction->setEnabled(true);
    });

}

bool MainWidget::copyFile(QString srcFile, QString dstFile, bool cover) {
    if (srcFile == dstFile) {
        return true;
    }
    if (!QFile::exists(srcFile)) {
        return false;
    }
    QDir* createfile = new QDir;
    bool exist = createfile->exists(dstFile);
    if (exist) {
        if (cover) {
            createfile->remove(dstFile);
        }
    }

    return QFile::copy(srcFile, dstFile);
}
void MainWidget::enableReconstruction(bool enable) {

    if (pushButtonReconstruction != nullptr) {
        pushButtonReconstruction->setEnabled(enable);
    }
}

