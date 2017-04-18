package opic;

import java.awt.Button;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.Toolkit;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;



public class Test_p extends JFrame{

	JFrame fr = new JFrame();
	JPanel pn;
	JButton btn, play_btn, recorde_btn;
	Boolean recorded;
	ImageIcon image1;
	Image img1;
	int n;
	Change_thread ct = new Change_thread();
	
	Test_p(int num,  int x, int y){
		n = num;
		ct.setPriority(10);
		pn = new MyPanel(num, x, y);
		recorded = false;
		pn.setBackground(new Color(201, 205, 208));
		int btn_x = (int) (x*0.48);
		int btn_y = (int) (y*0.59);
		//btn = new JButton(num+"");
		//play_btn = new JButton(num+"");
		recorde_btn = new JButton(num+"");
		
		/*play_btn.setBorderPainted(false);
		play_btn.setFocusPainted(false);
		play_btn.setContentAreaFilled(false);
		*/
		recorde_btn.setBorderPainted(false);
		recorde_btn.setFocusPainted(false);
		recorde_btn.setContentAreaFilled(false);
		recorde_btn.setForeground(Color.BLACK);
		//recorde_btn.setVisible(false);
		fr.add(pn);
		pn.setLayout(null);
		
/*		btn.setBounds(btn_x, btn_y, 50, 50);
		pn.add(btn);

		play_btn.setBounds(150, 150, 50, 50);
		pn.add(play_btn);
		*/
		recorde_btn.setBounds(btn_x, btn_y, 50, 765);
		pn.add(recorde_btn);
	//녹음
		
		
	
	}
	
	void change(int num, int ch_num){
		int pic;
		
		if(ch_num == 1){
			pic = ((n*6)+8);
			if(num>=7){
				pic++;
			}
	    	ImageIcon image2 = new ImageIcon("JOPIC/JennyOPIc_Mock_Format_Sample.0"+pic+".jpeg");
	    	img1 = image2.getImage();
	    	System.out.println("바뀜 이거이거");
	    	repaint();
	    	pn.updateUI();
	    	pn.repaint();
	    	
		}
		if(ch_num == 2){
			pic = ((n*6)+9);
			if(num>=7){
				pic++;
			}
			ImageIcon image2 = new ImageIcon("JOPIC/JennyOPIc_Mock_Format_Sample.0"+pic+".jpeg");
	    	img1 = image2.getImage();
	    	System.out.println("바뀜");
	    	repaint();
	    	pn.updateUI();
	    	pn.repaint();
	    	
		}
		if(ch_num == 3){
			pic = ((n*6)+10);
			if(num>=7){
				pic++;
			}
			ImageIcon image2 = new ImageIcon("JOPIC/JennyOPIc_Mock_Format_Sample.0"+pic+".jpeg");
	    	img1 = image2.getImage();
	    	System.out.println("바뀜");
	    	repaint();
	    	pn.updateUI();
	    	pn.repaint();
	    	
		}

	
	}
	
	
	class MyPanel extends JPanel {

		 
	    int x, y;
	    
	    public MyPanel(int num, int screan_x, int screan_y){
	    	x = screan_x;
	    	y = screan_y;
	    	int plus = (int)((num/7));
	    	if(plus == 2){
	    		plus--;
	    	}
	    	image1 = new ImageIcon("JOPIC/JennyOPIc_Mock_Format_Sample.0"+(((num*6)+7)+plus)+".jpeg");
	    	img1 = image1.getImage();

	    }
	    
	    public void paintComponent(Graphics g){//그림이나 도형을 넣을때 기본적으로 사용되는 페인트컴포넌트
	       super.paintComponent(g);
	       
	       g.drawImage(img1, x/2-360, y/2-225, 720, 450, this);//(이미지, 위치x, 위치y, 크기x, 크기y, this)
	     
	    }
	 }
	
	class Change_thread extends Thread{
		Change_thread(){
			
		}
		
		public void run(){
			change(1, 1);
			System.out.println("스레드 작동");
		}
		
	}	

}



