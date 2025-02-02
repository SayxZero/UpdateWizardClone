#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DevMachines/QtitanRibbon>
#include <DevMachines/QtitanDocking>
#include <DevMachines/QtitanGrid>
#include <QPushButton>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QWindow>

#include <QMainWindow>
#include <QFile>

class GridDialog : public QDialog
{
public:
    GridDialog(Grid *grid);
    QPushButton* m_stopButton;
    QPushButton* m_removeButton;
    QPushButton* m_changeButton;
};

class MainWindow : public RibbonMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    DockPanelManager* m_manager;
    RibbonBar* m_ribbonBar;
    DockWidgetPanel* m_panel_1;
    DockWidgetPanel* m_panel_2;
    QPushButton* m_button;
    QTabWidget* m_tabWidget;
    Qtitan::TreeGrid* m_treeGrid1;
    Qtitan::TreeGrid* m_treeGrid2;
    Qtitan::Grid* m_grid1;
    Qtitan::Grid* m_grid2;
    GridDialog* m_gridDlg;

    QAction *m_panelAction1;
    QAction *m_panelAction2;

    bool m_isPanelClosed1 = false;
    bool m_isPanelClosed2 = false;

public slots:

    void on_setingsButtonClicked();
    void on_taskListButtonClicked();
    void on_logButtonClicked();

    void aboutToClosePanel(DockPanelBase* panel, bool& handled);
    void aboutToShowPanel(DockPanelBase* panel, bool& handled);

};
#endif // MAINWINDOW_H
