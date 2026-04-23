public final class Musculacao extends Fitness
{
    private double peso;

    //  Construtor Completo
    public Musculacao(String nome, String objetivo, String regras, double peso)
    {
        super(nome, objetivo, regras);
        setPeso(peso);
    }

    //  Sobrecarga
    public Musculacao(String nome, String objetivo, String regras)
    {
        this(nome, objetivo, regras, 0.0);
    }

    //  Getters e Setters
    public double getPeso() { return this.peso; }
    public void setPeso(double peso)    { if(peso > 0.0) this.peso = peso; }
}