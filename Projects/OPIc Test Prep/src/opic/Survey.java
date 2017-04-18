package opic;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.Label;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextField;


class Survey extends JFrame{
	JPanel starting;
	JPanel sur;
    JButton Snext_btn;
	JScrollPane scroll;
	JPanel jp_label;
	JPanel scrollBACK;
	
	Survey(int x, int y, JPanel m_P, CardLayout cardLayoutSet, JFrame jf){

		scrollBACK = new BACKPanel(x, y);
		JPanel passW = new MyPanel(11, x, y, cardLayoutSet, m_P, jf);
		JPanel starting1 = new MyPanel(1, x, y, cardLayoutSet, m_P, jf);
		//JPanel starting2 = new JPanel();
		JPanel starting2 = new MyPanel(2, x, y, cardLayoutSet, m_P, jf);
		//JPanel starting3 = new MyPanel(3, x, y, cardLayoutSet, m_P, jf);
		JPanel starting3 = new JPanel();
		JPanel starting4 = new MyPanel(4, x, y, cardLayoutSet, m_P, jf);
		JPanel starting5 = new MyPanel(5, x, y, cardLayoutSet, m_P, jf);
		JPanel mid = new MyPanel(49, x, y, cardLayoutSet, m_P, jf);
		JPanel end = new MyPanel(97, x, y, cardLayoutSet, m_P, jf);

		jp_label = new MySPanel(x, y, cardLayoutSet, m_P, jf);


		jp_label.setLayout(new GridBagLayout());  
		jp_label.setBackground(Color.WHITE);

		Dimension size = new Dimension();//����� �����ϱ� ���� ��ü ����
		size.setSize(500, 1940);//��ü�� ����� ����
		jp_label.setPreferredSize(size);
 

		scroll = new JScrollPane(jp_label);  // ��ũ���г��� ����
		scroll.setBounds(x/2-315, y/2-155, 630, 350);    // �����ӿ� ��ũ���г��� ��ġ�� ���Ѵ�
		//scrollBACK.add(scroll);
		//scrollBACK.setVisible(false);
		
		//m_P.add(scroll, "s3");
	
		scroll.getVerticalScrollBar().setUnitIncrement(16);
		//
/*		JScrollPane jScrollPane = new JScrollPane();//��ũ���� ����
		JPanel panel_ex = new MySPanel(x, y);//��ũ���ҿ� ���� �г� ����
		Dimension size = new Dimension();//����� �����ϱ� ���� ��ü ����
		size.setSize(704, 2942);//��ü�� ����� ����
		panel_ex.setPreferredSize(size);//������ ������ ������ �ִ� ��ü�� �̿��� �г��� ������ ����
		jScrollPane.setViewportView(panel_ex);//��ũ�� �� ���� �г��� �ø���.
		//starting2.add(jScrollPane);
		//starting2.setBackground(new Color(201, 205, 208));
		jScrollPane.setBackground(new Color(201, 205, 208));
		jScrollPane.getVerticalScrollBar().setUnitIncrement(16); */
//
		Snext_btn.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent arg0) {

				cardLayoutSet.show(m_P, "0");
				
			}
			
			
		});
