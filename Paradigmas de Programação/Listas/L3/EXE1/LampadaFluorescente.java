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
    
    // Getters
    public double getComprimento() { return this.comprimento; }
    
    // Setters
    public void setComprimento(double comprimento) { if(comprimento > 0.0) this.comprimento = comprimento; }
}