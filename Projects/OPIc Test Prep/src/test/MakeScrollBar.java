package test;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;

 

public class MakeScrollBar extends JFrame{
   CardLayout cardLayoutSet = new CardLayout();
   JPanel main = new JPanel();
   JPanel pn = new JPanel();
   JFrame frame;
   JPanel jp_label, jp_btn;
   JScrollPane scroll;
   JLabel label;
   JButton btn ;
   int count =1;
   GridBagLayout Gbag = new GridBagLayout();
   GridBagConstraints gbc1;
   JButton Snext_btn;

   MakeScrollBar(){
      main.setLayout(cardLayoutSet);
      add(main);

      setLayout(null);    // ���̾ƿ��� NULL�� �����Ѵ�
      setSize(1500,900);

      jp_label = new MySPanel(1500, 900);

      int x = 1500;
      int y = 900;
  

      jp_label.setLayout(Gbag);  
      jp_label.setBackground(Color.WHITE);

      Dimension size = new Dimension();//����� �����ϱ� ���� ��ü ����
      size.setSize(704, 2942);//��ü�� ����� ����
      jp_label.setPreferredSize(size);
 

      scroll = new JScrollPane(jp_label);  // ��ũ���г��� ����
      scroll.setBounds(x/2-360, y/2-225,720,450);    // �����ӿ� ��ũ���г��� ��ġ�� ���Ѵ�

      
      //starting3.add(scroll);
      main.add(scroll, "s3");
      cardLayoutSet.show(main, "s3");   
      
      pn.setBackground(new Color(201, 205, 208));
      
     // add(pn);
    //  add(scroll);   // ��ũ���г� �߰�
      setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

      setVisible(true);

}



 public static void main(String[] args) {
      MakeScrollBar bar = new  MakeScrollBar();
 }
   class MySPanel extends JPanel {
      ImageIcon image1 = new ImageIcon();
      Image img1;
       int x, y;
       public MySPanel(int x2, int y2){
          x = x2;
          y = y2;

          Snext_btn = new JButton(new ImageIcon("JOPIC/next.jpg"));
          add(Snext_btn);

         Snext_btn.setBorderPainted(false);
         Snext_btn.setFocusPainted(false);
         Snext_btn.setContentAreaFilled(false);
         Snext_btn.setForeground(Color.BLACK);


       }
       
       public void paintComponent(Graphics g){//�׸��̳� ������ ������ �⺻������ ���Ǵ� ����Ʈ������Ʈ
          super.paintComponent(g);
          g.drawImage(img1, 0, 0, 704, 2382, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)

          Snext_btn.setBounds(500, 122, 150, 50);

          image1 = new ImageIcon("JOPIC/survey.jpg");
          img1 = image1.getImage();
          
       }
    }

}