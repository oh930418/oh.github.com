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
        //cout<<"Load Error"<<endl;
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

    //QLabel *IbView = new QLabel(this);
    IbView = new QLabel(this);
    IbView->setPixmap(*buffer);
    IbView->resize(buffer->width(),buffer->height());
    IbView->move(0,0);
    IbView->show();


    help = new QPushButton("help", this);
   // help->setVisible(false);
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

    //QIcon btn_image("C:\\pan_btn.jpg");


    for(int i = 0; i < 19; i++){  //바둑판 초기화
        for(int j = 0; j < 19; j++){
            pan_btn[i][j] = new QPushButton("", this);
            pan_btn[i][j]->setIcon(QIcon("C:\\pan_btn.jpg"));
            pan_btn[i][j]->setIconSize(QSize(30,30));
            pan_btn[i][j]->setGeometry(i*30+30, j*30+160, 30, 30);
            pan_btn[i][j]->setVisible(false);
  //        pan_btn[i][j]->setPaletteBackgroundPixmap(Pixmap)
            //pan_btn[i][j]->setMask(maskedRegion);
            pan_btn[i][j]->setFlat(true);
            connect(pan_btn[i][j], SIGNAL(clicked(bool)), this, SLOT(pan_c()));
            ////qDebug("%d  %s\n", ((19*i)+j), (QString)((19*i)+j));
        }
    }

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(btn_c()));
    connect(btn2, SIGNAL(clicked(bool)), this, SLOT(Choice_stone()));
    connect(btn3, SIGNAL(clicked(bool)), this, SLOT(PLAY_start()));
    connect(btn_W, SIGNAL(clicked(bool)), this, SLOT(PLAY_start()));
    connect(btn_B, SIGNAL(clicked(bool)), this, SLOT(PLAY_start()));
    connect(help, SIGNAL(clicked(bool)), this, SLOT(Help()));



    //label = new QLabel();
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
       //qDebug("not yet  %d", stone_count);

   }else
   {
       PC_DO_CHECK(stone, 0);  //컴퓨터가 돌을 두는 함수 호출
       int final_y = MAX_x_PC[0][0];
       int final_x = MAX_y_PC[0][0];
       //qDebug("click!!!  x : %d  y : %d  (", final_x, final_y);
        pan_btn[final_x][final_y]->click();  //입력받은 위치에 바둑돌 두기
   }
}

