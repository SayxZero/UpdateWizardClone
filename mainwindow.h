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


};
#endif // MAINWINDOW_H
