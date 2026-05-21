public final class BoloChocolate extends BoloBase
{
    public BoloChocolate(String tamanho)    { super(tamanho); }
    
    public void preparar()  { System.out.println("Derretendo chocolate."); }
    public void assar() { System.out.println("Assando bolo de chocolate tamanho " + getTamanho()); }
    public void embalar()   { System.out.println("Embalando bolo de chocolate."); }
}