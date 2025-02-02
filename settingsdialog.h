#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QTableView>
#include <QLineEdit>
#include <QCheckBox>

class SettingsDialog : public QDialog
{
public:
    SettingsDialog();

    ~SettingsDialog();

    QTabWidget* tabWidget;

    QLineEdit* m_browseLineEdit;
    QPushButton* m_browseButton;
    QCheckBox* m_db5CheckBox;

    QPushButton* m_addButton;
    QPushButton* m_removeButton;
    QPushButton* m_getButton;
    QTableView* m_numbersTableView;

    QCheckBox* proxyCheckBox;
    QCheckBox* systemProxyCheckBox;
    QPushButton* importButton;
    QPushButton* coonectionCheckButton;

    QLineEdit* adressLineEdit;
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QLineEdit* portLineEdit;

    QPushButton* okButton;
    QPushButton* cancelButton;

};

#endif // SETTINGSDIALOG_H