//
		m_P.add(starting1, "s1");
		m_P.add(starting2, "s2");
		//m_P.add(jScrollPane, "s3");
		//m_P.add(starting2, "s2");
		m_P.add(starting4, "s4");
		m_P.add(starting5, "s5");
		m_P.add(mid, "mid");
		m_P.add(end, "15");
		m_P.add(passW, "passW");



	}
	class MyPanel extends JPanel {

		ImageIcon image1 = new ImageIcon();
		Image img1;
	    int x, y;
	    JButton next_btn;
	    
	    public MyPanel(int num, int screan_x, int screan_y, CardLayout cardLayoutSet, JPanel m_P, JFrame jf){
	/*    	int x2 = (int) (screan_x*0.5)+180;
	    	int y2 = (int) (screan_y*0.5)+50;*/
	    	int x2 = (int) (screan_x*0.5)+180;
	    	int y2 = (int) (screan_y*0.5)+120;
	    	x = screan_x;
	    	y = screan_y;
	    	image1 = new ImageIcon("JOPIC/JennyOPIc_Mock_Format_Sample.00"+num+".jpeg");
	    	img1 = image1.getImage();
			setBackground(new Color(201, 205, 208));
			setLayout(null);
			if(num == 11){
				next_btn = new JButton("pass");
				next_btn.setBounds(x2, y2-68, 150, 50);
				JTextField na = new JTextField();
				
				add(na);
				/*next_btn.setBorderPainted(false);
				next_btn.setFocusPainted(false);
				next_btn.setContentAreaFilled(false);
				next_btn.setForeground(Color.BLACK);*/
			}
			if(num == 1){
				next_btn = new JButton("");
				next_btn.setBounds(x2, y2-68, 150, 50);
				next_btn.setBorderPainted(false);
				next_btn.setFocusPainted(false);
				next_btn.setContentAreaFilled(false);
				next_btn.setForeground(Color.BLACK);
			}
			else if(num == 49){
				next_btn = new JButton("");
				next_btn.setBounds(x2-60, y2-125, 110, 100);
				next_btn.setBorderPainted(false);
				next_btn.setFocusPainted(false);
				next_btn.setContentAreaFilled(false);
				next_btn.setForeground(Color.BLACK);

			}
			else if(num == 97){
				
				next_btn = new JButton("");
				next_btn.setBounds(x2/2+250, y2-38, 150, 50);
				next_btn.setBorderPainted(false);
				next_btn.setFocusPainted(false);
				next_btn.setContentAreaFilled(false);
				next_btn.setForeground(Color.BLACK);

			}
			else{
				next_btn = new JButton(new ImageIcon("JOPIC/next.jpg"));
				next_btn.setBorderPainted(false);
				next_btn.setFocusPainted(false);
				next_btn.setContentAreaFilled(false);
				next_btn.setForeground(Color.BLACK);
				next_btn.setBounds(x2-20, y2, 150, 50);
			}
			add(next_btn);
			
			next_btn.addActionListener(new ActionListener(){

				@Override
				public void actionPerformed(ActionEvent arg0) {

					cardLayoutSet.show(m_P, "s"+(num+1));
					if(num == 2){
						jf.setLayout(null);
						jf.add(scroll);
						jf.add(new Label(""));
						
						
						JLabel limg = new JLabel(new ImageIcon("JOPIC/srcoll.jpg"));
						JLabel limg2 = new JLabel("");
						limg2.setBounds(0, 10, 720, 450);
						//jf.add(limg2);
						//limg.setBounds(0, 10, 720, 450);
						limg.setBounds(x/2-360, y/2-225, 720, 450);
						jf.add(limg);
						
						
						
						Label al = new Label("");
						al.setBackground(new Color(201, 205, 208));
						al.setBounds(0, 0, 10000, 10000);
						jf.add(al);
						//jf.setBackground(Color.black);
						
						
						//jf.setBackground(Color.BLACK);
						m_P.setVisible(false);
						scroll.updateUI();
						jf.repaint();
					}
					if(num == 3){
						jf.setLayout(new BorderLayout());
						cardLayoutSet.show(m_P, "0");
		
					}
					else if(num == 49){
						cardLayoutSet.show(m_P, "7");

					}
					else if(num == 97){
						System.exit(0);
					}

				}
				
				
			});
	    	
	    	
	    }
	    
	    public void paintComponent(Graphics g){//�׸��̳� ������ ������ �⺻������ ���Ǵ� ����Ʈ������Ʈ
	       super.paintComponent(g);
	       
	       g.drawImage(img1, x/2-360, y/2-225, 720, 450, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)
	     
	    }
	 }
	class MySPanel extends JPanel {
		//JButton Snext_btn;
		ImageIcon image1 = new ImageIcon();
		Image img1;
	    int x, y;
	    public MySPanel(int x2, int y2, CardLayout cardLayoutSet, JPanel m_P, JFrame jf){
	    	x = x2;
	    	y = y2;

	        Snext_btn = new JButton(new ImageIcon("JOPIC/next.jpg"));
		    add(Snext_btn);

			Snext_btn.setBorderPainted(false);
			Snext_btn.setFocusPainted(false);
			Snext_btn.setContentAreaFilled(false);
			Snext_btn.setForeground(Color.BLACK);
			Snext_btn.addActionListener(new ActionListener(){

				@Override
				public void actionPerformed(ActionEvent arg0) {

				
					jf.setLayout(new BorderLayout());
					scroll.setVisible(false);
					m_P.setVisible(true);
					cardLayoutSet.show(m_P, "0");

					
				}
				
				
			});

	    }
	    
	    public void paintComponent(Graphics g){//�׸��̳� ������ ������ �⺻������ ���Ǵ� ����Ʈ������Ʈ
	       super.paintComponent(g);
	       g.drawImage(img1, 0, 0, 571, 1935, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)

	      // Snext_btn.setBounds(x/2+200, 2622, 150, 50);
	          Snext_btn.setBounds(480, 1865, 150, 50);

	    	image1 = new ImageIcon("JOPIC/survey.jpg");
	    	img1 = image1.getImage();
	          
	    }
	 }

	class BACKPanel extends JPanel {
		//JButton Snext_btn;
		ImageIcon image1 = new ImageIcon();
		Image img1;
	    int x, y;
	    public BACKPanel(int x2, int y2){
	    	x = x2;
	    	y = y2;
	    	image1 = new ImageIcon("JOPIC/scroll.jpg");
	    	img1 = image1.getImage();

	    }
	    
	    public void paintComponent(Graphics g){//�׸��̳� ������ ������ �⺻������ ���Ǵ� ����Ʈ������Ʈ
	       super.paintComponent(g);
	       g.drawImage(img1, x/2-360, y/2-225, 720, 450, this);//(�̹���, ��ġx, ��ġy, ũ��x, ũ��y, this)

	       
	    }
	 }
}

