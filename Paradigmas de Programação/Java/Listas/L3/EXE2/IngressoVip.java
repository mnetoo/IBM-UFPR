public class IngressoVip extends Ingresso
{
    // Atributos
    protected double adicionalVip;
    
    // Construtor
    public IngressoVip(double valor, double adicionalVip)
    {
        super(valor);
        setAdicionalVip(adicionalVip);
    }
    
    // Getters e Setters
    public double getAdicionalVip() { return this.adicionalVip; }
    public void setAdicionalVip(double adicionalVip) { if(adicionalVip > 29.0) this.adicionalVip = adicionalVip; }

    // Métodos 
    public double calcularTotal() { return getValor() + getAdicionalVip(); }

    @Override
    public void imprimir() { System.out.println("Valor Ingresso VIP: R$" + calcularTotal()); }
}