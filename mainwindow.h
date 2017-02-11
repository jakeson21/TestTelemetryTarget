#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

#include <../UdpServer/udpserver.hpp>
#include <../GenericDelegate/GenericDelegate.h>

#include <boost/thread/thread.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void initializeTable();
    void startServer();

    void handle_receive(const boost::shared_ptr<std::vector<uint8_t> >& data,
                        const boost::shared_ptr<udp::endpoint>& endpoint);

public slots:
    void on_buttonUpdateListen_clicked(bool inChecked);

private:
    Ui::MainWindow *ui;
    /// Delegate to callback method
    Comm::ReceiveCallbackSignature mMethodCallback;
    Comm::UdpServer server;

};

#endif // MAINWINDOW_H
