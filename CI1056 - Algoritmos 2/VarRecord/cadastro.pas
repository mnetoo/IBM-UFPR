program bancodedados;

const maxCliente = 4;

type
		
	cliente = record
		nome: string;
		cpf: int64;
		telefone: int64;
		endereco: string;
		end;

	vetor = array [1..4] of cliente;

var
	cadastro: vetor;
	i: integer;

begin

	for i:= 1 to maxCliente do
	begin
		readln(cadastro[i].nome);
		readln(cadastro[i].cpf);
		readln(cadastro[i].telefone);
		readln(cadastro[i].endereco);
		writeln;
	end;

	for i:= 1 to maxCliente do
	begin
		writeln('Cliente ', i, ': ', cadastro[i].nome, ' / ', 'CPF: ', cadastro[i].cpf, ' / ', 'Telefone: ', cadastro[i].telefone, ' / ', 'Endereco: ', cadastro[i].endereco);
		writeln;
	end;
end.
