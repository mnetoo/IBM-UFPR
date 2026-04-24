public class Endereco 
{
    //  Atributos
    private String rua, bairro, cidade, estado;
    private int numero;

    //  Construtor
    public Endereco(String rua, int numero, String bairro, String cidade, String estado)
    {
        setRua(rua);
        setNumero(numero);
        setBairro(bairro);
        setCidade(cidade);
        setEstado(estado);
    }
    
    public Endereco(String rua, int numero, String cidade)  { this(rua, numero, "", cidade, ""); }
    public Endereco(String rua, int numero)  { this(rua, numero, "", "", "UF"); }

    //  Getters
    public String getRua()  { return this.rua; }
    public String getBairro()  { return this.bairro; }
    public String getCidade()  { return this.cidade; }
    public String getEstado()  { return this.estado; }
    public int getNumero()  { return this.numero; }

    //  Setters
    public void setRua(String rua)  { if(rua != null) this.rua = rua; }
    public void setBairro(String bairro)    { if(bairro != null) this.bairro = bairro; }
    public void setCidade(String cidade)    { if(cidade != null) this.cidade = cidade; }
    public void setEstado(String estado)    { if(estado != null) this.estado = estado; }
    public void setNumero(int numero)   { if(numero > 0) this.numero = numero; }

    @Override
    public String toString() { return String.format("%s %d - %s, %s/%s.", rua, numero, bairro, cidade, estado); }
}
