package team;
import java.awt.Button;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.Panel;
import java.awt.TextArea;
import java.awt.TextField;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ConnectException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.Timer;

/** 
 * // 실행 방법 // java MultichatGUIClient 대화명 
 *  
 * @since 2012. 07. 11. 
 * @author yanggun7201 
 */ 
public class MultichatGUIClient_final extends JPanel implements ActionListener {
    Frame startf;//시작프레임
    Frame f; //동작프레임
    String user; 
    MyPanel back; //배경패널
    JPanel q_list; //질문항목 리스트
    loginPanel login = new loginPanel(); //로그인하는 패널  
    Button logbt;//로그인버튼
    Button b1;//입력버튼 
    Button b2;//취소버튼   
    TextField tf; 
    TextField tf2;
    JTextArea ta;  
    TextArea ta2;//채팅창  
    JTextField na;//이름 입력공간
    
    String Q_s[] = new String[100];
    int Q_i[] = new int[100];
    boolean Q_like[] = new boolean[100];
    int data_num = 0;
    // =============================== 
    String name;
    
    ClientSender sender;
    JScrollPane scroll;//스크롤
    //JScrollPane scroll2;//스크롤
    // =============================== 

    public MultichatGUIClient_final(String name) { 
        // =============================== 
        this.name = name; 
        //===프레입부분===
        f = new Frame(name);
        f.setSize(400, 955);
        //===시작프레임부분입니다.===
        startf = new Frame();
        startf.setSize(315, 437);
        //===질문/채팅 동작패널입니다.===
        back = new MyPanel();
        back.setLayout(null);
        //질문버튼이 올라가는 패널입니다. 리스트 크기입니다. 최대 100줄
        q_list = new JPanel(new GridLayout(100,1));
        q_list.setBackground(Color.white);            
        //==========스크롤부분=============
        scroll = new JScrollPane(q_list);  
        scroll.setBounds(15,300,350,170);
        scroll.setBackground(Color.white);
        //==============================
        
            
        tf = new TextField(50);
        tf.setBounds(15,810,350,25);
     
        //===전송버튼부분입니다.===
        b1 = new Button("전송");
        b1.setBounds(15,855,130,40);  
        b1.setBackground(Color.white);
        //===취소버튼부분입니다.===
        b2 = new Button("취소");
        b2.setBounds(235,855,130,40);
        b2.setBackground(Color.white);
        
        //질문입력공간=================================================
        ta = new JTextArea(tf.getText(), 20, 50);//들어갈 텍스트, 사이즈 ,사이즈
        //행 넘기기 기능 켜기
        ta.setLineWrap(true);
        //행 넘길 때 행의 마지막 단어가 두행에 걸쳐 나뉘지 않도록 하기
        ta.setWrapStyleWord(true);
        //=============================================================
        
        //===채팅삽입공간입니다.===
        ta2 = new TextArea(20, 50);//들어갈 텍스트, 사이즈 ,사이즈
        ta2.setBounds(15,620,350,170);
        ta2.setBackground(Color.white);
        //==========================================================
        
        back.add(scroll);
        back.add(ta2);
        back.add(tf);
        back.add(b1);
        back.add(b2);

        startf.add(login);
        f.add(back);
     }
    

    public void launchTest() {
         f.addWindowListener(new WindowAdapter() {
             public void windowClosing(WindowEvent e) {
                 System.exit(0); 
            } 
        }); 
         startf.addWindowListener(new WindowAdapter() {
             public void windowClosing(WindowEvent e) {
                 System.exit(0); 
            } 
        }); 
        
         b1.addActionListener(this);
         b2.addActionListener(new ActionListener(){

            public void actionPerformed(ActionEvent arg0) {
               // TODO Auto-generated method stub
               //System.out.println("취소 눌렸다!!");
                 tf.setText(" ");
                 tf.requestFocus();
                 
            }
         });
        
        tf.setColumns(40); 
        tf.addKeyListener(new KeyAdapter() { 
            public void keyReleased(KeyEvent e) {
                 char keyCode = e.getKeyChar();
                 if (keyCode == KeyEvent.VK_ENTER) {
                     actionPerformed(null); 
                } 
            } 
        }); 

        //처음 시작시 보여주는 패널은 스타트패널입니다.
        startf.setVisible(true); 

        // =================================================
         Socket socket = null; 
        try { 
            String serverIp = "128.0.0.1"; 
            socket = new Socket(serverIp, 7779); // 소켓을 생성하여 연결을 요청한다.
            System.out.println("서버에 연결되었습니다.");
 
            // 메시지 전송용 Thread 생성 
            sender = new ClientSender(socket);
 
            // 메시지 수신용 Thread 생성 
            Thread receiver = new Thread(new ClientReceiver(socket));
 
            receiver.start(); 
        } catch (ConnectException ce) { 
            ce.printStackTrace(); 
        } catch (Exception e) { 
        } 
        // =================================================
     } 

