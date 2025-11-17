#ifndef TCPFILESENDER_H
#define TCPFILESENDER_H

#include <QDialog>
#include<QtNetwork>
#include<QtWidgets>

class TcpFileSender : public QDialog
{
    Q_OBJECT

public:
    TcpFileSender(QWidget *parent = nullptr);
    ~TcpFileSender();
public slots:
    void start();
    void startTransfer();
    void updateClientProgress(qint64 numBytes);
    void openFile();
private:
    QProgressBar    *clientProgressBar;
    QLabel          *clientStatusLable;
    QPushButton     *startButton;
    QPushButton     *openButton;
    QPushButton     *quitButton;
    QDialogButtonBox    *buttonBox;
    QTcpSocket      *tcpClient;

    qint64          totalBytes;
    qint64          bytesWritten;
    qint64          bytesToWrite;
    qint64          loadSize;
    QString         fileNane;
    QFile           *localFlie;
    QByteArray      outBlock;
};
#endif // TCPFILESENDER_H
