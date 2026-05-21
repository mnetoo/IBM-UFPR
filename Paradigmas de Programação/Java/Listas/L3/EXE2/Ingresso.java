public class Ingresso
{
    // Atributos
    protected double valor;
    
    // Construtor
    public Ingresso(double valor) { setValor(valor); }
    
    // Getters e Setters
    public double getValor() { return this.valor; }
    public void setValor(double valor) { if(valor > 0.0) this.valor = valor; }
    
    // Métodos
    public void imprimir() { System.out.println("Valor do Ingresso: R$" + getValor()); }
}