    @Override 
    public void actionPerformed(ActionEvent e) {
         // ========================= 
       Data data = new Data();
       data.q = tf.getText();
       data.q_num = 0;
       

        sender.send(data); 
        // ========================= 
        tf.setText(""); 
        tf.requestFocus(); 
 
    
    } 
    // =================================================
    public void setMessage(Data data) {
       //ta.append(new Button(message));
       
       Button btn = new Button(data.q);
        btn.setBackground(Color.white);
         
        data.q_num++;

        String m;
        String message2 = data.q;
        //String message2 = btn.getLabel();

        m = message2.substring(message2.indexOf(' ')+1, message2.indexOf('/'));
             
       String str_buf = message2.substring(message2.indexOf("공감")+3);
       int q_n = Integer.parseInt(str_buf);
           
        System.out.println("-------------");   
              
        btn.addActionListener(new ActionListener(){
           
           public void actionPerformed(ActionEvent arg0) {
              String m;
              String message2 = btn.getLabel();
              m = message2.substring(message2.indexOf(' ')+1, message2.indexOf('/'));              

              String str_buf = message2.substring(message2.indexOf("공감")+3);
              int q_n = Integer.parseInt(str_buf)+1;
              data.q_num = q_n;
              
              int data_num_buf = data_num;
              for(int i = 0; i < data_num_buf; i++){
                 Data data_b = new Data();
                 data_b.q = Q_s[i];
                 data_b.q_num = Q_i[i];
                 System.out.println("공감클릭 " + (i+1) + "번째 배열데이터 전송");
                 if((":"+m).equalsIgnoreCase(Q_s[i])){
                    System.out.println(data_b.q + data_b.q_num + "공감+ 전송");
                    //System.out.println();

                    //data_b.q =  ":"+data_b.q.substring();
                    data_b.q_num = q_n;
                    sender.send(data_b); 
                 }
                 else {
                    System.out.println(data.q +"_"+ Q_s[i]+ "-----------------전송");

                    System.out.println(data_b.q + data_b.q_num + "전송");
                    data_b.q = Q_s[i];

                    sender.send(data_b);                     
                 }
                 data_num--;
              }
              q_list.updateUI();

              return;
           }
        });

        setBtnColor(btn, q_n);
        
        q_list.add(btn);
        q_list.updateUI();
        ta.append(data.q);      
        ta.append("\n"); 
    }
    // =================================================
    
    
   Button btn;

    public void setBtnColor(Button btn, int q_n) {


       Timer timer = new Timer(1, new ActionListener(){
          Color color;
           int col2 = 255;
          int num = -1;
         @Override
         public void actionPerformed(ActionEvent e) {
            // TODO Auto-generated method stub
              int n = 1;

              if(col2 + (num*10) <= 255 && (col2+(num*10)) >= 0){
                 col2 += (num*10);

              }
              else if(col2 + (num*10) > 255){
                 num = -1;

              }else if((col2+(num*10)) < 0){
                 num = 1;
                 
              }
            color = new Color(255, col2, col2);
               btn.setBackground(color);
               q_list.updateUI();
         }
         
      });
        int col = 255;
        if(q_n >= 5){
           col -= 50;
            btn.setBackground(new Color(255, col, col));
            q_list.updateUI();

        }if(q_n >= 10){
           col -= 100;
            btn.setBackground(new Color(255, col, col));
            q_list.updateUI();


        }if(q_n >= 15){
           col -= 50;
            btn.setBackground(new Color(255, col, col));
            q_list.updateUI();

        }if(q_n >= 20){
           timer.start();
        }
      
    }
 
