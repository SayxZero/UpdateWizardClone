#include <QSizePolicy>
#include <QSpacerItem>

#include "treemodel.h"
#include "mainwindow.h"
#include "settingsdialog.h"



MainWindow::MainWindow(QWidget *parent)
    : RibbonMainWindow(parent)
    , m_panel_1(Q_NULL)
    , m_panel_2(Q_NULL)
{
    const QRect availableGeometry = screen()->availableGeometry();
    resize(availableGeometry.width() / 4 * 3, availableGeometry.height() / 4 * 3);
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    setMinimumHeight(availableGeometry.height() / 3);
    setMinimumWidth(availableGeometry.width() / 5);

    m_panelAction1 = new QAction(QIcon(tr("://res/TaskList.svg")), tr("Список задач"));
    m_panelAction1->setCheckable(true);
    m_panelAction1->setChecked(true);

    m_panelAction2 = new QAction(QIcon(tr("://res/Log.svg")), tr("Протокол работы"));
    m_panelAction2->setCheckable(true);
    m_panelAction2->setChecked(true);

    m_ribbonBar = new RibbonBar(this);
    m_ribbonBar->addPage(QStringLiteral("Главная"));
    m_ribbonBar->page(0)->addGroup(tr("Данные"));
    m_ribbonBar->page(0)->group(0)->addAction(QIcon(tr(":/res/Update.svg")), tr("Обновить информацию"));
    m_ribbonBar->page(0)->group(0)->addAction(QIcon(tr("://res/FileDownloading.svg")), tr("Скачать"));
    m_ribbonBar->page(0)->addGroup(tr("Настройки"));
    m_ribbonBar->page(0)->group(1)->addAction(QIcon(tr("://res/Settings.svg")), tr("Настройки"));
    m_ribbonBar->page(0)->addGroup(tr("Вид"));
    m_ribbonBar->page(0)->group(2)->addAction(m_panelAction1);
    m_ribbonBar->page(0)->group(2)->addAction(m_panelAction2);
    m_ribbonBar->setFont(QFont("Calibri", 9));
    setRibbonBar(m_ribbonBar);

    connect(m_ribbonBar->page(0)->group(1)->actions().at(0), SIGNAL(triggered()), this, SLOT(on_setingsButtonClicked()));
    connect(m_panelAction1, SIGNAL(triggered()), this, SLOT(on_taskListButtonClicked()));
    connect(m_panelAction2, SIGNAL(triggered()), this, SLOT(on_logButtonClicked()));

    const QStringList headers1({ tr("Название базы"), tr("Регион"), tr("Дата обновления"), tr("Размер") });
    QFile file1("://res/primerDB.txt");
    file1.open(QIODevice::ReadOnly);
    TreeModel* model1 = new TreeModel(headers1, file1.readAll());
    file1.close();

    const QStringList headers2({ tr("Наименование"), tr("Описание"), tr("Размер"), tr("Серийный номер"), tr("Организация") });
    QFile file2("://res/primerProgram.txt");
    file2.open(QIODevice::ReadOnly);
    TreeModel* model2 = new TreeModel(headers2, file2.readAll());
    file2.close();

    m_tabWidget = new QTabWidget();

    m_treeGrid1 = new Qtitan::TreeGrid();
    m_treeGrid1->setViewType(Qtitan::TreeGrid::TreeView);
    Qtitan::GridTreeView* treeview1 = m_treeGrid1->view<Qtitan::GridTreeView>();
    treeview1->beginUpdate();
    treeview1->options().setGestureEnabled(true);
    treeview1->options().setShowFocusDecoration(true);
    treeview1->setModel(model1);
    treeview1->endUpdate();
    treeview1->bestFit(Qtitan::FitToHeaderAndContent);
    treeview1->expandToLevel(3);
    m_tabWidget->addTab(m_treeGrid1, QIcon(tr("://res/DB.svg")), tr("Базы данных"));

    m_treeGrid2 = new Qtitan::TreeGrid();
    m_treeGrid2->setViewType(Qtitan::TreeGrid::TreeView);
    Qtitan::GridTreeView* treeview2 = m_treeGrid2->view<Qtitan::GridTreeView>();
    treeview2->beginUpdate();
    treeview2->options().setGestureEnabled(true);
    treeview2->options().setShowFocusDecoration(true);
    treeview2->setModel(model2);
    treeview2->endUpdate();
    treeview2->bestFit(Qtitan::FitToHeaderAndContent);
    treeview2->expandToLevel(3);
    m_tabWidget->addTab(m_treeGrid2, QIcon(tr("://res/Program.svg")), tr("Программные продукты"));

    m_grid1 = new Qtitan::Grid();
    m_grid1->setViewType(Qtitan::Grid::TableView);
    Qtitan::GridTableView* tableview1 = m_grid1->view<Qtitan::GridTableView>();
    tableview1->options().setCellButtonAutoRaise(true);

    m_grid2 = new Qtitan::Grid();
    m_grid2->setViewType(Qtitan::Grid::TableView);
    Qtitan::GridTableView* tableview2 = m_grid2->view<Qtitan::GridTableView>();
    tableview2->options().setCellButtonAutoRaise(true);

    setCentralWidget(m_tabWidget);
    m_manager = new DockPanelManager(this);
    m_panel_1 = m_manager->addDockPanel("Список задач", Qtitan::BottomDockPanelArea);
    m_panel_1->setIcon(QIcon(tr("://res/TaskList.svg")));
//    m_panel_1->resize(m_panel_1->width(), height() / 2);
//    m_panel_1->setMinimumHeight(m_panel_1->height() / 5);
    m_gridDlg = new GridDialog(m_grid1);
    m_panel_1->setObjectName("_qtn_widget_panel_id_1");
    m_panel_1->setWidget(m_gridDlg);
    m_panel_2 = m_manager->addDockPanel("Протокол работы", Qtitan::InsideDockPanelArea, m_panel_1);
    m_panel_2->setObjectName("_qtn_widget_panel_id_2");
    m_panel_2->setIcon(QIcon(tr("://res/Log.svg")));
//    m_panel_2->setMinimumHeight(m_panel_1->height() / 5);
    m_panel_2->setWidget(m_grid2);

    connect(m_manager, SIGNAL(aboutToClose(DockPanelBase*, bool&)), this, SLOT(aboutToClosePanel(DockPanelBase*, bool&)));
    connect(m_manager, SIGNAL(aboutToShow(DockPanelBase*, bool&)), this, SLOT(aboutToShowPanel(DockPanelBase*, bool&)));


    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_setingsButtonClicked()
{
    SettingsDialog* dlg = new SettingsDialog();
    dlg->setModal(true);
    dlg->exec();
}

void MainWindow::on_taskListButtonClicked()
{
    if (!m_isPanelClosed1)
    {
        m_panel_1->closePanel();
    }
    else
    {
        m_manager->showDockPanel(m_panel_1);
        m_isPanelClosed1 = false;
    }
}

void MainWindow::on_logButtonClicked()
{
    if (!m_isPanelClosed2)
    {
        m_panel_2->closePanel();
    }
    else
    {
        m_manager->showDockPanel(m_panel_2);
    }
}

void MainWindow::aboutToClosePanel(DockPanelBase *panel, bool &handled)
{
    if (panel == m_panel_1)
    {
        m_panelAction1->setChecked(false);
        m_isPanelClosed1 = true;
    }
    else if (panel == m_panel_2)
    {
        m_panelAction2->setChecked(false);
        m_isPanelClosed2 = true;
    }
    handled = true;
}

void MainWindow::aboutToShowPanel(DockPanelBase *panel, bool &handled)
{
    if (panel == m_panel_1)
    {
        m_panelAction1->setChecked(true);
        m_isPanelClosed1 = false;
        m_gridDlg->show();
    }
    else if (panel == m_panel_2)
    {
        m_panelAction2->setChecked(true);
        m_isPanelClosed2 = false;
    }
    handled = true;
}

GridDialog::GridDialog(Grid *grid) {
    QSize buttonSize = QSize(30, 30);
    m_stopButton = new QPushButton(QIcon(tr("://res/Stop.svg")), "");
    m_stopButton->setEnabled(false);
    m_stopButton->setIconSize(buttonSize);
    m_removeButton = new QPushButton(QIcon(tr("://res/Remove.svg")), "");
    m_removeButton->setEnabled(false);
    m_removeButton->setIconSize(buttonSize);
    m_changeButton = new QPushButton(QIcon(tr("://res/Program.svg")), "");
    m_changeButton->setEnabled(false);
    m_changeButton->setIconSize(buttonSize);
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    vlayout->addLayout(hlayout);
    vlayout->addWidget(grid);
    QSpacerItem *spacer = new QSpacerItem(buttonSize.width(), buttonSize.height(), QSizePolicy::Expanding, QSizePolicy::Minimum);
    hlayout->addWidget(m_stopButton);
    hlayout->addWidget(m_removeButton);
    hlayout->addWidget(m_changeButton);
    hlayout->addItem(spacer);
}
