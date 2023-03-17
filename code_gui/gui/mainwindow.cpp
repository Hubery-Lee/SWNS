#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QApplication>
#include <QWidget>
#include <QProcess>
//#include <QDesktopWidget>

//https://doc.qt.io/qt-5/qtwidgets-tutorials-notepad-example.html

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/images/logo-1.png"));
    setWindowTitle("SWNS-GUI");

    setWindowState(windowState()^Qt::WindowMaximized);
//    setWindowState(windowState()^Qt::WindowFullScreen);

}

MainWindow::~MainWindow()
{
    delete ui;
}
//=================================
// 文本打开与保存
void MainWindow::on_OpenButton_clicked()
{
    ui->plainTextEdit->clear();
    QString curPath=QDir::currentPath();//获取系统当前目录;
    QString dlgTitle="open a file"; //对话框标题;
    QString filter="text(*.txt);;all(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;

    OpenTextFile(aFileName);
}

bool MainWindow::OpenTextFile(const QString &aFileName)
{
    QFile   aFile(aFileName);
    if (!aFile.exists()) //文件不存在
        return false;
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    ui->plainTextEdit->setPlainText(aFile.readAll());
    aFile.close();
    ui->tabWidget->setCurrentIndex(0);
    return  true;
}

void MainWindow::on_SaveButton_clicked()
{

    QString curPath=QDir::currentPath();//获取系统当前目录;
    QString dlgTitle="save a file"; //对话框标题;
    QString filter="text(*.txt);;all(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);

    if (aFileName.isEmpty())
    {
        return;
    }
    saveToFile(aFileName);
}

bool MainWindow::saveToFile(const QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QString str=ui->plainTextEdit->toPlainText();//整个内容作为字符串
    QByteArray  strBytes=str.toUtf8();//转换为字节数组
    aFile.write(strBytes,strBytes.length());  //写入文件
    aFile.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

//=======================================================
// 材料定义

//------------------------------------
// 化合物和混合物的定义
void MainWindow::on_ComposeSubmit_clicked()
{
    composeMat= ":MIXT "+ui->ComposeMatName->text()+" "+ui->ComposeMatDensity->text()+" "+QString::number(ui->ComposeElmNum->value());
    //获取表格内容
    for(int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
        composeMat+=" "+ui->tableWidget_2->item(i,0)->text();
        composeMat+=" "+ui->tableWidget_2->item(i,1)->text();
    }
    //获取混合类型
    int index = ui->comboBox_Type->currentIndex();
    if(index==0)
    {
        composeMat= composeMat+" "+":MIXT_BY_WEIGHT";
    }
    else if(index == 1)
    {
        composeMat= composeMat+" "+":MIXT_BY_NATOMS";
    }
    else if(index == 2)
    {
        composeMat= composeMat+" "+":MIXT_BY_VOLUME";
    }

    ui->plainTextEdit->appendPlainText(composeMat);
}
//----------------------------------
// options

void MainWindow::on_AddComposeElemNum_clicked()
{
//    composeMat= composeMat+" "+QString::number(ui->ComposeElmNum->value());
    //建立表格
    ui->tableWidget_2->setRowCount(ui->ComposeElmNum->value());
    QTableWidgetItem *item = new QTableWidgetItem();
    ui->tableWidget_2->setItem(ui->ComposeElmNum->value(),0,item);
}

//------------------------------------
// 单质
void MainWindow::on_Mat1Submit_clicked()
{
    Mat1= ":MATE "+ui->Mat1Name->text()+" "+ui->Mat1Z->text()+" "+ui->Mat1A->text()+" "+ui->Mat1Density->text();
    ui->plainTextEdit->appendPlainText(Mat1);
}

//--------------------------------------------
// 元素

//
// 元素 由单一同位素组成
//
void MainWindow::on_ElemSubmit_clicked()
{
    Elem=":ELEM "+ui->ElemName->text()+" "+ui->ElemSymbol->text()+" "+ui->ElemZ->text()
            +" "+ui->ElemA->text();
    ui->plainTextEdit->appendPlainText(Elem);
}

//
// Isotope
//

void MainWindow::on_IsoSubmit_clicked()
{
    Iso=":ISOT "+ui->IsoName->text()+" "+ui->IsoZ->text()+" "+ui->IsoN->text()+" "+ui->IsoA->text();
    ui->plainTextEdit->appendPlainText(Iso);
}

//
// element composed of several isotopes
//
void MainWindow::on_ElemCompIsoSubmit_clicked()
{
    ElemCompIso=":ELEM_FROM_ISOT "+ui->ElemCompIsoName->text()+" "+ui->ElemCompIsoSymbol->text();
    ElemCompIso=ElemCompIso+" "+QString::number(ui->ElemCompIsoNum->value());
    //获取表格内容
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        ElemCompIso+=" "+ui->tableWidget->item(i,0)->text();
        ElemCompIso+=" "+ui->tableWidget->item(i,1)->text();
    }

    ui->plainTextEdit->appendPlainText(ElemCompIso);

}
void MainWindow::on_AddElemCompIsoNum_clicked()
{
//    ElemCompIso=ElemCompIso+" "+QString::number(ui->ElemCompIsoNum->value());
    //建立表格
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列宽自动分配
    ui->tableWidget->setRowCount(ui->ElemCompIsoNum->value());
    QTableWidgetItem *item = new QTableWidgetItem();
    ui->tableWidget->setItem(ui->ElemCompIsoNum->value(),0,item);
}
//=======================================================
// 几何建模
//

//--------------------------
// Box

void MainWindow::on_BoxSubmit_clicked()
{
    BoxData=":SOLID "+ui->BoxName->text()+" BOX"+" "+QString::number(ui->HalfX->value())+" "+QString::number(ui->HalfY->value())+" "+QString::number(ui->HalfZ->value());
    ui->plainTextEdit->appendPlainText(BoxData);
    //清除输入框内容
    ui->BoxName->clear();
//    ui->HalfX->setValue(0.0);
//    ui->HalfY->setValue(0.0);
//    ui->HalfZ->setValue(0.0);
}
//----------------------------------
// Tube
void MainWindow::on_TubeSubmit_clicked()
{
    TubsData=":SOLID "+ui->TubeName->text()+" TUBS"+" "+QString::number(ui->TubeinnerR->value())+" "+QString::number(ui->TubeOuterR->value())+" "+QString::number(ui->TubeHalfLength->value())
            +" "+QString::number(ui->TubeStartDegree->value())+" "+QString::number(ui->TubeDeltaDegree->value());

    ui->plainTextEdit->appendPlainText(TubsData);
    // clear input
//    ui->TubeName->clear();
//    ui->TubeinnerR->setValue(0.0);
//    ui->TubeOuterR->setValue(0.0);
//    ui->TubeHalfLength->setValue(0.0);
//    ui->TubeStartDegree->setValue(0.0);
//    ui->TubeDeltaDegree->setValue(0.0);
}

//--------------------------------------
// Cons

void MainWindow::on_ConsSubmit_clicked()
{

    ConsData=":SOLID "+ui->ConsName->text()+" CONS"+" "+QString::number(ui->ConsInnerR1->value())+" "+QString::number(ui->ConsInnerR2->value())
            +" "+QString::number(ui->ConsOuterR1->value())+" "+QString::number(ui->ConsOuterR2->value())+" "+QString::number(ui->ConsHalfLength->value())
            +" "+QString::number(ui->ConsStartDegree->value())+" "+QString::number(ui->ConsDeltaDegree->value());

    ui->plainTextEdit->appendPlainText(ConsData);
    // clear input
//    ui->ConsName->clear();
//    ui->ConsInnerR1->setValue(0.0);
//    ui->ConsInnerR2->setValue(0.0);
//    ui->ConsOuterR1->setValue(0.0);
//    ui->ConsOuterR2->setValue(0.0);
//    ui->ConsHalfLength->setValue(0.0);
//    ui->ConsStartDegree->setValue(0.0);
//    ui->ConsDeltaDegree->setValue(0.0);
}

//------------------------------------------
// 梯形

// trapzoid trd

void MainWindow::on_TRDSubmit_clicked()
{
    TRDData=":SOLID "+ui->TRDName->text()+" TRD"+" "+QString::number(ui->TRDHalfX1->value())+" "+QString::number(ui->TRDHalfY1->value())
            +" "+QString::number(ui->TRDHalfX2->value())+" "+QString::number(ui->TRDHalfY2->value())+" "+QString::number(ui->TRDHalfLength->value());

    ui->plainTextEdit->appendPlainText(TRDData);
    // clear input
    ui->TRDName->clear();
//    ui->TRDHalfX1->setValue(0.0);
//    ui->TRDHalfY1->setValue(0.0);
//    ui->TRDHalfX2->setValue(0.0);
//    ui->TRDHalfY2->setValue(0.0);
//    ui->TRDHalfLength->setValue(0.0);
}

