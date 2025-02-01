#include "settingsdialog.h"
#include <QSpacerItem>
#include <QFrame>

#include "QVBoxLayout"

SettingsDialog::SettingsDialog()
{
    setWindowTitle(tr("Настройки"));

    QVBoxLayout* mainLayout = new QVBoxLayout();

    tabWidget = new QTabWidget();

    okButton = new QPushButton(tr("ОК"));
    cancelButton = new QPushButton(tr("Отмена"));

    QSpacerItem *spacer0 = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout* mainButtonLayout = new QHBoxLayout();
    mainButtonLayout->addItem(spacer0);
    mainButtonLayout->addWidget(okButton);
    mainButtonLayout->addWidget(cancelButton);

    mainLayout->addWidget(tabWidget);
    mainLayout->addLayout(mainButtonLayout);

    QSize buttonSize = QSize(30, 30);

    QVBoxLayout* firstLayout = new QVBoxLayout();

    QLabel *browseLabel = new QLabel(tr("Папка по умолчанию"));
    firstLayout->addWidget(browseLabel);

    m_browseLineEdit = new QLineEdit();
    m_browseButton = new QPushButton(QIcon(tr("://res/Change.svg")), "");

    QHBoxLayout* browseLayout = new QHBoxLayout();

    browseLayout->addWidget(m_browseLineEdit);
    browseLayout->addWidget(m_browseButton);
    firstLayout->addLayout(browseLayout);

    m_db5CheckBox = new QCheckBox(tr("Формировать пакет обновлений db5update"));
    m_db5CheckBox->setChecked(true);
    firstLayout->addWidget(m_db5CheckBox);

    m_addButton = new QPushButton(QIcon(tr("://res/Add.svg")), tr(""));
    m_addButton->setIconSize(buttonSize);
    m_removeButton = new QPushButton(QIcon(tr("://res/Remove.svg")), tr(""));
    m_removeButton->setIconSize(buttonSize);
    m_getButton = new QPushButton(tr("Определить серийный номер"));
    m_getButton->resize(buttonSize.height(), 400);
    m_getButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    QSpacerItem *spacer = new QSpacerItem(buttonSize.width(), buttonSize.height(), QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(m_addButton);
    buttonsLayout->addWidget(m_removeButton);
    buttonsLayout->addItem(spacer);
    buttonsLayout->addWidget(m_getButton);

    m_numbersTableView = new QTableView();

    QFrame *numbersFrame = new QFrame();
//    numbersFrame->setLineWidth(1);
    numbersFrame->setFrameStyle(QFrame::StyledPanel);
//    numbersFrame->set

//    QLabel *numbersLabel = new QLabel(tr("Серийные номера"));

    QVBoxLayout *numbersLayout = new QVBoxLayout();
//    numbersLayout->addWidget(numbersLabel);
    numbersLayout->addLayout(buttonsLayout);
    numbersLayout->addWidget(m_numbersTableView);
    numbersFrame->setLayout(numbersLayout);

    firstLayout->addWidget(numbersFrame);

    QDialog *dialog = new QDialog();
    dialog->setLayout(firstLayout);

    tabWidget->addTab(dialog, tr("Серийные номера и загрузка"));

    proxyCheckBox = new QCheckBox();
    systemProxyCheckBox;
    importButton;
    coonectionCheckButton;

    adressLineEdit;
    usernameLineEdit;
    passwordLineEdit;
    portLineEdit;

    setLayout(mainLayout);
}

SettingsDialog::~SettingsDialog()
{

}
