public abstract class Fitness extends ModalidadeEsportiva
{
    //  nome, objetivo
    protected String duracao;

    //  Construtores
    public Fitness(String nome, String objetivo, String regras, String duracao)
    {   
        super(nome, objetivo, regras);
        setDuracao(duracao);
    }

    public Fitness(String nome, String objetivo, String regras)
    {   
        this(nome, objetivo, regras, "");
    }

    //  Getters e Setters
    public String getDuracao()  { return this.duracao; }
    public void setDuracao(String duracao)  { if(duracao != null) this.duracao = duracao; }
}