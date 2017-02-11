#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeTable();

    startServer();
}

MainWindow::~MainWindow()
{
    server.Stop();
    delete ui;
}

void MainWindow::initializeTable()
{
    int rows = 5;
    int cols = 3;
    ui->tableWidget->setRowCount(rows);
    ui->tableWidget->setColumnCount(cols);
    QStringList colHeaders;
    colHeaders << "Data" << "Data_Type" << "Value";
    ui->tableWidget->setHorizontalHeaderLabels(colHeaders);

    for (int r=0; r<rows; r++)
    {
        QTableWidgetItem *newItem = 0;

        newItem = new QTableWidgetItem(tr("Val_%1").arg(r+1));
        ui->tableWidget->setItem(r, 0, newItem);

        newItem = new QTableWidgetItem(tr("uint8_t"));
        ui->tableWidget->setItem(r, 1, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(r+1));
        ui->tableWidget->setItem(r, 2, newItem);
    }
}

void MainWindow::startServer()
{
    // configure server
    server.listen_on(ui->editIpAddress->text().toStdString(), ui->editPort->text().toInt());

    // Start server thread
    server.Start();
}

void MainWindow::on_buttonUpdateListen_clicked(bool inChecked)
{
    server.Stop();

    this->startServer();
}

void MainWindow::handle_receive(const boost::shared_ptr<std::vector<uint8_t> >& inData,
                               const boost::shared_ptr<udp::endpoint>& inEndpoint)
{
    QString receivedData;
    std::vector<uint8_t> data;
    BOOST_FOREACH(uint8_t byte, *inData)
    {
        data.push_back(byte);
        receivedData += QString(byte);
    }
    std::cout << "Address=" << inEndpoint->address().to_string() << ":" << inEndpoint->port() << std::endl;
    //emit updateReceivedText(receivedData);
}
