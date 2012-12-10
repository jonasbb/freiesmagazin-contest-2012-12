package org.bushart.freiesmagazin_contest_2012_12.model;

public class Size {
	private int width;
	private int height;

	public Size (int width, int height) throws IllegalArgumentException {
		if (width > 0 && height > 0) {
			setWidth (width);
			setHeight (height);
		} else {
			throw new IllegalArgumentException ("Arguments has to be greater than 0!");
		}
	}
	
	public boolean isPositionValid (Position p) {
		return (p.getX() <= width && p.getY() <= height);
	}

	public int getHeight () {
		return height;
	}

	public void setHeight (int height) throws IllegalArgumentException {
		if (height > 0) {
			this.height = height;
		} else {
			throw new IllegalArgumentException ("Arguments has to be greater than 0!");
		}
	}

	public int getWidth () {
		return width;
	}

	public void setWidth (int width) throws IllegalArgumentException {
		if (width > 0) {
			this.width = width;
		} else {
			throw new java.lang.IllegalArgumentException ("Arguments has to be greater than 0!");
		}
	}
}
