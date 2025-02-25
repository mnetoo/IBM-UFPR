program cadastrodois;

const maxCliente = 4;

type
		cliente = record
			nome: string;
			cpf: int64;
			telefone: int64;
			endereco: string;
			end;

		vetor = array [1..maxCliente] of cliente;
var
	cadastro: vetor;
	
procedure carregaCadastro (var cadastro: vetor; const maxCliente: integer);
var
	i: integer;
begin
	for i:= 1 to maxCliente do
	begin
		readln(cadastro[i].nome);
		readln(cadastro[i].cpf);
		readln(cadastro[i].telefone);
		readln(cadastro[i].endereco);
	end;
end;

procedure imprimeCadastro (var cadastro: vetor; const  maxCliente: integer);
var
	i: integer;
begin
	for i:= 1 to maxCliente do
	begin
		writeln;
		writeln('Nome: ', cadastro[i].nome, ' / ', 'CPF: ', cadastro[i].cpf, ' ', 'Telefone: ', cadastro[i].telefone, ' ', 'Endereco: ', cadastro[i].endereco);
		writeln;
	end;
end;

begin

	carregaCadastro(cadastro, maxCliente);
	imprimeCadastro(cadastro, maxCliente);
end.
