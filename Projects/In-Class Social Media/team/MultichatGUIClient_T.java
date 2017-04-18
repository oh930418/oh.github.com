package team;
import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.FlowLayout;
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
import java.net.Socket;
import java.util.Scanner;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.Timer;

/** 
 * // ���� ��� // java MultichatGUIClient ��ȭ�� 
 *  
 * @since 2012. 07. 11. 
 * @author yanggun7201 
 */ 
public class MultichatGUIClient_T extends JPanel implements ActionListener {
   Frame f;
    MyPanel back; //����г�
    JPanel q_list;
    TextField tf; 
    TextArea ta; 
    String Q_s[] = new String[100];
    int Q_i[] = new int[100];
    
    int data_num = 0;
    // =============================== 
    String name;
    String passWord; 
    JScrollPane scroll;//��ũ��
    ClientSender sender; 
    // =============================== 

    public MultichatGUIClient_T(String name) { 
        // =============================== 
        this.name = name; 
        f = new Frame(name); 
        f.setSize(400, 861);
        
        back = new MyPanel();
        back.setLayout(null);
        
        q_list = new JPanel(new GridLayout(100,1));//����Ʈ ũ���Դϴ�. �ִ� 100��
        q_list.setBackground(Color.white);
        
        //==========��ũ�Ѻκ�=============
        scroll = new JScrollPane(q_list);  
        scroll.setBounds(15,170,350,630);
        scroll.setBackground(Color.white);


        tf = new TextField(); 
        ta = new TextArea(20, 50);
     }

