# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '/home/hubery-lee/SWNS-Scoring-v2.0/code_gui/gui/about.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_About(object):
    def setupUi(self, About):
        About.setObjectName("About")
        About.resize(882, 526)
        About.setStyleSheet("#About\n"
"{\n"
"border-image: url(:/images/about_bg.png);\n"
"}")
        self.gridLayout = QtWidgets.QGridLayout(About)
        self.gridLayout.setObjectName("gridLayout")
        self.textBrowser = QtWidgets.QTextBrowser(About)
        self.textBrowser.setObjectName("textBrowser")
        self.gridLayout.addWidget(self.textBrowser, 0, 0, 1, 1)

        self.retranslateUi(About)
        QtCore.QMetaObject.connectSlotsByName(About)

    def retranslateUi(self, About):
        _translate = QtCore.QCoreApplication.translate
        About.setWindowTitle(_translate("About", "Form"))
        self.textBrowser.setHtml(_translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'SimSun\'; font-size:11.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt;\">关于SWNS</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">    </span><span style=\" font-size:12pt;\">SWNS是一款用于工作现场中子谱蒙特卡罗模拟软件。此部分为SWNS软件的建模输入卡编写工具包，主要包括实验材料定义、几何构建与布置及探测器设置与数据输出等相关功能。</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">    </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">    SWNS软件由中国辐射防护研究院核与辐射前沿技术研究中心核探测与成像研究室所开发，使用过程中如遇任何问题，可通过</span><a href=\"hrbeulh@126.com\"><span style=\" font-size:12pt; text-decoration: underline; color:#0000ff;\">hrbeulh@126.com</span></a><span style=\" font-size:12pt;\">联系开发人员。此软件的获取途径除邮件联系外还有两种，1）通过微信</span><a href=\"HuberyLeeNB\"><span style=\" font-size:12pt; text-decoration: underline; color:#0000ff;\">HuberyLeeNB</span></a><span style=\" font-size:12pt;\">联系作者；2）通过</span><a href=\"https://github.com/Hubery-Lee/SWNS\"><span style=\" font-size:12pt; text-decoration: underline; color:#0000ff;\">https://github.com/Hubery-Lee/SWNS </span></a><a href=\"https://github.com/Hubery-Lee/SWNS\"><span style=\" font-size:12pt; text-decoration: underline; color:#000000;\">下载软件</span></a></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; text-decoration: underline; color:#000000;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/scanCode.png\" /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt; text-decoration: underline; color:#000000;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt; color:#000000;\"><br /></p></body></html>"))

