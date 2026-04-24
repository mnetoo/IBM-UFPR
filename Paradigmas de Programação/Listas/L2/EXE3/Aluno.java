import java.util.ArrayList;

public class Aluno
{
    // Atributos
    private String nome;
    private int cr;
    
    // Construtores
    public Aluno(String nome, int cr)
    {
        setNome(nome);
        setCr(cr);
    }
    
    public Aluno()  { this("", 0); }
    public Aluno(String nome)  { this(nome, 0); }
    public Aluno(int cr)  { this("", cr); }
    
    // Getters
    public String getNome() { return this.nome; }
    public int getCr() { return this.cr; }

    // Setters
    public void setNome(String nome) { if(nome != null) this.nome = nome; }
    public void setCr(int cr) { if(cr >= 0) this.cr = cr; }
    
    @Override
    public String toString() { return "Nome: " + nome + " CR: " + cr; }
}