void MainWindow::pan_c() //바둑판의 버튼이 눌리면 실행되는 함수
{
    if(first == 0){
        stone = 1;
        //qDebug("stone = 1");
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
                ////qDebug("[%d][%d]버튼 클릭 \n", i, j);
                 IbView->move(i*30+30, j*30+160);
                 IbView->show();
                 //pan_btn[i][j]->setFlat(true);
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
                //else
                    //continue;
                 //pan_btn[i][j]->setEnabled(false);
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
                    //else
                        //continue;
                     //pan_btn[i][j]->setEnabled(false);
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
            //qDebug("x : %d, y: %d ", location[num1][0], location[num1][1]);

            for(int i = 0; i < 5; i++){  //연속된 돌에 이미지 변경
                //이미지 변경
                QImage img("C:\\black2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num1][1]*30+30, location[num1][0]*30+160+(i*30));
                IbView->show();
                //qDebug("변경중");
            }
        }
        if(how == 2)  //y값 증가로 연속된경우
        {
            //qDebug("x : %d, y: %d ", location[num1][0], location[num1][1]);

            for(int i = 0; i < 5; i++){ //연속된 돌에 이미지 변경
                //이미지 변경
                QImage img("C:\\black2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num1][1]*30+30+(i*30), location[num1][0]*30+160);
                IbView->show();
                //qDebug("변경중");
            }
        }
        if(how == 3) //대각선1의 경우
        {
            //qDebug("x : %d, y: %d ", location[num1][0], location[num1][1]);

            for(int i = 0; i < 5; i++){ //연속된 돌 이미지 변
                //이미지 변경
                QImage img("C:\\black2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num1][1]*30+30+(i*30), location[num1][0]*30+160+(i*30));
                IbView->show();
                //qDebug("변경중");
            }
        }
        if(how == 4)//대각선2의경우
        {
            //qDebug("x : %d, y: %d ", location[num1][0], location[num1][1]);

            for(int i = 0; i < 5; i++){  //연속된 돌의 이미지 변경
                //이미지 변경
                QImage img("C:\\black2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num1][1]*30+30-(i*30), location[num1][0]*30+160+(i*30));
                IbView->show();
                //qDebug("변경중");
            }
        }

    }else if(num2 != -1){ //2번에 돌을 다섯개 두었을 경우
        how = num2%10;
        num2 /= 10;

        if(how == 1)
        {
            //qDebug("x : %d, y: %d ", location[num2][0], location[num2][1]);

            for(int i = 0; i < 5; i++){
                //이미지 변경
                QImage img("C:\\white2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num2][1]*30+30, location[num2][0]*30+160+(i*30));
                IbView->show();
                //qDebug("변경중");
            }
        }
        if(how == 2)
        {
            //qDebug("x : %d, y: %d ", location[num2][0], location[num2][1]);

            for(int i = 0; i < 5; i++){
                //이미지 변경
                QImage img("C:\\white2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num2][1]*30+30+(i*30), location[num2][0]*30+160);
                IbView->show();
                //qDebug("변경중");
            }
        }
        if(how == 3)
        {
            //qDebug("x : %d, y: %d ", location[num2][0], location[num2][1]);

            for(int i = 0; i < 5; i++){
                //이미지 변경
                QImage img("C:\\white2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num2][1]*30+30+(i*30), location[num2][0]*30+160+(i*30));
                IbView->show();
                //qDebug("변경중");
            }
        }
        if(how == 4)
        {
            //qDebug("x : %d, y: %d ", location[num2][0], location[num2][1]);

            for(int i = 0; i < 5; i++){
                //이미지 변경
                QImage img("C:\\white2.png");
                QPixmap buf = QPixmap::fromImage(img);
                IbView = new QLabel(this);
                IbView->setPixmap(buf);
                IbView->resize(buf.width(),buf.height());

                IbView->move(location[num2][1]*30+30-(i*30), location[num2][0]*30+160+(i*30));
                IbView->show();
                //qDebug("변경중");
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
        //cout<<"Load Error"<<endl;
    }
   // QLabel *IbView = new QLabel(this);
    IbView->setPixmap(*buffer);
    IbView->resize(buffer->width(),buffer->height());
    IbView->move(0,0);
    IbView->show();

    //btn2 = new QPushButton("버튼2", this);

   ////qDebug("aaa\n");

    //



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
       ////qDebug("white 선택 \n");

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
       //qDebug("black 선택 play : %d pc_s : %d\n", play, pc_s);
    }

    stone = p1_s;



    str1 = "black's score : " + buf.setNum(score[1]);

    l1 = new QLabel(str1, this);

    str1 = "white's score : " + buf.setNum(score[2]);

    l2 = new QLabel(str1, this);
    ////qDebug("%s  %s  %d  %d",str1, str2, score[1], score[2]);
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

////////////////////////////////////////////////////////////
/// \brief MainWindow::~MainWindow
///
/// ////////////////////////////////////////////////////////
///
///
///
///

void MainWindow::Think_Depth(int depth, int pc)  //연산의 깊이에 따라 컴퓨터가 돌을 두는 함수
{

    CHECK_SCORE(pc_s);
    CHECK_SCORE(p1_s);
    int not_stone = ((stone == 2)? 1 : 2);

    prev_score1 = score[stone]; //최고점수 확인 후 점수 복귀를 위한 변수
    prev_score2 = score[not_stone]; //최고점수 확인 후 점수 복귀를 위한 변수

    PC_DO(pc, depth);
    //pan_btn[MAX_x_PC[0]][MAX_x_PC[0]]->click(); //x,y 변경해야할수도있음!!!!!!!!!!!
   ////qDebug("PC_DO end!!!   ->  x: %d   y: %d", MAX_x_PC[0], MAX_y_PC[0]);

   ////qDebug("0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8");
    for(int i = 0; i < 19; i++){
       ////qDebug("%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d. (%d)",pan[i][0],pan[i][1],pan[i][2],pan[i][3],pan[i][4],pan[i][5],pan[i][6],pan[i][7],pan[i][8],pan[i][9],pan[i][10],pan[i][11],pan[i][12],pan[i][13],pan[i][14],pan[i][15],pan[i][16],pan[i][17],pan[i][18], i);
    }
   ////qDebug("\n");

//    pan_btn[MAX_x_PC[0]][MAX_y_PC[0]]->click();
   /*
    int *pc_x = new int[depth];
    int *pc_y = new int[depth];
    int *player_x = new int[depth];
    int *player_y = new int[depth];

    int MAX_score = 0;
    int MAX_score_PC = 0;
    int MAX_score_PLAYER = 0;

    for(int i = 0; i < depth; i++){
       PC_DO(pc, pc_x[i], pc_y[i]);
       pan[pc_x[i]][pc_y[i]] = pc;

       PC_DO(p1_s, player_x[i], player_y[i]);
       pan[player_x[i]][player_y[i]] = (p1_s);
    }

    //*pan[pc_x[0]][pc_y[0]]에 돌을 두도록 추가!

    for(int i = 0; i < depth; i++){
       pan[pc_x[i]][pc_y[i]] = 0; // 복원
       pan[player_x[i]][player_y[i]] = 0; // 복원

    }

    */

}



int MainWindow::CHECK_SCORE(int stone)  //연속된 돌의 개수를 확인하며 점수를 확인하는 함수
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int x_2 = 0, y_2 = 0, dia1_2 = 0, dia2_2 = 0;
    int five = -1;

    for(int i = 0; i < stone_count; i++){
       ////qDebug("(%d)  : %d   x:%d y:%d", i, pan[location[i][0]][location[i][1]], location[i][0], location[i][1]) ;
    }
    score[stone] = 0;
    for(int i = 0; i < stone_count; i++){
       if(pan[location[i][0]][location[i][1]] == stone){
         ////qDebug("*Find sameone at (%d)st loop", i);

          for(int j = 0; j < stone_count; j++){
            ////qDebug("checking at (%d) x : %d  y : %d => %d (x:%d y:%d)", j, location[j][0], location[j][1], pan[location[j][0]][location[j][1]], location[i][0], location[i][1]);

             if((location[j][0]-location[i][0]) <= 4 && location[j][1] == location[i][1] && (location[j][0]-location[i][0]) >= 0){ //[0]->x축 [1]은 y축/ y축은 같고 x축 값의 차이가 5 이내 일때
                if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                      x++;
                     ////qDebug("---------- x-> %d", x);

                }
             }


             if((location[j][1]-location[i][1]) <= 4 && location[j][0] == location[i][0] && (location[j][1]-location[i][1]) >= 0 ){
                if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                    y++;
                   ////qDebug("---------- y-> %d", y);

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

       //////qDebug("one step end!");
 //연결된 돌의 개수 확인  5개연속일경우 20+30 = 50점 획득 , 4개연속일경우 30점 획득
       if(x == 5){
           if(pan[location[i][0]+5][location[i][1]] != stone){

                 playing = false;//게임종료
                score[stone] += 20;
               ////qDebug("(x) 40 plus! ");
                five = 1+(i*10);
           }
       }
       if(x == 4){  //---------------+인지 -인지 확인, 값 확인
          if(pan[location[i][0]+4][location[i][1]] != stone){
             score[stone] += 30;
            ////qDebug("(x) 10 plus! ");

          }
       }


       if(y == 5){
          playing = false;
          if(pan[location[i][0]][location[i][1]+5] != stone){
            score[stone] += 20;
           ////qDebug("(y) 30 plus! ");
            five = 2+(i*10);

          }

       }
       if(y == 4){
          if(pan[location[i][0]][location[i][1]+4] != stone){
             score[stone] += 30;
            ////qDebug("(y) 10 plus!  y: %d ", y);

          }
       }

       if(dia1 == 5){
           if(pan[location[i][0]+5][location[i][1]+5] != stone){

                playing = false;
                score[stone] += 20;
               ////qDebug("(dia1) 30 plus! ");

                five = 3+(i*10);

           }

       }
       if(dia1 == 4){
          if(pan[location[i][0]+4][location[i][1]+4] != stone){
             score[stone] += 30;
            ////qDebug("(dia1) 10 plus! ");

          }
       }


       if(dia2 == 5){
           if(pan[location[i][0]+5][location[i][1]-5] != stone){

                playing = false;
                score[stone] += 20;
               ////qDebug("(dia2) 30 plus! ");
                five = 4+(i*10);

           }

       }
       if(dia2 == 4){
          if(pan[location[i][0]+4][location[i][1]-4] != stone){
             score[stone] += 30;\
            ////qDebug("(dia2) 10 plus! ");

          }
       }

       ///

       if(x_2 == 5){
           if(pan[location[i][0]-5][location[i][1]] != stone){

                playing = false;//게임종료
                score[stone] += 20;
               ////qDebug("(x_2) 40 plus! ");
                five = i;

           }
       }
       if(x_2 == 4){  //---------------+인지 -인지 확인, 값 확인
          if(pan[location[i][0]-4][location[i][1]] != stone){
             score[stone] += 10;
            ////qDebug("(x_2) 10 plus! ");

          }
       }


       if(y_2 == 5){
           if(pan[location[i][0]][location[i][1]+5] != stone){

                playing = false;
                score[stone] += 20;
               ////qDebug("(y_2) 30 plus! ");
                five = i;

           }

       }
       if(y_2 == 4){
          if(pan[location[i][0]][location[i][1]+4] != stone){
             score[stone] += 30;
            ////qDebug("(y_2) 10 plus!  y: %d ", y);

          }
       }

       if(dia1_2 == 5){
           if(pan[location[i][0]+5][location[i][1]+5] != stone){

                playing = false;
                score[stone] += 20;
               ////qDebug("(dia1_2) 30 plus! ");
                five = i;

            }
       }
       if(dia1_2 == 4){
          if(pan[location[i][0]+4][location[i][1]+4] != stone){
             score[stone] += 30;
            ////qDebug("(dia1_2) 10 plus! ");

          }
       }


       if(dia2_2 == 5){
           if(pan[location[i][0]+5][location[i][1]-5] != stone){

                playing = false;
                score[stone] += 20;
               ////qDebug("(dia2_2) 30 plus! ");
                five = i;

           }

       }
       if(dia2_2 == 4){
          if(pan[location[i][0]+4][location[i][1]-4] != stone){
             score[stone] += 30;\
            ////qDebug("(dia2_2) 10 plus! ");

          }
       }





    //   return 점수;


       }
       else{
           continue;
       }
       ////qDebug("x : %d, y : %d, dia1 : %d, dia2 : %d", x, y, dia1, dia2);
    x = 0; y = 0; dia1 = 0; dia2 = 0;
    x_2 = 0; y_2 = 0; dia1_2 = 0; dia2_2 = 0;

    }

    return five;


}



int MainWindow::Think_do_somewhere(int stone, int num, int start, int end) //사이에 돌을 둘 경우 연속된 돌이 생기는 위치를 확인하는 함수/ 양쪽에 돌이 상대방 돌이 있을경우 돌을 두지 않음
{
    int x = 0, y = 0, dia1 = 0, dia2 = 0;
    int count = 0;
    //stone = ((stone == 2)? 1 : 2);
    int not_stone = ((stone == 2)? 1 : 2);
    //qDebug("Think_do_somewhere  :%d", start);

    for(int i = 0; i < 19; i++){
        for(int j = 0; j < 19; j++){  //바둑판 전체 확인
            x = 0, y = 0, dia1 = 0, dia2 = 0;

            if(pan[i][j] == 0){

                pan[i][j] = stone;

                for(int loop = (start*(-1))+1; loop <= start-1; loop++){  //각각의 범위에서 연속된 돌이 있을경우 변수값 증가

                    if(pan[i+loop][j] == stone)
                    {
                        x++;
                        //qDebug("x ++ %d", x);

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
                        //qDebug("dia1 ++ %d", dia1);

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
                        //qDebug("dia2 ++ %d", dia2);

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
                //qDebug(" value = %d  x: %d  y: %d  dia1: %d  dia2: %d", start, x, y, dia1, dia2);

                if(x == start || y == start || dia1 == start || dia2 == start)  //연속된 돌을 찾은경우 종료
                {
                    //qDebug(" value = %d  x: %d  y: %d  dia1: %d  dia2: %d", start, x, y, dia1, dia2);
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
    //stone = ((stone == 2)? 1 : 2);
    int not_stone = ((stone == 2)? 1 : 2);
    //qDebug("Think_do_somewhere_left  :%d", start);


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
                    //qDebug(" value = %d  x: %d  y: %d  dia1: %d  dia2: %d", start, x, y, dia1, dia2);
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
    //stone = ((stone == 2)? 1 : 2);
    int not_stone = ((stone == 2)? 1 : 2);
    ////qDebug("Think_mewhere_right  :%d", start);

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
                    //qDebug(" value = %d  x: %d  y: %d  dia1: %d  dia2: %d", start, x, y, dia1, dia2);
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

    //qDebug("0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8");
     for(int i = 0; i < 19; i++){
        //qDebug("%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d. (%d)",pan[i][0],pan[i][1],pan[i][2],pan[i][3],pan[i][4],pan[i][5],pan[i][6],pan[i][7],pan[i][8],pan[i][9],pan[i][10],pan[i][11],pan[i][12],pan[i][13],pan[i][14],pan[i][15],pan[i][16],pan[i][17],pan[i][18], i);
     }
    //qDebug("\n");

    //stone = ((stone == 2)? 1 : 2);
    //qDebug("Think_do_somewhere_for_five  :%d", start);
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
                    //qDebug(" value = %d  x: %d  y: %d  dia1: %d  dia2: %d  (%d, %d)", start, x, y, dia1, dia2 , i, j);

                }

                if(x == start || y == start || dia1 == start || dia2 == start)
                {
                    //qDebug(" value = %d  x: %d  y: %d  dia1: %d  dia2: %d  (%d, %d)", start, x, y, dia1, dia2 , i, j);
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
    //stone = ((stone == 2)? 1 : 2);
    int not_stone = ((stone == 2)? 1 : 2);

    for(int stone_num = start; stone_num >= end; stone_num--)  //매개변수로 입력받은 돌의 개수부터 end값까지 확인
        for(int i = 0; i < stone_count; i++){ // 현재 있는 돌만 확인
           if(pan[location[i][0]][location[i][1]] == stone){
             ////qDebug("*Find sameone at (%d)st loop", i);
              //qDebug("%d 개 do", start);
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
                       //qDebug("---------- y-> %d", y);

                    }
                 }

                 if((location[j][0]-location[i][0])==(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (기준y) - (비교y)일때
                    if((location[j][0]-location[i][0]) < stone_num && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                        if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                            dia1++;
                           //qDebug("---------- dia1-> %d", dia1);

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
               int loop_buf = 0;

               if(pan[location[i][0]][location[i][1]] != stone){ //그 위치의 돌이 같은색 아니면

                    continue;
               }

               if(x==stone_num){



                 //qDebug(" -return x : %d   / last stone x : %d y : %d stone_num : %d", x, location[i][0], location[i][1], stone_num);
                  if(pan[location[i][0]+1][location[i][1]] == 0){
                     ////qDebug("testing : y : %d x : %d ",location[j][0]+1, location[j][1]);
                      //qDebug("1");
                      MAX_x_PC[num][0] = location[i][0]+1;
                      MAX_y_PC[num][0] = location[i][1];
                      //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);
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
                          //qDebug("2");

                          MAX_x_PC[num][0] = location[i][0]+stone_num;
                          MAX_y_PC[num][0] = location[i][1];
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                          pc_do_count[stone][num]++;
                          return 0;

                      }
                      loop_buf = 0;



                  }
                  if(pan[location[i][0]-1][location[i][1]] == 0)
                  {
                      //qDebug("3");

                     ////qDebug("testing : y : %d x : %d ",location[j][0]+1, location[j][1]);
                      MAX_x_PC[num][0] = location[i][0]-1;
                      MAX_y_PC[num][0] = location[i][1];
                      //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

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
                          //qDebug("4");

                          MAX_x_PC[num][0] = location[i][0]-stone_num;
                          MAX_y_PC[num][0] = location[i][1];
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                          pc_do_count[stone][num]++;
                          return 0;

                      }
                      loop_buf = 0;




                  }

               }
               if(y==stone_num){
                 //qDebug(" -return y : %d   / last stone x : %d y : %d stone_num : %d", y, location[i][0], location[i][1], stone_num);
                  if(pan[location[i][0]][location[i][1]+1] == 0){
                      //qDebug("5");
                      //pan[location[i][0]][location[i][1]+1] = 10;

                     ////qDebug("testing : y : %d x : %d ",location[j][0]+1, location[j][1]);
                      MAX_x_PC[num][0] = location[i][0];
                      MAX_y_PC[num][0] = location[i][1]+1;
                      //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                      pc_do_count[stone][num]++;
                      return 0;


                  } if(pan[location[i][0]][location[i][1]+stone_num] == 0){
                      //




                     // pan[location[i][0]][location[i][1]+stone_num] = 100;
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
                      //pan[location[i][0]][location[i][1]-1] = 1000;

                     ////qDebug("testing : y : %d x : %d ",location[j][0]+1, location[j][1]);
                      MAX_x_PC[num][0] = location[i][0];
                      MAX_y_PC[num][0] = location[i][1]-1;
                      //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                      pc_do_count[stone][num]++;
                      return 0;


                  }
                  if(pan[location[i][0]][location[i][1]-stone_num] == 0){
                      //pan[location[i][0]][location[i][1]-stone_num] = 10000;
                      //qDebug("10000 is created(1)!");
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
               if(dia1==stone_num){
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
               if(dia2==stone_num){
                 //qDebug(" -return dia2 : %d   / last stone x : %d y : %d stone_num : %d", dia2, location[i][0], location[i][1], stone_num);

                 if(pan[location[i][0]-1][location[i][1]+1] == 0){
                     //qDebug("13");

                     // pan[location[i][0]-1][location[i][1]+1] = 10;
                      MAX_x_PC[num][0] = location[i][0]-1;
                      MAX_y_PC[num][0] = location[i][1]+1;
                      //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                      pc_do_count[stone][num]++;
                      return 0;


                  } if(pan[location[i][0]+stone_num][location[i][1]-stone_num] == 0){
                     //pan[location[i][0]+stone_num][location[i][1]-stone_num] = 100;
                     for(int loop = 0; loop < stone_num; loop++){
                         if(pan[location[i][0]+stone_num-loop][location[i][1]-stone_num+loop] == stone){
                             loop_buf++;
                         }
                     }
                     if(loop_buf == stone_num-1){
                         //qDebug("14");

                        //  pan[location[i][0]+stone_num][location[i][1]-stone_num] = 1000;
                          MAX_x_PC[num][0] = location[i][0]+stone_num;
                          MAX_y_PC[num][0] = location[i][1]-stone_num;
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

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
                     //pan[location[i][0]-stone_num][location[i][1]+stone_num] = 10000;
                     //qDebug("10000 is created(2)!");

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
    //stone = ((stone == 2)? 1 : 2);
   not_stone = ((stone == 2)? 1 : 2);

    for(int stone_num = start; stone_num >= end; stone_num--)
        for(int i = 0; i < stone_count; i++){
           if(pan[location[i][0]][location[i][1]] == stone){
             ////qDebug("*Find sameone at (%d)st loop", i);
               //qDebug("%d개  (if- @000 do not)", start);

              for(int j = 0; j < stone_count; j++){
                //qDebug("checking at (%d) x : %d  y : %d => %d (x:%d y:%d)", j, location[j][0], location[j][1], pan[location[j][0]][location[j][1]], location[i][0], location[i][1]);
                tr_x = 0, tr_y = 0, tr_dia1 = 0, tr_dia2 = 0;
                 if((location[j][0]-location[i][0]) < stone_num && location[j][1] == location[i][1] && (location[j][0]-location[i][0]) >= 0){ //[0]->x축 [1]은 y축/ y축은 같고 x축 값의 차이가 5 이내 일때
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                          x++;
                        // //qDebug("---------- x-> %d", x);

                    }//다른조건에도 수정
                 }


                 if((location[j][1]-location[i][1]) < stone_num && location[j][0] == location[i][0] && (location[j][1]-location[i][1]) >= 0 ){
                    if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                        y++;
                       //qDebug("---------- y-> %d", y);

                    }
                 }

                 if((location[j][0]-location[i][0])==(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (기준y) - (비교y)일때
                    if((location[j][0]-location[i][0]) < stone_num && (location[j][0]-location[i][0]) >= 0){//차이가 5이내 일때
                        if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                            dia1++;
                          // //qDebug("---------- dia1-> %d", dia1);

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
               int loop_buf = 0;

//               if(pan[location[i][0]][location[i][1]] != stone){ //그 위치의 돌이 같은색 아니면

//                    continue;
//               }

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
                        //qDebug("x1하나 막힘");
                        tr_x = 1;
                   }
                   if(pan[location[i][0]+1][location[i][1]] == not_stone && pan[location[i][0]-stone_num][location[i][1]] == 0){
                      //qDebug("x2하나 막힘");

                       tr_x = 1;
                   }
                   if(pan[location[i][0]-1][location[i][1]] == 0 && pan[location[i][0]+stone_num][location[i][1]] == not_stone){
                       //qDebug("x3하나 막힘");

                       tr_x = 1;
                   }
                   if(pan[location[i][0]-1][location[i][1]] == not_stone && pan[location[i][0]+stone_num][location[i][1]] == 0){
                      // //qDebug("x4하나 막힘");

                       tr_x = 1;
                   }
                   //qDebug("x확인");

                  if( tr_x == 0){
                      //qDebug("x진입");

                      //qDebug(" -return x : %d   / last stone x : %d y : %d stone_num : %d", x, location[i][0], location[i][1], stone_num);
                      if(pan[location[i][0]+1][location[i][1]] == 0){
                         ////qDebug("testing : y : %d x : %d ",location[j][0]+1, location[j][1]);
                          //qDebug("1");
                          MAX_x_PC[num][0] = location[i][0]+1;
                          MAX_y_PC[num][0] = location[i][1];
                          //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);
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
                              //qDebug("2");

                              MAX_x_PC[num][0] = location[i][0]+stone_num;
                              MAX_y_PC[num][0] = location[i][1];
                              //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                              pc_do_count[stone][num]++;
                              return 0;

                          }
                          loop_buf = 0;



                      }
                      if(pan[location[i][0]-1][location[i][1]] == 0)
                      {
                          //qDebug("3");

                         ////qDebug("testing : y : %d x : %d ",location[j][0]+1, location[j][1]);
                          MAX_x_PC[num][0] = location[i][0]-1;
                          MAX_y_PC[num][0] = location[i][1];
                         //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

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
                              //qDebug("4");

                              MAX_x_PC[num][0] = location[i][0]-stone_num;
                              MAX_y_PC[num][0] = location[i][1];
                             //qDebug("(x : %d)  (y : %d)", MAX_x_PC[num][0], MAX_y_PC[num][0]);

                              pc_do_count[stone][num]++;
                              return 0;

                          }

                          loop_buf = 0;



                      }
                  }
               }else //qDebug("entering in x fail");
               //qDebug("y확인");

               if(y==stone_num){
                   //qDebug("y진입");

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
                       //qDebug("하나 막힘");
                       tr_y = 1;
                   }

                   if(pan[location[i][0]][location[i][1]+1] == 0 && pan[location[i][0]][location[i][1]-stone_num] == not_stone){
                       //qDebug("y1하나 막힘");

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
  //  PC_DO_CHECK(not_stone, 0);
    int num = 0;


    PC_DO_CHECK(stone, 0);

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 50; j++){
             //qDebug("i : %d j : %d   pc : %d", i, j, pc_do_count[i][j]);
        }
    }




    int player_prev = PC_DO_CHECK_SCORE(not_stone);
    int temp1 = temp;
    int temp2 = player_prev;
    for(int j = 0; j < 100; j++){
      //  //qDebug(" pc do count-> x : %d  y : %d ", MAX_x_PC[0][j], MAX_y_PC[0][j]);
    }
  //  MAX_x_PC[num][0] = location[i][0]-stone_num;

    int pc_remove_x, pc_remove_y;
    int player_remove_x, player_remove_y;


   ///
   ///
   ///
   ///-----------------------이후의 코드는 -------------------------
   /// 연산 깊이를 조절에따라 최적의 위치에 돌을
   /// 두도록 하는 코드이나 지나친 cpu연산으로
   /// 실행이 불가능하여 다른 방식으로 구현하면서 사용하지 않는 코드입니다.
   /// -----------------------------------------------------------
   ///
    //qDebug("\n\n ------------------****pc turn****----------------------");
//    for(int i = 0; i < 5; i++){
//        if(i>=pc_do_count[stone][0]){
//            //qDebug("i : %d  count :%d  break", i, pc_do_count[stone][0]);
//            break;
//        }
//      //  //qDebug("i : %d  count :%d", i, pc_do_count[stone][0]);

//        //qDebug("pc ->(%d) x: %d y : %d ", i, MAX_x_PC[0][i], MAX_y_PC[0][i]);

//        if(pan[MAX_x_PC[0][i]][MAX_y_PC[0][i]] == 0){
//            pan[MAX_x_PC[0][i]][MAX_y_PC[0][i]] = stone;
//            pc_remove_x = MAX_x_PC[0][i];
//            pc_remove_y = MAX_y_PC[0][i];
//            location[stone_count][0] = MAX_x_PC[0][i];
//            location[stone_count][1] = MAX_y_PC[0][i];
//            stone_count++;
//        }else {
//            continue;
//        }


//        int MAX_length_temp_pc = 0, MAX_length_temp_player = 0, MAX_count_temp_pc = 0, MAX_count_temp_player = 0;
//        int temp_pc = 0, temp_player = 0;

//        int pc_temp = PC_DO_CHECK_SCORE(stone);

//        temp1 = pc_temp - temp1;

//        if(MAX < temp1){
//            MAX = temp1;
//            //qDebug("change!!! ");
//            final_y = MAX_x_PC[0][i];
//            final_x = MAX_y_PC[0][i];
//        }

//        MAX_length_temp_pc = MAX_length;
//        MAX_count_temp_pc = MAX_count;
//        temp_pc = temp;
//        //qDebug("(PC)  MAX_length : %d temp : %d", MAX_length, MAX_length_temp);
//        //qDebug("MAX_count : %d temp : %d", MAX_count, MAX_count_temp);
//        //qDebug("MAX : %d temp : %d", MAX, temp );

///*
//        if(MAX_length_temp_pc < MAX_length){
//            MAX_length_temp_pc = MAX_length;
//            //qDebug("change!!! ");
//            final_y = MAX_x_PC[0][i];
//            final_x = MAX_y_PC[0][i];
//        }
//        if(MAX_length_temp == MAX_length){
//            if(MAX_count_temp < MAX_count  || MAX < temp){
//                MAX = temp;
//                MAX_length_temp = MAX_length;
//                MAX_count_temp = MAX_count;
//                //qDebug("change!!! ");
//                final_y = MAX_x_PC[0][i];
//                final_x = MAX_y_PC[0][i];
//            }
//        }

//        */


//        MAX_count = 0;
//        MAX_length = 0;



//        for(int j = 0; j < 5; j++){
//            if(j>=pc_do_count[not_stone][0]){
//                //qDebug("i : %d  count :%d  break", i, pc_do_count[stone][0]);
//             //   break;
//            }
//         //   //qDebug("i : %d  count :%d", i, pc_do_count[not_stone][0]);

//            //qDebug("player ->(%d) x: %d y : %d ", j, MAX_x_PC[0][j], MAX_y_PC[0][j]);
//            for(int j = 0; j < 50; j++){
//                pc_do_count[not_stone][j] = 0;
//            }
//            PC_DO_CHECK(not_stone, 0);


//            if(pan[MAX_x_PC[0][j]][MAX_y_PC[0][j]] == 0){
//                pan[MAX_x_PC[0][j]][MAX_y_PC[0][j]] = not_stone;
//                player_remove_x = MAX_x_PC[0][i];
//                player_remove_y = MAX_y_PC[0][i];
//                location[stone_count][0] = MAX_x_PC[0][j];
//                location[stone_count][1] = MAX_y_PC[0][j];
//                stone_count++;
//            }else {
//                continue;
//            }
//            //qDebug("0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8    comparing...%d", i);

//             for(int i = 0; i < 19; i++){
//                //qDebug("%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d. (%d)",pan[i][0],pan[i][1],pan[i][2],pan[i][3],pan[i][4],pan[i][5],pan[i][6],pan[i][7],pan[i][8],pan[i][9],pan[i][10],pan[i][11],pan[i][12],pan[i][13],pan[i][14],pan[i][15],pan[i][16],pan[i][17],pan[i][18],i);
//             }
//            //qDebug("\n");

//            int player_temp = PC_DO_CHECK_SCORE(stone);

//            temp2 = player_temp - temp2;

//            if(MAX_player < temp2){
//                MAX = temp1;
//                //qDebug("change!!! ");
//                final_y = MAX_x_PC[0][i];
//                final_x = MAX_y_PC[0][i];
//            }

///*
//            temp = PC_DO_CHECK_SCORE(not_stone);
//            MAX_length_temp_player = MAX_length;
//            MAX_length_temp_player = MAX_count;
//            temp_player = temp;


//            //qDebug("(PLAYER)   MAX_length : %d temp : %d", MAX_length, MAX_length_temp);
//            //qDebug("MAX_count : %d temp : %d", MAX_count, MAX_count_temp);
//            //qDebug("MAX : %d temp : %d", MAX, temp );

//            if(MAX_length_temp < MAX_length){
//                MAX_length_temp = MAX_length;
//                //qDebug("change!!! ");
//                final_y = MAX_x_PC[0][i];
//                final_x = MAX_y_PC[0][i];
//            }
//            if(MAX_length_temp == MAX_length){
//                if(MAX_count_temp < MAX_count  || MAX < temp){
//                    MAX = temp;
//                    MAX_length_temp = MAX_length;
//                    MAX_count_temp = MAX_count;
//                    //qDebug("change!!! ");
//                    final_y = MAX_x_PC[0][i];
//                    final_x = MAX_y_PC[0][i];
//                }
//            }*/
//            MAX_count = 0;
//            MAX_length = 0;

//            pan[MAX_x_PC[0][j]][MAX_y_PC[0][j]] = 0;
//            //pan[player_remove_x][player_remove_y] = 0;
//            location[stone_count][0] = 0;
//            location[stone_count][1] = 0;
//            stone_count--;



//        }
//        MAX_count = 0;
//        MAX_length = 0;

//        //pan[MAX_x_PC[0][i]][MAX_y_PC[0][i]] = 0;
//        pan[pc_remove_x][pc_remove_y] = 0;

//        location[stone_count][0] = 0;
//        location[stone_count][1] = 0;
//        stone_count--;

//    }

    final_y = MAX_x_PC[0][0];
    final_x = MAX_y_PC[0][0];
    //qDebug("click!!!  x : %d  y : %d", final_x, final_y);


    pan_btn[final_x][final_y]->click();


    MAX_x_PC[num][0] = 0;
    MAX_y_PC[num][0] = 0;

    //qDebug("0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8");

     for(int i = 0; i < 19; i++){
        //qDebug("%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d. (%d)",pan[i][0],pan[i][1],pan[i][2],pan[i][3],pan[i][4],pan[i][5],pan[i][6],pan[i][7],pan[i][8],pan[i][9],pan[i][10],pan[i][11],pan[i][12],pan[i][13],pan[i][14],pan[i][15],pan[i][16],pan[i][17],pan[i][18],i);
     }
    //qDebug("\n");
    ////qDebug("%d  %d  ", MAX_x_PC[0], MAX_y_PC[0]);






    //MAX_x_PC[0] = 0;
    //MAX_y_PC[0] = 0;
    return 0;
}
/*
int MainWindow::PC_DO(int stone, int& MAX_x, int& MAX_y , int depth)//인덱스의 depth수정할것!!!
{
    // int MAX_x = -1, MAX_y = -1;
     int MAX_score = 0; //최고점수 확인
     int score_temp = 0;


     int not_stone = ((stone == 2)? 1 : 2);

     int sub = 0;

     int temp_score1 = 0;
     int temp_score2 = 0;



     int MAX_SUB = 0;

     int de1_x, de1_y, de2_x, de2_y, de3_x, de3_y, de4_x, de4_y, de5_x, de5_y;
     int end1, end2, end3, end4, end5;

     if(depth == 5){
         de1_x = -2;
         de1_y = -2;
         de2_x = -2;
         de2_y = -2;
         de3_x = -2;
         de3_y = -2;
         de4_x = -2;
         de4_y = -2;
         de5_x = -2;
         de5_y = -2;

         end1 = 2;
         end2 = 2;
         end3 = 2;
         end4 = 2;
         end5 = 2;

     }else if(depth == 4){
         de1_x = 19;
         de1_y = 19;
         de2_x = -2;
         de2_y = -2;
         de3_x = -2;
         de3_y = -2;
         de4_x = -2;
         de4_y = -2;
         de5_x = -2;
         de5_y = -2;

         end1 = 19;
         end2 = 2;
         end3 = 2;
         end4 = 2;
         end5 = 2;

     }else if(depth == 3){
         de1_x = -2;
         de1_y = -2;
         de2_x = -2;
         de2_y = -2;
         de3_x = -2;
         de3_y = -2;
         de4_x = -2;
         de4_y = -2;
         de5_x = -2;
         de5_y = -2;

         end1 = 2;
         end2 = 2;
         end3 = 2;
         end4 = 2;
         end5 = 2;

     }else if(depth == 2){
         de1_x = 19;
         de1_y = 19;
         de2_x = 19;
         de2_y = 19;
         de3_x = -2;
         de3_y = -2;
         de4_x = -2;
         de4_y = -2;
         de5_x = -2;
         de5_y = -2;

         end1 = 19;
         end2 = 19;
         end3 = 2;
         end4 = 2;
         end5 = 2;


     }else if(depth == 1){
         de1_x = 19;
         de1_y = 19;
         de2_x = 19;
         de2_y = 19;
         de3_x = 19;
         de3_y = 19;
         de4_x = 19;
         de4_y = 19;
         de5_x = -2;
         de5_y = -2;

         end1 = 19;
         end2 = 19;
         end3 = 19;
         end4 = 19;
         end5 = 2;


     }
     for(int i = 0; i < stone_count; i++){ //각각의 돌 확인
        ////qDebug("-----looping----");

                     for(de4_x = -2; de4_x <= 2; de4_x++){
                     for(de4_y = -2; de4_y <= 2; de4_y++){
                             if(pan[location[i][0]+de4_x][location[i][1]+de4_y] == 0  && (location[i][0]+de4_x) < 19 && (location[i][0]+de4_x) >= 0 && (location[i][1]+de4_y) < 19 && (location[i][1]+de4_y) >= 0){//그 위치가 바둑판 범위 안이고 빈칸이면
                               pan[location[i][0]+de4_x][location[i][1]+de4_y] = stone;
                               location[stone_count][0] = location[i][0]+de4_x;
                               location[stone_count][1] = location[i][1]+de4_y;
                               stone_count++;
                             }
                             else
                                continue;

                             for(de5_x = -2; de5_x <= 2; de5_x++){
                                 for(de5_y = -2; de5_y <= 2; de5_y++){
                                     if(pan[location[i][0]+de5_x][location[i][1]+de5_y] == 0  && (location[i][0]+de5_x) < 19 && (location[i][0]+de5_x) >= 0 && (location[i][1]+de5_y) < 19 && (location[i][1]+de5_y) >= 0){//그 위치가 바둑판 범위 안이고 빈칸이면
                                         pan[location[i][0]+de5_x][location[i][1]+de5_y] = p1_s;
                                         location[stone_count][0] = location[i][0]+de5_x;
                                         location[stone_count][1] = location[i][1]+de5_y;
                                         stone_count++;
                                     }
                                     else
                                         continue;

                                    ////qDebug("================================================(depth : %d  j : %d  n : %d)", depth_main - depth + 1, de5_x, de5_y);
                                     for(int i2 = 0; i2 < 19; i2++){
                                         ////qDebug("%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.",pan[i2][0],pan[i2][1],pan[i2][2],pan[i2][3],pan[i2][4],pan[i2][5],pan[i2][6],pan[i2][7],pan[i2][8],pan[i2][9],pan[i2][10],pan[i2][11],pan[i2][12],pan[i2][13],pan[i2][14],pan[i2][15],pan[i2][16],pan[i2][17],pan[i2][18]);
                                     }
                                    ////qDebug("\n");

                                    ////qDebug("de1_x : %d de1_y : %d de2_x : %d de2_y : %d de3_x : %d de3_y : %d de4_x : %d de4_y : %d de5_x : %d de5_y : %d ", de1_x, de1_y, de2_x, de2_y, de3_x, de3_y, de4_x, de4_y, de5_x, de5_y);


                                     SCORE_PC[0] = PC_DO_CHECK(pc_s);
                                     SCORE_PLAYER[0] = PC_DO_CHECK(p1_s);
                                     //temp_score1 = score[stone] - prev_score1;
                                     //temp_score2 = score[not_stone] - prev_score2;

                                     sub = SCORE_PC[0] - SCORE_PLAYER[0];

                                    ////qDebug(" *return : %d , %d *************************", SCORE_PC[0], SCORE_PLAYER[0]);


                                     if(MAX_SUB < sub){
                                         MAX_SUB = sub;
                                        ////qDebug("changed");
                                         if(depth == 1){
                                         MAX_x = location[i][0]+de4_x;
                                         MAX_y = location[i][1]+de4_y;
                                         }
                                         if(depth == 2){
                                         MAX_x = location[i][0]+de3_x;
                                         MAX_y = location[i][1]+de3_y;
                                         }
                                         if(depth == 3){
                                         MAX_x = location[i][0]+de1_x;
                                         MAX_y = location[i][1]+de1_y;
                                         }


                                        ////qDebug("*************************************************");
                                     }
                                 pan[location[i][0]+de5_x][location[i][1]+de5_y] = 0;
                                 location[stone_count][0] = 0;
                                 location[stone_count][1] = 0;
                                 stone_count--;

                                 }
                             }
                             pan[location[i][0]+de4_x][location[i][1]+de4_y] = 0;
                             location[stone_count][0] = 0;
                             location[stone_count][1] = 0;
                             stone_count--;
                         }
                     }


        }

   return 0;

}
*/
/*
     for(int i = 0; i <= stone_count; i++){ //각각의 돌 확인

         while(de1_x <= end1){
             while(de1_y <= end1){

                 if(pan[location[i][0]+de1_x][location[i][1]+de1_y] == 0  && (location[i][0]+de1_x) < 19 && (location[i][0]+de1_x) >= 0 && (location[i][1]+de1_y) < 19 && (location[i][1]+de1_y) >= 0)//그 위치가 바둑판 범위 안이고 빈칸이면
                    pan[location[i][0]+de1_x][location[i][1]+de1_y] = stone;
                 else{
                     de1_y++;
                     continue;
                 }

                 while(de2_x <= end2){
                    while(de2_y <= end2){
                        if(pan[location[i][0]+de2_x][location[i][1]+de2_y] == 0  && (location[i][0]+de2_x) < 19 && (location[i][0]+de2_x) >= 0 && (location[i][1]+de2_y) < 19 && (location[i][1]+de2_y) >= 0)//그 위치가 바둑판 범위 안이고 빈칸이면
                            pan[location[i][0]+de2_x][location[i][1]+de2_y] = p1_s;
                        else{
                            de2_y++;
                            continue;
                        }


                        while(de3_x <= end3){
                            while(de3_y <= end3){
                                 if(pan[location[i][0]+de3_x][location[i][1]+de3_y] == 0  && (location[i][0]+de3_x) < 19 && (location[i][0]+de3_x) >= 0 && (location[i][1]+de3_y) < 19 && (location[i][1]+de3_y) >= 0)//그 위치가 바둑판 범위 안이고 빈칸이면
                                      pan[location[i][0]+de3_x][location[i][1]+de3_y] = stone;
                                 else{
                                     de3_y++;
                                     continue;
                                 }


                                 while(de4_x <= end4){
                                      while(de4_y <= end4){
                                           if(pan[location[i][0]+de4_x][location[i][1]+de4_y] == 0  && (location[i][0]+de4_x) < 19 && (location[i][0]+de4_x) >= 0 && (location[i][1]+de4_y) < 19 && (location[i][1]+de4_y) >= 0)//그 위치가 바둑판 범위 안이고 빈칸이면
                                                 pan[location[i][0]+de4_x][location[i][1]+de4_y] = p1_s;
                                           else{
                                               de4_y++;
                                               continue;
                                           }

                                           while(de5_x <= end5){
                                                while(de5_y <= end5){

                                                     if(pan[location[i][0]+de5_x][location[i][1]+de5_y] == 0  && (location[i][0]+de5_x) < 19 && (location[i][0]+de5_x) >= 0 && (location[i][1]+de5_y) < 19 && (location[i][1]+de5_y) >= 0)//그 위치가 바둑판 범위 안이고 빈칸이면
                                                         pan[location[i][0]+de5_x][location[i][1]+de5_y] = stone;
                                                     else{
                                                         de5_y++;
                                                         continue;
                                                     }
                                                    ////qDebug("================================================(depth : %d  j : %d  n : %d)", depth_main - depth + 1, de5_x, de5_y);
                                                     for(int i2 = 0; i2 < 19; i2++){
                                                         ////qDebug("%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.",pan[i2][0],pan[i2][1],pan[i2][2],pan[i2][3],pan[i2][4],pan[i2][5],pan[i2][6],pan[i2][7],pan[i2][8],pan[i2][9],pan[i2][10],pan[i2][11],pan[i2][12],pan[i2][13],pan[i2][14],pan[i2][15],pan[i2][16],pan[i2][17],pan[i2][18]);
                                                     }
                                                    ////qDebug("\n");

                                                    ////qDebug("de1_x : %d de1_y : %d de2_x : %d de2_y : %d de3_x : %d de3_y : %d de4_x : %d de4_y : %d de5_x : %d de5_y : %d ", de1_x, de1_y, de2_x, de2_y, de3_x, de3_y, de4_x, de4_y, de5_x, de5_y);


                                                     SCORE_PC[0] = PC_DO_CHECK(pc_s);
                                                     SCORE_PLAYER[0] = PC_DO_CHECK(p1_s);
                                                     //temp_score1 = score[stone] - prev_score1;
                                                     //temp_score2 = score[not_stone] - prev_score2;

                                                     sub = SCORE_PLAYER[0] - SCORE_PC[0];

                                                    ////qDebug(" return : %d , %d *************************", SCORE_PC[0], SCORE_PLAYER[0]);


                                                     if(MAX_SUB < sub){
                                                         MAX_SUB = sub;
                                                         if(depth == 1){
                                                             MAX_x = location[i][0]+de5_x;
                                                             MAX_y = location[i][1]+de5_y;
                                                         }
                                                         if(depth == 2){
                                                             MAX_x = location[i][0]+de3_x;
                                                             MAX_y = location[i][1]+de3_y;
                                                         }
                                                         if(depth == 3){
                                                             MAX_x = location[i][0]+de1_x;
                                                             MAX_y = location[i][1]+de1_y;
                                                         }


                                                        ////qDebug("*************************************************");
                                                     }

                                                     pan[location[i][0]+de5_x][location[i][1]+de5_y] = 0;
                                                     de5_y++;
                                                 }
                                                de5_x++;
                                                de5_y = -2;

                                             }
                                             pan[location[i][0]+de4_x][location[i][1]+de4_y] = 0;
                                             de4_y++;
                                         }
                                         de4_x++;
                                         de4_y = -2;

                                     }
                                     pan[location[i][0]+de3_x][location[i][1]+de3_y] = 0;
                                     de3_y++;
                                 }
                                de3_x++;
                                if(depth >= 2)
                                    de3_y = -2;

                             }
                             pan[location[i][0]+de2_x][location[i][1]+de2_y] = 0;
                             de2_y++;
                         }
                         de2_x++;
                         if(depth == 3)
                            de2_y = -2;


                 }
                 pan[location[i][0]+de1_x][location[i][1]+de1_y] = 0;
                 de1_y++;
             }
             de1_x++;
             if(depth == 3)
                de1_y = -2;


         }
     }

    return 0;

    */
     //////////////////////




    ////////////////////////

     /*
     if(depth > 0){
        for(int i = 0; i < stone_count; i++){ //각각의 돌 확인
           for(int j = -2; j <= 2; j++){ //각각의 돌 기준으로 주변 -5~5 확인
              for(int n = -2; n <= 2; n++){



                   if(pan[location[i][0]+j][location[i][1]+n] == 0  && (location[i][0]+j) < 19 && (location[i][0]+j) >= 0 && (location[i][1]+n) < 19 && (location[i][1]+n) >= 0){//그 위치가 바둑판 범위 안이고 빈칸이면
                      pan[location[i][0]+j][location[i][1]+n] = stone;

                     ////qDebug("================================================(depth : %d  j : %d  n : %d)", depth_main - depth + 1, j, n);
                      for(int i = 0; i < 19; i++){
                         ////qDebug("%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.",pan[i][0],pan[i][1],pan[i][2],pan[i][3],pan[i][4],pan[i][5],pan[i][6],pan[i][7],pan[i][8],pan[i][9],pan[i][10],pan[i][11],pan[i][12],pan[i][13],pan[i][14],pan[i][15],pan[i][16],pan[i][17],pan[i][18]);
                      }
                     ////qDebug("\n");

///////////////////////////////////////
                      if(stone == pc_s){
                            PC_DO(p1_s, MAX_x_PLAYER[depth_main-depth+1], MAX_y_PLAYER[depth_main-depth+1], depth);
                            stone = p1_s;

                            for(int i = stone_count-1; i < stone_count; i++){ //각각의 돌 확인
                               for(int j = -2; j <= 2; j++){ //각각의 돌 기준으로 주변 -5~5 확인
                                  for(int n = -2; n <= 2; n++){
                                      if(depth > 0){


                                          if(pan[location[i][0]+j][location[i][1]+n] == 0  && (location[i][0]+j) < 19 && (location[i][0]+j) >= 0 && (location[i][1]+n) < 19 && (location[i][1]+n) >= 0){//그 위치가 바둑판 범위 안이고 빈칸이면
                                             pan[location[i][0]+j][location[i][1]+n] = stone;

                                            ////qDebug("================================================(depth : %d  j : %d  n : %d)", depth_main - depth + 1, j, n);
                                             for(int i = 0; i < 19; i++){
                                                ////qDebug("%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.%d.",pan[i][0],pan[i][1],pan[i][2],pan[i][3],pan[i][4],pan[i][5],pan[i][6],pan[i][7],pan[i][8],pan[i][9],pan[i][10],pan[i][11],pan[i][12],pan[i][13],pan[i][14],pan[i][15],pan[i][16],pan[i][17],pan[i][18]);
                                             }
                                            ////qDebug("\n");



                                             SCORE_PC[depth_main-depth] = PC_DO_CHECK(pc_s);
                                             SCORE_PLAYER[depth_main-depth] = PC_DO_CHECK(p1_s);
                                            // temp_score1 = score[stone] - prev_score1;
                                             //temp_score2 = score[not_stone] - prev_score2;

                                             sub = SCORE_PLAYER[depth_main-depth] - SCORE_PC[depth_main-depth];

                                            ////qDebug(" return : %d , %d *************************", SCORE_PC[depth_main-depth], SCORE_PLAYER[depth_main-depth]);


                                             if(MAX_SUB < sub){
                                                 MAX_SUB = sub;
                                                 MAX_x = location[i][0]+j;
                                                 MAX_y = location[i][1]+n;


                                                ////qDebug("*************************************************");
                                             }

                                             pan[location[i][0]+j][location[i][1]+n] = 0;

                                          }

                                      }
                                      else
                                          return 0;

                                  }
                               }
                            }


                      }
                      /////////////////////////////////////

                      SCORE_PC[depth_main-depth+1] = PC_DO_CHECK(pc_s);
                      SCORE_PLAYER[depth_main-depth+1] = PC_DO_CHECK(p1_s);
                     // temp_score1 = score[stone] - prev_score1;
                      //temp_score2 = score[not_stone] - prev_score2;

                      sub = SCORE_PC[depth_main-depth+1] - SCORE_PLAYER[depth_main-depth+1];

                     ////qDebug("************************* return : %d , %d", SCORE_PC[depth_main-depth+1], SCORE_PLAYER[depth_main-depth+1]);


                      if(MAX_SUB < sub){
                          MAX_SUB = sub;
                          MAX_x = location[i][0]+j;
                          MAX_y = location[i][1]+n;


                         ////qDebug("*************************************************");
                      }

                      else{
                      }
                      depth -= 1;
                      pan[location[i][0]+j][location[i][1]+n] = 0;

                   }


               }


           }
        }

     }
     else
        return 0;

     MAX_x_PC[0] = MAX_x;
     MAX_y_PC[0] = MAX_y;
     if(depth == 1){
   //      pan_btn[MAX_x][MAX_y]->click(); //x,y 변경해야할수도있음!!!!!!!!!!!
     }

     return 0;
     */

/*
     for(int i = 0; i < stone_count; i++){ //각각의 돌 확인
        for(int j = -2; j <= 2; j++){ //각각의 돌 기준으로 주변 -5~5 확인
           for(int n = -2; n <= 2; n++){
              if(pan[location[i][0]+j][location[i][1]+n] == 0  && (location[i][0]+j) < 19 && (location[i][0]+j) >= 0 && (location[i][1]+n) < 19 && (location[i][1]+n) >= 0){//그 위치가 바둑판 범위 안이고 빈칸이면
                 pan[location[i][0]+j][location[i][1]+n] = stone; //돌이 위치 한 것으로 가정
                 CHECK_SCORE(stone);// 점수 확인
                 score_temp = score[stone];
                 ////qDebug("pC do it do it  x : %d  y : %d  ",location[i][0]+j, location[i][1]+n);

                 if(score_temp > MAX_score){ //돌의 위치를 가정한 점수가 최고점수이면
                     MAX_x = j; MAX_y = n; //위치, 점수 변경
                     MAX_score = score_temp;
                    ////qDebug("**BIG one**");

                 }
                 pan[location[i][0]+j][location[i][1]+n] = 0; //돌 복원
                 score[stone] = prev_score;
              }
           }
        }
     }//1단계 깊이 PC_DO
    ////qDebug("no big one T^T  MAX : %d  prev : %d  ", MAX_score, prev_score);
*/
/*
     if(MAX_score == prev_score){ //어느곳에 두어도 점수 변화가 없을경우
     //연결된 플레이어의 돌들을 수비, 연결된 pc의 돌을 연결하여 공격 하는 알고리즘
     //계산된 위치에 돌을 위치하도록 추가!

       ////qDebug("plan B start!!!");
        int x = 0, y = 0, dia1 = 0, dia2 = 0;
        int temp;
        for(int loop = 4 ; loop > 0; loop--){
            x = 0, y = 0, dia1 = 0, dia2 = 0;
            for(int i = 0; i < stone_count; i++){
                if(pan[location[i][0]][location[i][1]] == stone){// stone의 값을 pc와 플레이어 각각 하도록 반복문 수정!
                   ////qDebug("%d  :  %d 비교  ", pan[location[i][0]][location[i][1]], stone);
                    for(int j = i; j < stone_count; j++){
                       ////qDebug("%d 범위 check ",(location[j][0]-location[i][0]));
                        if((location[j][0]-location[i][0]) < loop && location[j][1] == location[i][1]){ //[0]->x축 [1]은 y축/ y축은 같고 x축 값의 차이가 5 이내 일때
                            if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                                x++;
                               ////qDebug("x++ => %d", x);

                            }
                        }
                        if((location[j][1]-location[i][1]) < loop && location[j][0] == location[i][0]){
                            if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                                y++;
                               ////qDebug("y++ => %d", y);

                            }
                        }

                        if((location[j][0]-location[i][0])==(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (기준y) - (비교y)일때
                            if((location[j][0]-location[i][0]) < loop){//차이가 5이내 일때
                                if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                                    dia1++;
                                   ////qDebug("dia1++ => %d", dia1);

                                }
                            }
                        }

                        if((location[j][0]-location[i][0])==(-1)*(location[j][1]-location[i][1])){ //(기준x) - (비교x) == (-1)*(기준y) - (비교y)일때(x는 증가 y는 감소)
                            if((location[j][0]-location[i][0]) < loop){//차이가 5이내 일때
                                if(pan[location[j][0]][location[j][1]] == stone){ //그 위치의 돌이 같은색이면
                                    dia2++;
                                   ////qDebug("dia2++ => %d", dia2);

                                }
                            }
                        }
                    }
                }
                if(x == loop){
                   ////qDebug("X same");
                    if((location[i][0]-1 < 19) && (location[i][1] >= 0) && (pan[location[i][0]-1][location[i][1]]) == 0){ //범위 안이고 빈칸이면
                        if(pan[location[i][1]][location[i][0]-1] == 0){
                            ////qDebug("x:%d  y:%d => %d",location[i][0]-1,location[i][1], pan[location[i][0]-1][location[i][1]]);

                            pan_btn[location[i][1]][location[i][0]-1]->click();
                            return;
                        }
                    }
                    if((location[i][0]+loop < 19) && (location[i][1] >= 0) && (pan[location[i][0]+loop][location[i][1]]) == 0){ //범위 안이고 빈칸이면
                        if(pan[location[i][1]][location[i][0]] == 0){
                            pan_btn[location[i][0]][location[i][1]]->click();

                            return;
                        }
                    }

                }
                if(y == loop){
                   ////qDebug("Y same");

                    if((location[i][0] < 19) && (location[i][1]-1 >= 0) && (pan[location[i][0]][location[i][1]-1]) == 0){ //범위 안이고 빈칸이면
                         if(pan[location[i][1]-1][location[i][0]] == 0){
                            pan_btn[location[i][1]-1][location[i][0]]->click();
                           ////qDebug("***************");

                            return;
                         }
                    }
                    if((location[i][0] < 19) && (location[i][1]+loop >= 0) && (pan[location[i][0]][location[i][1]+loop]) == 0){ //범위 안이고 빈칸이면
                         if(pan[location[i][1]+loop][location[i][0]] == 0){
                            pan_btn[location[i][1]+loop][location[i][0]]->click();
                           ////qDebug("================");
                           ////qDebug("x:%d  y:%d   loop : %d",location[i][0], location[i][1]+1, loop);


                            return;
                         }
                    }
                }
                if(dia1 == loop){
                   ////qDebug("Dia1 same");

                    if((location[i][0]-1 < 19) && (location[i][1]-1 >= 0) && (pan[location[i][0]-1][location[i][1]-1]) == 0){ //범위 안이고 빈칸이면
                         if(pan[location[i][1]][location[i][0]] == 0){
                            pan_btn[location[i][1]][location[i][0]]->click();
                            return;
                         }
                    }
                    if((location[i][0]+loop < 19) && (location[i][1]+loop >= 0) && (pan[location[i][0]+loop][location[i][1]+loop]) == 0){ //범위 안이고 빈칸이면
                         if(pan[location[i][1]][location[i][0]] == 0){
                            pan_btn[location[i][1]][location[i][0]]->click();
                            return;
                         }
                    }
                }
                if(dia2 == loop){ //+- 확인....
                   ////qDebug("Dia2 same");

                    if((location[i][0]-1 < 19) && (location[i][1]+1 >= 0) && (pan[location[i][0]-1][location[i][1]+1]) == 0){ //범위 안이고 빈칸이면
                         if(pan[location[i][1]][location[i][0]] == 0){
                            pan_btn[location[i][1]][location[i][0]]->click();
                            return;
                         }
                    }
                    if((location[i][0]-loop < 19) && (location[i][1]+loop >= 0) && (pan[location[i][0]-loop][location[i][1]+loop]) == 0){ //범위 안이고 빈칸이면
                         if(pan[location[i][1]][location[i][0]] == 0){
                            pan_btn[location[i][1]][location[i][0]]->click();
                            return;
                         }
                    }
                }
             //   temp = i;
            }   //연결된 돌들 확인 완료
            //int i = temp;

        }
    }
    */
//}



MainWindow::~MainWindow()
{

}
