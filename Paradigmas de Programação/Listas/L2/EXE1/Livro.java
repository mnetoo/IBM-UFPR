public class Livro
{
    // Atributos
    private String titulo;
    private int ano;
    private String autor;
    
    // Construtores
    public Livro(String titulo, int ano, String autor)
    {
        setTitulo(titulo);
        setAno(ano);
        setAutor(autor);
    }
    
    public Livro(String titulo, int ano, Autor autor)
    {
        setTitulo(titulo);
        setAno(ano);
        this.autor = autor.getNome();
    }
    
    public Livro(String titulo, int ano)
    {
        setTitulo(titulo);
        setAno(ano);
        this.autor = null;
    }
    
    // Getters
    public String getTitulo() { return this.titulo; }
    public int getAno() { return this.ano; }
    public String getAutor() { return this.autor; }
    
    // Setters
    public void setTitulo(String titulo) { if(titulo != null) this.titulo = titulo; }
    public void setAno(int ano) { if(ano > 0) this.ano = ano; }
    public void setAutor(String autor) { if(autor != null) this.autor = autor; }
    
    // Métodos
    @Override
    public String toString() { return "Título: " + titulo + "\nAno: " + ano + "\nAutor: " + autor; }
}