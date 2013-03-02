#ifndef PLUGIN_INSTALL
#define PLUGIN_INSTALL

#include <QObject>
#include "ui_ltr.h"
#include "wine_launcher.h"

class Extractor;

class PluginInstall : public QObject
{
  Q_OBJECT
 public:
  PluginInstall(const Ui::LinuxtrackMainForm &ui);
  ~PluginInstall();
 private slots:
  void installWinePlugin();
  void instFinished(bool result);
  void tirFirmwareInstall();
  void tirFirmwareInstalled(bool ok);
  
 private:
  const Ui::LinuxtrackMainForm &gui;
  void Connect();
  WineLauncher *inst;
  Extractor *dlfw;
  bool isTirFirmwareInstalled();
  const QString poem1;
  const QString poem2;
  const QString gameData;
};


#endif
