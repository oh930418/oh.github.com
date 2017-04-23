
package opic;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

import javax.sound.sampled.AudioFileFormat;
import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.DataLine;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.TargetDataLine;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.Timer;

import javazoom.jl.decoder.JavaLayerException;
import javazoom.jl.player.Player;



public class AudioRecorder_2
extends Thread
{
	public TargetDataLine		m_line;
	private AudioFileFormat.Type	m_targetType;
	private AudioInputStream	m_audioInputStream;
	private File			m_outputFile;
	JPanel pn;
	AudioRecorder_2	recorder;
	
	
	public AudioRecorder_2(TargetDataLine line,
				     AudioFileFormat.Type targetType,
				     File file)
	{
		m_line = line;
		m_audioInputStream = new AudioInputStream(line);
		m_targetType = targetType;
		m_outputFile = file;
	}

	AudioRecorder_2(JPanel p){
		pn = p;
	}

	/** Starts the recording.
	    To accomplish this, (i) the line is started and (ii) the
	    thread is started.
	*/
	public void start()
	{
		/* Starting the TargetDataLine. It tells the line that
		   we now want to read data from it. If this method
		   isn't called, we won't
		   be able to read data from the line at all.
		*/
		m_line.start();

		/* Starting the thread. This call results in the
		   method 'run()' (see below) being called. There, the
		   data is actually read from the line.
		*/
		super.start();
	}


	/** Stops the recording.

	    Note that stopping the thread explicitely is not necessary. Once
	    no more data can be read from the TargetDataLine, no more data
	    be read from our AudioInputStream. And if there is no more
	    data from the AudioInputStream, the method 'AudioSystem.write()'
	    (called in 'run()' returns. Returning from 'AudioSystem.write()'
	    is followed by returning from 'run()', and thus, the thread
	    is terminated automatically.

	    It's not a good idea to call this method just 'stop()'
	    because stop() is a (deprecated) method of the class 'Thread'.
	    And we don't want to override this method.
	*/
	public void stopRecording()
	{
		m_line.stop();
		m_line.close();
	}




	/** Main working method.
	    You may be surprised that here, just 'AudioSystem.write()' is
	    called. But internally, it works like this: AudioSystem.write()
	    contains a loop that is trying to read from the passed
	    AudioInputStream. Since we have a special AudioInputStream
	    that gets its data from a TargetDataLine, reading from the
	    AudioInputStream leads to reading from the TargetDataLine. The
	    data read this way is then written to the passed File. Before
	    writing of audio data starts, a header is written according
	    to the desired audio file type. Reading continues untill no
	    more data can be read from the AudioInputStream. In our case,
	    this happens if no more data can be read from the TargetDataLine.
	    This, in turn, happens if the TargetDataLine is stopped or closed
	    (which implies stopping). (Also see the comment above.) Then,
	    the file is closed and 'AudioSystem.write()' returns.
	*/
	public void run()
	{
			try
			{
				AudioSystem.write(
					m_audioInputStream,
					m_targetType,
					m_outputFile);
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
	}


	
	void stop_re(){
	/*	try
		{
			System.in.read();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}*/
		recorder.stopRecording();
	}
	File	outputFile;
	AudioFormat	audioFormat;
	DataLine.Info	info;
	TargetDataLine	targetDataLine;
	AudioFileFormat.Type	targetType;
	JButton s_btn = new JButton("");
	JButton replay = new JButton("");
	
	void restart(int num){
		//s_btn.setVisible(true);
		s_btn.setEnabled(true);
		replay.setEnabled(false);
		timer.stop();
		
	}
	
	
	Timer timer = new Timer(5000, new ActionListener(){

//	@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			
			if(replay.isEnabled()){
				replay.setEnabled(false);
				System.out.println("타이머 작동");
				restart(timer_n);
				ppp.change(timer_n, 3);
				return;
			}
			
		}

	});
	int timer_n;
	Test_p ppp;
	void recorde(int num, Test_p p, CardLayout cardLayoutSet, JPanel m_P, int x, int y)
	{
		ppp = p;
		timer_n = num;
		p.change(num, 2);
		Scanner in = new Scanner(System.in);
		timer.start();
		p.recorde_btn.setVisible(false);
		
		int re_x = (int) (x*0.48);
		int re_y = (int) (y*0.59);
		
		replay.setBorderPainted(false);
		replay.setFocusPainted(false);
		replay.setContentAreaFilled(false);
		replay.setForeground(Color.BLACK);
		s_btn.setBorderPainted(false);
		s_btn.setFocusPainted(false);
		s_btn.setContentAreaFilled(false);
		s_btn.setForeground(Color.BLACK);
		
		replay.setBounds(re_x, re_y, 50, 65);

		
		p.pn.add(replay);
		replay.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				s_btn.setEnabled(false);
				p.pn.updateUI();
				p.pn.repaint();
				try {
					Player p = new Player(new FileInputStream("recorde"+ num +".mp3"));
					p.play();
					p.close();
				
				} catch (FileNotFoundException | JavaLayerException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				restart(num);
				p.change(num, 3);
			
			}
			
		});

		
		s_btn.setBounds(re_x+145, re_y-17, 113, 70);
		p.pn.add(s_btn);
		
		String	strFilename = "test_recode"+num+".wma";
		outputFile = new File(strFilename);
		
		audioFormat = new AudioFormat(
			AudioFormat.Encoding.PCM_SIGNED,
			44100.0F, 16, 2, 4, 44100.0F, false);

		info = new DataLine.Info(TargetDataLine.class, audioFormat);
		targetDataLine = null;
		try
		{
			targetDataLine = (TargetDataLine) AudioSystem.getLine(info);
			targetDataLine.open(audioFormat);
		}
		catch (LineUnavailableException e)
		{
			out("unable to get a recording line");
			e.printStackTrace();
			System.exit(1);
		}

		targetType = AudioFileFormat.Type.WAVE;

		recorder = new AudioRecorder_2(
			targetDataLine,
			targetType,
			outputFile);

	
		out("Press ENTER to start the recording.");

		recorder.start();
		out("Recording...");
		
		out("Press ENTER to stop the recording.");
		
		
		s_btn.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				
				System.out.println("녹음 종료중...");
			/*	try
				{
					System.in.read();
				}
				catch (IOException e1)
				{
					e1.printStackTrace();
				}*/
				/* Here, the recording is actually stopped.
				 */
				System.out.println("녹음 종료..!");
				recorder.stopRecording();
				out("Recording stopped.");		
				int next = num + 1;
				if(next == 7){
					cardLayoutSet.show(m_P, "mid");
				}
				else{
					cardLayoutSet.show(m_P, next+"");
				}
				m_P.updateUI();
			}
			
			
		});
		

		
	}



	private static void printUsageAndExit()
	{
		out("SimpleAudioRecorder: usage:");
		out("\tjava SimpleAudioRecorder -h");
		out("\tjava SimpleAudioRecorder <audiofile>");
		System.exit(0);
	}



	private static void out(String strMessage)
	{
		System.out.println(strMessage);
	}
}

/*** SimpleAudioRecorder.java ***/
