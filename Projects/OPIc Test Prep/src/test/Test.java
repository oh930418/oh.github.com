package test;

import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;

public class Test extends JFrame{
	CardLayout cardLayoutSet = new CardLayout();
	JPanel main = new JPanel();
	Test(){
		main.setLayout(cardLayoutSet);
		add(main);

		JScrollPane jScrollPane = new JScrollPane();//스크롤팬 생성
		JPanel panel_ex = new MySPanel();//스크롤팬에 붙일 패널 생성
		Dimension size = new Dimension();//사이즈를 지정하기 위한 객체 생성
		size.setSize(704, 2382);//객체의 사이즈를 지정
		panel_ex.setPreferredSize(size);//사이즈 정보를 가지고 있는 객체를 이용해 패널의 사이즈 지정
		jScrollPane.setViewportView(panel_ex);//스크롤 팬 위에 패널을 올린다.
		
		main.add(jScrollPane, "scroll");
		cardLayoutSet.show(main, "scroll");		
		setSize(1000, 700);
		setVisible(true);
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("이거 실행됨");
		Test t = new Test();
	}
	class MySPanel extends JPanel {

		ImageIcon image1 = new ImageIcon();
		Image img1;
	    int x, y;
	    JButton next_btn;
	    
	    public MySPanel(){
	
	    	image1 = new ImageIcon("JOPIC/survey.jpg");
	    	img1 = image1.getImage();
	    }
	    
	    public void paintComponent(Graphics g){//그림이나 도형을 넣을때 기본적으로 사용되는 페인트컴포넌트
	       super.paintComponent(g);
	       
	       g.drawImage(img1, 0, 0, 704, 2382, this);//(이미지, 위치x, 위치y, 크기x, 크기y, this)
	     
	    }
	 }

}
