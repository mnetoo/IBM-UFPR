public class CartaoDiaDosNamorados extends CartaoWeb
{
    // destinatario

    public CartaoDiaDosNamorados(String destinatario)   {   super(destinatario);  }

    @Override
    public String retornarMensagem(String remetente)
    {
        return String.format("%s, feliz dia dos namorados!, com amor, %s", destinatario, remetente);
    }
}