    // ===============================================================================
     // 메시지 전송용 객체  
    // Thread 아님!!! (GUI 버전이므로, Event를 받아서 처리함)
     class ClientSender { 
        Socket socket; 
        DataOutputStream out; 

        ClientSender(Socket socket) { 
            this.socket = socket; 

            try { 
                this.out = new DataOutputStream(socket.getOutputStream());
                // 시작하자 마자, 자신의 대화명을 서버로 전송 
                if (out != null) {
                     out.writeUTF(name); 
                } 

            } catch (Exception e) { 
            } 
        } 

        public void send(Data data) {
             if (out != null) {
                 try { 
                     String m;
                     m = data.q;
                     
                     int q_n = data.q_num;
                     System.out.println(data.q+"초기 입력");
                     if(data.q.substring(0,1).equalsIgnoreCase(":") ){
                         out.writeUTF(" " + data.q + "/ 공감 " + data.q_num);
                     }
                     else{ 
                        //out.writeUTF(" "+ data.q + "/ 공감 " + data.q_num);
                        out.writeUTF(" [" + user + "] : " + data.q + "/ 공감 " + data.q_num);
                     }
                 } catch (IOException e) { 
                } 
            } 
        } 
    } 

    // 메시지 수신용 Thread 
    class ClientReceiver implements Runnable {
         Socket socket; 
        DataInputStream in; 
        // 생성자 
        ClientReceiver(Socket socket) { 
            this.socket = socket; 

            try { 
                // 서버로 부터 데이터를 받을 수 있도록 DataInputStream 생성
                 this.in = new DataInputStream(socket.getInputStream());
             } catch (IOException e) { 
            } 
        } 
        public void run() {
             while (in != null) { 
                try { 
                    // 서버로 부터 전송되는 데이터를 출력 
                   Data data = new Data();
                   data.q = in.readUTF();
                   
                   String m;
                   String message2 = data.q;
                   
                   m = message2.substring(message2.indexOf(' ')+1, message2.indexOf('/'));
                   if(!data.q.substring(1,2).equalsIgnoreCase(":") ){
                       ta2.append(data.q.substring(1,message2.indexOf("/"))); 
                       ta2.append("\n"); 
                   }
                   else{
                      
                       String space = " ";       
                       space += data.q.substring(2);       
                       data.q = space;
                      
                      if(m.equalsIgnoreCase(Q_s[0])){
                         q_list.removeAll();
                      }
                      if(m.equalsIgnoreCase(":CLEAR_ALL")){
                          q_list.removeAll();
                          for(int i = 0; i<100; i++){
                              Q_s[i] = null;
                              Q_i[i] = 0;
                          }
                         System.out.println("선생님 전체 삭제");

                          data_num = 0;
                         continue;
                         }
                      if(m.indexOf("CLEAR")==0){
                          q_list.removeAll();
                           String str_buf = m.substring(m.indexOf("R")+1);
                        //   data_num = Integer.parseInt(str_buf)-1;
                           data_num = 0;
                           System.out.println("clear 된수 질문수 : " + data_num);
                           for(int i = 0; i<100; i++){
                               Q_s[i] = null;
                               Q_i[i] = 0;
                           }
                      }
   
                      else {
        
                         String str_buf = message2.substring(message2.indexOf("공감")+3);
                          int q_n = Integer.parseInt(str_buf);
                          int buf=data_num;


                          
                          System.out.println(m+"현제 입력된 문자");

                          for(int i = 0; i <= data_num; i++){
                              if(m.equalsIgnoreCase(Q_s[i]) && Q_i[i]+1 == q_n){
                                 Q_s[i] = m;
                                 Q_i[i] = q_n; 
                                 System.out.println(i + "번째 " +Q_s[i]  + Q_i[i] +"숫자 증가!!!");
                                 continue;
                              }
                              else if(i == data_num && !m.equalsIgnoreCase(Q_s[i])){
                                 Q_s[data_num] = m;
                                 Q_i[data_num] = q_n;    
                                 System.out.println(i + "번째 " +Q_s[i]  + Q_i[i]  + "data_num : " + data_num  +" 추가");
                              }
                              else{
                       
                                 System.out.println(m+"같은문자 못찾음");

                                 continue;
   
                              }
                           }
                          
                                              
                         data_num++;
                         System.out.println("==================");
                         System.out.println(data_num + "    배열에 저장된 질문수 ");
                         
                            for(int i = 0; i <data_num; i++){
                              System.out.println("배열["+i +"]"+ Q_s[i]);                            
                            }
                        System.out.println("==================");
   
                          MultichatGUIClient_final.this.setMessage(data);
                      }
                  }
                 } catch (IOException e) { 
                } 
            } 
        } 
    }
    

