public class IngressoCamarote extends IngressoVip
{
    // Atributos
    private double adicionalCamarote;
    
    // Construtor
    public IngressoCamarote(double valor, double adicionalVip, double adicionalCamarote)
    {
        super(valor, adicionalVip);
        setAdicionalCamarote(adicionalCamarote);
    }
    
    // Getters e Setters
    public double getAdicionalCamarote() { return this.adicionalCamarote; }
    public void setAdicionalCamarote (double adicionalCamarote) 
    { 
        if(adicionalCamarote > 99.9) 
            this.adicionalCamarote = adicionalCamarote; 
    }
    
    // Métodos
    @Override
    public double calcularTotal() { return super.calcularTotal() + getAdicionalCamarote(); }
    
    @Override
    public void imprimir() { System.out.println("Valor Ingresso CAMAROTE: R$" + calcularTotal()); }
}