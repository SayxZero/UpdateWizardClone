#include <QSizePolicy>
#include <QSpacerItem>
#include <QMessageBox>

#include "treemodel.h"
#include "mainwindow.h"
#include "settingsdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : RibbonMainWindow(parent)
    , m_taskListPanel(Q_NULL)
    , m_workProtocolPanel(Q_NULL)
{
    const QRect availableGeometry = screen()->availableGeometry();
    resize(availableGeometry.width() / 4 * 3, availableGeometry.height() / 4 * 3);
    move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
    setMinimumHeight(availableGeometry.height() / 3);
    setMinimumWidth(availableGeometry.width() / 5);

    m_taskListPanelAction = new QAction(QIcon(tr("://res/TaskList.svg")), tr("Список задач"));
    m_taskListPanelAction->setCheckable(true);
    m_taskListPanelAction->setChecked(true);

    m_workProtocolPanelAction = new QAction(QIcon(tr("://res/Log.svg")), tr("Протокол работы"));
    m_workProtocolPanelAction->setCheckable(true);
    m_workProtocolPanelAction->setChecked(true);

    m_mainMenuBar = new RibbonBar(this);
    m_mainMenuBar->addPage(QStringLiteral("Главная"));
    m_mainMenuBar->page(0)->addGroup(tr("Данные"));
    m_mainMenuBar->page(0)->group(0)->addAction(QIcon(tr(":/res/Update.svg")), tr("Обновить информацию"));
    m_mainMenuBar->page(0)->group(0)->addAction(QIcon(tr("://res/FileDownloading.svg")), tr("Скачать"));
    m_mainMenuBar->page(0)->addGroup(tr("Настройки"));
    m_mainMenuBar->page(0)->group(1)->addAction(QIcon(tr("://res/Settings.svg")), tr("Настройки"));
    m_mainMenuBar->page(0)->addGroup(tr("Вид"));
    m_mainMenuBar->page(0)->group(2)->addAction(m_taskListPanelAction);
    m_mainMenuBar->page(0)->group(2)->addAction(m_workProtocolPanelAction);
    m_mainMenuBar->setFont(QFont("Calibri", 9));
    setRibbonBar(m_mainMenuBar);

    connect(m_mainMenuBar->page(0)->group(0)->actions().at(0), SIGNAL(triggered()), this, SLOT(on_updateButtonClicked()));
    connect(m_mainMenuBar->page(0)->group(0)->actions().at(1), SIGNAL(triggered()), this, SLOT(on_downloadButtonClicked()));
    connect(m_mainMenuBar->page(0)->group(1)->actions().at(0), SIGNAL(triggered()), this, SLOT(on_setingsButtonClicked()));
    connect(m_taskListPanelAction, SIGNAL(triggered()), this, SLOT(on_taskListButtonClicked()));
    connect(m_workProtocolPanelAction, SIGNAL(triggered()), this, SLOT(on_logButtonClicked()));

    const QStringList headers1({ tr("Название базы"), tr("Регион"), tr("Дата обновления"), tr("Размер") });
    QFile file1("://res/primerDB.txt");
    file1.open(QIODevice::ReadOnly);
    TreeModel* databaseTreeGridModel = new TreeModel(headers1, file1.readAll());
    file1.close();

    const QStringList headers2({ tr("Наименование"), tr("Описание"), tr("Размер"), tr("Серийный номер"), tr("Организация") });
    QFile file2("://res/primerProgram.txt");
    file2.open(QIODevice::ReadOnly);
    TreeModel* productTreeGridModel = new TreeModel(headers2, file2.readAll());
    file2.close();

    m_mainWorkspaceTabWidget = new QTabWidget();

    m_databaseTreeGrid = new Qtitan::TreeGrid();
    m_databaseTreeGrid->setViewType(Qtitan::TreeGrid::TreeView);
    Qtitan::GridTreeView* databaseTreeGridView = m_databaseTreeGrid->view<Qtitan::GridTreeView>();
    databaseTreeGridView->beginUpdate();
    databaseTreeGridView->options().setGestureEnabled(true);
    databaseTreeGridView->options().setShowFocusDecoration(true);
    databaseTreeGridView->setModel(databaseTreeGridModel);
    databaseTreeGridView->endUpdate();
    databaseTreeGridView->bestFit(Qtitan::FitToHeaderAndContent);
    databaseTreeGridView->expandToLevel(3);
    m_mainWorkspaceTabWidget->addTab(m_databaseTreeGrid, QIcon(tr("://res/DB.svg")), tr("Базы данных"));

    m_productTreeGrid = new Qtitan::TreeGrid();
    m_productTreeGrid->setViewType(Qtitan::TreeGrid::TreeView);
    Qtitan::GridTreeView* productTreeGridView = m_productTreeGrid->view<Qtitan::GridTreeView>();
    productTreeGridView->beginUpdate();
    productTreeGridView->options().setGestureEnabled(true);
    productTreeGridView->options().setShowFocusDecoration(true);
    productTreeGridView->setModel(productTreeGridModel);
    productTreeGridView->endUpdate();
    productTreeGridView->bestFit(Qtitan::FitToHeaderAndContent);
    productTreeGridView->expandToLevel(3);
    m_mainWorkspaceTabWidget->addTab(m_productTreeGrid, QIcon(tr("://res/Program.svg")), tr("Программные продукты"));

    m_taskListGrid = new Qtitan::Grid();
    m_taskListGrid->setViewType(Qtitan::Grid::TableView);
    Qtitan::GridTableView* taskListGridTableView = m_taskListGrid->view<Qtitan::GridTableView>();
    taskListGridTableView->options().setCellButtonAutoRaise(true);

    m_workProtocolGrid = new Qtitan::Grid();
    m_workProtocolGrid->setViewType(Qtitan::Grid::TableView);
    Qtitan::GridTableView* workProtocolTableView2 = m_workProtocolGrid->view<Qtitan::GridTableView>();
    workProtocolTableView2->options().setCellButtonAutoRaise(true);

    setCentralWidget(m_mainWorkspaceTabWidget);
    m_manager = new DockPanelManager(this);
    m_taskListPanel = m_manager->addDockPanel("Список задач", Qtitan::BottomDockPanelArea);
    m_taskListPanel->setIcon(QIcon(tr("://res/TaskList.svg")));
    m_taskListContainerDialog = new GridDialog(m_taskListGrid);
    m_taskListPanel->setObjectName("_qtn_widget_panel_id_1");
    m_taskListPanel->setWidget(m_taskListContainerDialog);
    m_workProtocolPanel = m_manager->addDockPanel("Протокол работы", Qtitan::InsideDockPanelArea, m_taskListPanel);
    m_workProtocolPanel->setObjectName("_qtn_widget_panel_id_2");
    m_workProtocolPanel->setIcon(QIcon(tr("://res/Log.svg")));
    m_workProtocolPanel->setWidget(m_workProtocolGrid);

    connect(m_manager, SIGNAL(aboutToClose(DockPanelBase*, bool&)), this, SLOT(aboutToClosePanel(DockPanelBase*, bool&)));
    connect(m_manager, SIGNAL(aboutToShow(DockPanelBase*, bool&)), this, SLOT(aboutToShowPanel(DockPanelBase*, bool&)));

    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
}

