package org.bushart.freiesmagazin_contest_2012_12.model;

public class Position {
	
	private int x;
	private int y;
	
	public Position (int x, int y) {
		setX (x);
		setY (y);
	}
	
	public boolean equals (Position p) {
		return x == p.getX () && y == p.getY ();
	}

	public int getX () {
		return x;
	}

	private void setX (int x) throws IllegalArgumentException {
		if (x > 0) {
			this.x = x;
		} else {
			throw new java.lang.IllegalArgumentException ("Arguments has to be greater than 0!");
		}
	}

	public int getY () {
		return y;
	}

	private void setY (int y) throws IllegalArgumentException {
		if (y > 0) {
			this.y = y;
		} else {
			throw new java.lang.IllegalArgumentException ("Arguments has to be greater than 0!");
		}
	}
	
	public String toString () {
		return String.format("Position: x: %d; y: %d", x, y);
	}
}