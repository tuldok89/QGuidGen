#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUuid>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void exitButtonClicked();
    void newGuidButtonClicked();
    void copyButtonClicked();

private:
    Ui::MainWindow *ui;
    QUuid uuid;
    QString formattedUuid;
    void newUuid();
    void formatUuid();
};
#endif // MAINWINDOW_H
