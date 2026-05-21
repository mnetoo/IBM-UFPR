public abstract class CartaoWeb implements Cartao
{
    protected String destinatario;

    public CartaoWeb(String destinatario)   {   setDestinatario(destinatario);  }

    public String getDestinatario() { return this.destinatario; }
    public void setDestinatario(String destinatario)
    {   
        if(destinatario != null)    
            this.destinatario = destinatario;
    }
}