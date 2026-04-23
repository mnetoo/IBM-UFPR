public final class Natacao extends Fitness
{
    private double profundidade;

    //  Construtor Completo
    public Natacao(String nome, String objetivo, String regras, double profundidade)
    {
        super(nome, objetivo, regras);
        setProfundidade(profundidade);
    }

    //  Sobreprofundidade
    public Natacao(String nome, String objetivo, String regras)
    {
        this(nome, objetivo, regras, 0.0);
    }

    //  Getters e Setters
    public double getProfundidade()    { return this.profundidade; }
    public void setProfundidade(double profundidade)  { if(profundidade > 0.0) this.profundidade = profundidade; }
}