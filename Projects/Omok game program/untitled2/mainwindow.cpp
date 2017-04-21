#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    first = 0;
    stone_count = 0;
    QImage *Img = new QImage();
    QPixmap *buffer = new QPixmap();
    play = 0;
    if(Img->load("C:\\seadol2.jpg"))
    {
        *buffer = QPixmap::fromImage(*Img);
        *buffer = buffer->scaled(Img->width(),Img->height());
    }else{
    }

    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){
            pan[i][j] = 0;
        }
    }
    for(int i = -1; i < 20; i++)
    {
        for(int j = -1; j < 20; j++)
        {
            if(i < 0 || i > 18 || j < 0 || j > 18)
            {
                pan[i][j] = 3;
            }
        }
    }
    for(int i = 0; i < 3; i++){
        score[i] = 0;
    }

    IbView = new QLabel(this);
    IbView->setPixmap(*buffer);
    IbView->resize(buffer->width(),buffer->height());
    IbView->move(0,0);
    IbView->show();


    help = new QPushButton("help", this);
    help->setGeometry(625, 670, 140, 50);
    btn2 = new QPushButton("PC vs PLAYER", this);
    btn2->setVisible(false);
    btn2->setGeometry(350, 300, 140, 50);
    btn3 = new QPushButton("PLAYER vs PLAYER", this);
    btn3->setVisible(false);
    btn3->setGeometry(350, 400, 140, 50);

    btn_W = new QPushButton("white", this);
    btn_W->setVisible(false);
    btn_W->setGeometry(350, 300, 140, 50);
    btn_B = new QPushButton("black", this);
    btn_B->setVisible(false);
    btn_B->setGeometry(350, 400, 140, 50);


    btn = new QPushButton("START", this);
    btn->setGeometry(350, 370, 90, 60);
    setFixedSize(800, 600);

    QIcon icon("C:\\seadol.jpg");

    hard[0] = new QPushButton("1", this);
    hard[1] = new QPushButton("2", this);
    hard[2] = new QPushButton("3", this);
    hard[3] = new QPushButton("4", this);
    hard[4] = new QPushButton("5", this);

    for(int i = 0; i < 5; i++){
        hard[i]->setGeometry(350, 300+ (i*30), 140, 50);
        hard[i]->setVisible(false);
        connect(hard[i], SIGNAL(clicked(bool)), this, SLOT(Choice_stone()));

    }



    for(int i = 0; i < 19; i++){  //바둑판 초기화
        for(int j = 0; j < 19; j++){
            pan_btn[i][j] = new QPushButton("", this);
            pan_btn[i][j]->setIcon(QIcon("C:\\pan_btn.jpg"));
            pan_btn[i][j]->setIconSize(QSize(30,30));
            pan_btn[i][j]->setGeometry(i*30+30, j*30+160, 30, 30);
            pan_btn[i][j]->setVisible(false);
            pan_btn[i][j]->setFlat(true);
            connect(pan_btn[i][j], SIGNAL(clicked(bool)), this, SLOT(pan_c()));
        }
    }

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(btn_c()));
    connect(btn2, SIGNAL(clicked(bool)), this, SLOT(Choice_stone()));
    connect(btn3, SIGNAL(clicked(bool)), this, SLOT(PLAY_start()));
    connect(btn_W, SIGNAL(clicked(bool)), this, SLOT(PLAY_start()));
    connect(btn_B, SIGNAL(clicked(bool)), this, SLOT(PLAY_start()));
    connect(help, SIGNAL(clicked(bool)), this, SLOT(Help()));



}
void MainWindow::Help()  //help버튼 클릭시 컴퓨터알고리즘 호출로 사용자을 도와주는 함수
{

    if(playing == false){ //게임이 종료되면 더 이상 클릭 불가
        return ;
    }


   if(stone_count < 2){  //바둑돌이 1개 이하일때 경고문 출력
       QLabel *la;
       QImage img("C:\\Think.jpg");
       QPixmap buf = QPixmap::fromImage(img);
       la = new QLabel();
       la->setPixmap(buf);
       la->resize(buf.width(),buf.height());
       la->move(300, 300);
       la->show();

   }else
   {
       PC_DO_CHECK(stone, 0);  //컴퓨터가 돌을 두는 함수 호출
       int final_y = MAX_x_PC[0][0];
       int final_x = MAX_y_PC[0][0];
        pan_btn[final_x][final_y]->click();  //입력받은 위치에 바둑돌 두기
   }
}

void MainWindow::pan_c() //바둑판의 버튼이 눌리면 실행되는 함수
{
    if(first == 0){
        stone = 1;
        first = 1;
    }


    if(stone == 1){  //1일경우 검은돌
        QImage img("C:\\black.png");
        QPixmap buf = QPixmap::fromImage(img);
        IbView = new QLabel(this);
        IbView->setPixmap(buf);
        IbView->resize(buf.width(),buf.height());
    }
    else if(stone == 2){ //2일경우 흰돌
        QImage img("C:\\white.png");
        QPixmap buf = QPixmap::fromImage(img);
        IbView = new QLabel(this);
        IbView->setPixmap(buf);
        IbView->resize(buf.width(),buf.height());
    }

    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){
            if(sender() == pan_btn[i][j]){  //눌린 벼튼의 위치를 찾아서 버튼 클릭
                 pan[j][i] = stone;
                 IbView->move(i*30+30, j*30+160);
                 IbView->show();
                 pan_btn[i][j]->setVisible(false);
                 location[stone_count][0] = j;
                 location[stone_count][1] = i;
                 stone_count++;

            }
        }
    }


    CHECK_SCORE(stone);
    stone = ((stone==1)? 2:1);
    CHECK_SCORE(stone);  //각각의 돌의 점수 확인


    str1 = "black's score : " + buf.setNum(score[1]);
    l1->setText(str1);
    str1 = "white's score : " + buf.setNum(score[2]);
    l2->setText(str1);  //확인한 돌의 점수 라벨로 출력
    if(playing == false){
        Game_end();
        for(int i = 0; i < 19; i++){
            for(int j = 0; j < 19; j++){
                if(pan[j][i] == 0){  //게임 종료시 돌이 없는 위치에 라벨 생성으로 버튼 클릭 막음
                    QImage img("C:\\pan_btn.jpg");
                    QPixmap buf = QPixmap::fromImage(img);
                    IbView = new QLabel(this);
                    IbView->setPixmap(buf);
                    IbView->resize(buf.width(),buf.height());

                    IbView->move(i*30+30, j*30+160);
                    IbView->show();
                }

            }
        }
        return;
    }




    if(play == stone){ //컴퓨터와 하는거면

       Think_Depth(depth_main, stone); //pc가 돌을 두는 함수 호출
    }
    if (play == 0){

        str1 = "black's score : " + buf.setNum(score[1]);
        l1->setText(str1);
        str1 = "white's score : " + buf.setNum(score[2]);
        l2->setText(str1);
        if(playing == false){
            Game_end();
            for(int i = 0; i < 19; i++){
                for(int j = 0; j < 19; j++){
                    if(pan[j][i] == 0){
                        QImage img("C:\\pan_btn.jpg");
                        QPixmap buf = QPixmap::fromImage(img);
                        IbView = new QLabel(this);
                        IbView->setPixmap(buf);
                        IbView->resize(buf.width(),buf.height());

                        IbView->move(i*30+30, j*30+160);
                        IbView->show();
                    }
                }
            }
            return;

        }





        return;
    }





}

