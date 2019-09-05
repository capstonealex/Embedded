#include <iostream>
#include "GPIO/GPIOManager.h"
#include "GPIO/GPIOConst.h"
#include <unistd.h>//for sleep

int main() {
  GPIO::GPIOManager* gp = GPIO::GPIOManager::getInstance();
  int pin = GPIO::GPIOConst::getInstance()->getGpioByKey("P9_23");
	
	gp->setDirection(pin, GPIO::INPUT);
	
	while(true){
      printf("Pin 9.23 value: %d\n",gp->getValue(pin));
      sleep(1);
  }

  gp->~GPIOManager();

  return 0;
}
