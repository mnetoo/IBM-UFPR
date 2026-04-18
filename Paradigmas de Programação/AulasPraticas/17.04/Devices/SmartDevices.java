public abstract class SmartDevices implements Online
{
    protected boolean estado;
    protected boolean conexao;

    public SmartDevices(boolean estado, boolean conexao)  
    { 
        isEstado(estado);
        isConexao(conexao); 
    }

    public boolean getEstado()  { return this.estado; }
    public boolean getConexao() { return this.conexao; }

    public void isEstado(boolean estado)    { this.estado = estado; }
    public void isConexao(boolean conexao)  { this.conexao = conexao; }
}