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

		JScrollPane jScrollPane = new JScrollPane();//��ũ���� ����
		JPanel panel_ex = new MySPanel();//��ũ���ҿ� ���� �г� ����
		Dimension size = new Dimension();//����� �����ϱ� ���� ��ü ����
		size.setSize(704, 2382);//��ü�� ����� ����
		panel_ex.setPreferredSize(size);//������ ������ ������ �ִ� ��ü�� �̿��� �г��� ������ ����
		jScrollPane.setViewportView(panel_ex);//��ũ�� �� ���� �г��� �ø���.
		
		main.add(jScrollPane, "scroll");
		cardLayoutSet.show(main, "scroll");		
		setSize(1000, 700);
		setVisible(true);
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("�̰� �����");
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
	    
	    public void paintComponent(Graphics g){//�׸��̳� ������ ������ �⺻������ ���Ǵ� ����Ʈ������Ʈ
	       super.paintComponent(g);
	       
	       g.drawImage(img1, 0, 0, 704, 2382, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)
	     
	    }
	 }

}
