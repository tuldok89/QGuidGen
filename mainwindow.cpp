#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QCoreApplication>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());

    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::exitButtonClicked);
    connect(ui->newGuidButton, &QPushButton::clicked, this, &MainWindow::newGuidButtonClicked);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::copyButtonClicked);
    connect(ui->format1RadioButton, &QRadioButton::clicked, this, [=]() { formatUuid(); });
    connect(ui->format2RadioButton, &QRadioButton::clicked, this, [=]() { formatUuid(); });
    connect(ui->format3RadioButton, &QRadioButton::clicked, this, [=]() { formatUuid(); });
    connect(ui->format4RadioButton, &QRadioButton::clicked, this, [=]() { formatUuid(); });
    connect(ui->format5RadioButton, &QRadioButton::clicked, this, [=]() { formatUuid(); });
    connect(ui->format6RadioButton, &QRadioButton::clicked, this, [=]() { formatUuid(); });
    newUuid();
    formatUuid();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exitButtonClicked()
{
    QCoreApplication::exit();
}

void MainWindow::newUuid()
{
    uuid = QUuid::createUuid();
}

void MainWindow::newGuidButtonClicked()
{
    newUuid();
    formatUuid();
}

void MainWindow::copyButtonClicked()
{
    qApp->clipboard()->setText(formattedUuid);
}

void MainWindow::formatUuid()
{
    auto line1format = "// {%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}\n";
    auto line3format = "0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x);\n";
    if (ui->format1RadioButton->isChecked())
    {
        formattedUuid.clear();
        formattedUuid.append(QString::asprintf(line1format,
                                               uuid.data1,
                                               uuid.data2,
                                               uuid.data3,
                                               uuid.data4[0],
                                               uuid.data4[1],
                                               uuid.data4[2],
                                               uuid.data4[3],
                                               uuid.data4[4],
                                               uuid.data4[5],
                                               uuid.data4[6],
                                               uuid.data4[7]))
            .append(QStringLiteral("IMPLEMENT_OLECREATE(<<class>>, <<external_name>>,\n"))
            .append(QString::asprintf(line3format,
                                      uuid.data1,
                                      uuid.data2,
                                      uuid.data3,
                                      uuid.data4[0],
                                      uuid.data4[1],
                                      uuid.data4[2],
                                      uuid.data4[3],
                                      uuid.data4[4],
                                      uuid.data4[5],
                                      uuid.data4[6],
                                      uuid.data4[7]));
    }
    else if (ui->format2RadioButton->isChecked())
    {
        formattedUuid.clear();
        formattedUuid.append(QString::asprintf(line1format,
                                               uuid.data1,
                                               uuid.data2,
                                               uuid.data3,
                                               uuid.data4[0],
                                               uuid.data4[1],
                                               uuid.data4[2],
                                               uuid.data4[3],
                                               uuid.data4[4],
                                               uuid.data4[5],
                                               uuid.data4[6],
                                               uuid.data4[7]))
            .append(QStringLiteral("DEFINE_GUID(<<name>>,\n"))
            .append(QString::asprintf(line3format,
                                      uuid.data1,
                                      uuid.data2,
                                      uuid.data3,
                                      uuid.data4[0],
                                      uuid.data4[1],
                                      uuid.data4[2],
                                      uuid.data4[3],
                                      uuid.data4[4],
                                      uuid.data4[5],
                                      uuid.data4[6],
                                      uuid.data4[7]));
    }
    else if (ui->format3RadioButton->isChecked())
    {
        formattedUuid.clear();
        formattedUuid.append(QString::asprintf(line1format,
                                               uuid.data1,
                                               uuid.data2,
                                               uuid.data3,
                                               uuid.data4[0],
                                               uuid.data4[1],
                                               uuid.data4[2],
                                               uuid.data4[3],
                                               uuid.data4[4],
                                               uuid.data4[5],
                                               uuid.data4[6],
                                               uuid.data4[7]))
            .append(QStringLiteral("static const GUID <<name>> =\n"))
            .append(QString::asprintf("{ 0x%x, 0x%x, 0x%x, { 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x } };",
                                      uuid.data1,
                                      uuid.data2,
                                      uuid.data3,
                                      uuid.data4[0],
                                      uuid.data4[1],
                                      uuid.data4[2],
                                      uuid.data4[3],
                                      uuid.data4[4],
                                      uuid.data4[5],
                                      uuid.data4[6],
                                      uuid.data4[7]));
    }
    else if (ui->format4RadioButton->isChecked())
    {
        formattedUuid = uuid.toString();
    }
    else if (ui->format5RadioButton->isChecked())
    {
        formattedUuid = QStringLiteral("[Guid(\"%1\")]").arg(uuid.toString(QUuid::WithoutBraces));
    }
    else if (ui->format6RadioButton->isChecked())
    {
        formattedUuid = QStringLiteral("<Guid(\"%1\")>").arg(uuid.toString(QUuid::WithoutBraces));
    }

    ui->resultLabel->setText(formattedUuid);
}