// generic trapzoid
void MainWindow::on_TRAPSubmit_clicked()
{
    TRAPData=":SOLID "+ui->TRAPName->text()+" TRAP"+" "+QString::number(ui->TRAPHalfLength->value())
            +" "+QString::number(ui->TRAPPolarAngle->value())+" "+QString::number(ui->TRAPAzimuthalAngle->value())
            +" "+QString::number(ui->TRAPHalfY1->value())+" "+QString::number(ui->TRAPHalfX1->value())
            +" "+QString::number(ui->TRAPHalfX2->value())+" "+QString::number(ui->TRAPAngle1->value())
            +" "+QString::number(ui->TRAPHalfY2->value())+" "+QString::number(ui->TRAPHalfX3->value())
            +" "+QString::number(ui->TRAPHalfX4->value())+" "+QString::number(ui->TRAPAngle2->value());

    ui->plainTextEdit->appendPlainText(TRAPData);
    // clear input
//    ui->TRAPName->clear();
//    ui->TRAPHalfLength->setValue(0.0);
//    ui->TRAPPolarAngle->setValue(0.0);
//    ui->TRAPAzimuthalAngle->setValue(0.0);
//    ui->TRAPHalfY1->setValue(0.0);
//    ui->TRAPHalfX1->setValue(0.0);
//    ui->TRAPHalfX2->setValue(0.0);
//    ui->TRAPAngle1->setValue(0.0);
//    ui->TRAPHalfY2->setValue(0.0);
//    ui->TRAPHalfX3->setValue(0.0);
//    ui->TRAPHalfX4->setValue(0.0);
//    ui->TRAPAngle2->setValue(0.0);
}

//--------------------------------------------
// paralellepipe 平行六面体
void MainWindow::on_PARASubmit_clicked()
{
    PARAData=":SOLID "+ui->PARAName->text()+" PARA"+" "+QString::number(ui->PARAHalfX->value())+" "+QString::number(ui->PARAHalfY->value())
            +" "+QString::number(ui->PARAHalfZ->value())+" "+QString::number(ui->PARAAlpha->value())+" "+QString::number(ui->PARATheta->value())
            +" "+QString::number(ui->PARAPhi->value());
    ui->plainTextEdit->appendPlainText(PARAData);
    // clear input
//    ui->PARAName->clear();
//    ui->PARAHalfX->setValue(0.0);
//    ui->PARAHalfY->setValue(0.0);
//    ui->PARAHalfZ->setValue(0.0);
//    ui->PARAAlpha->setValue(0.0);
//    ui->PARATheta->setValue(0.0);
//    ui->PARAPhi->setValue(0.0);
}

//--------------------------------------------
// sphere 球
void MainWindow::on_SphereSubmit_clicked()
{
    SphereData=":SOLID "+ui->SphereName->text()+" SPHERE"+" "+QString::number(ui->SphereInnerR->value())
            +" "+QString::number(ui->SphereOuterR->value())+" "+QString::number(ui->SphereStartPhi->value())+" "+QString::number(ui->SphereDeltaPhi->value())
            +" "+QString::number(ui->SphereStartTheta->value())+" "+QString::number(ui->SphereDeltaTheta->value());
    ui->plainTextEdit->appendPlainText(SphereData);
    // input clear
//    ui->SphereName->clear();
//    ui->SphereInnerR->setValue(0.0);
//    ui->SphereOuterR->setValue(0.0);
//    ui->SphereStartPhi->setValue(0.0);
//    ui->SphereDeltaPhi->setValue(0.0);
//    ui->SphereStartTheta->setValue(0.0);
//    ui->SphereDeltaTheta->setValue(0.0);
}

// torus 圆环

void MainWindow::on_TORUSSubmit_clicked()
{
    TorusData=":SOLID "+ui->TORUSName->text()+" TORUS"+" "+QString::number(ui->TORUSInsideR->value())+" "+QString::number(ui->TORUSOutsideR->value())
            +" "+QString::number(ui->TORUSSweptR->value())+" "+QString::number(ui->TORUSStartAngle->value())+" "+QString::number(ui->TORUSDeltaAngle->value());
    ui->plainTextEdit->appendPlainText(TorusData);
    //clear input
//    ui->TORUSName->clear();
//    ui->TORUSInsideR->setValue(0.0);
//    ui->TORUSOutsideR->setValue(0.0);
//    ui->TORUSSweptR->setValue(0.0);
//    ui->TORUSStartAngle->setValue(0.0);
//    ui->TORUSDeltaAngle->setValue(0.0);
}

// Polycone 多园锥体

void MainWindow::on_POLYCONESubmit_clicked()
{
    PolyconeData=":SOLID "+ui->POLYCONEName->text()+" POLYCONE"+" "+QString::number(ui->POLYCONEStartAngle->value())
            +" "+QString::number(ui->POLYCONETotalAngle->value())+" "+QString::number(ui->POLYCONERZNum->value());

    //获取表格内容
    for(int i=0;i<ui->tableWidget_3->rowCount();i++)
    {
        PolyconeData+=" "+ui->tableWidget_3->item(i,0)->text();
        PolyconeData+=" "+ui->tableWidget_3->item(i,1)->text();
        PolyconeData+=" "+ui->tableWidget_3->item(i,2)->text();
    }

    ui->plainTextEdit->appendPlainText(PolyconeData);
    //clear input
//    ui->POLYCONEName->clear();
//    ui->POLYCONEStartAngle->setValue(0);
//    ui->POLYCONETotalAngle->setValue(0);
//    ui->POLYCONERZNum->setValue(0);
//    ui->POLYCONEPositionZ->setValue(0);
//    ui->POLYCONEInnerR->setValue(0);
//    ui->POLYCONEOuterR->setValue(0);
}

void MainWindow::on_AddPOLYCONERZNum_clicked()
{
    PolyconeData=PolyconeData+" "+QString::number(ui->POLYCONERZNum->value());
    //建立表格
    ui->tableWidget_3->setRowCount(ui->POLYCONERZNum->value());
    QTableWidgetItem *item = new QTableWidgetItem();
    ui->tableWidget_2->setItem(ui->POLYCONERZNum->value(),0,item);
}

// Polyhedra 多棱锥体
void MainWindow::on_PHedraSubmit_clicked()
{
    PolyhedraData=":SOLID "+ui->PHedraName->text()+" POLYHEDRA"+" "+QString::number(ui->PHedraStartAngle->value())
            +" "+QString::number(ui->PHedraTotalAngle->value())+" "+QString::number(ui->PHedraNumSide->value())+" "+QString::number(ui->PHedraRZNum->value());

    //获取表格内容
    for(int i=0;i<ui->tableWidget_4->rowCount();i++)
    {
        PolyhedraData+=" "+ui->tableWidget_4->item(i,0)->text();
        PolyhedraData+=" "+ui->tableWidget_4->item(i,1)->text();
        PolyhedraData+=" "+ui->tableWidget_4->item(i,2)->text();
    }


    ui->plainTextEdit->appendPlainText(PolyhedraData);
    //clear input
//    ui->PHedraName->clear();
//    ui->PHedraStartAngle->setValue(0);
//    ui->PHedraTotalAngle->setValue(0);
//    ui->PHedraNumSide->setValue(0);
//    ui->PHedraRZNum->setValue(0);
//    ui->PHedraPositionZ->setValue(0);
//    ui->PHedraInnerR->setValue(0);
//    ui->PHedraOuterR->setValue(0);
}

void MainWindow::on_AddPHedraRZNum_clicked()
{
    //建立表格
    ui->tableWidget_4->setRowCount(ui->PHedraRZNum->value());
    QTableWidgetItem *item = new QTableWidgetItem();
    ui->tableWidget_4->setItem(ui->PHedraRZNum->value(),0,item);
}


//elliptical tube 椭圆管
void MainWindow::on_EllipticalSubmit_clicked()
{
    EllipticalTubeData=":SOLID "+ui->EllipticalTubeName->text()+" ELLIPTICAL_TUBE"+" "+QString::number(ui->ETHalfX->value())
            +" "+QString::number(ui->ETHalfY->value())+" "+QString::number(ui->ETHalfZ->value());
    ui->plainTextEdit->appendPlainText(EllipticalTubeData);
    //clear inputs
//    ui->EllipticalTubeName->clear();
//    ui->ETHalfX->setValue(0);
//    ui->ETHalfY->setValue(0);
//    ui->ETHalfZ->setValue(0);
}

