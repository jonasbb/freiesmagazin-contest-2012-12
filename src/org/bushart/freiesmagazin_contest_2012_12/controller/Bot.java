package org.bushart.freiesmagazin_contest_2012_12.controller;

import org.bushart.freiesmagazin_contest_2012_12.model.FieldState;
import org.bushart.freiesmagazin_contest_2012_12.model.Position;
import org.bushart.freiesmagazin_contest_2012_12.model.World;

public class Bot {
	
	private World<FieldState> map;
	
	private Communicator comm;
	
	private int round;
	private Position pos;
	private int flood_level;
	private int commands_left;
	private boolean running;
	
	public Bot () {
		comm = Communicator.getCommunicator ();
		map = new World<FieldState> (comm.getGameboard ());
		
		round = 0;
		flood_level = 0;
		running = true;
		
		pos = new Position(1, 1);
	}

	public void run() {
		String s;
		
		while (running) {
			s = comm.getCommand ();
			int x, y;
			
			//Commands can have multiple parts, split them to get just the commands name
			switch (s.split(" ")[0]) {
			case "ROUND": //ROUND X Y,Z		Round X, Position Y,Z
				int r = Integer.parseInt(s.split("[ \\,]")[1]);
				x = Integer.parseInt(s.split("[ \\,]")[2]);
				y = Integer.parseInt(s.split("[ \\,]")[3]);
				round++;
				
				//special case ROUND 1, no known position yes, so set one
				if (round == 1)
					pos = new Position(x, y);
				
				if (!pos.equals(new Position (x, y)))
					throw new RuntimeException(String.format("Problem with bot position. Game says Position x: %d; y: %d, but expected: %s", x, y, pos.toString()));
				
				if (r != round)
					throw new RuntimeException(String.format("Problem with round number. Game says Round %d, but expected: %d", r, round));
				
				commands_left = 3;
				makeMoves ();
				break;
			case "INCRFLOOD": //INCRFLOOD [0|1]
				if (s.split(" ")[1].equals("1"))
					flood_level++;
				break;
			case "FLOOD": //FLOOD X,Y	X,Y numbers
				x = Integer.parseInt(s.split("[ \\,]")[1]);
				y = Integer.parseInt(s.split("[ \\,]")[2]);
				flood (new Position (x, y));
				break;
			case "END":
				running = false;
				break;
			}
		}
	}
	
	private void flood (Position p) {
		//System.err.print(map.getField(p).toString());
		switch (map.getField(p)) {
		case DRY:
			map.setField(p, FieldState.FLOODED);
			break;
		case FLOODED:
			map.setField(p, FieldState.WATER);
			break;
		default:
			throw new Error ("A water field cannot be flooded again. Error in submission at " + p.toString ());
		}
	}
	
	private void makeMoves () {
		//TODO etwas Sinnvolles :)
		//aktuell versucht der Bot nur seine Umgebung trocken zu legen
		
		//viel bewegen nur in den ersten Runden
		//danach möglichst viel trockenlegen
		while (commands_left > 0) {
			try {
				if (map.getField(pos) == FieldState.FLOODED) {
					//Current
					comm.send ("DRY CURRENT");
					map.setField(pos, FieldState.DRY);
					commands_left--;
					continue;
				}
			} catch (Exception e) {}
			

			try {
				if (map.getField(new Position (pos.getX(), pos.getY()-1)) == FieldState.FLOODED) {
					//North
					comm.send ("DRY NORTH");
					map.setField(new Position (pos.getX(), pos.getY()-1), FieldState.DRY);
					commands_left--;
					continue;
				}
			} catch (Exception e) {}
				
			try {
				if (map.getField(new Position (pos.getX()+1, pos.getY())) == FieldState.FLOODED) {
					//EAST
					comm.send ("DRY EAST");
					map.setField(new Position (pos.getX()+1, pos.getY()), FieldState.DRY);
					commands_left--;
					continue;
				}
			} catch (Exception e) {}
				

			try {
				if (map.getField(new Position (pos.getX(), pos.getY()+1)) == FieldState.FLOODED) {
					//SOUTH
					comm.send ("DRY SOUTH");
					map.setField(new Position (pos.getX(), pos.getY()+1), FieldState.DRY);
					commands_left--;
					continue;
				}
			} catch (Exception e) {}
				

			try {
				if (map.getField(new Position (pos.getX()-1, pos.getY())) == FieldState.FLOODED) {
					//WEST
					comm.send ("DRY WEST");
					map.setField(new Position (pos.getX()-1, pos.getY()), FieldState.DRY);
					commands_left--;
					continue;
				}
			} catch (Exception e) {}
			
			comm.send ("GO CURRENT");
			commands_left--;
		}
	}
}