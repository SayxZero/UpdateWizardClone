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

    Q_OBJECT

public:

    SettingsDialog();
    ~SettingsDialog();

    QTabWidget* m_tabWidget;

    QLineEdit* m_browseLineEdit;
    QPushButton* m_browseButton;
    QCheckBox* m_db5CheckBox;

    QPushButton* m_addButton;
    QPushButton* m_removeButton;
    QPushButton* m_getButton;
    QTableView* m_numbersTableView;

    QCheckBox* m_proxyCheckBox;
    QCheckBox* m_systemProxyCheckBox;
    QPushButton* m_importButton;
    QPushButton* m_connectionCheckButton;

    QLineEdit* m_adressLineEdit;
    QLineEdit* m_usernameLineEdit;
    QLineEdit* m_passwordLineEdit;
    QLineEdit* m_portLineEdit;

    QPushButton* m_okButton;
    QPushButton* m_cancelButton;

    void showMessageNotRealised();

public slots:

    void on_browseButtonClicked();
    void on_addButtonClicked();
    void on_removeButtonClicked();
    void on_getButtonClicked();
    void on_importButtonClicked();
    void on_connectionButtonClicked();

};

#endif // SETTINGSDIALOG_H
