package org.bushart.freiesmagazin_contest_2012_12.controller;

import java.util.Scanner;

public class Communicator {
	
	private static Communicator communicator;
	private Scanner sc;
	
	private Communicator () {
		sc = new Scanner(System.in);
		sc.useDelimiter(System.getProperty("line.separator"));
	}
	
	public static Communicator getCommunicator () {
		if (communicator == null)
			communicator = new Communicator();
		return communicator;
	}
	
	public String getGameboard () {
		StringBuilder sb = new StringBuilder();
		
		String s = "";
		while (!(s = getCommand ()).equals("GAMEBOARDEND")) {
			sb.append(s);
			sb.append("\n");
		}
		return sb.toString ();
	}
	
	public String getCommand () {
		while (!sc.hasNext()) {
			try {
				Thread.sleep(5);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return sc.next();
	}
	
	public void send (String s) {
		System.out.printf("%s\n", s);
		System.out.flush();
	}
}