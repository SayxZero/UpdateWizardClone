#include "settingsdialog.h"
#include <QSpacerItem>
#include <QFrame>


#include "QVBoxLayout"

SettingsDialog::SettingsDialog()
{
    resize(650, 450);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

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
    numbersFrame->setFrameStyle(QFrame::StyledPanel);

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

    QVBoxLayout* secondLayout = new QVBoxLayout();

    QSpacerItem *importSpacer = new QSpacerItem(buttonSize.width(), buttonSize.height(), QSizePolicy::Expanding, QSizePolicy::Minimum);
    importButton = new QPushButton(tr("Импорт системных настроек"));
    importButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    importButton->resize(10, 200);
    QHBoxLayout* importLayout = new QHBoxLayout();
    importLayout->addItem(importSpacer);
    importLayout->addWidget(importButton);
    secondLayout->addLayout(importLayout);

    QVBoxLayout* checkboxLayout = new QVBoxLayout();
    QVBoxLayout* coonectionCheckLayout = new QVBoxLayout();
    QHBoxLayout* checkLayout = new QHBoxLayout();
    QSpacerItem *coonectionCheckSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *checkboxSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

    proxyCheckBox = new QCheckBox(tr("Использовать прокси-сервер"));
    systemProxyCheckBox = new QCheckBox(tr("Использовать системные настройки прокси-сервера"));
    coonectionCheckButton = new QPushButton(tr("Проверка соединения"));
    coonectionCheckButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    coonectionCheckButton->resize(10, 200);

    checkboxLayout->addItem(checkboxSpacer);
    checkboxLayout->addWidget(proxyCheckBox);
    checkboxLayout->addWidget(systemProxyCheckBox);
    coonectionCheckLayout->addWidget(coonectionCheckButton);
    coonectionCheckLayout->addItem(coonectionCheckSpacer);

    checkLayout->addLayout(checkboxLayout);
    checkLayout->addLayout(coonectionCheckLayout);
    secondLayout->addLayout(checkLayout);

    QFrame *proxyFrame = new QFrame();
    proxyFrame->setFrameStyle(QFrame::StyledPanel);
    secondLayout->addWidget(proxyFrame);

    adressLineEdit = new QLineEdit();
    usernameLineEdit = new QLineEdit();
    passwordLineEdit = new QLineEdit();
    portLineEdit = new QLineEdit();

    QLabel *adressLabel = new QLabel(tr("Адрес сервера:"));
    QLabel *usernameLabel = new QLabel(tr("Имя пользователя:"));
    QLabel *passwordLabel = new QLabel(tr("Пароль:"));
    QLabel *portLabel = new QLabel(tr("Порт:"));

    QSpacerItem *adressSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *usernameSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *passwordSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *portSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *pwAndUnSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Fixed);
    QSpacerItem *portUnderSpacer = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem *proxyUnderSpacer = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);
    QSpacerItem *proxyUpperSpacer = new QSpacerItem(10, 10, QSizePolicy::Fixed, QSizePolicy::Expanding);


    QHBoxLayout* adressLayout = new QHBoxLayout();
    adressLayout->addItem(adressSpacer);
    adressLayout->addWidget(adressLabel);
    QHBoxLayout* usernameLayout = new QHBoxLayout();
    usernameLayout->addItem(usernameSpacer);
    usernameLayout->addWidget(usernameLabel);
    QHBoxLayout* passwordLayout = new QHBoxLayout();
    passwordLayout->addItem(passwordSpacer);
    passwordLayout->addWidget(passwordLabel);
    QHBoxLayout* portLayout = new QHBoxLayout();
    portLayout->addItem(portSpacer);
    portLayout->addWidget(portLabel);

    QVBoxLayout* proxyLayout0 = new QVBoxLayout();
    proxyLayout0->addLayout(adressLayout);
    proxyLayout0->addLayout(usernameLayout);
    proxyLayout0->addLayout(passwordLayout);

    QVBoxLayout* proxyLayout1 = new QVBoxLayout();
    proxyLayout1->addWidget(usernameLineEdit);
    proxyLayout1->addWidget(passwordLineEdit);

    QHBoxLayout* proxyLayout2 = new QHBoxLayout();
    proxyLayout2->addLayout(proxyLayout1);
    proxyLayout2->addItem(pwAndUnSpacer);

    QVBoxLayout* proxyLayout3 = new QVBoxLayout();
    proxyLayout3->addWidget(adressLineEdit);
    proxyLayout3->addLayout(proxyLayout2);

    QHBoxLayout* proxyLayout4 = new QHBoxLayout();
    proxyLayout4->addLayout(portLayout);
    proxyLayout4->addWidget(portLineEdit);

    QVBoxLayout* proxyLayout5 = new QVBoxLayout();
    proxyLayout5->addLayout(proxyLayout4);
    proxyLayout5->addItem(portUnderSpacer);

    QHBoxLayout* mainProxyLayout = new QHBoxLayout();
    mainProxyLayout->addLayout(proxyLayout0);
    mainProxyLayout->addLayout(proxyLayout3);
    mainProxyLayout->addLayout(proxyLayout5);

    QVBoxLayout* mainFrameLayout = new QVBoxLayout();
    mainFrameLayout->addItem(proxyUpperSpacer);
    mainFrameLayout->addLayout(mainProxyLayout);
    mainFrameLayout->addItem(proxyUnderSpacer);

    proxyFrame->setLayout(mainFrameLayout);

    QSpacerItem *mainUnderSpacer = new QSpacerItem(10, 1000, QSizePolicy::Fixed, QSizePolicy::Maximum);
    secondLayout->addItem(mainUnderSpacer);

    dialog = new QDialog();
    dialog->setLayout(secondLayout);

    tabWidget->addTab(dialog, tr("Настройки подключения"));

    setLayout(mainLayout);
}

SettingsDialog::~SettingsDialog()
{

}
