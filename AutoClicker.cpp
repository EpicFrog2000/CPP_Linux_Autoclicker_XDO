#include <iostream>
#include <xdo.h>
#include <unistd.h>
using namespace std;

extern "C" {
#include <xdo.h>
}

#define CURRENTWINDOW (0)
xdo_t* xdoMain;
int main(){
xdoMain = xdo_new(NULL);

//xdo_move_mouse(xdoMain,500,100,0);

for (int i = 0; i < 10; i++)
{
xdo_click_window(xdoMain, 0, 1);
sleep(1);
}

xdo_free(xdoMain);
return 0;
}
