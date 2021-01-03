#include "preferences.h"
#include "ui_preferences.h"

/// TODO:
/// Preferences pane should be used for setting:
///     * Default save location
///     * Default alignment algo
///     * Default export/save/paste format for sequences/alignments
///     * Turn on whether to use debug, information, or no terminal output.

Preferences::Preferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferences)
{
    ui->setupUi(this);
}

Preferences::~Preferences()
{
    delete ui;
}
