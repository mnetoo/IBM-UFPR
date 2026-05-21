public final class Spinning extends Fitness
{
    private double carga;

    //  Construtor Completo
    public Spinning(String nome, String objetivo, String regras, double carga)
    {
        super(nome, objetivo, regras);
        setCarga(carga);
    }

    //  Sobrecarga
    public Spinning(String nome, String objetivo, String regras)
    {
        this(nome, objetivo, regras, 0.0);
    }

    //  Getters e Setters
    public double getCarga()    { return this.carga; }
    public void setCarga(double carga)  { if(carga > 0.0) this.carga = carga; }
}