// ellipsoid 椭球
void MainWindow::on_EllipsoidSubmit_clicked()
{
    EllipsoidData=":SOLID "+ui->EllipsoidName->text()+" ELLIPSOID"+" "+QString::number(ui->ESHalfX->value())+" "+QString::number(ui->ESHalfY->value())
            +" "+QString::number(ui->ESHalfZ->value())+" "+QString::number(ui->ESBottomCutZ->value())+" "+QString::number(ui->ESTopCutZ->value());
    ui->plainTextEdit->appendPlainText(EllipsoidData);
    //clear inputs
//    ui->EllipsoidName->clear();
//    ui->ESHalfX->setValue(0);
//    ui->ESHalfY->setValue(0);
//    ui->ESHalfZ->setValue(0);
//    ui->ESBottomCutZ->setValue(0);
//    ui->ESTopCutZ->setValue(0);
}

// elliptical cone 椭圆锥
void MainWindow::on_EllipticalConeSubmit_clicked()
{
    EllipticalConeData=":SOLID "+ui->EllipticalConeName->text()+" ELLIPTICAL_CONE"+" "+QString::number(ui->ECHalfX->value())
            +" "+QString::number(ui->ECHalfY->value())+" "+QString::number(ui->ECHalfZ->value())+" "+QString::number(ui->ECCutZ->value());
    ui->plainTextEdit->appendPlainText(EllipticalConeData);
    //clear inputs
//    ui->EllipticalConeName->clear();
//    ui->ECHalfX->setValue(0);
//    ui->ECHalfY->setValue(0);
//    ui->ECHalfZ->setValue(0);
//    ui->ECCutZ->setValue(0);
}

// hyperbolic profile 双曲面
void MainWindow::on_HYPESubmit_clicked()
{
    HyperbolicData=":SOLID "+ui->HYPEName->text()+" HYPE"+" "+QString::number(ui->HYPEInnerR->value())+" "+QString::number(ui->HYPEOuterR->value())
            +" "+QString::number(ui->HYPEInnerStereoAngle->value())+" "+QString::number(ui->HYPEOuterStereoAngle->value())+" "+QString::number(ui->HYPEHalfZ->value());
    ui->plainTextEdit->appendPlainText(HyperbolicData);
    // clear inputs
//    ui->HYPEName->clear();
//    ui->HYPEInnerR->setValue(0);
//    ui->HYPEOuterR->setValue(0);
//    ui->HYPEInnerStereoAngle->setValue(0);
//    ui->HYPEOuterStereoAngle->setValue(0);
//    ui->HYPEHalfZ->setValue(0);
}

// tetrahedron 四面体
void MainWindow::on_TETSubmit_clicked()
{
    TetrahedronData=":SOLID "+ui->TETName->text()+" TET";

    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETAnchorP1X->value());
    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETAnchorP1Y->value());
    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETAnchorP1Z->value());

    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP2X->value());
    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP2Y->value());
    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP2Z->value());

    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP3X->value());
    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP3Y->value());
    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP3Z->value());

    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP4X->value());
    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP4Y->value());
    TetrahedronData=TetrahedronData+" "+QString::number(ui->TETP4Z->value());

    int index = ui->DegeneracyFlag->currentIndex();
    if(index==0)
    {
        TetrahedronData=TetrahedronData+" "+"0";
    }
    else if(index==1)
    {
        TetrahedronData=TetrahedronData+" "+"1";
    }

    ui->plainTextEdit->appendPlainText(TetrahedronData);
    // clear inputs
//    ui->TETAnchorP1X->setValue(0);
//    ui->TETAnchorP1Y->setValue(0);
//    ui->TETAnchorP1Z->setValue(0);

//    ui->TETP2X->setValue(0);
//    ui->TETP2Y->setValue(0);
//    ui->TETP2Z->setValue(0);

//    ui->TETP3X->setValue(0);
//    ui->TETP3Y->setValue(0);
//    ui->TETP3Z->setValue(0);

//    ui->TETP4X->setValue(0);
//    ui->TETP4Y->setValue(0);
//    ui->TETP4Z->setValue(0);

//    ui->DegeneracyFlag->setCurrentIndex(0);
}


// twist box 扭曲立方体
void MainWindow::on_TwistBoxSubmit_clicked()
{
    TwistBoxData=":SOLID "+ui->TwistBoxName->text()+" TWISTED_BOX"+" "+QString::number(ui->TwistAngle->value())+" "+QString::number(ui->TwistBoxHalfX->value())
            +" "+QString::number(ui->TwistBoxHalfY->value())+" "+QString::number(ui->TwistBoxHalfZ->value());
    ui->plainTextEdit->appendPlainText(TwistBoxData);
    //clear inputs
//    ui->TwistBoxName->clear();
//    ui->TwistAngle->setValue(0);
//    ui->TwistBoxHalfX->setValue(0);
//    ui->TwistBoxHalfY->setValue(0);
//    ui->TwistBoxHalfZ->setValue(0);
}

// twist tubs 扭曲管

void MainWindow::on_TwistTubsSubmit_clicked()
{
    TwistTubsData=":SOLID "+ui->TwistTubsName->text()+" TWISTED_TUBS"+" "+QString::number(ui->TwistTubsAngle->value())+" "+QString::number(ui->TwistTubsInnerR->value())
            +" "+QString::number(ui->TwistTubsOuterR->value())+" "+QString::number(ui->TwistTubsHalfZ->value())+" "+QString::number(ui->TwistTubsPhi->value());
    ui->plainTextEdit->appendPlainText(TwistTubsData);
    // clear inputs
//    ui->TwistTubsName->clear();
//    ui->TwistTubsAngle->setValue(0);
//    ui->TwistTubsInnerR->setValue(0);
//    ui->TwistTubsOuterR->setValue(0);
//    ui->TwistTubsHalfZ->setValue(0);
//    ui->TwistTubsPhi->setValue(0);
}

// boolean solids 几何体布尔运算
void MainWindow::on_BoolSolidSubmit_clicked()
{
    BooleanSolidData=":SOLID "+ui->BoolGeoName->text();

    int index =ui->BoolOption->currentIndex();
    if(index==0)
    {
        BooleanSolidData=BooleanSolidData+" "+"UNION";
    }else if (index==1) {
        BooleanSolidData=BooleanSolidData+" "+"SUBTRACTION";
    }else if (index==2) {
        BooleanSolidData=BooleanSolidData+" "+"INTERSECTION";
    }

    BooleanSolidData=BooleanSolidData+" "+ui->Geometry1Name->text();
    BooleanSolidData=BooleanSolidData+" "+ui->Geometry2Name->text();

    BooleanSolidData=BooleanSolidData+" "+ui->MatrixName->text();

    ui->plainTextEdit->appendPlainText(BooleanSolidData);

    BooleanSolidData=BooleanSolidData+" "+ui->MatrixX->text();
    BooleanSolidData=BooleanSolidData+" "+ui->MatrixY->text();
    BooleanSolidData=BooleanSolidData+" "+ui->MatrixZ->text();
    // clear inputs
//    ui->BoolGeoName->clear();
//    ui->BoolOption->setCurrentIndex(0);
//    ui->Geometry1Name->clear();
//    ui->Geometry2Name->clear();
//    ui->MatrixName->clear();
//    ui->MatrixX->setValue(0);
//    ui->MatrixY->setValue(0);
//    ui->MatrixZ->setValue(0);
}

//=======================================================
// logical volume 逻辑体定义

void MainWindow::on_LogicalVolumeSubmit_clicked()
{
    LogicalData=":VOLU "+ui->VOLUName->text();
    LogicalData=LogicalData+" "+ui->SOLIDName->text();
    LogicalData=LogicalData+" "+ui->MaterialName->text();

    ui->plainTextEdit->appendPlainText(LogicalData);
    // clear data
//    ui->VOLUName->clear();
//    ui->SOLIDName->clear();
//    ui->MaterialName->clear();
}

//============================================
// Physical volumes 放置方式

//single placement
void MainWindow::on_SinglePlacementSubmit_clicked()
{
    SinglePlacementData=":PLACE "+ui->PLACEVolumeName->text();
    SinglePlacementData=SinglePlacementData+" "+QString::number(ui->SPCopyNum->value());
    SinglePlacementData=SinglePlacementData+" "+ui->SPParentName->text();
    SinglePlacementData=SinglePlacementData+" "+ui->SPLACEMatrix->text();
    SinglePlacementData=SinglePlacementData+" "+ui->SPositionX->text();
    SinglePlacementData=SinglePlacementData+" "+ui->SPositionY->text();
    SinglePlacementData=SinglePlacementData+" "+ui->SPositionZ->text();

    ui->plainTextEdit->appendPlainText(SinglePlacementData);
    // clear inputs
//    ui->PLACEVolumeName->clear();
//    ui->SPCopyNum->setValue(0);
//    ui->SPParentName->clear();
//    ui->SPLACEMatrix->clear();
//    ui->SPositionX->setValue(0);
//    ui->SPositionY->setValue(0);
//    ui->SPositionZ->setValue(0);
}

