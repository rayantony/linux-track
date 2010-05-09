#ifndef LTR_GUI__H
#define LTR_GUI__H

#include <QCloseEvent>

#include "ui_ltr.h"
#include "webcam_prefs.h"
#include "wiimote_prefs.h"
#include "tir_prefs.h"
#include "ltr_show.h"
#include "ltr_dev_help.h"
#include "ltr_model.h"
//#include "scp_form.h"
#include "log_view.h"
class LinuxtrackGui : public QWidget
{
  Q_OBJECT
 public:
  LinuxtrackGui(QWidget *parent = 0);
  ~LinuxtrackGui();
 protected:
  void closeEvent(QCloseEvent *event);
 signals:
  void customSectionChanged();
 private slots:
  void on_QuitButton_pressed();
  void on_DeviceSelector_activated(int index);
  void on_RefreshDevices_pressed();
  void on_EditSCButton_pressed();
  void on_XplanePluginButton_pressed();
  void on_FilterSlider_valueChanged(int value);
  void on_Profiles_currentIndexChanged(const QString &text);
  void on_CreateNewProfile_pressed();
  void on_SaveButton_pressed();
  void on_ViewLogButton_pressed();
  void trackerStopped();
  void trackerRunning();
  void ffChanged(float f);
 private:
  Ui::LinuxtrackMainForm ui;
  LtrGuiForm *showWindow;
  LtrDevHelp *helper;
  WebcamPrefs *wcp;
  WiimotePrefs *wiip;
  TirPrefs *tirp;
  ModelEdit *me;
//  ScpForm *sc;
  LogView *lv;
};


#endif