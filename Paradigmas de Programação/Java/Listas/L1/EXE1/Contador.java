public class Contador
{
	private int count;

	public int getContador() { return this.count; }
	public void setContador(int qtde) { if(qtde > 0) this.count = qtde; }
	public void incrementarContador(int qtde) { if(qtde > 0) this.count += qtde; }
	public void decrementarContador(int qtde) { if(qtde > 0) this.count -= qtde; }
	public void zerarContador() { this.count = 0; }
}