// Replica 复制
void MainWindow::on_ReplicaSubmit_clicked()
{
    ReplicaData=":REPL "+ui->ReplicaName->text();
    ReplicaData=ReplicaData+" "+ui->ReplicaParentName->text();
    ReplicaData=ReplicaData+" "+ui->ReplicaDivisionAxis->currentText();
    ReplicaData=ReplicaData+" "+QString::number(ui->ReplicaDivisionNum->value());
    ReplicaData=ReplicaData+" "+QString::number(ui->ReplicaDivisionWidth->value());
    ui->plainTextEdit->appendPlainText(ReplicaData);
    // clear inputs
//    ui->ReplicaParentName->clear();
//    ui->ReplicaName->clear();
//    ui->ReplicaDivisionAxis->setCurrentIndex(0);
//    ui->ReplicaDivisionNum->setValue(0);
//    ui->ReplicaDivisionWidth->setValue(0);
}

// assemble volumes 组装体

// 1. lv
void MainWindow::on_AssembleLVSubmit_clicked()
{
    AssembleLVData=":VOLU_ASSEMBLY "+ui->AssembleName->text();
    AssembleLVData=AssembleLVData+" "+QString::number(ui->AssembleComponentNum->value());
    AssembleLVData=AssembleLVData+" "+ui->AssembleDivisionAxis->currentText();
    AssembleLVData=AssembleLVData+" "+QString::number(ui->AssembleReplicaDivisionNum->value());
    AssembleLVData=AssembleLVData+" "+QString::number(ui->AssembleReplicaDivisionWidth->value());

    ui->plainTextEdit->appendPlainText(AssembleLVData);
    //clear inputs
//    ui->AssembleName->clear();
//    ui->AssembleComponentNum->setValue(0);
//    ui->AssembleDivisionAxis->setCurrentIndex(0);
//    ui->AssembleReplicaDivisionNum->setValue(0);
//    ui->AssembleReplicaDivisionWidth->setValue(0);
}

//2. component 组分
void MainWindow::on_AsCSubmit_clicked()
{
    AssembleComponentData=ui->AsComponentName->text();
    AssembleComponentData=AssembleComponentData+" "+ui->AsComponentMatrixName->text();
    AssembleComponentData=AssembleComponentData+" "+ui->AsCPositionX->text();
    AssembleComponentData=AssembleComponentData+" "+ui->AsCPositionY->text();
    AssembleComponentData=AssembleComponentData+" "+ui->AsCPositionZ->text();
    ui->plainTextEdit->appendPlainText(AssembleComponentData);
    //clear inputs
//    ui->AsComponentName->clear();
//    ui->AsComponentMatrixName->clear();
//    ui->AsCPositionX->setValue(0);
//    ui->AsCPositionY->setValue(0);
//    ui->AsCPositionZ->setValue(0);
}

//3. physical volume 组装体放置

void MainWindow::on_AsPLaceSubmit_clicked()
{
    AssemblePVData=":PLACE_ASSEMBLY "+ui->AsPLaceVLName->text();
    AssemblePVData=AssemblePVData+" "+QString::number(ui->AsCopyNum->value());
    AssemblePVData=AssemblePVData+" "+ui->AsParentVLName->text();
    AssemblePVData=AssemblePVData+" "+ui->AsRotMatrixName->text();
    AssemblePVData=AssemblePVData+" "+QString::number(ui->AsPositionX->value());
    AssemblePVData=AssemblePVData+" "+QString::number(ui->AsPositionY->value());
    AssemblePVData=AssemblePVData+" "+QString::number(ui->AsPositionZ->value());

    ui->plainTextEdit->appendPlainText(AssemblePVData);
    //clear inputs
//    ui->AsPLaceVLName->clear();
//    ui->AsCopyNum->setValue(0);
//    ui->AsParentVLName->clear();
//    ui->AsRotMatrixName->clear();
//    ui->AsPositionX->setValue(0);
//    ui->AsPositionY->setValue(0);
//    ui->AsPositionZ->setValue(0);
}
// rotation matrix 旋转矩阵

// method 1
void MainWindow::on_RotMatrix1Submit_clicked()
{
    RotMatrix1Data=":ROTM "+ui->RotMatrix1Name->text();
    RotMatrix1Data+=" "+QString::number(ui->RotX->value());
    RotMatrix1Data+=" "+QString::number(ui->RotY->value());
    RotMatrix1Data+=" "+QString::number(ui->RotZ->value());

    ui->plainTextEdit->appendPlainText(RotMatrix1Data);
    // clear inputs
//    ui->RotMatrix1Name->clear();
//    ui->RotX->setValue(0.0);
//    ui->RotY->setValue(0.0);
//    ui->RotZ->setValue(0.0);
}
//method 2
void MainWindow::on_RotMatrix2Submit_clicked()
{
    RotMatrix2Data=":ROTM "+ui->RotMatrix2Name->text();
    RotMatrix2Data+=" "+QString::number(ui->RotXPolar->value());
    RotMatrix2Data+=" "+QString::number(ui->RotXAzimuthal->value());
    RotMatrix2Data+=" "+QString::number(ui->RotYPolar->value());
    RotMatrix2Data+=" "+QString::number(ui->RotYAzimuthal->value());
    RotMatrix2Data+=" "+QString::number(ui->RotZPolar->value());
    RotMatrix2Data+=" "+QString::number(ui->RotZAzimuthal->value());

    ui->plainTextEdit->appendPlainText(RotMatrix2Data);
    // clear inputs
//    ui->RotMatrix2Name->clear();
//    ui->RotXPolar->setValue(0);
//    ui->RotXAzimuthal->setValue(0);
//    ui->RotYPolar->setValue(0);
//    ui->RotYAzimuthal->setValue(0);
//    ui->RotZPolar->setValue(0);
//    ui->RotZAzimuthal->setValue(0);
}

// other tags 其他属性设置

//1. 显示设置 vis
void MainWindow::on_VISSubmit_clicked()
{
    VISFlag=":VIS "+ui->VISVLName->text();
    if(ui->VISBool->currentIndex()==0)
    {
        VISFlag+=" OFF";
    }
    else if (ui->VISBool->currentIndex()==1)
    {
        VISFlag+=" ON";
    }

    ui->plainTextEdit->appendPlainText(VISFlag);
    //clear inputs
//    ui->VISVLName->clear();
//    ui->VISBool->setCurrentIndex(0);
}

//2. 颜色属性设置 color
void MainWindow::on_ColorAttrSubmit_clicked()
{
    COLORData=":COLOR "+ui->ColorVLName->text();
    COLORData+=" "+QString::number(ui->ColorRProportion->value());
    COLORData+=" "+QString::number(ui->ColorGProportion->value());
    COLORData+=" "+QString::number(ui->ColorBProportion->value());

    ui->plainTextEdit->appendPlainText(COLORData);
    //clear
//    ui->ColorVLName->clear();
//    ui->ColorRProportion->setValue(0);
//    ui->ColorGProportion->setValue(0);
//    ui->ColorBProportion->setValue(0);
}
//3. 重叠检测 checkoverlap
void MainWindow::on_CheckOverlapSubmit_clicked()
{
    CheckOverlapFlag=":CHECK_OVERLAPS "+ui->CheckOverlapVLName->text();
    if(ui->CheckOverlapBool->currentIndex()==0)
    {
        CheckOverlapFlag+=" OFF";
    }
    else if (ui->CheckOverlapBool->currentIndex()==1)
    {
        CheckOverlapFlag+=" ON";
    }

    ui->plainTextEdit->appendPlainText(CheckOverlapFlag);
    //clear inputs
    ui->CheckOverlapVLName->clear();
    ui->CheckOverlapBool->setCurrentIndex(0);
}

// detector and readout setting
void MainWindow::on_OpenButton_2_clicked()
{
    ui->plainTextEdit->clear();
    QString curPath=QDir::currentPath();//获取系统当前目录;
    QString dlgTitle="open a file"; //对话框标题;
    QString filter="macros(*.mac);;all(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;

    OpenTextFile(aFileName);
}

void MainWindow::on_SaveButton_2_clicked()
{
    QString curPath=QDir::currentPath();//获取系统当前目录;
    QString dlgTitle="save a file"; //对话框标题;
    QString filter="macros(*.mac);;all(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);

    if (aFileName.isEmpty())
    {
        return;
    }
    saveToFile(aFileName);
}
// 虚拟探测器
void MainWindow::on_AddPosition_2_clicked()
{
    QString Probe="/score/create/probe ";
    Probe+=ui->ProbeName->text()+" "+QString::number(ui->CubicHalfSize->value())+" "+"mm";
    ui->plainTextEdit->appendPlainText(Probe);

    //    ui->ProbeName->clear();
    //    ui->CubicHalfSize->setValue(0.0);
}

// material name
void MainWindow::on_AddPosition_4_clicked()
{
    QString Mat="/score/probe/material ";
    Mat=Mat+ui->MatName->text();
    ui->plainTextEdit->appendPlainText(Mat);
}

