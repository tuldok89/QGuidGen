#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUuid>

#include "guidgen.h"

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
    void copyButtonClicked();
    void updateUi();
    void updateUi(const QUuid& uuid);
private:
    Ui::MainWindow *ui;
    QString formattedUuid;
    GuidGen* _guidGen;
    constexpr static char const* _commentFormat = "// {%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}\n";
    constexpr static char const* _guidFormat1 = "0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x);\n";
    constexpr static char const* _guidFormat2 = "{ 0x%x, 0x%x, 0x%x, { 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x } };";
    void newUuid();
};
#endif // MAINWINDOW_H
