public final class BoloVegano extends BoloBase
{
    public BoloVegano(String tamanho) { super(tamanho); }
    
    public void preparar()  { System.out.println("Colocando leite vegano."); }
    public void assar() { System.out.println("Assando bolo vegano tamanho " + getTamanho()); }
    public void embalar()   { System.out.println("Embalando bolo vegano."); }
}