// probe position
void MainWindow::on_AddPosition_clicked()
{
    QString Pos = "/score/probe/locate ";
    Pos+=QString::number(ui->PositionX_2->value())+" "+QString::number(ui->PositionY_2->value())+" "+QString::number(ui->PositionZ_2->value())+" mm";
    ui->plainTextEdit->appendPlainText(Pos);
}

//realWoldLogVOl
void MainWindow::on_AddRealWorldLogVol_clicked()
{
    QString RealWLV="/score/create/realWorldLogVol ";
    RealWLV+=ui->RealWorldLogVol->text()+" "+QString::number(ui->CopyNum->value());
    ui->plainTextEdit->appendPlainText(RealWLV);
}
//boxMesh
void MainWindow::on_boxMeshName_clicked()
{   QString boxMesh="/score/create/boxMesh ";  //!!!!!!!
    boxMesh+=ui->boxMesh->text();
    ui->plainTextEdit->appendPlainText(boxMesh);
}
//

void MainWindow::on_BoxSize_clicked()
{
    QString boxSize="/score/mesh/boxSize ";
    boxSize+=QString::number(ui->AsCPositionX_5->value())+" "+QString::number(ui->AsCPositionY_5->value())+" "+QString::number(ui->AsCPositionZ_5->value());
    ui->plainTextEdit->appendPlainText(boxSize);
}
//
void MainWindow::on_translatexyz_clicked()
{
    QString Txyz="/score/mesh/tranlate/xyz ";
    Txyz+=QString::number(ui->AsCPositionX_4->value())+" "+QString::number(ui->AsCPositionY_4->value())+" "+QString::number(ui->AsCPositionZ_4->value());
    ui->plainTextEdit->appendPlainText(Txyz);
}

void MainWindow::on_translatereset_clicked()
{
    QString Treset="/score/mesh/translate/reset ";
    Treset+=QString::number(ui->AsCPositionX_4->value())+" "+QString::number(ui->AsCPositionY_4->value())+" "+QString::number(ui->AsCPositionZ_4->value());
    ui->plainTextEdit->appendPlainText(Treset);
}

void MainWindow::on_BoxNBins_clicked()
{
    QString BNBin="/score/mesh/nBin ";
    BNBin+=QString::number(ui->spinBox->value())+" "+QString::number(ui->spinBox_2->value())+" "+QString::number(ui->spinBox_3->value());
    ui->plainTextEdit->appendPlainText(BNBin);
}

void MainWindow::on_RotX_2_clicked()
{
    QString RotX="/score/mesh/rotate/rotateX ";
    RotX+=QString::number(ui->AsCPositionX_6->value())+" degree";
    ui->plainTextEdit->appendPlainText(RotX);
}

void MainWindow::on_RotY_2_clicked()
{
    QString RotY="/score/mesh/rotate/rotateY ";
    RotY+=QString::number(ui->AsCPositionY_6->value())+" degree";
    ui->plainTextEdit->appendPlainText(RotY);
}

void MainWindow::on_RotZ_2_clicked()
{
    QString RotZ="/score/mesh/rotate/rotateZ ";
    RotZ+=QString::number(ui->AsCPositionZ_6->value())+" degree";
    ui->plainTextEdit->appendPlainText(RotZ);
}
//cylinderMesh
void MainWindow::on_cylinderMeshName_clicked()
{
    QString cylinderMesh="/score/create/cylinderMesh ";
    cylinderMesh+=ui->cylinderMesh->text();
    ui->plainTextEdit->appendPlainText(cylinderMesh);
}

void MainWindow::on_TubeSubmit_2_clicked()
{
    QString cylinderSize="/score/mesh/cylinderSize ";
    cylinderSize+=QString::number(ui->TubeOuterR_2->value())+" "+QString::number(ui->TubeHalfLength_2->value());
    ui->plainTextEdit->appendPlainText(cylinderSize);
}


void MainWindow::on_cylinderxyz_clicked()
{
    QString Txyz="/score/mesh/tranlate/xyz ";
    Txyz+=QString::number(ui->AsCPositionX_7->value())+" "+QString::number(ui->AsCPositionY_7->value())+" "+QString::number(ui->AsCPositionZ_7->value());
    ui->plainTextEdit->appendPlainText(Txyz);
}

void MainWindow::on_cylinderreset_clicked()
{
    QString Treset="/score/mesh/translate/reset ";
    Treset+=QString::number(ui->AsCPositionX_7->value())+" "+QString::number(ui->AsCPositionY_7->value())+" "+QString::number(ui->AsCPositionZ_7->value());
    ui->plainTextEdit->appendPlainText(Treset);
}

void MainWindow::on_cylinderNBin_clicked()
{
    QString BNBin="/score/mesh/nBin ";
    BNBin+=QString::number(ui->spinBox_4->value())+" "+QString::number(ui->spinBox_5->value())+" "+QString::number(ui->spinBox_6->value());
    ui->plainTextEdit->appendPlainText(BNBin);
}

void MainWindow::on_RotX_3_clicked()
{
    QString RotX="/score/mesh/rotate/rotateX ";
    RotX+=QString::number(ui->AsCPositionX_9->value())+" degree";
    ui->plainTextEdit->appendPlainText(RotX);
}

void MainWindow::on_RotY_3_clicked()
{
    QString RotY="/score/mesh/rotate/rotateY ";
    RotY+=QString::number(ui->AsCPositionY_9->value())+" degree";
    ui->plainTextEdit->appendPlainText(RotY);
}

void MainWindow::on_RotZ_3_clicked()
{
    QString RotZ="/score/mesh/rotate/rotateZ ";
    RotZ+=QString::number(ui->AsCPositionZ_9->value())+" degree";
    ui->plainTextEdit->appendPlainText(RotZ);
}

// data readout 数据读出

void MainWindow::on_AddQuantityName_clicked()
{
    int index = ui->ReadOutQuantity->currentIndex();
    if(index==0)
    {
        QString cellCharge="/score/quantity/cellCharge ";
        cellCharge+= ui->QuantityName->text()+" e+";
        ui->plainTextEdit->appendPlainText(cellCharge);
    }else if(index==1)
    {
        QString cellFlux="/score/quantity/cellFlux ";
        cellFlux+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(cellFlux);
    }else if(index==2)
    {
        QString passageCellFlux="/score/quantity/passageCellFlux ";
        passageCellFlux+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(passageCellFlux);
    }else if(index==3)
    {
        QString passageCellCurrent="/score/quantity/passageCellCurrent ";
        passageCellCurrent+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(passageCellCurrent);
    }else if(index==4)
    {
        QString doseDeposit="/score/quantity/doseDeposit ";
        doseDeposit+= ui->QuantityName->text()+" Gy";
        ui->plainTextEdit->appendPlainText(doseDeposit);
    }else if(index==5)
    {
        QString energyDeposit="/score/quantity/energyDeposit ";
        energyDeposit+= ui->QuantityName->text()+" MeV";
        ui->plainTextEdit->appendPlainText(energyDeposit);
    }else if(index==6)
    {
        QString flatSurfaceCurrent="/score/quantity/flatSurfaceCurrent ";
        flatSurfaceCurrent+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(flatSurfaceCurrent);
    }else if(index==7)
    {
        QString flatSurfaceFlux="/score/quantity/flatSurfaceFlux ";
        flatSurfaceFlux+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(flatSurfaceFlux);
    }else if(index==8)
    {
        QString nOfCollision="/score/quantity/nOfCollision ";
        nOfCollision+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(nOfCollision);
    }else if(index==9)
    {
        QString nOfSecondary="/score/quantity/nOfSecondary ";
        nOfSecondary+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(nOfSecondary);
    }else if(index==10)
    {
        QString nOfStep="/score/quantity/nOfStep ";
        nOfStep+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(nOfStep);
    }else if(index==11)
    {
        QString nOfTerminatedTrack="/score/quantity/nOfTerminatedTrack ";
        nOfTerminatedTrack+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(nOfTerminatedTrack);
    }else if(index==12)
    {
        QString nOfTrack="/score/quantity/nOfTrack ";
        nOfTrack+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(nOfTrack);
    }else if(index==13)
    {
        QString passageTrackLength="/score/quantity/passageTrackLength ";
        passageTrackLength+= ui->QuantityName->text()+" true mm";
        ui->plainTextEdit->appendPlainText(passageTrackLength);
    }else if(index==14)
    {
        QString population="/score/quantity/population ";
        population+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(population);
    }else if(index==15)
    {
        QString trackLength="/score/quantity/trackLength ";
        trackLength+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(trackLength);
    }
    else if(index==16)
    {
        QString volumeFlux="/score/quantity/volumeFlux ";
        volumeFlux+= ui->QuantityName->text();
        ui->plainTextEdit->appendPlainText(volumeFlux);
    }
}


