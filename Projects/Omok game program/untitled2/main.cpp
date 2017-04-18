#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}



/*



                  if(pan[location[j][0]-1][location[j][1]-1] == 0){
                      MAX_y_PC[num] = location[j][0]-1;
                      MAX_x_PC[num] = location[j][1]-1;
                      return dia1;
                  }else if(pan[location[j][0]-stone_num][location[j][1]-stone_num] == 0){
                      MAX_x_PC[num] = location[j][1]-stone_num;
                      MAX_y_PC[num] = location[j][0]-stone_num;
                      return dia1;
                  }


 *
 *
 *
 * */
