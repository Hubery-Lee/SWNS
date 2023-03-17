#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "about.h"
#include "help.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //methods
    bool saveToFile(const QString &aFileName);
    bool OpenTextFile(const QString &aFileName);
    void RefPhyWrite(QString as);
private slots:

    void on_SaveButton_clicked();
    void on_OpenButton_clicked();

    //--composed material 化合物和混合物定义
    void on_ComposeSubmit_clicked();
    void on_AddComposeElemNum_clicked();

    //-- simple substance 单质
    void on_Mat1Submit_clicked();

    //--- element
    //made of one unique isotope
    void on_ElemSubmit_clicked();

    // isotope
    void on_IsoSubmit_clicked();

    // element composed of several isotopes
    void on_ElemCompIsoSubmit_clicked();
    void on_AddElemCompIsoNum_clicked();

    //================================
    // 几何建模

    // Box
    void on_BoxSubmit_clicked();

    // Tubs
    void on_TubeSubmit_clicked();

    // cons
    void on_ConsSubmit_clicked();

    // trapzoid trd 梯形
    void on_TRDSubmit_clicked();

    // generic trapzoid 泛梯形
    void on_TRAPSubmit_clicked();

    // paralellepiped 平行六面体
    void on_PARASubmit_clicked();

    // sphere 球
    void on_SphereSubmit_clicked();

    // torus 圆环
    void on_TORUSSubmit_clicked();

    // polycone 多圆锥体
    void on_POLYCONESubmit_clicked();
    void on_AddPOLYCONERZNum_clicked();


    // Polyhedra 多棱锥体
    void on_PHedraSubmit_clicked();
    void on_AddPHedraRZNum_clicked();

    //elliptical tube 椭圆管
    void on_EllipticalSubmit_clicked();

    // ellipsoid 椭球
    void on_EllipsoidSubmit_clicked();

    // elliptical cone 椭圆锥
    void on_EllipticalConeSubmit_clicked();

    // hyperbolic profile 双曲面
    void on_HYPESubmit_clicked();

    // tetrahedron 四面体
    void on_TETSubmit_clicked();

    // twist box 扭曲立方体
    void on_TwistBoxSubmit_clicked();

    // twist tubs 扭曲管
    void on_TwistTubsSubmit_clicked();

    // boolean solids 几何体布尔运算
    void on_BoolSolidSubmit_clicked();

    //============================================
    // logical volume 逻辑体
    void on_LogicalVolumeSubmit_clicked();

    //============================================
    // Physical volumes 放置方式

    //single placement
    void on_SinglePlacementSubmit_clicked();

    // Replica 复制
    void on_ReplicaSubmit_clicked();

    // assemble volumes 组装体
    //1. lv
    void on_AssembleLVSubmit_clicked();

    //2. component 组分
    void on_AsCSubmit_clicked();

    //3. physical volume 组装体放置
    void on_AsPLaceSubmit_clicked();

    // rotation matrix 旋转矩阵

    // method 1
    void on_RotMatrix1Submit_clicked();
    // method 2
    void on_RotMatrix2Submit_clicked();

    // other tags 其他属性设置

    //1. 显示设置 vis
    void on_VISSubmit_clicked();
    //2. 颜色属性设置 color
    void on_ColorAttrSubmit_clicked();
    //3. 重叠检测 checkoverlap
    void on_CheckOverlapSubmit_clicked();

    // detector and readout setting
    void on_OpenButton_2_clicked();
    void on_SaveButton_2_clicked();

    // probe 虚拟探测器
    void on_AddPosition_2_clicked();
    // probe material
    void on_AddPosition_4_clicked();
    // probe position
    void on_AddPosition_clicked();

    // realWorld LogVol
    void on_AddRealWorldLogVol_clicked();
    //boxMesh
    void on_boxMeshName_clicked();
    void on_BoxSize_clicked();
    void on_translatexyz_clicked();
    void on_translatereset_clicked();
    void on_BoxNBins_clicked();
    void on_RotX_2_clicked();
    void on_RotY_2_clicked();
    void on_RotZ_2_clicked();
    // cylinderMesh
    void on_cylinderMeshName_clicked();
    void on_TubeSubmit_2_clicked();
    void on_cylinderxyz_clicked();
    void on_cylinderreset_clicked();
    void on_cylinderNBin_clicked();
    void on_RotX_3_clicked();
    void on_RotY_3_clicked();
    void on_RotZ_3_clicked();

    // data readout 数据读出
    void on_AddQuantityName_clicked();
    void on_FilterEkin_clicked();
    void on_AddParticle_clicked();
    void on_AddEkinParticle_clicked();
    void on_dumpData_clicked();
    void on_dumpData_2_clicked();
    void on_Addhist_clicked();
    void on_histToFile_clicked();
    void on_pushButton_13_clicked();
    void on_printRun_clicked();
    void on_RunNum_clicked();

    //=====================================
    // 射线源设置
    void on_OpenButton_3_clicked();
    void on_SaveButton_3_clicked();
    void on_ParticleName_2_clicked();
    void on_AddIon_clicked();
    void on_PEkin_clicked();
    void on_Addposition_clicked();
    void on_Adddirection_clicked();
    void on_posType_clicked();
    void on_AddXsigma_clicked();
    void on_AddYsigma_clicked();
    void on_AddRsigma_clicked();
    void on_Shape_clicked();
    void on_posCenter_clicked();
    void on_RotMatrix1_2_clicked();
    void on_RotMatrix1_3_clicked();
    void on_AddHalfX_2_clicked();
    void on_AddHalfY_2_clicked();
    void on_AddHalfZ_2_clicked();
    void on_AddSphereOuterR_2_clicked();
    void on_AddSphereInnerR_2_clicked();
    void on_AddPARAAlpha_2_clicked();
    void on_AddPARATheta_2_clicked();
    void on_AddPARAPhi_2_clicked();
    void on_angType_clicked();
    void on_AddSigmaX_clicked();
    void on_AddSigmaY_clicked();
    void on_AddSigmaR_clicked();
    void on_AddMiniThe_clicked();
    void on_AddMaxThe_clicked();
    void on_AddMinPhi_clicked();
    void on_AddMaxPhi_clicked();
    void on_RotMatrix1_4_clicked();
    void on_RotMatrix1_5_clicked();
    void on_AddFocusPoint_clicked();
    void on_eneType_clicked();
    void on_Ekin_clicked();
    void on_Addsigma_clicked();
    void on_AddAlpha_clicked();
    void on_AddE0_clicked();
    void on_AddGradient_clicked();
    void on_AddIntercept_clicked();
    void on_AddPoint_clicked();
    void on_AddHistFile_clicked();
    void on_AddInter_clicked();
    void on_reset_clicked();

    // 物理过程

    void on_OpenButton_4_clicked();
    void on_SaveButton_4_clicked();
    void on_AddRefference_clicked();

    void on_AddRefferenceReset_clicked();
    void on_AddEmPhysics_clicked();
    void on_AddEmPhysicsReset_clicked();
    void on_AddOptical_clicked();

    // 运行程序 cmd
    void on_AddFileName_clicked();

    void on_actionabout_triggered();

    void on_actionhelp_triggered();

    void on_actionRun_triggered();

