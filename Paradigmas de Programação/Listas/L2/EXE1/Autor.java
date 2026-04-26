public class Autor
{
    private String nome;
    private String nacionalidade;
    
    public Autor(String nome, String nacionalidade)
    {
        setNome(nome);
        setNacionalidade(nacionalidade);
    }
    
    public Autor(String nome)   { this(nome, ""); }
    public Autor()  { this(null, null); }
    
    // Getters
    public String getNome() { return this.nome; }
    public String getNacionalidade() { return this.nacionalidade; }
    
    // Setters
    public void setNome(String nome) { if(nome != null) this.nome = nome; }
    public void setNacionalidade(String nacionalidade) { if(nacionalidade != null) this.nacionalidade = nacionalidade; }
    
    // Métodos
    @Override
    public String toString() { return "Autor: " + nome + "\nNacionalidade: " + nacionalidade; }
}
