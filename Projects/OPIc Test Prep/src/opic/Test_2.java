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
	

	Test_2(){
		m_P.setLayout(cardLayoutSet);

		setLayout(null);
		setLayout(new BorderLayout());
		setTitle("OPIC");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setExtendedState(JFrame.MAXIMIZED_BOTH);
		setVisible(true);
		getContentPane().setPreferredSize( Toolkit.getDefaultToolkit().getScreenSize());   

		pack();  
		setResizable(false);
		setLocation(0, -20);  //


		for(int i = 0; i < MAX; i++){
			str = i+"";
			x = this.getWidth();
			y = this.getHeight();
			
			Tp[i] = new Test_p(i, this.getWidth(), this.getHeight());
		

			m_P.add(Tp[i].pn, str);

			Tp[i].recorde_btn.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent arg0) {
					System.out.println(arg0.getActionCommand());
					int n = Integer.parseInt(arg0.getActionCommand());

					Tp[n].change(n, 1);
	
					
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
		x = this.getWidth();
		y = this.getHeight();
		
		Survey s = new Survey(x, y, m_P, cardLayoutSet, this);
		cardLayoutSet.show(m_P, "s1");
		
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Test_2 t = new Test_2();
	}



}
