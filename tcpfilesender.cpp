#include "tcpfilesender.h"

TcpFileSender::TcpFileSender(QWidget *parent)
    : QDialog(parent)
{
    loadSize =1024 * 4;
    totalBytes =0;
    bytesWritten =0;
    bytesToWrite =0;
    clientProgressBar = new QProgressBar;
    clientStatusLable = new QLabel(tr("客戶端就緒"));
    startButton =new QPushButton(tr("開始"));
    quitButton =new QPushButton(tr("退出"));
    openButton =new QPushButton(tr("開檔"));
    startButton->setEnabled(false);
    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(startButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(openButton,QDialogButtonBox::ActionRole);
    buttonBox->addButton(quitButton,QDialogButtonBox::RejectRole);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(clientProgressBar);
    mainLayout->addWidget(clientStatusLable);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    setWindowTitle(tr("檔案傳送"));
    connect(openButton, SIGNAL(clicked()),this,SLOT(openFile()));
    connect(startButton, SIGNAL(clicked()),this,SLOT(start()));
    connect(&tcpClient,SIGNAL(connected()),this,SLOT(startTransfer()));
    connect(&tcpClient,SIGNAL(bytesWritten(qint64)),this,SLOT(updateClientProgress(qint64)));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
}

TcpFileSender::~TcpFileSender() {

}
void TcpFileSender::start(){
    startButton->setEnabled(false);
    bytesWritten = 0;
    clientStatusLable->setText(tr("連線中..."));
    tcpClient.connectToHost(QHostAddress::LocalHost,16689);
}
void TcpFileSender::startTransfer(){
    localFlie = new QFile(fileNane);
    if(!localFlie->open(QFile::ReadOnly)){
        QMessageBox::warning(this,tr("應用程式"),
                             tr("無法讀取 %1:\n%2.").arg(fileNane)
                                 .arg(localFlie->errorString()));
        return;
    }
    totalBytes = localFlie->size();
    QDataStream sendOut(&outBlock,QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_6);
    QString currentFile = fileNane.right(fileNane.size() -
                                         fileNane.lastIndexOf("/")-1);
    sendOut <<qint64(0)<<qint64(0)<<currentFile;
    totalBytes += outBlock.size();

    sendOut.device()->seek(0);
    sendOut<<totalBytes<<qint64((outBlock.size()-sizeof(qint64)*2));
    bytesToWrite = totalBytes -
}
void TcpFileSender::updateClientProgress(qint64 numBytes){

}
void TcpFileSender::openFile(){
    fileNane = QFileDialog::getOpenFileName(this);
        if(!fileNane.isEmpty()) startButton->setEnabled(true);
}
