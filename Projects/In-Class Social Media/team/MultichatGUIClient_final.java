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
 * // ���� ��� // java MultichatGUIClient ��ȭ�� 
 *  
 * @since 2012. 07. 11. 
 * @author yanggun7201 
 */ 
public class MultichatGUIClient_final extends JPanel implements ActionListener {
    Frame startf;//����������
    Frame f; //����������
    String user; 
    MyPanel back; //����г�
    JPanel q_list; //�����׸� ����Ʈ
    loginPanel login = new loginPanel(); //�α����ϴ� �г�  
    Button logbt;//�α��ι�ư
    Button b1;//�Է¹�ư 
    Button b2;//��ҹ�ư   
    TextField tf; 
    TextField tf2;
    JTextArea ta;  
    TextArea ta2;//ä��â  
    JTextField na;//�̸� �Է°���
    
    String Q_s[] = new String[100];
    int Q_i[] = new int[100];
    boolean Q_like[] = new boolean[100];
    int data_num = 0;
    // =============================== 
    String name;
    
    ClientSender sender;
    JScrollPane scroll;//��ũ��
    //JScrollPane scroll2;//��ũ��
    // =============================== 

    public MultichatGUIClient_final(String name) { 
        // =============================== 
        this.name = name; 
        //===�����Ժκ�===
        f = new Frame(name);
        f.setSize(400, 955);
        //===���������Ӻκ��Դϴ�.===
        startf = new Frame();
        startf.setSize(315, 437);
        //===����/ä�� �����г��Դϴ�.===
        back = new MyPanel();
        back.setLayout(null);
        //������ư�� �ö󰡴� �г��Դϴ�. ����Ʈ ũ���Դϴ�. �ִ� 100��
        q_list = new JPanel(new GridLayout(100,1));
        q_list.setBackground(Color.white);            
        //==========��ũ�Ѻκ�=============
        scroll = new JScrollPane(q_list);  
        scroll.setBounds(15,300,350,170);
        scroll.setBackground(Color.white);
        //==============================
        
            
        tf = new TextField(50);
        tf.setBounds(15,810,350,25);
     
        //===���۹�ư�κ��Դϴ�.===
        b1 = new Button("����");
        b1.setBounds(15,855,130,40);  
        b1.setBackground(Color.white);
        //===��ҹ�ư�κ��Դϴ�.===
        b2 = new Button("���");
        b2.setBounds(235,855,130,40);
        b2.setBackground(Color.white);
        
        //�����Է°���=================================================
        ta = new JTextArea(tf.getText(), 20, 50);//�� �ؽ�Ʈ, ������ ,������
        //�� �ѱ�� ��� �ѱ�
        ta.setLineWrap(true);
        //�� �ѱ� �� ���� ������ �ܾ ���࿡ ���� ������ �ʵ��� �ϱ�
        ta.setWrapStyleWord(true);
        //=============================================================
        
        //===ä�û��԰����Դϴ�.===
        ta2 = new TextArea(20, 50);//�� �ؽ�Ʈ, ������ ,������
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
               //System.out.println("��� ���ȴ�!!");
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

        //ó�� ���۽� �����ִ� �г��� ��ŸƮ�г��Դϴ�.
        startf.setVisible(true); 

        // =================================================
         Socket socket = null; 
        try { 
            String serverIp = "128.0.0.1"; 
            socket = new Socket(serverIp, 7779); // ������ �����Ͽ� ������ ��û�Ѵ�.
            System.out.println("������ ����Ǿ����ϴ�.");
 
            // �޽��� ���ۿ� Thread ���� 
            sender = new ClientSender(socket);
 
            // �޽��� ���ſ� Thread ���� 
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
             
       String str_buf = message2.substring(message2.indexOf("����")+3);
       int q_n = Integer.parseInt(str_buf);
           
        System.out.println("-------------");   
              
        btn.addActionListener(new ActionListener(){
           
           public void actionPerformed(ActionEvent arg0) {
              String m;
              String message2 = btn.getLabel();
              m = message2.substring(message2.indexOf(' ')+1, message2.indexOf('/'));              

              String str_buf = message2.substring(message2.indexOf("����")+3);
              int q_n = Integer.parseInt(str_buf)+1;
              data.q_num = q_n;
              
              int data_num_buf = data_num;
              for(int i = 0; i < data_num_buf; i++){
                 Data data_b = new Data();
                 data_b.q = Q_s[i];
                 data_b.q_num = Q_i[i];
                 System.out.println("����Ŭ�� " + (i+1) + "��° �迭������ ����");
                 if((":"+m).equalsIgnoreCase(Q_s[i])){
                    System.out.println(data_b.q + data_b.q_num + "����+ ����");
                    //System.out.println();

                    //data_b.q =  ":"+data_b.q.substring();
                    data_b.q_num = q_n;
                    sender.send(data_b); 
                 }
                 else {
                    System.out.println(data.q +"_"+ Q_s[i]+ "-----------------����");

                    System.out.println(data_b.q + data_b.q_num + "����");
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
     // �޽��� ���ۿ� ��ü  
    // Thread �ƴ�!!! (GUI �����̹Ƿ�, Event�� �޾Ƽ� ó����)
     class ClientSender { 
        Socket socket; 
        DataOutputStream out; 

        ClientSender(Socket socket) { 
            this.socket = socket; 

            try { 
                this.out = new DataOutputStream(socket.getOutputStream());
                // �������� ����, �ڽ��� ��ȭ���� ������ ���� 
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
                     System.out.println(data.q+"�ʱ� �Է�");
                     if(data.q.substring(0,1).equalsIgnoreCase(":") ){
                         out.writeUTF(" " + data.q + "/ ���� " + data.q_num);
                     }
                     else{ 
                        //out.writeUTF(" "+ data.q + "/ ���� " + data.q_num);
                        out.writeUTF(" [" + user + "] : " + data.q + "/ ���� " + data.q_num);
                     }
                 } catch (IOException e) { 
                } 
            } 
        } 
    } 

    // �޽��� ���ſ� Thread 
    class ClientReceiver implements Runnable {
         Socket socket; 
        DataInputStream in; 
        // ������ 
        ClientReceiver(Socket socket) { 
            this.socket = socket; 

            try { 
                // ������ ���� �����͸� ���� �� �ֵ��� DataInputStream ����
                 this.in = new DataInputStream(socket.getInputStream());
             } catch (IOException e) { 
            } 
        } 
        public void run() {
             while (in != null) { 
                try { 
                    // ������ ���� ���۵Ǵ� �����͸� ��� 
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
                         System.out.println("������ ��ü ����");

                          data_num = 0;
                         continue;
                         }
                      if(m.indexOf("CLEAR")==0){
                          q_list.removeAll();
                           String str_buf = m.substring(m.indexOf("R")+1);
                        //   data_num = Integer.parseInt(str_buf)-1;
                           data_num = 0;
                           System.out.println("clear �ȼ� ������ : " + data_num);
                           for(int i = 0; i<100; i++){
                               Q_s[i] = null;
                               Q_i[i] = 0;
                           }
                      }
   
                      else {
        
                         String str_buf = message2.substring(message2.indexOf("����")+3);
                          int q_n = Integer.parseInt(str_buf);
                          int buf=data_num;


                          
                          System.out.println(m+"���� �Էµ� ����");

                          for(int i = 0; i <= data_num; i++){
                              if(m.equalsIgnoreCase(Q_s[i]) && Q_i[i]+1 == q_n){
                                 Q_s[i] = m;
                                 Q_i[i] = q_n; 
                                 System.out.println(i + "��° " +Q_s[i]  + Q_i[i] +"���� ����!!!");
                                 continue;
                              }
                              else if(i == data_num && !m.equalsIgnoreCase(Q_s[i])){
                                 Q_s[data_num] = m;
                                 Q_i[data_num] = q_n;    
                                 System.out.println(i + "��° " +Q_s[i]  + Q_i[i]  + "data_num : " + data_num  +" �߰�");
                              }
                              else{
                       
                                 System.out.println(m+"�������� ��ã��");

                                 continue;
   
                              }
                           }
                          
                                              
                         data_num++;
                         System.out.println("==================");
                         System.out.println(data_num + "    �迭�� ����� ������ ");
                         
                            for(int i = 0; i <data_num; i++){
                              System.out.println("�迭["+i +"]"+ Q_s[i]);                            
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
    

    //�α����г�
    class loginPanel extends JPanel {
        ImageIcon image = new ImageIcon("��������Ʈ/login.png");//�׸��� ��ġ�� ������Ʈ ������.(src������ ���̴°�)
        Image img = image.getImage();
        
       public loginPanel(){
          setLayout(null);
          setSize(300,400);
            //setBackground(new Color(170, 218, 219));//rgb�÷�
          na = new JTextField(6);
          na.setBounds(100,275,100,20);
          
          logbt = new Button("�α���"); 
          logbt.setBackground(Color.white);
          logbt.setBounds(210,275,40,20);
          logbt.setActionCommand("�α���");//��ư������
          logbt.addActionListener(new MyListenerA());//����˴ϴ�.
                      
            add(na);
            add(logbt);
       } 
       
       public void paintComponent(Graphics g){//�׸��̳� ������ ������ �⺻������ ���Ǵ� ����Ʈ������Ʈ
            super.paintComponent(g);
            g.drawImage(img, 0, 0, 300, 400, this);

       }
    }
    
  
    //����ä�� �г�
    class MyPanel extends JPanel {

        ImageIcon image1 = new ImageIcon("��������Ʈ/���.png");//�׸��� ��ġ�� ������Ʈ ������.(src������ ���̴°�)
        Image img1 = image1.getImage();
        ImageIcon image2 = new ImageIcon("��������Ʈ/���2.png");
        Image img2 = image2.getImage();
        ImageIcon image3 = new ImageIcon("��������Ʈ/����.png");
        Image img3 = image3.getImage();
        ImageIcon image4 = new ImageIcon("��������Ʈ/ä��.png");
        Image img4 = image4.getImage();
        ImageIcon image5 = new ImageIcon("��������Ʈ/��������.png");
        Image img5 = image5.getImage();
        
        public MyPanel(){

            setBackground(new Color(200, 200, 200));
        }
        
        public void paintComponent(Graphics g){//�׸��̳� ������ ������ �⺻������ ���Ǵ� ����Ʈ������Ʈ
           super.paintComponent(g);
           g.drawImage(img1, 15, 140, 150, 184, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)
           g.drawImage(img2, 200, 460, 150, 184, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)
           g.drawImage(img3, 110, 130, 400, 200, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)
           g.drawImage(img4, -30, 460, 400, 200, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)
           g.drawImage(img5, 90, 10, 270, 133, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)
           //�������� 276 : 338 = 150 : x
        }
     }
    
    //�α��ι�ư �Դϴ�.
    class MyListenerA implements ActionListener{
            
       public void actionPerformed(ActionEvent e){
          System.out.println("��ư���� ����");
          name = na.getText();
          user = name;
          //TODO Auto-generated method stub
          startf.setVisible(false); 
          f.setTitle(name);
            f.setVisible(true); 

       }
    }
    // ===============================================================================
 
    // ���� ��� 
    // java MultichatGUIClient ��ȭ�� 
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
                System.out.println("��ȭ���� �ѱ��� �̻� �Է��ؾ� �մϴ�.\n\n");
             } 
        } while (name.isEmpty()); 

        new MultichatGUIClient_final(name).launchTest();
     } 
} 