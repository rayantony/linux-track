#include "pref_int.h"
#include "ltr_gui_prefs.h"
#include "map"

#include <iostream>

PrefProxy *PrefProxy::prf = NULL;


PrefProxy::PrefProxy()
{
  
  if(!read_prefs(NULL, false)){
    log_message("Couldn't load preferences!\n");
  }
}

PrefProxy::~PrefProxy()
{
  if(prf != NULL){
    delete prf;
  }
  free_prefs();
}

PrefProxy& PrefProxy::Pref()
{
  if(prf == NULL){
    prf = new PrefProxy();
  }
  return *prf;
}

bool PrefProxy::activateDevice(const QString &sectionName)
{
  pref_id dev_selector;
  if(!open_pref((char *)"Global", (char *)"Input", &dev_selector)){
    return false;
  }
  set_str(&dev_selector, sectionName.toAscii().data());
  close_pref(&dev_selector);
  return true;
}

bool PrefProxy::createDevice(QString &sectionName)
{
  int i = 0;
  QString newSecName = sectionName;
  while(1){
    if(!section_exists(newSecName.toAscii().data())){
      break;
    }
    newSecName = QString("%1_%2").arg(sectionName).
                                           arg(QString::number(i));
  }
  add_section(newSecName.toAscii().data());
  sectionName = newSecName;
  return true;
}

bool PrefProxy::getKeyVal(const QString &sectionName, const QString &keyName, 
			  QString &result)
{
  char *val = get_key(sectionName.toAscii().data(), 
                      keyName.toAscii().data());
  if(val != NULL){
    result = val;
    return true;
  }else{
    return false;
  }
}

bool PrefProxy::addKeyVal(const QString &sectionName, const QString &keyName, 
			  const QString &value)
{
  return add_key(sectionName.toAscii().data(), keyName.toAscii().data(), 
		 value.toAscii().data());
}



bool PrefProxy::setKeyVal(const QString &sectionName, const QString &keyName, 
			  const QString &value)
{
  pref_id kv;
  if(!open_pref(sectionName.toAscii().data(), keyName.toAscii().data(), &kv)){
    return false;
  }
  bool res = true;
  if(!set_str(&kv, value.toAscii().data())){
    res = false;
  }
  close_pref(&kv);
  return res;
}

bool PrefProxy::getFirstDeviceSection(const QString &devType, QString &result)
{
  char **sections = NULL;
  get_section_list(&sections);
  char *name;
  int i = 0;
  while((name = sections[i]) != NULL){
    char *dev_name;
    if((dev_name = get_key(name, (char *)"Capture-device")) != NULL){
      if(QString(dev_name) == devType){
	break;
      }
    }
    ++i;
  }
  bool res;
  if(name != NULL){
    result = QString(name);
    res = true;
  }else{
    res = false;
  }
  array_cleanup(&sections);
  return res;
}

bool PrefProxy::getFirstDeviceSection(const QString &devType, 
				      const QString &devId, QString &result)
{
  char **sections = NULL;
  get_section_list(&sections);
  char *name;
  int i = 0;
  while((name = sections[i]) != NULL){
    char *dev_name = get_key(name, (char *)"Capture-device");
    char *dev_id = get_key(name, (char *)"Capture-device-id");
    if((dev_name != NULL) && (dev_id != NULL)){
      if((QString(dev_name) == devType) && (QString(dev_id) == devId)){
	break;
      }
    }
    ++i;
  }
  bool res;
  if(name != NULL){
    result = QString(name);
    res = true;
  }else{
    res = false;
  }
  array_cleanup(&sections);
  return res;
}

bool PrefProxy::getActiveDevice(deviceType_t &devType, QString &id)
{
  char *dev_section = get_key((char *)"Global", (char *)"Input");
  if(dev_section == NULL){
    return false;
  }
  char *dev_name = get_key(dev_section, (char *)"Capture-device");
  char *dev_id = get_key(dev_section, (char *)"Capture-device-id");
  if((dev_name == NULL) || (dev_id == NULL)){
    return false;
  }
  QString dn = dev_name;
  if(dn.compare((char *)"Webcam", Qt::CaseInsensitive) == 0){
    devType = WEBCAM;
  }else if(dn.compare((char *)"Wiimote", Qt::CaseInsensitive) == 0){
    devType = WIIMOTE;
  }else if(dn.compare((char *)"Tir", Qt::CaseInsensitive) == 0){
    devType = TIR;
  }else if(dn.compare((char *)"Tir_openusb", Qt::CaseInsensitive) == 0){
    devType = TIR;
  }else{
    devType = NONE;
  }
  id = dev_id;
  return true;
}