void MainWindow::Game_end()  //게임이 끝날경우 실행되는 함수
{
    int num1, num2;
    int how;


    num1 = CHECK_SCORE(1);
    num2 = CHECK_SCORE(2);


    if(num1 != -1){  //1번이 돌을 다섯개 두었을 경우
        how = num1%10;  //4가지연속된 경우중 어떻게 연속되었는지 확인하는 변수
        num1 /= 10;

        if(how == 1)  //x값 증가로 연속된경우
        {

            for(int i = 0; i < 5; i++){  //연속된 돌에 이미지 변경
                //이미지 변경
                QImage img("C:\\black2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num1][1]*30+30, location[num1][0]*30+160+(i*30));
                IbView->show();
            }
        }
        if(how == 2)  //y값 증가로 연속된경우
        {

            for(int i = 0; i < 5; i++){ //연속된 돌에 이미지 변경
                //이미지 변경
                QImage img("C:\\black2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num1][1]*30+30+(i*30), location[num1][0]*30+160);
                IbView->show();
            }
        }
        if(how == 3) //대각선1의 경우
        {

            for(int i = 0; i < 5; i++){ //연속된 돌 이미지 변
                //이미지 변경
                QImage img("C:\\black2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num1][1]*30+30+(i*30), location[num1][0]*30+160+(i*30));
                IbView->show();
            }
        }
        if(how == 4)//대각선2의경우
        {

            for(int i = 0; i < 5; i++){  //연속된 돌의 이미지 변경
                //이미지 변경
                QImage img("C:\\black2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num1][1]*30+30-(i*30), location[num1][0]*30+160+(i*30));
                IbView->show();
            }
        }

    }else if(num2 != -1){ //2번에 돌을 다섯개 두었을 경우
        how = num2%10;
        num2 /= 10;

        if(how == 1)
        {

            for(int i = 0; i < 5; i++){
                //이미지 변경
                QImage img("C:\\white2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num2][1]*30+30, location[num2][0]*30+160+(i*30));
                IbView->show();
            }
        }
        if(how == 2)
        {

            for(int i = 0; i < 5; i++){
                //이미지 변경
                QImage img("C:\\white2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num2][1]*30+30+(i*30), location[num2][0]*30+160);
                IbView->show();
            }
        }
        if(how == 3)
        {

            for(int i = 0; i < 5; i++){
                //이미지 변경
                QImage img("C:\\white2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num2][1]*30+30+(i*30), location[num2][0]*30+160+(i*30));
                IbView->show();
            }
        }
        if(how == 4)
        {

            for(int i = 0; i < 5; i++){
                //이미지 변경
                QImage img("C:\\white2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num2][1]*30+30-(i*30), location[num2][0]*30+160+(i*30));
                IbView->show();
            }
        }

    }


    if(score[1] > score[2]) //점수확인하여 승리이미지 출력
    {
        QLabel *la;
        QImage img("C:\\black_win2.jpg");
        QPixmap buf = QPixmap::fromImage(img);
        la = new QLabel();
        la->setPixmap(buf);
        la->resize(buf.width(),buf.height());
        la->move(300, 500);
        la->show();
    }
    else
    {
        QLabel *la;
        QImage img("C:\\white_win2.jpg");
        QPixmap buf = QPixmap::fromImage(img);
        la = new QLabel();
        la->setPixmap(buf);
        la->resize(buf.width(),buf.height());
        la->move(300, 500);
        la->show();
    }
}

void MainWindow::Choice_hard()  //난이도를 정하는 함수
{


    btn2->setVisible(false);
    btn3->setVisible(false);

    play = pc_s;//컴퓨터랑 함

    for(int i = 0; i < 5; i++){
        hard[i]->setVisible(true);
    }
}

void MainWindow::Choice_stone()  //컴퓨터와 대결시 돌을 선택하는 함수
{
    for(int i = 0; i < 5; i++){
        hard[i]->setVisible(false);

        if(sender()==hard[i]){
            depth_main = i+1;
        }
    }

    btn2->setVisible(false);
    btn3->setVisible(false);

    play = 1;

    btn_W->setVisible(true);
    btn_B->setVisible(true);
}


void MainWindow::PLAY_start()  //게임화면으로 넘어가는 함수
{
    //
    this->move(100, 100);
    QImage *Img = new QImage();
    QPixmap *buffer = new QPixmap();
    setFixedSize(1080, 750);

    if(Img->load("C:\\pan3_2.jpg"))
    {
        *buffer = QPixmap::fromImage(*Img);
        *buffer = buffer->scaled(Img->width(),Img->height());
    }else{
    }
    IbView->setPixmap(*buffer);
    IbView->resize(buffer->width(),buffer->height());
    IbView->move(0,0);
    IbView->show();


    btn2->setVisible(false);
    btn3->setVisible(false);
    btn_W->setVisible(false);
    btn_B->setVisible(false);


    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){
            pan_btn[i][j]->setVisible(true);  //바둑판 버튼 출력
        }
    }

    if(sender() == btn_W){  //백 선택
        p1_s = 2;
        pc_s = 1;
        stone_count++;
        location[0][0] = 9;
        location[0][1] = 9;
        first = 1;

        pan_btn[9][9]->setVisible(false);

        QImage img("C:\\black.png");  //사용자가 백돌 선택시 컴퓨터인 흑돌을 초기값에 맞게 둠
        QPixmap buf = QPixmap::fromImage(img);
        IbView = new QLabel(this);
        IbView->setPixmap(buf);
        IbView->resize(buf.width(),buf.height());
        pan[9][9] = 1;
        IbView->move(9*30+30, 9*30+160);
        IbView->show();


    }
    if(sender() == btn_B){  //흑 선택
        p1_s = 1;
        pc_s = 2;
        first = 1;

        play = pc_s;
    }

    stone = p1_s;



    str1 = "black's score : " + buf.setNum(score[1]);

    l1 = new QLabel(str1, this);

    str1 = "white's score : " + buf.setNum(score[2]);

    l2 = new QLabel(str1, this);
    l1->setGeometry(825, 487, 300, 300);
    l2->setGeometry(825, 550, 300, 300);
    l1->show();
    l2->show();
    l1->setFont(QFont("BDF", 15, QFont::Bold));
    l2->setFont(QFont("QPF", 15, QFont::Bold));

}

void MainWindow::btn_c()
{

    btn2->setVisible(true);
    btn3->setVisible(true);
    btn->setVisible(false);

}


void MainWindow::Think_Depth(int depth, int pc)  //연산의 깊이에 따라 컴퓨터가 돌을 두는 함수
{

    CHECK_SCORE(pc_s);
    CHECK_SCORE(p1_s);
    int not_stone = ((stone == 2)? 1 : 2);

    prev_score1 = score[stone]; //최고점수 확인 후 점수 복귀를 위한 변수
    prev_score2 = score[not_stone]; //최고점수 확인 후 점수 복귀를 위한 변수

    PC_DO(pc, depth);
}



int MainWindow::CHECK_SCORE(int stone)  //연속된 돌의 개수를 확인하며 점수를 확인하는 함수
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int x_2 = 0, y_2 = 0, dia1_2 = 0, dia2_2 = 0;
    int five = -1;

    for(int i = 0; i < stone_count; i++){
    }
    score[stone] = 0;
    for(int i = 0; i < stone_count; i++){
       if(pan[location[i][0]][location[i][1]] == stone){

          for(int j = 0; j < stone_count; j++){

             if((location[j][0]-location[i][0]) <= 4 && location[j][1] == location[i][1] && (location[j][0]-location[i][0]) >= 0){ //[0]->x축 [1]은 y축/ y축은 같고 x축 값의 차이가 5 이내 일때
                if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                      x++;

                }
             }


             if((location[j][1]-location[i][1]) <= 4 && location[j][0] == location[i][0] && (location[j][1]-location[i][1]) >= 0 ){
                if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                    y++;
                }
             }

             if((location[j][0]-location[i][0])==(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (기준y) - (비교y)일때
                if((location[j][0]-location[i][0]) <= 4 && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                        dia1++;
                    }
                }
             }

            if((location[j][0]-location[i][0])==(-1)*(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (-1)*(기준y) - (비교y)일때(x는 증가 y는 감소)
                if((location[j][0]-location[i][0]) <= 4  && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                        dia2++;
                    }
                }
             }
        }

 //연결된 돌의 개수 확인  5개연속일경우 20+30 = 50점 획득 , 4개연속일경우 30점 획득
       if(x == 5){
           if(pan[location[i][0]+5][location[i][1]] != stone){

                 playing = false;//게임종료
                score[stone] += 20;
                five = 1+(i*10);
           }
       }
       if(x == 4){  //---------------+인지 -인지 확인, 값 확인
          if(pan[location[i][0]+4][location[i][1]] != stone){
             score[stone] += 30;

          }
       }


       if(y == 5){
          playing = false;
          if(pan[location[i][0]][location[i][1]+5] != stone){
            score[stone] += 20;
            five = 2+(i*10);

          }

       }
       if(y == 4){
          if(pan[location[i][0]][location[i][1]+4] != stone){
             score[stone] += 30;

          }
       }

       if(dia1 == 5){
           if(pan[location[i][0]+5][location[i][1]+5] != stone){

                playing = false;
                score[stone] += 20;

                five = 3+(i*10);

           }

       }
       if(dia1 == 4){
          if(pan[location[i][0]+4][location[i][1]+4] != stone){
             score[stone] += 30;

          }
       }


       if(dia2 == 5){
           if(pan[location[i][0]+5][location[i][1]-5] != stone){

                playing = false;
                score[stone] += 20;
                five = 4+(i*10);

           }

       }
       if(dia2 == 4){
          if(pan[location[i][0]+4][location[i][1]-4] != stone){
             score[stone] += 30;\
          }
       }

       ///

       if(x_2 == 5){
           if(pan[location[i][0]-5][location[i][1]] != stone){

                playing = false;//게임종료
                score[stone] += 20;
                five = i;

           }
       }
       if(x_2 == 4){  //---------------+인지 -인지 확인, 값 확인
          if(pan[location[i][0]-4][location[i][1]] != stone){
             score[stone] += 10;

          }
       }


       if(y_2 == 5){
           if(pan[location[i][0]][location[i][1]+5] != stone){

                playing = false;
                score[stone] += 20;
                five = i;

           }

       }
       if(y_2 == 4){
          if(pan[location[i][0]][location[i][1]+4] != stone){
             score[stone] += 30;

          }
       }

       if(dia1_2 == 5){
           if(pan[location[i][0]+5][location[i][1]+5] != stone){

                playing = false;
                score[stone] += 20;
                five = i;

            }
       }
       if(dia1_2 == 4){
          if(pan[location[i][0]+4][location[i][1]+4] != stone){
             score[stone] += 30;

          }
       }


       if(dia2_2 == 5){
           if(pan[location[i][0]+5][location[i][1]-5] != stone){

                playing = false;
                score[stone] += 20;
                five = i;

           }

       }
       if(dia2_2 == 4){
          if(pan[location[i][0]+4][location[i][1]-4] != stone){
             score[stone] += 30;\

          }
       }


       }
       else{
           continue;
       }
    x = 0; y = 0; dia1 = 0; dia2 = 0;
    x_2 = 0; y_2 = 0; dia1_2 = 0; dia2_2 = 0;

    }

    return five;


}



int MainWindow::Think_do_somewhere(int stone, int num, int start, int end) //사이에 돌을 둘 경우 연속된 돌이 생기는 위치를 확인하는 함수/ 양쪽에 돌이 상대방 돌이 있을경우 돌을 두지 않음
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int count = 0;
    int not_stone = ((stone == 2)? 1 : 2);

    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){  //바둑판 전체 확인
            x = 0, y = 0, dia1 = 0, dia2 = 0;

            if(pan[i][j] == 0){

                pan[i][j] = stone;

                for(int loop = (start*(-1))+1; loop <= start-1; loop++){  //각각의 범위에서 연속된 돌이 있을경우 변수값 증가

                    if(pan[i+loop][j] == stone)
                    {
                        x++;

                        if(x == start)
                        {
                            if(pan[i+loop+1][j] != 0 && pan[i+loop-start][j] != 0)  //한쪽이라도 막혀있으면 두지않음
                            {
                                x = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        x = 0;
                    }

                    if(pan[i][j+loop] == stone)
                    {

                        y++;
                        //qDebug("y ++ %d", y);

                        if(y == start)
                        {
                            if(pan[i][j+loop+1] != 0 && pan[i][j+loop-start] != 0)//한쪽이라도 막혀있으면 두지않음
                            {
                                y = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        y = 0;
                    }

                    if(pan[i+loop][j+loop] == stone)
                    {
                        dia1++;

                        if(dia1 == start)
                        {
                            if(pan[i+loop+1][j+loop+1] != 0 && pan[i+loop-start][j+loop-start] != 0)//한쪽이라도 막혀있으면 두지않음
                            {
                                dia1 = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        dia1 = 0;
                    }

                    if(pan[i-loop][j+loop] == stone)
                    {
                        dia2++;

                        if(dia2 == start)
                        {
                            if(pan[i-loop-1][j+loop+1] != 0 && pan[i-loop+start][j+loop-start] != 0)//한쪽이라도 막혀있으면 두지않음
                            {
                                dia2 = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        dia2 = 0;
                    }

                }

                if(x == start || y == start || dia1 == start || dia2 == start)  //연속된 돌을 찾은경우 종료
                {
                    pan[i][j] = 0;
                    MAX_x_PC[num][0] = i;
                    MAX_y_PC[num][0] = j;
                    return 0;
                }

                pan[i][j] = 0;
            }
        }
        x = 0, y = 0, dia1 = 0, dia2 = 0;
    }
    return -1;
}


int MainWindow::Think_do_somewhere_left(int stone, int num, int start, int end) //사이에 돌을 둘 경우 연속된 돌이 생기는 위치를 확인하는 함수 /한쪽이 뚫려있을경우 둠 그 이외는 위의 함수와 같습니다.
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int count = 0;
    int not_stone = ((stone == 2)? 1 : 2);


    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){
            x = 0, y = 0, dia1 = 0, dia2 = 0;

            if(pan[i][j] == 0){
                pan[i][j] = stone;

                for(int loop = (start*(-1))+1; loop <= start-1; loop++){
                    //x
                    if(pan[i+loop][j] == stone)
                    {
                        x++;
                        if(x == start)
                        {
                            if(pan[i+loop-start][j] != 0)  //한쪽이 막혀있을경우
                            {
                                x = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        x = 0;
                    }

                    if(pan[i][j+loop] == stone)
                    {
                        y++;
                        if(y == start)
                        {
                            if(pan[i][j+loop-start] != 0) //한쪽이 막혀있을경우
                            {
                                y = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        y = 0;
                    }

                    if(pan[i+loop][j+loop] == stone)
                    {
                        dia1++;
                        if(dia1 == start)
                        {
                            if(pan[i+loop-start][j+loop-start] != 0) //한쪽이 막혀있을경우
                            {
                                dia1 = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        dia1 = 0;
                    }

                    if(pan[i-loop][j+loop] == stone)
                    {
                        dia2++;
                        if(dia2 == start)
                        {
                            if(pan[i-loop+start][j+loop-start] != 0) //한쪽이 막혀있을경우
                            {
                                dia2 = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        dia2 = 0;
                    }

                }

                if(x == start || y == start || dia1 == start || dia2 == start)//연속된 돌을 찾은경우 종료
                {
                    pan[i][j] = 0;
                    MAX_x_PC[num][0] = i;
                    MAX_y_PC[num][0] = j;
                    return 0;
                }

                pan[i][j] = 0;
            }
        }
        x = 0, y = 0, dia1 = 0, dia2 = 0;
    }
    return -1;
}


int MainWindow::Think_do_somewhere_right(int stone, int num, int start, int end)  //사이에 돌을 둘 경우 연속된 돌이 생기는 위치를 확인하는 함수 /한쪽이 뚫려있을경우 둠 그 이외는 위의 함수와 같습니다.
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int count = 0;
    int not_stone = ((stone == 2)? 1 : 2);

    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){
            x = 0, y = 0, dia1 = 0, dia2 = 0;

            if(pan[i][j] == 0){
                pan[i][j] = stone;

                for(int loop = (start*(-1))+1; loop <= start-1; loop++){
                    if(pan[i+loop][j] == stone)
                    {
                        x++;
                        if(x == start)
                        {
                            if(pan[i+loop+1][j] != 0) //한쪽이 막혀있을경우
                            {
                                x = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        x = 0;
                    }

                    if(pan[i][j+loop] == stone)
                    {
                        y++;
                        if(y == start)
                        {
                            if(pan[i][j+loop+1] != 0) //한쪽이 막혀있을경우
                            {
                                y = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        y = 0;
                    }

                    if(pan[i+loop][j+loop] == stone)
                    {
                        dia1++;
                        if(dia1 == start)
                        {
                            if(pan[i+loop+1][j+loop+1] != 0) //한쪽이 막혀있을경우
                            {
                                dia1 = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        dia1 = 0;
                    }

                    if(pan[i-loop][j+loop] == stone)
                    {
                        dia2++;
                        if(dia2 == start)
                        {
                            if(pan[i-loop-1][j+loop+1] != 0) //한쪽이 막혀있을경우
                            {
                                dia2 = 0;
                            }else
                            {
                                   break;
                            }
                        }
                    }else
                    {
                        dia2 = 0;
                    }

                }

                if(x == start || y == start || dia1 == start || dia2 == start)//연속된 돌을 찾은경우 종료
                {
                    pan[i][j] = 0;
                    MAX_x_PC[num][0] = i;
                    MAX_y_PC[num][0] = j;
                    return 0;
                }

                pan[i][j] = 0;
            }
        }
        x = 0, y = 0, dia1 = 0, dia2 = 0;
    }
    return -1;
}




int MainWindow::Think_do_somewhere_for_five(int stone, int num, int start, int end) // 사이에 돌을 두면 연속된 돌이 5개가 되는경우 양쪽이 막혀있어도 돌을 둠
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int count = 0;

     for(int i = 0; i < 19; i++){
     }

    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){
            x = 0, y = 0, dia1 = 0, dia2 = 0;
            if(pan[i][j] == 0){
                pan[i][j] = stone;

                for(int loop = (start*(-1))+1; loop <= start-1; loop++){
                    //x
                    if(pan[i+loop][j] == stone)
                    {
                        x++;

                    }else
                    {
                        x = 0;
                    }

                    if(pan[i][j+loop] == stone)
                    {
                        y++;

                    }else
                    {
                        y = 0;
                    }

                    if(pan[i+loop][j+loop] == stone)
                    {
                        dia1++;

                    }else
                    {
                        dia1 = 0;
                    }

                    if(pan[i-loop][j+loop] == stone)
                    {
                        dia2++;

                    }else
                    {
                        dia2 = 0;
                    }
                    if(x == start || y == start || dia1 == start || dia2 == start)
                    {
                        break;
                    }

                }

                if(x == start || y == start || dia1 == start || dia2 == start)
                {
                    pan[i][j] = 0;
                    MAX_x_PC[num][0] = i;
                    MAX_y_PC[num][0] = j;
                    return 0;
                }

                pan[i][j] = 0;
            }
        }
    }
    return -1;
}


int MainWindow::Think_do(int stone, int num, int start, int end) //연속된 돌을 확인하여 돌을 두는 함수
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int not_stone = ((stone == 2)? 1 : 2);

    for(int stone_num = start; stone_num >= end; stone_num--)  //매개변수로 입력받은 돌의 개수부터 end값까지 확인
        for(int i = 0; i < stone_count; i++){ // 현재 있는 돌만 확인
           if(pan[location[i][0]][location[i][1]] == stone){

              for(int j = 0; j < stone_count; j++){

                 if((location[j][0]-location[i][0]) < stone_num && location[j][1] == location[i][1] && (location[j][0]-location[i][0]) >= 0){ //[0]->x축 [1]은 y축/ y축은 같고 x축 값의 차이가 5 이내 일때
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                          x++;

                    }
                 }


                 if((location[j][1]-location[i][1]) < stone_num && location[j][0] == location[i][0] && (location[j][1]-location[i][1]) >= 0 ){
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                        y++;

                    }
                 }

                 if((location[j][0]-location[i][0])==(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (기준y) - (비교y)일때
                    if((location[j][0]-location[i][0]) < stone_num && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                        if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                            dia1++;

                        }
                    }
                 }

                if((location[j][0]-location[i][0])==(-1)*(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (-1)*(기준y) - (비교y)일때(x는 증가 y는 감소)
                    if((location[j][0]-location[i][0]) < stone_num  && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                        if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                            dia2++;

                        }
                    }
                 }
               int loop_buf = 0;

               if(pan[location[i][0]][location[i][1]] != stone){ //그 위치의 돌이 같은색 아니면

                    continue;
               }

               if(x==stone_num){



                 //qDebug(" -return x : %d   / last stone x : %d y : %d stone_num : %d", x, location[i][0], location[i][1], stone_num);
                  if(pan[location[i][0]+1][location[i][1]] == 0){
                      MAX_x_PC[num][0] = location[i][0]+1;
                      MAX_y_PC[num][0] = location[i][1];
                      pc_do_count[stone][num]++;
                      return 0;
                  }
                  if(pan[location[i][0]+stone_num][location[i][1]] == 0)
                    {
                      for(int loop = 0; loop < stone_num; loop++){

                          if(pan[location[i][0]+stone_num-loop][location[i][1]] == stone){
                              loop_buf++;
                          }
                      }
                      if(loop_buf == stone_num-1){

                          MAX_x_PC[num][0] = location[i][0]+stone_num;
                          MAX_y_PC[num][0] = location[i][1];

                          pc_do_count[stone][num]++;
                          return 0;

                      }
                      loop_buf = 0;



                  }
                  if(pan[location[i][0]-1][location[i][1]] == 0)
                  {

                      MAX_x_PC[num][0] = location[i][0]-1;
                      MAX_y_PC[num][0] = location[i][1];

                      pc_do_count[stone][num]++;
                      return 0;


                  }
                  if(pan[location[i][0]-stone_num][location[i][1]] == 0)
                  {
                      for(int loop = 0; loop < stone_num; loop++){

                          if(pan[location[i][0]-stone_num+loop][location[i][1]] == stone){
                              loop_buf++;
                          }
                      }
                      if(loop_buf == stone_num-1){

                          MAX_x_PC[num][0] = location[i][0]-stone_num;
                          MAX_y_PC[num][0] = location[i][1];

                          pc_do_count[stone][num]++;
                          return 0;

                      }
                      loop_buf = 0;




                  }

               }
               if(y==stone_num){
                  if(pan[location[i][0]][location[i][1]+1] == 0){

                      MAX_x_PC[num][0] = location[i][0];
                      MAX_y_PC[num][0] = location[i][1]+1;

                      pc_do_count[stone][num]++;
                      return 0;


                  } if(pan[location[i][0]][location[i][1]+stone_num] == 0){

                      for(int loop = 0; loop < stone_num; loop++){
                          if(pan[location[i][0]][location[i][1]+stone_num-loop] == stone){
                              loop_buf++;
                          }
                      }
                      if(loop_buf == stone_num-1){


                          MAX_x_PC[num][0] = location[i][0];
                          MAX_y_PC[num][0] = location[i][1]+stone_num;

                          pc_do_count[stone][num]++;
                          return 0;

                      }

                      loop_buf = 0;


                  } if(pan[location[i][0]][location[i][1]-1] == 0){

                      MAX_x_PC[num][0] = location[i][0];
                      MAX_y_PC[num][0] = location[i][1]-1;

                      pc_do_count[stone][num]++;
                      return 0;


                  }
                  if(pan[location[i][0]][location[i][1]-stone_num] == 0){

                      for(int loop = 0; loop < stone_num; loop++){
                          if(pan[location[i][0]][location[i][1]-stone_num+loop] == stone){
                              loop_buf++;
                          }
                      }
                      if(loop_buf == stone_num-1){
                          MAX_x_PC[num][0] = location[i][0];
                          MAX_y_PC[num][0] = location[i][1]-stone_num;
                          pc_do_count[stone][num]++;
                          return 0;

                      }
                      loop_buf = 0;



                  }
               }
               if(dia1==stone_num){
                  if(pan[location[i][0]+1][location[i][1]+1] == 0){

                      MAX_x_PC[num][0] = location[i][0]+1;
                      MAX_y_PC[num][0] = location[i][1]+1;

                      pc_do_count[stone][num]++;
                      return 0;


                  } if(pan[location[i][0]-stone_num][location[i][1]-stone_num] == 0){
                      for(int loop = 0; loop < stone_num; loop++){
                          if(pan[location[i][0]-stone_num+loop][location[i][1]-stone_num+loop] == stone){
                              loop_buf++;
                          }
                      }
                      if(loop_buf == stone_num-1){


                          MAX_x_PC[num][0] = location[i][1]-stone_num;
                          MAX_y_PC[num][0] = location[i][0]-stone_num;

                          pc_do_count[stone][num]++;

                          return 0;

                      }

                      loop_buf = 0;



                  } if(pan[location[i][0]-1][location[i][1]-1] == 0){

                      MAX_x_PC[num][0] = location[i][0]-1;
                      MAX_y_PC[num][0] = location[i][1]-1;

                      pc_do_count[stone][num]++;
                      return 0;


                  } if(pan[location[i][0]+stone_num][location[i][1]+stone_num] == 0){
                      for(int loop = 0; loop < stone_num; loop++){
                          if(pan[location[i][0]+stone_num-loop][location[i][1]+stone_num-loop] == stone){
                              loop_buf++;
                          }
                      }
                      if(loop_buf == stone_num-1){

                          MAX_x_PC[num][0] = location[i][0]+stone_num;
                          MAX_y_PC[num][0] = location[i][1]+stone_num;

                          pc_do_count[stone][num]++;
                          return 0;



                      }

                      loop_buf = 0;


                  }
               }
               if(dia2==stone_num){

                 if(pan[location[i][0]-1][location[i][1]+1] == 0){
                      MAX_x_PC[num][0] = location[i][0]-1;
                      MAX_y_PC[num][0] = location[i][1]+1;

                      pc_do_count[stone][num]++;
                      return 0;


                  } if(pan[location[i][0]+stone_num][location[i][1]-stone_num] == 0){
                     for(int loop = 0; loop < stone_num; loop++){
                         if(pan[location[i][0]+stone_num-loop][location[i][1]-stone_num+loop] == stone){
                             loop_buf++;
                         }
                     }
                     if(loop_buf == stone_num-1){
                          MAX_x_PC[num][0] = location[i][0]+stone_num;
                          MAX_y_PC[num][0] = location[i][1]-stone_num;

                          pc_do_count[stone][num]++;
                          return 0;

                     }
                     loop_buf = 0;



                  } if(pan[location[i][0] +1][location[i][1]-1] == 0){
                      //pan[location[i][0]+1][location[i][1]-1] = 100


                     //qDebug("15");

                      MAX_x_PC[num][0] = location[i][0]+1;
                      MAX_y_PC[num][0] = location[i][1]-1;
                      //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                      pc_do_count[stone][num]++;
                      return 0;



                  }if(pan[location[i][0] -stone_num][location[i][1]+stone_num] == 0){

                     for(int loop = 0; loop < stone_num; loop++){
                         if(pan[location[i][0] -stone_num+loop][location[i][1]+stone_num-loop] == stone){
                             loop_buf++;
                         }
                     }
                     if(loop_buf == stone_num-1){

                          MAX_x_PC[num][0] = location[i][0]-stone_num;
                          MAX_y_PC[num][0] = location[i][1]+stone_num;

                          pc_do_count[stone][num]++;
                          return 0;

                     }
                     loop_buf = 0;


                  }

               }


           }

            x = 0; y = 0; dia1 = 0; dia2 = 0;

        }
    }
    return -1;
}

int MainWindow::Think_do_not(int stone, int not_stone, int num, int start, int end)  //연속된 돌의 개수를 확인하여 돌을 두지만 한쪽이 막혀있을경우 돌을 두지 않는 함수
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int tr_x = 0, tr_y = 0, tr_dia1 = 0, tr_dia2 = 0;
   not_stone = ((stone == 2)? 1 : 2);

    for(int stone_num = start; stone_num >= end; stone_num--)
        for(int i = 0; i < stone_count; i++){
           if(pan[location[i][0]][location[i][1]] == stone){

              for(int j = 0; j < stone_count; j++){
                tr_x = 0, tr_y = 0, tr_dia1 = 0, tr_dia2 = 0;
                 if((location[j][0]-location[i][0]) < stone_num && location[j][1] == location[i][1] && (location[j][0]-location[i][0]) >= 0){ //[0]->x축 [1]은 y축/ y축은 같고 x축 값의 차이가 5 이내 일때
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                          x++;

                    }//다른조건에도 수정
                 }


                 if((location[j][1]-location[i][1]) < stone_num && location[j][0] == location[i][0] && (location[j][1]-location[i][1]) >= 0 ){
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                        y++;

                    }
                 }

                 if((location[j][0]-location[i][0])==(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (기준y) - (비교y)일때
                    if((location[j][0]-location[i][0]) < stone_num && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                        if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                            dia1++;

                        }
                    }
                 }

                if((location[j][0]-location[i][0])==(-1)*(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (-1)*(기준y) - (비교y)일때(x는 증가 y는 감소)
                    if((location[j][0]-location[i][0]) < stone_num  && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                        if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                            dia2++;

                        }
                    }
                 }
               int loop_buf = 0;

               if(x==stone_num){ //막혀있는걸 확인하는 스위치부분
                   int count1 = 0, count2 = 0;
                   for(int loop = 0; loop < stone_num; loop++){
                       if(pan[location[i][0]+loop][location[i][1]] == stone)
                           count1++;
                   }
                   for(int loop = 0; loop < stone_num; loop++){
                       if(pan[location[i][0]-loop][location[i][1]] == stone)
                           count2++;
                   }
                   if(count1 != stone_num  && count2 != stone_num){
                       tr_x = 1;
                   }
                   if(pan[location[i][0]+1][location[i][1]] == 0 && pan[location[i][0]-stone_num][location[i][1]] == not_stone){
                        tr_x = 1;
                   }
                   if(pan[location[i][0]+1][location[i][1]] == not_stone && pan[location[i][0]-stone_num][location[i][1]] == 0){

                       tr_x = 1;
                   }
                   if(pan[location[i][0]-1][location[i][1]] == 0 && pan[location[i][0]+stone_num][location[i][1]] == not_stone){

                       tr_x = 1;
                   }
                   if(pan[location[i][0]-1][location[i][1]] == not_stone && pan[location[i][0]+stone_num][location[i][1]] == 0){

                       tr_x = 1;
                   }

                  if( tr_x == 0){

                      if(pan[location[i][0]+1][location[i][1]] == 0){
                          MAX_x_PC[num][0] = location[i][0]+1;
                          MAX_y_PC[num][0] = location[i][1];
                          pc_do_count[stone][num]++;
                          return 0;

                      }
                      if(pan[location[i][0]+stone_num][location[i][1]] == 0)
                        {
                          for(int loop = 0; loop < stone_num; loop++){

                              if(pan[location[i][0]+stone_num-loop][location[i][1]] == stone){
                                  loop_buf++;
                              }
                          }
                          if(loop_buf == stone_num-1){

                              MAX_x_PC[num][0] = location[i][0]+stone_num;
                              MAX_y_PC[num][0] = location[i][1];

                              pc_do_count[stone][num]++;
                              return 0;

                          }
                          loop_buf = 0;



                      }
                      if(pan[location[i][0]-1][location[i][1]] == 0)
                      {

                          MAX_x_PC[num][0] = location[i][0]-1;
                          MAX_y_PC[num][0] = location[i][1];

                          pc_do_count[stone][num]++;
                          return 0;


                      }
                      if(pan[location[i][0]-stone_num][location[i][1]] == 0)
                      {
                          for(int loop = 0; loop < stone_num; loop++){

                              if(pan[location[i][0]-stone_num+loop][location[i][1]] == stone){
                                  loop_buf++;
                              }
                          }
                          if(loop_buf == stone_num-1){

                              MAX_x_PC[num][0] = location[i][0]-stone_num;
                              MAX_y_PC[num][0] = location[i][1];

                              pc_do_count[stone][num]++;
                              return 0;

                          }

                          loop_buf = 0;



                      }
                  }
               }else 
               if(y==stone_num){

                   int count1 = 0, count2 = 0; //막혀있는걸 확인하는 스위치부분
                   for(int loop = 0; loop < stone_num; loop++){
                       if(pan[location[i][0]][location[i][1]+loop] == stone)
                           count1++;
                   }
                   for(int loop = 0; loop < stone_num; loop++){
                       if(pan[location[i][0]][location[i][1]-loop] == stone)
                           count2++;
                   }

                   if(count1 != stone_num  && count2 != stone_num){
                       tr_y = 1;
                   }

                   if(pan[location[i][0]][location[i][1]+1] == 0 && pan[location[i][0]][location[i][1]-stone_num] == not_stone){

                       tr_y = 1;
                   }
                   if(pan[location[i][0]][location[i][1]+1] == not_stone && pan[location[i][0]][location[i][1]-stone_num] == 0){
                       //qDebug("y2하나 막힘");

                       tr_y = 1;
                   }
                   if(pan[location[i][0]][location[i][1]-1] == 0 && pan[location[i][0]][location[i][1]+stone_num] == not_stone){
                       //qDebug("y3하나 막힘");

                       tr_y = 1;
                   }
                   if(pan[location[i][0]][location[i][1]-1] == not_stone && pan[location[i][0]][location[i][1]+stone_num] == 0){
                       //qDebug("y4하나 막힘");

                       tr_y = 1;
                   }



                  if(tr_y == 0){
                      //qDebug(" -return y : %d   / last stone x : %d y : %d stone_num : %d", y, location[i][0], location[i][1], stone_num);
                      if(pan[location[i][0]][location[i][1]+1] == 0){
                          //qDebug("5");

                          //qDebug("testing : y : %d x : %d ",location[j][0]+1, location[j][1]);
                          MAX_x_PC[num][0] = location[i][0];
                          MAX_y_PC[num][0] = location[i][1]+1;
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                          pc_do_count[stone][num]++;
                          return 0;


                      } if(pan[location[i][0]][location[i][1]+stone_num] == 0){
                          for(int loop = 0; loop < stone_num; loop++){
                              if(pan[location[i][0]][location[i][1]+stone_num-loop] == stone){
                                  loop_buf++;
                              }
                          }
                          if(loop_buf == stone_num-1){

                              //qDebug("6");

                              MAX_x_PC[num][0] = location[i][0];
                              MAX_y_PC[num][0] = location[i][1]+stone_num;
                              //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                              pc_do_count[stone][num]++;
                              return 0;

                          }
                          loop_buf = 0;



                      } if(pan[location[i][0]][location[i][1]-1] == 0){
                          //qDebug("7");

                          //qDebug("testing : y : %d x : %d ",location[j][0]+1, location[j][1]);
                          MAX_x_PC[num][0] = location[i][0];
                          MAX_y_PC[num][0] = location[i][1]-1;
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                          pc_do_count[stone][num]++;
                          return 0;


                      }
                      if(pan[location[i][0]][location[i][1]-stone_num] == 0){
                          //qDebug("x  : %d  y : %d", location[i][0], location[i][1]-stone_num );
                          for(int loop = 0; loop < stone_num; loop++){
                              if(pan[location[i][0]][location[i][1]-stone_num+loop] == stone){
                                  loop_buf++;
                              }
                          }
                          if(loop_buf == stone_num-1){

                              //qDebug("8");

                              MAX_x_PC[num][0] = location[i][0];
                              MAX_y_PC[num][0] = location[i][1]-stone_num;
                              //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                              pc_do_count[stone][num]++;
                              return 0;

                          }
                          loop_buf = 0;



                      }
                  }
               }else //qDebug("entering in y fail");
               //qDebug("dia1");

               if(dia1==stone_num){
                   //qDebug("dia1진입");

                   int count1 = 0, count2 = 0; //막혀있는걸 확인하는 스위치부분
                   for(int loop = 0; loop < stone_num; loop++){
                       if(pan[location[i][0]+loop][location[i][1]+loop] == stone)
                           count1++;
                   }
                   for(int loop = 0; loop < stone_num; loop++){
                       if(pan[location[i][0]-loop][location[i][1]-loop] == stone)
                           count2++;
                   }

                   if(count1 != stone_num  && count2 != stone_num){
                       tr_dia1 = 1;
                   }

                   if(pan[location[i][0]+1][location[i][1]+1] == 0 && pan[location[i][0]-stone_num][location[i][1]-stone_num] == not_stone){
                       //qDebug("d11하나 막힘");

                       tr_dia1 = 1;
                   }
                   if(pan[location[i][0]+1][location[i][1]+1] == not_stone && pan[location[i][0]-stone_num][location[i][1]-stone_num] == 0){
                       //qDebug("d12하나 막힘");

                       tr_dia1 = 1;
                   }
                   if(pan[location[i][0]-1][location[i][1]-1] == 0 && pan[location[i][0]+stone_num][location[i][1]+stone_num] == not_stone){
                       //qDebug("d13하나 막힘");

                       tr_dia1 = 1;
                   }
                   if(pan[location[i][0]-1][location[i][1]-1] == not_stone && pan[location[i][0]+stone_num][location[i][1]+stone_num] == 0){
                       //qDebug("확인해봐 x: %d y: %d   x2: %d  y1:  %d",location[i][0]-1, location[i][1]-1,  location[i][0]-stone_num,location[i][1]-stone_num);
                       //qDebug("d14하나 막힘");

                       tr_dia1 = 1;
                   }


                  if(tr_dia1 == 0){
                      //qDebug(" -return dia1 : %d   / last stone x : %d y : %d stone_num : %d", dia1, location[i][0], location[i][1], stone_num);
                      if(pan[location[i][0]+1][location[i][1]+1] == 0){

                          //qDebug("9");

                          MAX_x_PC[num][0] = location[i][0]+1;
                          MAX_y_PC[num][0] = location[i][1]+1;
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                          pc_do_count[stone][num]++;
                          return 0;


                      } if(pan[location[i][0]-stone_num][location[i][1]-stone_num] == 0){
                          for(int loop = 0; loop < stone_num; loop++){
                              if(pan[location[i][0]-stone_num+loop][location[i][1]-stone_num+loop] == stone){
                                  loop_buf++;
                              }
                          }
                          if(loop_buf == stone_num-1){
                              //qDebug("10");


                              MAX_x_PC[num][0] = location[i][1]-stone_num;
                              MAX_y_PC[num][0] = location[i][0]-stone_num;
                              //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                              pc_do_count[stone][num]++;
                              return 0;

                          }
                          loop_buf = 0;



                      } if(pan[location[i][0]-1][location[i][1]-1] == 0){
                          //qDebug("11");

                          MAX_x_PC[num][0] = location[i][0]-1;
                          MAX_y_PC[num][0] = location[i][1]-1;
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                          pc_do_count[stone][num]++;
                          return 0;


                      } if(pan[location[i][0]+stone_num][location[i][1]+stone_num] == 0){
                          for(int loop = 0; loop < stone_num; loop++){
                              if(pan[location[i][0]+stone_num-loop][location[i][1]+stone_num-loop] == stone){
                                  loop_buf++;
                              }
                          }
                          if(loop_buf == stone_num-1){
                              //qDebug("12");

                              MAX_x_PC[num][0] = location[i][0]+stone_num;
                              MAX_y_PC[num][0] = location[i][1]+stone_num;
                              //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                              pc_do_count[stone][num]++;
                              return 0;



                          }
                          loop_buf = 0;



                      }
                  }
               }else //qDebug("entering in dia1 fail");
               //qDebug("dia2확인");

               if(dia2==stone_num){
                   //qDebug("dia2진입");

                   int count1 = 0, count2 = 0; //막혀있는걸 확인하는 스위치부분
                   for(int loop = 0; loop < stone_num; loop++){
                       if(pan[location[i][0]+loop][location[i][1]-loop] == stone)
                           count1++;
                   }
                   for(int loop = 0; loop < stone_num; loop++){
                       if(pan[location[i][0]-loop][location[i][1]+loop] == stone)
                           count2++;
                   }

                   if(count1 != stone_num  && count2 != stone_num){
                       tr_dia2 = 1;
                   }


                   if(pan[location[i][0]-1][location[i][1]+1] == 0 && pan[location[i][0]+stone_num][location[i][1]-stone_num] == not_stone){
                       //qDebug("d21하나 막힘");

                       tr_dia2 = 1;

                   }
                   if(pan[location[i][0]-1][location[i][1]+1] == not_stone && pan[location[i][0]+stone_num][location[i][1]-stone_num] == 0){
                       //qDebug("d22하나 막힘");

                       tr_dia2 = 1;
                   }
                   if(pan[location[i][0]+1][location[i][1]-1] == 0 && pan[location[i][0]-stone_num][location[i][1]+stone_num] == not_stone){
                       //qDebug("d23하나 막힘");

                       tr_dia2 = 1;
                   }
                   if(pan[location[i][0]+1][location[i][1]-1] == not_stone && pan[location[i][0]-stone_num][location[i][1]+stone_num] == 0){
                       //qDebug("d24하나 막힘");

                       tr_dia2 = 1;
                   }



                 if(tr_dia2 == 0){
                     //qDebug(" -return dia2 : %d   / last stone x : %d y : %d stone_num : %d", dia2, location[i][0], location[i][1], stone_num);

                     if(pan[location[i][0]-1][location[i][1]+1] == 0){
                         //qDebug("13");

                          MAX_x_PC[num][0] = location[i][0]-1;
                          MAX_y_PC[num][0] = location[i][1]+1;
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                          pc_do_count[stone][num]++;
                          return 0;



                      } if(pan[location[i][0]+stone_num][location[i][1]-stone_num] == 0){
                         for(int loop = 0; loop < stone_num; loop++){
                             if(pan[location[i][0]+stone_num-loop][location[i][1]-stone_num+loop] == stone){
                                 loop_buf++;
                             }
                         }
                         if(loop_buf == stone_num-1){
                             //qDebug("14");

                              MAX_x_PC[num][0] = location[i][0]+stone_num;
                              MAX_y_PC[num][0] = location[i][1]-stone_num;
                              //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                              pc_do_count[stone][num]++;
                              return 0;

                         }

                         loop_buf = 0;


                      } if(pan[location[i][0] +1][location[i][1]-1] == 0){
                         //qDebug("15");

                          MAX_x_PC[num][0] = location[i][0]+1;
                          MAX_y_PC[num][0] = location[i][1]-1;
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                          pc_do_count[stone][num]++;
                          return 0;


                      }if(pan[location[i][0] -stone_num][location[i][1]+stone_num] == 0){

                         for(int loop = 0; loop < stone_num; loop++){
                             if(pan[location[i][0] -stone_num+loop][location[i][1]+stone_num-loop] == stone){
                                 loop_buf++;
                             }
                         }

                         if(loop_buf == stone_num-1){
                              //qDebug("16");

                              MAX_x_PC[num][0] = location[i][0]-stone_num;
                              MAX_y_PC[num][0] = location[i][1]+stone_num;
                              //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                              pc_do_count[stone][num]++;
                              return 0;

                         }
                         loop_buf = 0;


                      }
                 }else
                 {
                     //qDebug("entering in dia2 fail");
                 }

               }


           }

            x = 0; y = 0; dia1 = 0; dia2 = 0;
            tr_x = 0, tr_y = 0, tr_dia1 = 0, tr_dia2 = 0;

        }
    }
    return -1;

}
int MainWindow::PC_DO_CHECK(int stone, int num) //각각의 함수를 호출하여 돌을 두는 위치 확인하는 함수
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int result = 0;
    //stone = ((stone == 2)? 1 : 2);
    int not_stone = ((stone == 2)? 1 : 2);
    //qDebug("공격");
    result = Think_do_somewhere_for_five(stone, num, 5, 5); //사이에 돌을 두면 5개가 되는것 확인, 공격
    if(result == 0) return 0;
    result = Think_do(stone, num, 4, 4);  //4개 공격
    if(result == 0) return 0;


    for(int i = 4; i > 1; i--){ //수비
        if(i == 4)
        {
            result = Think_do_somewhere_for_five(not_stone, num, i+1, i+1); //사이에 돌을 두면 5개가 되는것 수비
            if(result == 0) return 0;
        }



        if(i > 2)
        {


            if(i >= 3){ //수비할 것을 어느정도 하면 공격
                result = Think_do_not(stone, not_stone, num, i, i);  //i개 공격
                if(result == 0) return 0;
                //qDebug("aaa");

                result = Think_do_somewhere(stone, num, i+1, i+1); //사이에 돌을 두면 4개가 되는것중 양쪽이 뚫려 있는 것 확인
                if(result == 0) return 0;
                //qDebug("aaa");

            }

            result = Think_do_not(not_stone, stone, num, i, i);  //i개 수비
            if(result == 0) return 0;
            //qDebug("aaa");

            result = Think_do_somewhere(not_stone, num, i+1, i+1); //사이에 돌을 두면 i+1개가 되는것중 양쪽이 뚫려 있는 것 확인
            if(result == 0) return 0;
            //qDebug("aaa");


            result = Think_do_somewhere_left(not_stone, num, i+1, i+1);
            if(result == 0) return 0;
            //qDebug("aaa");

            result = Think_do_somewhere_right(not_stone, num, i+1, i+1);
            if(result == 0) return 0;
            //qDebug("aaa");

        }
        result = Think_do_not(not_stone, stone, num, i, i);  //i개 수비
        if(result == 0) return 0;
        //qDebug("aaa");

        result = Think_do(not_stone, num, i, i);  //i개 수비
        if(result == 0) return 0;
        //qDebug("aaa");


    }
    for(int i = 4; i > 0; i--){ //공격
        if(i == 4){  // 자신의 돌5개를 놓아 게임을 끝낼 경우 자신의 점수가 상대방보다 클 경우에만 5개를
            if(score[stone]+20 > score[not_stone])
            {
                result = Think_do_somewhere_for_five(stone, num, i+1, i+1); //사이에 돌을 두면 5개가 되는것 공격
                if(result == 0) return 0;
                result = Think_do_not(stone, not_stone, num, i, i);  //i개 공격
                if(result == 0) return 0;
            }


        }else
        {
            result = Think_do_not(stone, not_stone, num, i, i);  //i개 공격
            if(result == 0) return 0;
        }

        if(i > 2)
        {
            result = Think_do_somewhere(stone, num, i+1, i+1); //사이에 돌을 두면 4개가 되는것중 양쪽이 뚫려 있는 것 확인
            if(result == 0) return 0;
            result = Think_do_somewhere_left(stone, num, i+1, i+1);
            if(result == 0) return 0;
            result = Think_do_somewhere_right(stone, num, i+1, i+1);
            if(result == 0) return 0;
        }
        result = Think_do(stone, num, i, i);  //i개 공격
        if(result == 0) return 0;
    }
    //stone = ((stone == 2)? 1 : 2);


    return 0;
}
int MainWindow::PC_DO_CHECK_SCORE(int stone) //돌을 둘 위치를 확인할때 각각의 상황에따라 점수를 다르게 부여하여 연산깊이를 줄이는 함수
{
    int result = 0;
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    for(int stone_num = 4; stone_num > 1; stone_num--)
        for(int i = 0; i < stone_count; i++){
           if(pan[location[i][0]][location[i][1]] == stone){
             ////qDebug("*Find sameone at (%d)st loop", i);

              for(int j = 0; j < stone_count; j++){
                //qDebug("checking at (%d) x : %d  y : %d => %d (x:%d y:%d)", j, location[j][0], location[j][1], pan[location[j][0]][location[j][1]], location[i][0], location[i][1]);

                 if((location[j][0]-location[i][0]) < stone_num && location[j][1] == location[i][1] && (location[j][0]-location[i][0]) >= 0){ //[0]->x축 [1]은 y축/ y축은 같고 x축 값의 차이가 5 이내 일때
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                          x++;
                         //qDebug("---------- x-> %d", x);

                    }//다른조건에도 수정
                 }


                 if((location[j][1]-location[i][1]) < stone_num && location[j][0] == location[i][0] && (location[j][1]-location[i][1]) >= 0 ){
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                        y++;
                       //qDebug("---------- y-> %d   stone_num : %d  i - j : %d,  j - i  : %d ", y, stone_num, (location[i][1]-location[j][1]), (location[j][1]-location[i][1]));

                    }
                 }

                 if((location[j][0]-location[i][0])==(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (기준y) - (비교y)일때
                    if((location[j][0]-location[i][0]) < stone_num && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                        if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                            dia1++;
                           //qDebug("---------- dia1-> %d   stone_num : %d ", dia1, stone_num);

                        }
                    }
                 }

                if((location[j][0]-location[i][0])==(-1)*(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (-1)*(기준y) - (비교y)일때(x는 증가 y는 감소)
                    if((location[j][0]-location[i][0]) < stone_num  && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                        if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                            dia2++;
                           //qDebug("---------- dia2-> %d", dia2);

                        }
                    }
                 }

///////////////////////////////////////////////////////////////
                //////////////////////////////////////
                ///
                /// //////////////
                ///
               if(x==stone_num){
                   if(MAX_length <= x){
                       //qDebug("MAX ++!!!");
                       MAX_count++;
                       MAX_length = x;
                   }
                  //qDebug(" -return x : %d   / last stone x : %d y : %d stone_num : %d", x, location[j][0], location[j][1], stone_num);
                  if(pan[location[j][0]+1][location[j][1]] == 0){
                      //return x;
                      result += pow(10, x);
                  }else if(pan[location[j][0]+stone_num][location[j][1]] == 0){
                      result += pow(10, x);

                      //return x;
                  }else if(pan[location[j][0]-1][location[j][1]] == 0){
                      //return x;
                      result += pow(10, x);

                  }else if(pan[location[j][0]-stone_num][location[j][1]] == 0){
                      //return x;
                      result += pow(10, x);

                  }
               }
               if(y==stone_num){

                   if(MAX_length <= y){
                       //qDebug("MAX ++!!!");

                       MAX_count++;
                       result += pow(10, y);
                   }
                  //qDebug(" -return y : %d   / last stone x : %d y : %d stone_num : %d ", y, location[j][0], location[j][1], stone_num);
                  if(pan[location[j][0]][location[j][1]+1] == 0){
                      result += pow(10, y);

                      //return y;
                  }else if(pan[location[j][0]][location[j][1]+stone_num] == 0){
                      result += pow(10, y);

                      //return y;
                  }else if(pan[location[j][0]][location[j][1]-1] == 0){
                      result += pow(10, y);

                      //return y;
                  }else if(pan[location[j][0]][location[j][1]-stone_num] == 0){
                      result += pow(10, y);

                      //return y;
                  }
               }
               if(dia1==stone_num){
                   if(MAX_length <= dia1){
                       //qDebug("MAX ++!!!");

                       MAX_count++;
                       MAX_length = dia1;
                   }
                  //qDebug(" -return dia1 : %d   / last stone x : %d y : %d  stone_num : %d", dia1, location[j][0], location[j][1], stone_num);
                  if(pan[location[j][0]+1][location[j][1]+1] == 0){
                      result += pow(10, dia1);

                      //return dia1;
                  }else if(pan[location[j][0]-stone_num][location[j][1]-stone_num] == 0){
                      result += pow(10, dia1);

                      //return dia1;
                  }else if(pan[location[j][0]-1][location[j][1]-1] == 0){
                      result += pow(10, dia1);

                      //return dia1;
                  }else if(pan[location[j][0]+stone_num][location[j][1]+stone_num] == 0){
                      result += pow(10, dia1);

                      //return dia1;
                  }
               }
               if(dia2==stone_num){
                 //qDebug(" -return dia2 : %d   / last stone x : %d y : %d stone_num : %d", dia2, location[j][0], location[j][1], stone_num);
                 if(MAX_length <= dia2){
                     //qDebug("MAX ++!!!");

                     MAX_count++;
                     MAX_length = dia2;
                 }

                 if(pan[location[j][0]-1][location[j][1]+1] == 0){
                     result += pow(10, dia2);

                     //return dia2;
                  }else if(pan[location[j][0]-1][location[j][1]+1] == 0){
                     result += pow(10, dia2);

                     //return dia2;
                  }else if(pan[location[j][0] +1][location[j][1]-1] == 0){
                     result += pow(10, dia2);

                     //return dia2;
                  }if(pan[location[j][0] -stone_num][location[j][1]+stone_num] == 0){
                     result += pow(10, dia2);

                     //return dia2;
                  }
               }

            }
            x = 0; y = 0; dia1 = 0; dia2 = 0;
        }
    }
    return result;
}

int MainWindow::PC_DO(int stone, int depth)//깊이에 맞게 돌을 둘 곳을  연산하는 함수
{
    int not_stone = ((stone == 2)? 1 : 2);
    int final_x = 0, final_y = 0;
    int MAX = 0, temp = 0;
    int MAX_player = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 50; j++){
            pc_do_count[i][j] = 0;

        }
    }
    //qDebug("playe : %d stone_count : %d", play, stone_count);
    if(play == 2 && stone_count < 2){
        //qDebug("black computer first");
        pan_btn[location[0][0]][location[0][1]+1]->click();
        return 0;
    }

    MAX_count = 0;
    MAX_length = 0;
    int MAX_length_temp = 0;
    int MAX_count_temp = 0;
    int num = 0;


    PC_DO_CHECK(stone, 0);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 50; j++){
        }
    }




    int player_prev = PC_DO_CHECK_SCORE(not_stone);
    int temp1 = temp;
    int temp2 = player_prev;
    for(int j = 0; j < 100; j++){
    }
  //  MAX_x_PC[num][0] = location[i][0]-stone_num;

    int pc_remove_x, pc_remove_y;
    int player_remove_x, player_remove_y;

    final_y = MAX_x_PC[0][0];
    final_x = MAX_y_PC[0][0];


    pan_btn[final_x][final_y]->click();


    MAX_x_PC[num][0] = 0;
    MAX_y_PC[num][0] = 0;



    return 0;
}



MainWindow::~MainWindow()
{

}
