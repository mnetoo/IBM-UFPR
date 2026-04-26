public class LampadaFluorescente extends Lampada
{
    // Atributos
    private double comprimento;

    // Construtor
    public LampadaFluorescente(boolean estado, double comprimento)
    {
        super(estado);
        setComprimento(comprimento);
    }
    
    public LampadaFluorescente(boolean estado)  { this(estado, 0.0); }
    public LampadaFluorescente(double comprimento)  { this(false, comprimento); }
    
    // Getters
    public double getComprimento() { return this.comprimento; }
    
    // Setters
    public void setComprimento(double comprimento) { if(comprimento > 0.0) this.comprimento = comprimento; }
}
