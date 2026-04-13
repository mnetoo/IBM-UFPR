public class CartaoNatal extends CartaoWeb
{
    // destinatario

    public CartaoNatal(String destinatario)   {   super(destinatario);  }

    @Override
    public String retornarMensagem(String remetente)
    {
        return String.format("%s, feliz natal!, com amor, %s", destinatario, remetente);
    }
}