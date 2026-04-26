public class Livro
{
    // Atributos
    private String titulo;
    private int ano;
    private Autor autor;
    
    // Construtores
    public Livro(String titulo, int ano, Autor autor)
    {
        setTitulo(titulo);
        setAno(ano);
        setAutor(autor);
    }
    
    public Livro(String titulo, int ano)    { this(titulo, ano, null); }
    public Livro(String titulo, Autor autor)    { this(titulo, 0, autor); }
    public Livro(int ano, Autor autor)    { this("", ano, autor); }
    
    // Getters
    public String getTitulo() { return this.titulo; }
    public int getAno() { return this.ano; }
    public Autor getAutor() { return this.autor; }
    
    // Setters
    public void setTitulo(String titulo) { if(titulo != null) this.titulo = titulo; }
    public void setAno(int ano) { if(ano > 0) this.ano = ano; }
    public void setAutor(Autor autor) { if(autor != null) this.autor = autor; }
    
    // Métodos
    @Override
    public String toString() { return "Título: " + titulo + "\nAno: " + ano + "\nAutor: " + autor; }
}
