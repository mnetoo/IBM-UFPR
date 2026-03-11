public class Time
{
	private int hora;
	private int minuto;

	public Time(int h, int m)
	{
		this.hora = h;
		this.minuto = m;
	}

	public int getHora() { return this.hora; }
	public int getMinuto() { return this.minuto; }
	public void setHora(int h) { if(h >= 0) this.hora = h; }
	public void setMinuto(int m) { if(m >= 0) this.minuto = m; }

	public boolean anterior(int h, int m)
	{
		if(h > this.hora) return true;
		if(this.hora == h && m > this.minuto) return true;
		return false;
	}

	public boolean posterior(int h, int m)
	{
		if(this.hora > h) return true;
		if(this.hora == h && this.minuto > m) return true;
		return false;
	}

	public boolean equals(int h, int m)
	{
		return this.hora == h && this.minuto == m;
	}

	public String toString()
	{
		return this.hora + ":" + this.minuto;
	}
}