void MainWindow::on_FilterEkin_clicked()
{
    QString kineticEnergy="/score/filter/kineticEnergy ";
    kineticEnergy+=ui->EkinName->text()+" "+QString::number(ui->Elow->value())+" "+QString::number(ui->Ehigh->value());
    int index = ui->EkinUnit->currentIndex();
    if(index == 0)
    {
        kineticEnergy+=" eV";
        ui->plainTextEdit->appendPlainText(kineticEnergy);
    }else if(index == 1)
    {
        kineticEnergy+=" keV";
        ui->plainTextEdit->appendPlainText(kineticEnergy);
    }else if(index == 2)
    {
        kineticEnergy+=" MeV";
        ui->plainTextEdit->appendPlainText(kineticEnergy);
    }else if(index == 3)
    {
        kineticEnergy+=" GeV";
        ui->plainTextEdit->appendPlainText(kineticEnergy);
    }
}

void MainWindow::on_AddParticle_clicked()
{
    QString FilterParticle="/score/filter/particle ";
    FilterParticle+=ui->FName->text()+" "+ui->ParticleName->text();
    ui->plainTextEdit->appendPlainText(FilterParticle);
}

void MainWindow::on_AddEkinParticle_clicked()
{
    QString pWithEkin="/score/filter/particleWithKineticEnergy ";
    pWithEkin+=ui->FName_2->text()+" "+QString::number(ui->Elow_2->value())+" "+QString::number(ui->Ehigh_2->value());
    int index = ui->EkinUnit_2->currentIndex();
    if(index == 0)
    {
        pWithEkin+=" eV";
    }else if(index == 1)
    {
        pWithEkin+=" keV";
    }else if(index == 2)
    {
        pWithEkin+=" MeV";
    }else if(index == 3)
    {
        pWithEkin+=" GeV";
    }

    pWithEkin+=" "+ui->particleList->text();
    ui->plainTextEdit->appendPlainText(pWithEkin);
}

void MainWindow::on_dumpData_clicked()
{
    QString DumpData="/score/dumpQuantityToFile ";
    DumpData+=ui->ScoreName->text()+" "+ui->QuantityName_2->text()+" "+ui->dumpFileName->text();
    ui->plainTextEdit->appendPlainText(DumpData);
}

void MainWindow::on_dumpData_2_clicked()
{
    QString DumpData="/score/dumpAllQuantitiesToFile ";
    DumpData+=ui->ScoreName_2->text()+" "+ui->dumpFileName_2->text();
    ui->plainTextEdit->appendPlainText(DumpData);
}

void MainWindow::on_Addhist_clicked()
{
    QString hist="/analysis/h1/create ";
    hist+=ui->QName->text()+" "+ui->histName->text()+" "+QString::number(ui->nBins->value())+" "
            +QString::number(ui->Alow->value())+" "+QString::number(ui->Ahigh->value())+" "+ui->UnitName->text();

    int index = ui->AxisType->currentIndex();
    if(index == 0)
    {
        hist+=" ! linear";
    }else if(index == 1)
    {
        hist+=" ! log";
    }
    ui->plainTextEdit->appendPlainText(hist);
}


void MainWindow::on_histToFile_clicked()
{
    QString hist2File="/score/fill1D ";
    hist2File+= QString::number(ui->histNum->value())+" "+ui->QTohist->text()+" "+ui->hisName->text();
    ui->plainTextEdit->appendPlainText(hist2File);
}


void MainWindow::on_pushButton_13_clicked()
{
    QString aa="/score/close";
    ui->plainTextEdit->appendPlainText(aa);
}

void MainWindow::on_printRun_clicked()
{
    QString aa="/run/printProgress ";
    aa+=QString::number(ui->printRunNum->value());
    ui->plainTextEdit->appendPlainText(aa);
}

void MainWindow::on_RunNum_clicked()
{
    QString aa="/run/beamOn ";
    aa+=QString::number(ui->RunNumData->value());
    ui->plainTextEdit->appendPlainText(aa);
}
// 射线源设置
void MainWindow::on_OpenButton_3_clicked()
{
    ui->plainTextEdit->clear();
    QString curPath=QDir::currentPath();//获取系统当前目录;
    QString dlgTitle="open a file"; //对话框标题;
    QString filter="macros(*.mac);;all(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;

    OpenTextFile(aFileName);
}

void MainWindow::on_SaveButton_3_clicked()
{
    QString curPath=QDir::currentPath();//获取系统当前目录;
    QString dlgTitle="save a file"; //对话框标题;
    QString filter="macros(*.mac);;all(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);

    if (aFileName.isEmpty())
    {
        return;
    }
    saveToFile(aFileName);
}

void MainWindow::on_ParticleName_2_clicked()
{
    QString PN="/gps/particle ";
    int index = ui->PNcomboBox->currentIndex();
    if(index == 0)
    {
        PN+="geantion";
    }else if(index == 1)
    {
        PN+="gamma";
    }else if(index == 2)
    {
        PN+="neutron";
    }else if(index == 3)
    {
        PN+="proton";
    }else if(index == 4)
    {
        PN+="e-";
    }else if(index == 5)
    {
        PN+="ion";
    }else if(index == 6)
    {
        PN+="opticalphoton";
    }else if(index == 7)
    {
        PN+="alpha";
    }else if(index == 8)
    {
        PN+="deuteron";
    }else if(index == 9)
    {
        PN+="triton";
    }
    ui->plainTextEdit->appendPlainText(PN);
}

void MainWindow::on_AddIon_clicked()
{
    QString ION="/gps/ion ";
    ION+=QString::number(ui->spinBox_7->value())+" "+QString::number(ui->spinBox_8->value())+" "+QString::number(ui->spinBox_9->value())
            +" "+QString::number(ui->doubleSpinBox->value());
    ui->plainTextEdit->appendPlainText(ION);
}

void MainWindow::on_PEkin_clicked()
{
    QString PEk="/gps/energy ";
    PEk+=QString::number(ui->doubleSpinBox_2->value());
    int index = ui->EkinUnit_3->currentIndex();
    if(index == 0)
    {
        PEk+=" eV";
    }else if(index == 1)
    {
        PEk+=" keV";
    }else if(index == 2)
    {
        PEk+=" MeV";
    }else if(index == 3)
    {
        PEk+=" GeV";
    }

    ui->plainTextEdit->appendPlainText(PEk);
}


void MainWindow::on_Addposition_clicked()
{
    QString ps="/gps/position ";
    ps+=QString::number(ui->AsCPositionX_8->value())+" "+QString::number(ui->AsCPositionY_8->value())
            +" "+QString::number(ui->AsCPositionZ_8->value())+" mm";
    ui->plainTextEdit->appendPlainText(ps);
}

void MainWindow::on_Adddirection_clicked()
{
    QString ps="/gps/direction ";
    ps+=QString::number(ui->AsCPositionX_10->value())+" "+QString::number(ui->AsCPositionY_10->value())
            +" "+QString::number(ui->AsCPositionZ_10->value());
    ui->plainTextEdit->appendPlainText(ps);
}

// 位置分布

void MainWindow::on_posType_clicked()
{
    QString PEk="/gps/pos/type ";
    int index = ui->comboBox_2->currentIndex();
    if(index == 0)
    {
        PEk+="Point";
    }else if(index == 1)
    {
        PEk+="Beam";
    }else if(index == 2)
    {
        PEk+="Plane";
    }else if(index == 3)
    {
        PEk+="Surface";
    }else if(index == 4)
    {
        PEk+="Volume";
    }
    ui->plainTextEdit->appendPlainText(PEk);
}

void MainWindow::on_AddXsigma_clicked()
{
    QString sx="/gps/pos/sigma_x ";
    sx+=QString::number(ui->sigma_x->value())+" mm";
    ui->plainTextEdit->appendPlainText(sx);
}

void MainWindow::on_AddYsigma_clicked()
{
    QString sx="/gps/pos/sigma_y ";
    sx+=QString::number(ui->sigma_y->value())+" mm";
    ui->plainTextEdit->appendPlainText(sx);
}

void MainWindow::on_AddRsigma_clicked()
{
    QString sx="/gps/pos/sigma_r ";
    sx+=QString::number(ui->sigma_r->value())+" degree";
    ui->plainTextEdit->appendPlainText(sx);
}

void MainWindow::on_Shape_clicked()
{
    QString SHAPE="/gps/pos/shape ";
    int index = ui->comboBox_3->currentIndex();
    if(index == 0)
    {
        SHAPE+="Circle";
    }else if(index == 1)
    {
        SHAPE+="Annulus";
    }else if(index == 2)
    {
        SHAPE+="Ellipse";
    }else if(index == 3)
    {
        SHAPE+="Square";
    }else if(index == 4)
    {
        SHAPE+="Rectangle";
    }else if(index == 4)
    {
        SHAPE+="Sphere";
    }else if(index == 5)
    {
        SHAPE+="Ellipsoid";
    }else if(index == 6)
    {
        SHAPE+="Cylinder";
    }else if(index == 7)
    {
        SHAPE+="EllipticCylinder";
    }else if(index == 8)
    {
        SHAPE+="Para";
    }

    ui->plainTextEdit->appendPlainText(SHAPE);
}

