public final class BoloFruta extends BoloBase
{
    public BoloFruta(String tamanho)    { super(tamanho); }
    
    public void preparar()  { System.out.println("Cortando fruta."); }
    public void assar() { System.out.println("Assando bolo de fruta tamanho " + getTamanho()); }
    public void embalar()   { System.out.println("Embalando bolo de fruta."); }
}