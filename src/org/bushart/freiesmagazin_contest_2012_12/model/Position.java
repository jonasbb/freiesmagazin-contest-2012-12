package org.bushart.freiesmagazin_contest_2012_12.model;

public class Position {
	
	private int x;
	private int y;
	
	public Position (int x, int y) {
		setX (x);
		setY (y);
	}

	public int getX () {
		return x;
	}

	private void setX (int x) {
		if (x > 0) {
			this.x = x;
		} else {
			throw new java.lang.IllegalArgumentException ("Arguments has to be greater than 0!");
		}
	}

	public int getY () {
		return y;
	}

	private void setY (int y) {
		if (y > 0) {
			this.y = y;
		} else {
			throw new java.lang.IllegalArgumentException ("Arguments has to be greater than 0!");
		}
	}
}