    public void launchTest() {
         f.addWindowListener(new WindowAdapter() {
             public void windowClosing(WindowEvent e) {
                 System.exit(0); 
            } 
        }); 

        back.add(scroll);
        f.add(back);

        
        tf.setColumns(40); 
        tf.addKeyListener(new KeyAdapter() { 
            public void keyReleased(KeyEvent e) {
                 char keyCode = e.getKeyChar();
                 if (keyCode == KeyEvent.VK_ENTER) {
                     actionPerformed(null); 
                } 
            } 
        }); 

        f.setVisible(true); 
      //  f.pack(); 

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
 
/*        if(data_num < 50)
            data_num++;
         else{
            data_num = 0;
            System.out.println("�ʱ�ȭ");
            
         }*/
    
    } 
    // =================================================
    public void setMessage(Data data) {
        Button btn = new Button(data.q);
        btn.setBackground(Color.white);
      //btn.setBorderPainted(false);
      //btn.setFocusPainted(false);
      //btn.setContentAreaFilled(false); 

        data.q_num++;

        String m;
        String message2 = data.q;
        m = message2.substring(message2.indexOf(' ')+1, message2.indexOf('/'));
             
        String str_buf = message2.substring(message2.indexOf("����")+3);
        int q_n = Integer.parseInt(str_buf);
  
        System.out.println("-------------");   
   
        btn.addActionListener(new ActionListener(){
           
           public void actionPerformed(ActionEvent arg0) {
              // TODO Auto-generated method stub 
              String m;
              String message2 = btn.getLabel();
              m = message2.substring(message2.indexOf(' ')+1, message2.indexOf('/'));
              data.q = m;
              
              System.out.println("@@@@"+m +  " ����!!!!");
              Data data_b = new Data();

              data_b.q = ":CLEAR_ALL";
              data_b.q_num = 0;
              sender.send(data_b); 
    
              String str_buf = message2.substring(message2.indexOf("����")+3);
              int q_n = Integer.parseInt(str_buf)+1;
              data.q_num = q_n;
              int da_buf = data_num;
              if(data_num == 1){// ������ 1�� �������� Ŭ���� ��ü ����
                  data_b.q = ":CLEAR_ALL";
                  data_b.q_num = 0;
                  sender.send(data_b); 
                  return;
              }
              for(int i = 0; i <= da_buf; i++){ 
                 if((":"+m).equalsIgnoreCase(Q_s[i])){
                    for(int j = i; j <= da_buf; j++){
                       Q_i[j] = Q_i[j+1];
                       Q_s[j] = Q_s[j+1];

                    }
                    data_num--;
                    break;
                 }
              }
              System.out.println("==================");
              System.out.println(data_num + "    ���� ���� ����� �� ");
              
                 for(int i = 0; i <data_num; i++){
                   System.out.println("�迭["+i +"]"+ Q_s[i]);

                    
                 }
              System.out.println("==================");

              da_buf = data_num;
 
              for(int i = 0; i < da_buf; i++){

                 data_b.q = Q_s[i];
                 data_b.q_num = Q_i[i];
                 sender.send(data_b); 
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
                    
                    //data_num = read_data;
                     String m;
                     m = data.q;
                     
                     int q_n = data.q_num;
                     
       // Ű����� �Է¹��� �����͸� ������ ����
                     out.writeUTF(" " + data.q + "/ ���� " + data.q_num);
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
                  System.out.println(data.q+"________");
                  if(data.q.indexOf(" [") == 0){
                      System.out.println(data.q);
                      continue;
                  }
                  String space = " ";       
                  space += data.q.substring(2);       
                  data.q = space;
                  System.out.println(data.q+"________");

                  if(m.equalsIgnoreCase(Q_s[0])){
                     q_list.removeAll();
                  }
                  if(m.equalsIgnoreCase(":CLEAR_ALL")){
                      q_list.removeAll();
                      data_num = 0;
                      for(int i = 0; i < 100; i++){
                          Q_s[i] = null;
                          Q_i[i] = 0;
                      }
                      continue;
                  }
                  if(m.indexOf(":CLEAR")==0){
                      q_list.removeAll();
                       String str_buf = m.substring(m.indexOf("R")+1);
                      // data_num = Integer.parseInt(str_buf)-1;
                       data_num = 0;
                       for(int i = 0; i < 100; i++){
                           Q_s[i] = null;
                           Q_i[i] = 0;
                       }
                  }
                  else{
                     String str_buf = message2.substring(message2.indexOf("����")+3);
                      int q_n = Integer.parseInt(str_buf);
                   
                      int loop = data_num;
                      
                      for(int i = 0; i <= loop; i++){
                    	 if(m.equalsIgnoreCase(Q_s[i]) && Q_i[i] == q_n){
                          //continue;
                             data_num--;

                           System.out.println(i + "��° " +Q_s[i]  + Q_i[i] +"�������");
                         break;
                      }
                          if(m.equalsIgnoreCase(Q_s[i]) && Q_i[i]+1 == q_n){
                              //continue;

                             Q_s[i] = m;
                              Q_i[i] = q_n; 
                               System.out.println(i + "��° " +Q_s[i]  + Q_i[i] +"������ ����");
                               data_num--;
                             break;
                          }
                          else if(i == data_num && !m.equalsIgnoreCase(Q_s[i])){
                             Q_s[data_num] = m;
                              Q_i[data_num] = q_n;   
                              // data_num--;

                              System.out.println(i + "��° " +Q_s[i]  + Q_i[i]  + "data_num : " + data_num);
                          }
                          else{
                             System.out.println("�������"+m);
                            // data_num--;

                             continue;

                          }
                       }
                                          
                     data_num++;
  
                     System.out.println("==================");
                     System.out.println(data_num + "    �迭�� ����� ������ ");
                     
                        for(int i = 0; i <data_num; i++){
                          System.out.println("�迭["+i +"]"+ Q_s[i] +"   " +Q_i[i]);
  
                           
                        }
                    System.out.println("==================");

                     
                      MultichatGUIClient_T.this.setMessage(data);
                  }
                } catch (IOException e) { 
               } 
           } 
       } 
    } 

    //���������г�
    class MyPanel extends JPanel {
        ImageIcon image1 = new ImageIcon("��������Ʈ/���.png");//�׸��� ��ġ�� ������Ʈ ������.(src������ ���̴°�)
        Image img1 = image1.getImage();
        ImageIcon image2 = new ImageIcon("��������Ʈ/������.png");
        Image img2 = image2.getImage();
      
        public MyPanel(){
           setBackground(new Color(240, 200, 200));//rgb�÷�
        }
        
        public void paintComponent(Graphics g){//�׸��̳� ������ ������ �⺻������ ���Ǵ� ����Ʈ������Ʈ
           super.paintComponent(g);
           g.drawImage(img1, 15, 10, 150, 184, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)
           g.drawImage(img2, 130, 0, 400, 200, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)

        }
     }
    
    public static void main(String[] args) {
 
        String name = null; 
        Scanner scanner = new Scanner(System.in);
 
        do { 

             name = "PRO"; 
            if (name.isEmpty()) { 
                System.out.println("��ȭ���� �ѱ��� �̻� �Է��ؾ� �մϴ�.\n\n");
             } 
        } while (name.isEmpty()); 

        new MultichatGUIClient_T(name).launchTest();
     } 
} 