    //로그인패널
    class loginPanel extends JPanel {
        ImageIcon image = new ImageIcon("팀프로젝트/login.png");//그림의 위치는 프로젝트 폴더안.(src폴더가 보이는곳)
        Image img = image.getImage();
        
       public loginPanel(){
          setLayout(null);
          setSize(300,400);
            //setBackground(new Color(170, 218, 219));//rgb컬러
          na = new JTextField(6);
          na.setBounds(100,275,100,20);
          
          logbt = new Button("로그인"); 
          logbt.setBackground(Color.white);
          logbt.setBounds(210,275,40,20);
          logbt.setActionCommand("로그인");//버튼누를시
          logbt.addActionListener(new MyListenerA());//실행됩니다.
                      
            add(na);
            add(logbt);
       } 
       
       public void paintComponent(Graphics g){//그림이나 도형을 넣을때 기본적으로 사용되는 페인트컴포넌트
            super.paintComponent(g);
            g.drawImage(img, 0, 0, 300, 400, this);

       }
    }
    
  
    //질문채팅 패널
    class MyPanel extends JPanel {

        ImageIcon image1 = new ImageIcon("팀프로젝트/사랑.png");//그림의 위치는 프로젝트 폴더안.(src폴더가 보이는곳)
        Image img1 = image1.getImage();
        ImageIcon image2 = new ImageIcon("팀프로젝트/사랑2.png");
        Image img2 = image2.getImage();
        ImageIcon image3 = new ImageIcon("팀프로젝트/질문.png");
        Image img3 = image3.getImage();
        ImageIcon image4 = new ImageIcon("팀프로젝트/채팅.png");
        Image img4 = image4.getImage();
        ImageIcon image5 = new ImageIcon("팀프로젝트/상위제목.png");
        Image img5 = image5.getImage();
        
        public MyPanel(){

            setBackground(new Color(200, 200, 200));
        }
        
        public void paintComponent(Graphics g){//그림이나 도형을 넣을때 기본적으로 사용되는 페인트컴포넌트
           super.paintComponent(g);
           g.drawImage(img1, 15, 140, 150, 184, this);//(이미지, 위치x, 위치y, 크기x, 크기y, this)
           g.drawImage(img2, 200, 460, 150, 184, this);//(이미지, 위치x, 위치y, 크기x, 크기y, this)
           g.drawImage(img3, 110, 130, 400, 200, this);//(이미지, 위치x, 위치y, 크기x, 크기y, this)
           g.drawImage(img4, -30, 460, 400, 200, this);//(이미지, 위치x, 위치y, 크기x, 크기y, this)
           g.drawImage(img5, 90, 10, 270, 133, this);//(이미지, 위치x, 위치y, 크기x, 크기y, this)
           //사진비율 276 : 338 = 150 : x
        }
     }
    
    //로그인버튼 입니다.
    class MyListenerA implements ActionListener{
            
       public void actionPerformed(ActionEvent e){
          System.out.println("버튼눌림 ㅎㅎ");
          name = na.getText();
          user = name;
          //TODO Auto-generated method stub
          startf.setVisible(false); 
          f.setTitle(name);
            f.setVisible(true); 

       }
    }
    // ===============================================================================
 
    // 실행 방법 
    // java MultichatGUIClient 대화명 
    public static void main(String[] args) {
        
        String name = null; 
        Scanner scanner = new Scanner(System.in);
        InetAddress ia = null;
        try {
         ia=InetAddress.getLocalHost();
      } catch (UnknownHostException e) {
         // TODO Auto-generated catch block
         e.printStackTrace();
      }
    

        do { 
            name = " "+ia;

            if (name.isEmpty()) { 
                System.out.println("대화명은 한글자 이상 입력해야 합니다.\n\n");
             } 
        } while (name.isEmpty()); 

        new MultichatGUIClient_final(name).launchTest();
     } 
} 