private:
    Ui::MainWindow *ui;

    // Material
    QString composeMat;
    QString Mat1;
    QString Elem;
    QString Iso;//isotope
    QString ElemCompIso;// element composed of several isotopes

    // Geometry solid volume
    QString BoxData;
    QString TubsData;
    QString ConsData;
    QString TRDData;
    QString TRAPData;
    QString PARAData;
    QString SphereData;
    QString TorusData;
    QString PolyconeData;
    QString PolyhedraData;
    QString EllipticalTubeData;
    QString EllipsoidData;
    QString EllipticalConeData;
    QString HyperbolicData;
    QString TetrahedronData;
    QString TwistBoxData;
    QString TwistTubsData;
    QString BooleanSolidData;

    // logical volume
    QString LogicalData;

    // physical volume
    QString SinglePlacementData;
    QString ReplicaData;

    QString AssembleLVData;
    QString AssembleComponentData;
    QString AssemblePVData;

    // rotation matrix 旋转矩阵

    // method 1&2
    QString RotMatrix1Data;
    QString RotMatrix2Data;

    // other tags 其他属性设置
    QString VISFlag;
    QString COLORData;
    QString CheckOverlapFlag;

    //about
//    About *aboutwin;
//    Help *helpwin;

};
#endif // MAINWINDOW_H