void MainWindow::on_posCenter_clicked()
{
    QString posCen="/gps/pos/centre ";
    posCen+=QString::number(ui->AsCPositionX_11->value())+" "+QString::number(ui->AsCPositionY_11->value())
            +" "+QString::number(ui->AsCPositionZ_11->value())+" mm";
    ui->plainTextEdit->appendPlainText(posCen);
}

void MainWindow::on_RotMatrix1_2_clicked()
{
    QString rot1="/gps/pos/rot1 ";
    rot1+=QString::number(ui->RotX_4->value())+" "+QString::number(ui->RotY_4->value())
            +" "+QString::number(ui->RotZ_4->value());
    ui->plainTextEdit->appendPlainText(rot1);
}

void MainWindow::on_RotMatrix1_3_clicked()
{
    QString rot1="/gps/pos/rot2 ";
    rot1+=QString::number(ui->RotX_5->value())+" "+QString::number(ui->RotY_5->value())
            +" "+QString::number(ui->RotZ_5->value());
    ui->plainTextEdit->appendPlainText(rot1);
}

void MainWindow::on_AddHalfX_2_clicked()
{
    QString hlfx="/gps/pos/halfx ";
    hlfx+=QString::number(ui->PARAHalfX_2->value())+" mm";
    ui->plainTextEdit->appendPlainText(hlfx);
}

void MainWindow::on_AddHalfY_2_clicked()
{
    QString hlfx="/gps/pos/halfy ";
    hlfx+=QString::number(ui->PARAHalfY_2->value())+" mm";
    ui->plainTextEdit->appendPlainText(hlfx);
}

void MainWindow::on_AddHalfZ_2_clicked()
{
    QString hlfx="/gps/pos/halfz ";
    hlfx+=QString::number(ui->PARAHalfZ_2->value())+" mm";
    ui->plainTextEdit->appendPlainText(hlfx);
}


void MainWindow::on_AddSphereOuterR_2_clicked()
{
    QString Radius = "/gps/pos/radius ";
    Radius+=QString::number(ui->SphereOuterR_2->value())+" mm";
    ui->plainTextEdit->appendPlainText(Radius);
}

void MainWindow::on_AddSphereInnerR_2_clicked()
{
    QString Radius = "/gps/pos/inner_radius ";
    Radius+=QString::number(ui->SphereInnerR_2->value())+" mm";
    ui->plainTextEdit->appendPlainText(Radius);
}

void MainWindow::on_AddPARAAlpha_2_clicked()
{
    QString alpha="/gps/pos/paralp ";
    alpha+=QString::number(ui->PARAAlpha_2->value())+" degree";
    ui->plainTextEdit->appendPlainText(alpha);
}

void MainWindow::on_AddPARATheta_2_clicked()
{
    QString alpha="/gps/pos/parthe ";
    alpha+=QString::number(ui->PARATheta_2->value())+" degree";
    ui->plainTextEdit->appendPlainText(alpha);
}

void MainWindow::on_AddPARAPhi_2_clicked()
{
    QString alpha="/gps/pos/parphi ";
    alpha+=QString::number(ui->PARAPhi_2->value())+" degree";
    ui->plainTextEdit->appendPlainText(alpha);
}

//角分布

void MainWindow::on_angType_clicked()
{
    QString angT="/gps/ang/type ";
    int index = ui->comboBox_5->currentIndex();
    if(index == 0)
    {
        angT+="iso";
    }else if(index == 1)
    {
        angT+="cos";
    }else if(index == 2)
    {
        angT+="planar";
    }else if(index == 3)
    {
        angT+="beam1d";
    }else if(index == 4)
    {
        angT+="beam2d";
    }else if(index == 5)
    {
        angT+="focused";
    }
    ui->plainTextEdit->appendPlainText(angT);
}

void MainWindow::on_AddSigmaX_clicked()
{
    QString sx="/gps/ang/sigma_x ";
    sx+=QString::number(ui->sigmax->value())+" mm";
    ui->plainTextEdit->appendPlainText(sx);
}

void MainWindow::on_AddSigmaY_clicked()
{
    QString sx="/gps/ang/sigma_y ";
    sx+=QString::number(ui->sigmay->value())+" mm";
    ui->plainTextEdit->appendPlainText(sx);
}

void MainWindow::on_AddSigmaR_clicked()
{
    QString sx="/gps/ang/sigma_r ";
    sx+=QString::number(ui->sigmar->value())+" degree";
    ui->plainTextEdit->appendPlainText(sx);
}

void MainWindow::on_AddMiniThe_clicked()
{
    QString minT="/gps/ang/mintheta ";
    minT+=QString::number(ui->minTheta->value())+" degree";
    ui->plainTextEdit->appendPlainText(minT);
}

void MainWindow::on_AddMaxThe_clicked()
{
    QString minT="/gps/ang/maxtheta ";
    minT+=QString::number(ui->maxTheta->value())+" degree";
    ui->plainTextEdit->appendPlainText(minT);
}

void MainWindow::on_AddMinPhi_clicked()
{
    QString minT="/gps/ang/minphi ";
    minT+=QString::number(ui->minPhi->value())+" degree";
    ui->plainTextEdit->appendPlainText(minT);
}

void MainWindow::on_AddMaxPhi_clicked()
{
    QString minT="/gps/ang/maxphi ";
    minT+=QString::number(ui->maxPhi->value())+" degree";
    ui->plainTextEdit->appendPlainText(minT);
}

void MainWindow::on_RotMatrix1_4_clicked()
{
    QString rot1="/gps/ang/rot1 ";
    rot1+=QString::number(ui->RotX_6->value())+" "+QString::number(ui->RotY_6->value())
            +" "+QString::number(ui->RotZ_6->value());
    ui->plainTextEdit->appendPlainText(rot1);
}

void MainWindow::on_RotMatrix1_5_clicked()
{
    QString rot1="/gps/ang/rot2 ";
    rot1+=QString::number(ui->RotX_7->value())+" "+QString::number(ui->RotY_7->value())
            +" "+QString::number(ui->RotZ_7->value());
    ui->plainTextEdit->appendPlainText(rot1);
}

void MainWindow::on_AddFocusPoint_clicked()
{
    QString posCen="/gps/ang/focuspoint ";
    posCen+=QString::number(ui->AsCPositionX_13->value())+" "+QString::number(ui->AsCPositionY_13->value())
            +" "+QString::number(ui->AsCPositionZ_13->value())+" mm";
    ui->plainTextEdit->appendPlainText(posCen);
}

// 能量分布

void MainWindow::on_eneType_clicked()
{
    QString enet="/gps/ene/type ";
    int index = ui->comboBox_6->currentIndex();
    if(index == 0)
    {
        enet+="Mono";
    }else if (index == 1)
    {
        enet+="Lin";
    }else if (index == 2)
    {
        enet+="Pow";
    }else if (index == 3)
    {
        enet+="Exp";
    }else if (index == 4)
    {
        enet+="Gauss";
    }else if (index == 5)
    {
        enet+="Arb";
    }
    ui->plainTextEdit->appendPlainText(enet);
}

void MainWindow::on_Ekin_clicked()
{
    QString minE="/gps/ene/min "+QString::number(ui->Elow_3->value());
    QString maxE="/gps/ene/max "+QString::number(ui->Ehigh_3->value());
    int index = ui->EkinUnit_4->currentIndex();
    if(index == 0)
    {
        minE+=" eV";
        maxE+=" eV";
    }else if(index == 1)
    {
        minE+=" keV";
        maxE+=" keV";
    }else if(index == 2)
    {
        minE+=" MeV";
        maxE+=" MeV";
    }else if(index == 3)
    {
        minE+=" GeV";
        maxE+=" GeV";
    }
    ui->plainTextEdit->appendPlainText(minE);
    ui->plainTextEdit->appendPlainText(maxE);
}

void MainWindow::on_Addsigma_clicked()
{
    QString sg="/gps/ene/sigma ";
    sg+=QString::number(ui->sigma->value())+" keV";
    ui->plainTextEdit->appendPlainText(sg);
}

void MainWindow::on_AddAlpha_clicked()
{
    QString sg="/gps/ene/alpha ";
    sg+=QString::number(ui->alpha->value());
    ui->plainTextEdit->appendPlainText(sg);
}

void MainWindow::on_AddE0_clicked()
{
    QString sg="/gps/ene/ezero ";
    sg+=QString::number(ui->E0->value());
    ui->plainTextEdit->appendPlainText(sg);
}

void MainWindow::on_AddGradient_clicked()
{
    QString sg="/gps/ene/gradient ";
    sg+=QString::number(ui->gradient->value());
    ui->plainTextEdit->appendPlainText(sg);
}

