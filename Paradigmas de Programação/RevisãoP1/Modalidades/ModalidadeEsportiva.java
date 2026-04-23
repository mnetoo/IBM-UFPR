public abstract class ModalidadeEsportiva
{
    protected String nome;
    protected String objetivo;
    protected String regras;

    // Construtor Completo
    public ModalidadeEsportiva(String nome, String objetivo, String regras)
    {   
        setNome(nome);
        setObjetivo(objetivo);
        setRegras(regras);
    }

    // Sobrecarga
    public ModalidadeEsportiva(String nome, String objetivo)
    {
        this(nome, objetivo, "");
    }

    // Getters
    public String getNome() { return nome; }
    public String getObjetivo() { return objetivo; }
    public String getRegras() { return regras; }

    // Setters
    public void setNome(String nome) 
    {
        if (nome != null) 
            this.nome = nome;
    }

    public void setObjetivo(String objetivo) 
    {
        if (objetivo != null) 
            this.objetivo = objetivo;
    }

    public void setRegras(String regras) 
    {
        if (regras != null) 
            this.regras = regras;
    }

    // Método comum
    @Override
    public String toString()
    {   
        return String.format(
            "Modalidade: %s - Objetivo: %s - Regras: %s",
            getNome(), getObjetivo(), getRegras()
        );
    }
}