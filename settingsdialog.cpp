#include "settingsdialog.h"
#include <QSpacerItem>
#include <QFrame>
#include <QMessageBox>

#include "QVBoxLayout"

SettingsDialog::SettingsDialog()
{
    resize(650, 450);
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);

    setWindowTitle(tr("Настройки"));

    QVBoxLayout* mainLayout = new QVBoxLayout();

    m_tabWidget = new QTabWidget();

    m_okButton = new QPushButton(tr("ОК"));
    m_cancelButton = new QPushButton(tr("Отмена"));

    QSpacerItem *spacer0 = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

    QHBoxLayout* mainButtonLayout = new QHBoxLayout();
    mainButtonLayout->addItem(spacer0);
    mainButtonLayout->addWidget(m_okButton);
    mainButtonLayout->addWidget(m_cancelButton);

    mainLayout->addWidget(m_tabWidget);
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

    QVBoxLayout *numbersLayout = new QVBoxLayout();
    numbersLayout->addLayout(buttonsLayout);
    numbersLayout->addWidget(m_numbersTableView);
    numbersFrame->setLayout(numbersLayout);

    firstLayout->addWidget(numbersFrame);

    QDialog *dialog = new QDialog();
    dialog->setLayout(firstLayout);

    m_tabWidget->addTab(dialog, tr("Серийные номера и загрузка"));

    QVBoxLayout* secondLayout = new QVBoxLayout();

    QSpacerItem *importSpacer = new QSpacerItem(buttonSize.width(), buttonSize.height(), QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_importButton = new QPushButton(tr("Импорт системных настроек"));
    m_importButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_importButton->resize(10, 200);
    QHBoxLayout* importLayout = new QHBoxLayout();
    importLayout->addItem(importSpacer);
    importLayout->addWidget(m_importButton);
    secondLayout->addLayout(importLayout);

    QVBoxLayout* checkboxLayout = new QVBoxLayout();
    QVBoxLayout* coonectionCheckLayout = new QVBoxLayout();
    QHBoxLayout* checkLayout = new QHBoxLayout();
    QSpacerItem *coonectionCheckSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QSpacerItem *checkboxSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

    m_proxyCheckBox = new QCheckBox(tr("Использовать прокси-сервер"));
    m_systemProxyCheckBox = new QCheckBox(tr("Использовать системные настройки прокси-сервера"));
    m_connectionCheckButton = new QPushButton(tr("Проверка соединения"));
    m_connectionCheckButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_connectionCheckButton->resize(10, 200);

    checkboxLayout->addItem(checkboxSpacer);
    checkboxLayout->addWidget(m_proxyCheckBox);
    checkboxLayout->addWidget(m_systemProxyCheckBox);
    coonectionCheckLayout->addWidget(m_connectionCheckButton);
    coonectionCheckLayout->addItem(coonectionCheckSpacer);

    checkLayout->addLayout(checkboxLayout);
    checkLayout->addLayout(coonectionCheckLayout);
    secondLayout->addLayout(checkLayout);

    QFrame *proxyFrame = new QFrame();
    proxyFrame->setFrameStyle(QFrame::StyledPanel);
    secondLayout->addWidget(proxyFrame);

    m_adressLineEdit = new QLineEdit();
    m_usernameLineEdit = new QLineEdit();
    m_passwordLineEdit = new QLineEdit();
    m_portLineEdit = new QLineEdit();

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
    proxyLayout1->addWidget(m_usernameLineEdit);
    proxyLayout1->addWidget(m_passwordLineEdit);

    QHBoxLayout* proxyLayout2 = new QHBoxLayout();
    proxyLayout2->addLayout(proxyLayout1);
    proxyLayout2->addItem(pwAndUnSpacer);

    QVBoxLayout* proxyLayout3 = new QVBoxLayout();
    proxyLayout3->addWidget(m_adressLineEdit);
    proxyLayout3->addLayout(proxyLayout2);

    QHBoxLayout* proxyLayout4 = new QHBoxLayout();
    proxyLayout4->addLayout(portLayout);
    proxyLayout4->addWidget(m_portLineEdit);

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

    m_tabWidget->addTab(dialog, tr("Настройки подключения"));

    setLayout(mainLayout);

    connect(m_okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_browseButton, SIGNAL(clicked()), this, SLOT(on_browseButtonClicked()));
    connect(m_addButton, SIGNAL(clicked()), this, SLOT(on_addButtonClicked()));
    connect(m_removeButton, SIGNAL(clicked()), this, SLOT(on_removeButtonClicked()));
    connect(m_getButton, SIGNAL(clicked()), this, SLOT(on_getButtonClicked()));
    connect(m_importButton, SIGNAL(clicked()), this, SLOT(on_importButtonClicked()));
    connect(m_connectionCheckButton, SIGNAL(clicked()), this, SLOT(on_connectionButtonClicked()));

}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::showMessageNotRealised()
{
    QMessageBox notRealisedMessageBox(QMessageBox::Information, windowTitle(), QStringLiteral("Warning"), QMessageBox::Ok, this);
    notRealisedMessageBox.setInformativeText(QStringLiteral("Не реализовано"));
    notRealisedMessageBox.exec();
}

void SettingsDialog::on_browseButtonClicked()
{
    showMessageNotRealised();
}

void SettingsDialog::on_addButtonClicked()
{
    showMessageNotRealised();
}

void SettingsDialog::on_removeButtonClicked()
{
    showMessageNotRealised();
}

void SettingsDialog::on_getButtonClicked()
{
    showMessageNotRealised();
}

void SettingsDialog::on_importButtonClicked()
{
    showMessageNotRealised();
}

void SettingsDialog::on_connectionButtonClicked()
{
    showMessageNotRealised();
}
