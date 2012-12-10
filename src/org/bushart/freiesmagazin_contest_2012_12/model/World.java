package org.bushart.freiesmagazin_contest_2012_12.model;

import java.lang.reflect.Array;

public class World<G> {
	
	private G[][] map;
	private Size size;
	
	@SuppressWarnings("unchecked")
	public World (Size s, Class<G> value) {
		size = s;
		map = (G[][]) Array.newInstance(value, s.getWidth(), s.getHeight());
	}
	
	@SuppressWarnings("unchecked")
	public World (String s) throws IllegalArgumentException {
		String[] statements = s.split(System.getProperty("line.separator"));
		
		// first line form of
		// GAMEBOARDSTART 30,40
		int width = Integer.parseInt (statements[0].split("[ \\,]")[1]);
		int height = Integer.parseInt (statements[0].split("[ \\,]")[2]);
		size = new Size (width, height);
		
		map = (G[][]) Array.newInstance(FieldState.class, size.getWidth(), size.getHeight());
		
		//for each line = height
		//set each field = width
		for (int h = 1; h < statements.length; h++) {
			
			int w = 1;
			for (char c: statements[h].toCharArray()) {
				if (c == '.') {
					setField (new Position (w, h), (G) FieldState.WATER);
				} else if (c == 'o') {
					setField (new Position (w, h), (G) FieldState.FLOODED);
				} else if (c == '#') {
					setField (new Position (w, h), (G) FieldState.DRY);
				} else {
					throw new IllegalArgumentException ("Invalid characters for describing the map!");
				}
				w++;
			}
		}
	}

	public Size getSize() {
		return size;
	}
	
	public G getField (Position p) throws IllegalArgumentException {
		if (size.isPositionValid(p)) {
			return map [p.getX()-1][p.getY()-1];
		} else {
			throw new IllegalArgumentException ("Arguments has to be a valid position in this size!");
		}
	}
	
	public void setField (Position p, G value) throws IllegalArgumentException {
		if (size.isPositionValid(p)) {
			map [p.getX()-1][p.getY()-1] = value;
		} else {
			throw new IllegalArgumentException ("Arguments has to be a valid position in this size!");
		}
	}
}