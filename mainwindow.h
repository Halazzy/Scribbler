#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QTime>
#include <QtCore/QTextStream>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QErrorMessage>
#include <QtWidgets/QLabel>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtGui/QWheelEvent>

#include "preferencesdialog.h"
#include "fontdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    enum ToolButton : int {
        Render,
        Print,
        Save,
        Separator,
        Previous,
        SheetNumber,
        Next
    };

    Ui::MainWindow *ui;
    PreferencesDialog *preferencesDialog;
    FontDialog *fontDialog;
    QErrorMessage *errorMessage;
    QLabel *sheetNumberLabel;
    QVector<int> sheetPointers; //pointers to the beginning of the sheets
    int currentSheetNumber;     //number of sheet that is displaying or rendering now
    const QString version = "0.7 beta";
    void saveAllSheetsToImages(const QString &fileName, const int indexOfExtension);
    void saveAllSheetsToPDF(const QString &fileName);
    void preparePrinter(QPrinter *printer);
    QString simplifyEnd(const QString &str);

protected:
      bool eventFilter(QObject *obj, QEvent *ev);

private slots:
    void showAboutBox();
    void showLicensesBox();
    void showHowToBox();
    void renderFirstSheet();
    void renderNextSheet();
    void renderPreviousSheet();
    void loadFont();
    void saveSheet(QString fileName = QString());
    void saveAllSheets();
    void printSheet();
    void printAllSheets(QPrinter *printer = new QPrinter(QPrinter::HighResolution));
    void loadTextFromFile();
    void loadSettings();
    void countMissedCharacters();
    void showSheetNumber(int number);
};

#endif // MAINWINDOW_H
