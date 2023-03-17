/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(882, 526);
        About->setStyleSheet(QString::fromUtf8("#About\n"
"{\n"
"border-image: url(:/images/about_bg.png);\n"
"}"));
        verticalLayout = new QVBoxLayout(About);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(About);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QFont font;
        font.setPointSize(8);
        textBrowser->setFont(font);

        verticalLayout->addWidget(textBrowser);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QWidget *About)
    {
        About->setWindowTitle(QApplication::translate("About", "Form", nullptr));
        textBrowser->setHtml(QApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:18pt;\">\345\205\263\344\272\216SWNS</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-si"
                        "ze:9pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt;\">    </span><span style=\" font-family:'SimSun'; font-size:12pt;\">SWNS\346\230\257\344\270\200\346\254\276\347\224\250\344\272\216\345\267\245\344\275\234\347\216\260\345\234\272\344\270\255\345\255\220\350\260\261\350\222\231\347\211\271\345\215\241\347\275\227\346\250\241\346\213\237\350\275\257\344\273\266\343\200\202\346\255\244\351\203\250\345\210\206\344\270\272SWNS\350\275\257\344\273\266\347\232\204\345\273\272\346\250\241\350\276\223\345\205\245\345\215\241\347\274\226\345\206\231\345\267\245\345\205\267\345\214\205\357\274\214\344\270\273\350\246\201\345\214\205\346\213\254\345\256\236\351\252\214\346\235\220\346\226\231\345\256\232\344\271\211\343\200\201\345\207\240\344\275\225\346\236\204\345\273\272\344\270\216\345\270\203\347\275\256\345\217\212\346\216\242\346\265\213\345\231\250\350\256\276\347\275"
                        "\256\344\270\216\346\225\260\346\215\256\350\276\223\345\207\272\347\255\211\347\233\270\345\205\263\345\212\237\350\203\275\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">    </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:12pt;\">    SWNS\350\275\257\344\273\266\347\224\261\344\270\255\345\233\275\350\276\220\345\260\204\351\230\262\346\212\244\347\240\224\347\251\266\351\231\242\346\240\270\344\270\216\350\276\220\345\260\204\345\211\215\346\262\277\346\212\200\346\234\257\347\240\224\347\251\266\344\270\255\345\277\203\346\240\270\346\216\242\346\265\213\344\270\216\346\210\220\345\203\217\347\240\224\347\251\266\345\256\244\346\211\200\345\274\200\345\217\221\357\274\214\344\275\277\347\224\250\350\277\207\347\250\213\344"
                        "\270\255\345\246\202\351\201\207\344\273\273\344\275\225\351\227\256\351\242\230\357\274\214\345\217\257\351\200\232\350\277\207</span><a href=\"hrbeulh@126.com\"><span style=\" font-family:'SimSun'; font-size:12pt; text-decoration: underline; color:#0000ff;\">hrbeulh@126.com</span></a><span style=\" font-family:'SimSun'; font-size:12pt;\">\350\201\224\347\263\273\345\274\200\345\217\221\344\272\272\345\221\230\343\200\202\346\255\244\350\275\257\344\273\266\347\232\204\350\216\267\345\217\226\351\200\224\345\276\204\351\231\244\351\202\256\344\273\266\350\201\224\347\263\273\345\244\226\350\277\230\346\234\211\344\270\244\347\247\215\357\274\2141\357\274\211\351\200\232\350\277\207\345\276\256\344\277\241</span><a href=\"HuberyLeeNB\"><span style=\" font-family:'SimSun'; font-size:12pt; text-decoration: underline; color:#0000ff;\">HuberyLeeNB</span></a><span style=\" font-family:'SimSun'; font-size:12pt;\">\350\201\224\347\263\273\344\275\234\350\200\205\357\274\2332\357\274\211\351\200\232\350\277\207</span>"
                        "<a href=\"https://github.com/Hubery-Lee/SWNS\"><span style=\" font-family:'SimSun'; font-size:12pt; text-decoration: underline; color:#0000ff;\">https://github.com/Hubery-Lee/SWNS </span></a><a href=\"https://github.com/Hubery-Lee/SWNS\"><span style=\" font-family:'SimSun'; font-size:12pt; text-decoration: underline; color:#000000;\">\344\270\213\350\275\275\350\275\257\344\273\266</span></a></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:12pt; text-decoration: underline; color:#000000;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/scanCode.png\" /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt; text-decoratio"
                        "n: underline; color:#000000;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt; color:#000000;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
