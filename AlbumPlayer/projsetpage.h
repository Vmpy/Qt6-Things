#ifndef PROJSETPAGE_H
#define PROJSETPAGE_H

#include <QWizardPage>

namespace Ui {
class ProjSetPage;
}

class ProjSetPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ProjSetPage(QWidget *parent = nullptr);
    ~ProjSetPage();
    void getProjSetting(QString &Name, QString &Path);

private:
    Ui::ProjSetPage *ui;

protected:
    bool isComplete() const override;
private slots:
    void on_buttonBrowse_clicked();
};

#endif // PROJSETPAGE_H
