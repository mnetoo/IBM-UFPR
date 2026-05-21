public abstract class BoloFactory
{
    public abstract Bolo criarBolo(String tipo, String tamanho);
    
    public Bolo encomendarBolo(String tipo, String tamanho)
    {
        Bolo b = this.criarBolo(tipo, tamanho);
        b.preparar();
        b.assar();
        b.embalar();
        
        return b;
    }
}