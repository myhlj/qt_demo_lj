#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTableView>
#include <QCheckBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QCloseEvent>
#include <QStatusBar>

#include "IMainView.h"

class MainView : public QWidget, public IMainView
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = 0);
    virtual ~MainView();

signals:

public slots:

    // IMainView interface
public:
    void SetController(IMainController *controller);
    void Init();
    void ShowView();
    void ShowAcrossInfo(const QByteArray& data);

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *);

private:


private:
    IMainController *controller;
    QLabel *lblStatus;

    QStandardItemModel *mIdCardInfoModel;

    void InitControls();
private:
    QWidget         *ui;
    // main button
    QPushButton     *btnOpenCamera;
    QPushButton     *btnOpenEngine;

    // camera
    QLabel          *lblCameraVideo;
    QLabel          *lblFaceSamePeaple1_1;
    QLabel          *lblFaceSamePeaple1_n;
    QLabel          *lblScore1_1;
    QLabel          *lblFaceThumb1_1;
    QLabel          *lblFaceCapture1_1;
    QLabel          *lblFaceScore1_n;
    QLabel          *lblFaceUserId1_n;
    QLabel          *lblFaceCapture1_n;
    QLabel          *lblFaceStoreImage1_n;

    // id card
    QLabel          *lblIDImage;
    QTableView      *tblvIDMessage;

    // finger print
    QLabel          *lblFPImage;
    QLabel          *lblFPSamePeaple1_1;
    QLabel          *lblFPScore1_1;
    QLabel          *lblFPImage1_1;
    QLabel          *lblFPSamePeaple1_n;
    QLabel          *lblFPScore1_n;
    QLabel          *lblFPImage1_n;
    QLabel          *lblFPStoreImage1_n;

    // settings
    QCheckBox       *chkClosePreVerifyMode;
    QPushButton     *btnSetFaceVerifyMode1_1;
    QPushButton     *btnSetFaceVerifyMode1_n;
    QPushButton     *btnSaveFaceImage_1;
    QPushButton     *btnSaveFaceImage_n;
    QPushButton     *btnDelFaceImage_n;
    QPushButton     *btnDelFaceImage_1;
    QPushButton     *btnGetTh1_1;
    QPushButton     *btnSetTh1_1;
    QPushButton     *btnGetTh1_n;
    QPushButton     *btnSetTh1_n;
    QLineEdit       *txtFaceRemoveId;
    QLineEdit       *txtFaceTh1_1;
    QLineEdit       *txtFaceTh1_n;

    QPushButton     *btnSetFPVerifyMode1_1;
    QPushButton     *btnSetFPVerifyMode1_n;
    QPushButton     *btnSaveFPImage_1;
    QPushButton     *btnSaveFPImage_n;
    QPushButton     *btnDelFPImage_n;
    QPushButton     *btnDelFPImage_1;
    QPushButton     *btnGetFPTh1_1;
    QPushButton     *btnSetFPTh1_1;
    QPushButton     *btnGetFPTh1_n;
    QPushButton     *btnSetFPTh1_n;
    QPushButton     *btnGetFPQuaTh;
    QPushButton     *btnSetFPQuaTh;
    QLineEdit       *txtFPRemoveId;
    QLineEdit       *txtFPTh1_1;
    QLineEdit       *txtFPTh1_n;
    QLineEdit       *txtFPQuath;

    QStatusBar      *statusBar;
};

#endif // MAIN_VIEW_H
