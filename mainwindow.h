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
    RibbonBar* m_mainMenuBar;
    DockWidgetPanel* m_taskListPanel;
    DockWidgetPanel* m_workProtocolPanel;
    QTabWidget* m_mainWorkspaceTabWidget;
    Qtitan::TreeGrid* m_databaseTreeGrid;
    Qtitan::TreeGrid* m_productTreeGrid;
    Qtitan::Grid* m_taskListGrid;
    Qtitan::Grid* m_workProtocolGrid;
    GridDialog* m_taskListContainerDialog;

    QAction *m_taskListPanelAction;
    QAction *m_workProtocolPanelAction;

    bool m_isTaskListPanelClosed = false;
    bool m_isWorkProtocolPanelClosed = false;

    void showMessageNotRealised();

public slots:

    void on_updateButtonClicked();
    void on_downloadButtonClicked();
    void on_setingsButtonClicked();
    void on_taskListButtonClicked();
    void on_logButtonClicked();

    void aboutToClosePanel(DockPanelBase* panel, bool& handled);
    void aboutToShowPanel(DockPanelBase* panel, bool& handled);

};
#endif // MAINWINDOW_H