void MainWindow::on_AddIntercept_clicked()
{
    QString sg="/gps/ene/intercept ";
    sg+=QString::number(ui->intercept->value());
    ui->plainTextEdit->appendPlainText(sg);
}

// 能谱直方图
void MainWindow::on_AddPoint_clicked()
{
    QString ep="/gps/hist/point ";
    ep+=QString::number(ui->E->value())+ " "+QString::number(ui->Weight->value());
    ui->plainTextEdit->appendPlainText(ep);
}

void MainWindow::on_AddHistFile_clicked()
{
    QString hf="/gps/hist/file ";
    hf+=ui->lineEdit->text();
    ui->plainTextEdit->appendPlainText(hf);
}

void MainWindow::on_AddInter_clicked()
{
    QString interpolation = "/gps/hist/inter ";
    int index = ui->comboBox_4->currentIndex();
    if(index == 0)
    {
        interpolation+=" Lin";
    }else if (index == 1)
    {
        interpolation+=" Log";
    }else if (index == 2)
    {
        interpolation+=" Exp";
    }else if (index == 3)
    {
        interpolation+=" Spline";
    }
    ui->plainTextEdit->appendPlainText(interpolation);
}

void MainWindow::on_reset_clicked()
{
    QString rs = "/gps/hist/reset ";
    ui->plainTextEdit->appendPlainText(rs);
}


// 物理过程

void MainWindow::on_OpenButton_4_clicked()
{
    ui->plainTextEdit->clear();
    QString curPath=QDir::currentPath();//获取系统当前目录;
    QString dlgTitle="open a file"; //对话框标题;
    QString filter="text(*.txt);;all(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getOpenFileName(this,dlgTitle,curPath,filter);
    if (aFileName.isEmpty())
        return;

    OpenTextFile(aFileName);
}

void MainWindow::on_SaveButton_4_clicked()
{
    QString curPath=QDir::currentPath();//获取系统当前目录;
    QString dlgTitle="save a file"; //对话框标题;
    QString filter="text(*.txt);;all(*.*)"; //文件过滤器
    QString aFileName=QFileDialog::getSaveFileName(this,dlgTitle,curPath,filter);

    if (aFileName.isEmpty())
    {
        return;
    }
    saveToFile(aFileName);
}

void MainWindow::on_AddRefference_clicked()
{
    ui->plainTextEdit->appendPlainText("## refference physiclists");
    QString str[19]={"QBBC","QGS_BIC","QGSP_BERT","QGSP_BERT_HP","QGSP_BIC","QGSP_BIC_HP","QGSP_BIC_AllHP","QGSP_FTFP_BERT","QGSP_INCLXX_HP",
                     "FTF_BIC","FTFQGSP_BERT","FTFP_BERT","FTFP_BERT_HP","FTFP_BERT_ATL","FTFP_BERT_TRV","FTFP_INCLXX_HP",
                     "Shielding","ShieldingLEND","LBE"};

    QList<QCheckBox*> allCheckBox = ui->groupBox_33->findChildren<QCheckBox*>();
    QList<QCheckBox*>::iterator it;
    for(it = allCheckBox.begin();it!=allCheckBox.end();it++)
    {
        if((*it)->isChecked())
        {
            RefPhyWrite((*it)->objectName());
        }
    }
}

void MainWindow::RefPhyWrite(QString as)
{
    QString str[19]={"QBBC","QGS_BIC","QGSP_BERT","QGSP_BERT_HP","QGSP_BIC","QGSP_BIC_HP","QGSP_BIC_AllHP","QGSP_FTFP_BERT","QGSP_INCLXX_HP",
                     "FTF_BIC","FTFQGSP_BERT","FTFP_BERT","FTFP_BERT_HP","FTFP_BERT_ATL","FTFP_BERT_TRV","FTFP_INCLXX_HP",
                     "Shielding","ShieldingLEND","LBE"};
    //    QString::iterator it;
    //    for(it=str->begin();it!=str->end();it++)
    //    {
    //        qDebug()<<*it<<endl;
    //    }

    for(int i=0;i<19;i++)
    {
        if(as==str[i])
        {
            ui->plainTextEdit->appendPlainText(str[i]+" 1");
        }else {
            ui->plainTextEdit->appendPlainText(str[i]+" 0");

            //QList<QCheckBox*> allCheckBox = ui->groupBox_33->findChildren<QCheckBox*>(QString(),Qt::FindDirectChildrenOnly);
            // 参考：https://doc.qt.io/qt-5/qobject.html#findChildren
            // 实现的功能：ui->str[i]->setEnable(false);
            QList<QCheckBox*> allCheckBox = ui->groupBox_33->findChildren<QCheckBox*>();
            QList<QCheckBox*>::iterator it;
            for(it = allCheckBox.begin();it!=allCheckBox.end();it++)
            {
                //qDebug()<<(*it)->objectName();
                //qDebug()<<"##############";
                if((*it)->objectName()==str[i])
                {
                    (*it)->setCheckState(Qt::Unchecked);
                    (*it)->setEnabled(false);
                }
            }

        }
    }
}

void MainWindow::on_AddRefferenceReset_clicked()
{
    QList<QCheckBox*> allCheckBox = ui->groupBox_33->findChildren<QCheckBox*>();
    QList<QCheckBox*>::iterator it;
    for(it = allCheckBox.begin();it!=allCheckBox.end();it++)
    {
        (*it)->setCheckState(Qt::Unchecked);
        (*it)->setEnabled(true);
    }
}

void MainWindow::on_AddEmPhysics_clicked()
{
    ui->plainTextEdit->appendPlainText("## Electronic and magnetic physics");
    QString str[5]={"G4EmStandardPhysics","G4EmStandardPhysics_option1","G4EmStandardPhysics_option2",
                    "G4EmStandardPhysics_option3","G4EmStandardPhysics_option4"};

    QList<QCheckBox*> allCheckBox = ui->groupBox_35->findChildren<QCheckBox*>();
    QList<QCheckBox*>::iterator it,tmpit;
    for(it = allCheckBox.begin();it!=allCheckBox.end();it++)
    {
        if((*it)->isChecked())
        {
            ui->plainTextEdit->appendPlainText((*it)->objectName()+" 1");
            for(tmpit=allCheckBox.begin();tmpit!=allCheckBox.end();tmpit++)
            {
                if(tmpit!=it)
                {
                    (*tmpit)->setCheckState(Qt::Unchecked);
                    (*tmpit)->setEnabled(false);
                }
            }
        }else
        {
            ui->plainTextEdit->appendPlainText((*it)->objectName()+" 0");
        }
    }
}

void MainWindow::on_AddEmPhysicsReset_clicked()
{
    QList<QCheckBox*> allCheckBox = ui->groupBox_35->findChildren<QCheckBox*>();
    QList<QCheckBox*>::iterator it;
    for(it = allCheckBox.begin();it!=allCheckBox.end();it++)
    {
        (*it)->setCheckState(Qt::Unchecked);
        (*it)->setEnabled(true);
    }
}

void MainWindow::on_AddOptical_clicked()
{
    ui->plainTextEdit->appendPlainText("## optical physics");
    if(ui->OpticalPhysics->isChecked())
    {
        ui->plainTextEdit->appendPlainText("OpticalPhysics 1");
    }
    else
    {
        ui->plainTextEdit->appendPlainText("OpticalPhysics 0");
    }
}

void MainWindow::on_AddFileName_clicked()
{
    QString fileName="/analysis/setFileName ";
    fileName+=ui->FileName->text();
    ui->plainTextEdit->appendPlainText(fileName);
}

//////////////
/// \brief MainWindow::on_actionabout_triggered
///菜单栏
/// 关于
void MainWindow::on_actionabout_triggered()
{
    About *aboutwin = new About();
//    aboutwin = new About(this);
    aboutwin ->show();
}

//////////////
/// \brief MainWindow::on_actionhelp_triggered
///菜单栏
/// 帮助
void MainWindow::on_actionhelp_triggered()
{
    Help *helpwin = new Help();
    helpwin->show();

}
//////////////
/// \brief MainWindow::on_actionRun_triggered
///菜单栏
/// 运行
#include <QMessageBox>

void MainWindow::on_actionRun_triggered()
{

#if defined(__linux__) // Or #if __linux__
    // zhuanglan.zhihu.com/p/110544668
    QProcess *myPro=new QProcess();
    QString program = "gnome-terminal";
    QStringList arguments;
    arguments<<"-x"<<"./SWNS";
    myPro->startDetached(program,arguments);
#elif _WIN32
    // for windows
    QMessageBox msgBox;
    msgBox.setText("Windows应用只提供建模设置功能！！！运行模拟程序请将设置文件拷贝到安装完整版软件的Linux平台.");
    msgBox.exec();
#endif
}

