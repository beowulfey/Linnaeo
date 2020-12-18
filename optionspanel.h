#ifndef OPTIONSPANEL_H
#define OPTIONSPANEL_H

#include <QWidget>

namespace Ui {
class OptionsPanel;
}

class OptionsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsPanel(QWidget *parent = nullptr);
    ~OptionsPanel();

private:
    Ui::OptionsPanel *ui;
};

#endif // OPTIONSPANEL_H
