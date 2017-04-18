package opic;

import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.io.FileInputStream;
import java.io.FileNotFoundException;

import javax.swing.JFrame;
import javax.swing.JPanel;

import javazoom.jl.decoder.JavaLayerException;
import javazoom.jl.player.Player;

public class Test_2 extends JFrame{
	int MAX = 15;
	JPanel m_P = new JPanel();
	Test_p Tp[] = new Test_p[MAX];
	//Button btn[] = new Button[10];
	String str;
	CardLayout cardLayoutSet = new CardLayout();
	int x, y;
	//@Override
	protected void processWindowEvent(WindowEvent arg0) {
		// TODO Auto-generated method stub
		super.processWindowEvent(arg0);
	}
	
/*	 public void MatrixTime(int delayTime, AudioPlayer ap, int n){


	       long saveTime = System.currentTimeMillis();
	        long currTime = 0;
			Tp[n].change(n, 1);


	       while( currTime - saveTime < delayTime){
	            currTime = System.currentTimeMillis();
	        }

	 }

	*/
	
	Test_2(){
		m_P.setLayout(cardLayoutSet);

		setLayout(null);
		setLayout(new BorderLayout());
		setTitle("OPIC");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//		setLocationRelativeTo(null);
		setExtendedState(JFrame.MAXIMIZED_BOTH);
		setVisible(true);
		getContentPane().setPreferredSize( Toolkit.getDefaultToolkit().getScreenSize());   //
/*		int x = getWidth();
		int y = getHeight();
		x+=5;
		y+=15;S
		setSize(x, y);*/
		pack();  //
	//	setSize(500, 500);
		setResizable(false);
		setLocation(0, -20);  //
		/*Point p = new Point(0, 0);
		SwingUtilities.convertPoirjntToScreen(p, getContentPane());
		Point l = getLocation();
		l.x -= p.x;
		l.y -= p.y;
		setLocation(l);
		*/
		//show();

		for(int i = 0; i < MAX; i++){
			str = i+"";
			x = this.getWidth();
			y = this.getHeight();
			
			Tp[i] = new Test_p(i, this.getWidth(), this.getHeight());
		
	//		Button btn = new Button(str);

			//btn.setLocation(Tp[i].getWidth()-150, 400);
			//Tp[i].pn.add(btn);
			m_P.add(Tp[i].pn, str);

			Tp[i].recorde_btn.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent arg0) {
					//int n = Integer.parseInt(arg0.getActionCommand());
					System.out.println(arg0.getActionCommand());
					//int n = Integer.parseInt(arg0.getActionCommand().substring(6));
					int n = Integer.parseInt(arg0.getActionCommand());

					Tp[n].change(n, 1);
					//Tp[n].ct.start();
					//Tp[n].ct.setPriority(10);
					
					//update(null);
					//				MatrixTime(5000, ap, n);
				/*	AudioClip a = null;
					
					File file = new File("recode"+ n +".wma");
					try {
						a = Applet.newAudioClip(file.toURL());
					} catch (MalformedURLException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
		!			
					a.play();
				*/	
					/*
					AudioPlayer ap = new AudioPlayer(Tp[n], n);
					ap.play(n);
*/
					
					try {
						Player p = new Player(new FileInputStream("recorde"+ n +".mp3"));
						p.play();
						p.close();
					
					} catch (FileNotFoundException | JavaLayerException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					AudioRecorder_2 ar = new AudioRecorder_2(Tp[n].pn);
					
					if(Tp[n].recorded == false){
						Tp[n].recorded = true;
						ar.recorde(n, Tp[n], cardLayoutSet, m_P, x, y);

					}
					else{

					}

					
				}
			});
			
		
		}

		add(m_P);		
//		cardLayoutSet.show(m_P, "1");
		x = this.getWidth();
		y = this.getHeight();
		
		Survey s = new Survey(x, y, m_P, cardLayoutSet, this);
		//cardLayoutSet.show(m_P, "survey");

		cardLayoutSet.show(m_P, "s1");


		//cardLayoutSet.show(m_P, "passW");
		
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Test_2 t = new Test_2();
	}



}