void MainWindow::showMessageNotRealised()
{
    QMessageBox notRealisedMessageBox(QMessageBox::Information, windowTitle(), QStringLiteral("Warning"), QMessageBox::Ok, this);
    notRealisedMessageBox.setInformativeText(QStringLiteral("Не реализовано"));
    notRealisedMessageBox.exec();
}

void MainWindow::on_updateButtonClicked()
{
    showMessageNotRealised();
}

void MainWindow::on_downloadButtonClicked()
{
    showMessageNotRealised();
}

void MainWindow::on_setingsButtonClicked()
{
    SettingsDialog* settingsDialog = new SettingsDialog();
    settingsDialog->setModal(true);
    settingsDialog->exec();
    delete settingsDialog;
}

void MainWindow::on_taskListButtonClicked()
{
    if (!m_isTaskListPanelClosed)
    {
        m_taskListPanel->closePanel();
    }
    else
    {
        m_manager->showDockPanel(m_taskListPanel);
        m_isTaskListPanelClosed = false;
    }
}

void MainWindow::on_logButtonClicked()
{
    if (!m_isWorkProtocolPanelClosed)
    {
        m_workProtocolPanel->closePanel();
    }
    else
    {
        m_manager->showDockPanel(m_workProtocolPanel);
    }
}

void MainWindow::aboutToClosePanel(DockPanelBase *panel, bool &handled)
{
    if (panel == m_taskListPanel)
    {
        m_taskListPanelAction->setChecked(false);
        m_isTaskListPanelClosed = true;
    }
    else if (panel == m_workProtocolPanel)
    {
        m_workProtocolPanelAction->setChecked(false);
        m_isWorkProtocolPanelClosed = true;
    }
    handled = true;
}

void MainWindow::aboutToShowPanel(DockPanelBase *panel, bool &handled)
{
    if (panel == m_taskListPanel)
    {
        m_taskListPanelAction->setChecked(true);
        m_isTaskListPanelClosed = false;
        m_taskListContainerDialog->show();
    }
    else if (panel == m_workProtocolPanel)
    {
        m_workProtocolPanelAction->setChecked(true);
        m_isWorkProtocolPanelClosed = false;
    }
    handled = true;
}

GridDialog::GridDialog(Grid *grid)
{
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
