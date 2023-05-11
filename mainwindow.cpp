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

    _guidGen = new GuidGen();
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::exitButtonClicked);
    connect(ui->newGuidButton, &QPushButton::clicked, _guidGen, &GuidGen::newGuid);
    connect(ui->copyButton, &QPushButton::clicked, this, &MainWindow::copyButtonClicked);
    connect(ui->format1RadioButton, &QRadioButton::clicked, this, qOverload<>(&MainWindow::updateUi));
    connect(ui->format2RadioButton, &QRadioButton::clicked, this, qOverload<>(&MainWindow::updateUi));
    connect(ui->format3RadioButton, &QRadioButton::clicked, this, qOverload<>(&MainWindow::updateUi));
    connect(ui->format4RadioButton, &QRadioButton::clicked, this, qOverload<>(&MainWindow::updateUi));
    connect(ui->format5RadioButton, &QRadioButton::clicked, this, qOverload<>(&MainWindow::updateUi));
    connect(ui->format6RadioButton, &QRadioButton::clicked, this, qOverload<>(&MainWindow::updateUi));
    connect(_guidGen, qOverload<const QUuid&>(&GuidGen::guidChanged), this, qOverload<const QUuid&>(&MainWindow::updateUi));

    _guidGen->newGuid();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _guidGen;
}

void MainWindow::exitButtonClicked()
{
    qApp->exit();
}

void MainWindow::copyButtonClicked()
{
    qApp->clipboard()->setText(formattedUuid);
}

void MainWindow::updateUi(const QUuid& uuid)
{
    if (ui->format1RadioButton->isChecked())
    {
        formattedUuid.clear();
        formattedUuid.append(QString::asprintf(_commentFormat,
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
            .append(QString::asprintf(_guidFormat1,
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
        formattedUuid.append(QString::asprintf(_commentFormat,
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
            .append(QString::asprintf(_guidFormat1,
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
        formattedUuid.append(QString::asprintf(_commentFormat,
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
            .append(QString::asprintf(_guidFormat2,
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

void MainWindow::updateUi()
{
    updateUi(_guidGen->getGuid());
}
