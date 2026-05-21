public class CartaoAniversario extends CartaoWeb
{
    // destinatario

    public CartaoAniversario(String destinatario)   {   super(destinatario);  }

    @Override
    public String retornarMensagem(String remetente)
    {
        return String.format("%s, feliz aniversario!, com amor, %s", destinatario, remetente);
    }
}