public abstract class BoloBase implements Bolo
{
    protected String tamanho;
    
    public BoloBase(String tamanho) { setTamanho(tamanho); }
    public String getTamanho()  { return this.tamanho; }
    public void setTamanho(String tamanho)    { if(tamanho != null) this.tamanho = tamanho; }
}